#include "formwindow.h"

FormWindow::FormWindow(const QString &tableName, MenuWindow *menuWindow, QWidget *parent)
    : QMainWindow(parent), tableName(tableName), menuWindow(menuWindow) {
    this->resize(800, 600);
    setup();
    loadTableData();
}

FormWindow::~FormWindow() {}

void FormWindow::setup() {
    setupLayouts();
    setupTitleLabel();
    setupTableWidget();
    setupButtons();
    setupTextEditResult();

    formLayout->addLayout(labelsLayout);
    formLayout->addLayout(lineEditsLayout);

    buttonsLayout->addWidget(loadButton);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(deselectButton);
    buttonsLayout->addWidget(backButton);

    menuLayout->addWidget(titleLabel);
    menuLayout->addLayout(formLayout);
    menuLayout->addLayout(buttonsLayout);

    contentLayout->addLayout(menuLayout);
    contentLayout->addWidget(tableWidget);

    mainLayout->addLayout(contentLayout);
    mainLayout->addWidget(textEditResult);
}

void FormWindow::setupLayouts() {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    contentLayout = new QHBoxLayout();
    menuLayout = new QVBoxLayout();

    buttonsLayout = new QVBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignBottom);

    formLayout = new QHBoxLayout();
    labelsLayout = new QVBoxLayout();
    lineEditsLayout = new QVBoxLayout();
}

void FormWindow::setupTitleLabel() {
    titleLabel = new QLabel(tableName.toUpper(), this);
    titleLabel->setAlignment(Qt::AlignCenter);
}

void FormWindow::setupTableWidget() {
    tableWidget = new QTableWidget(this);
    tableWidget->setMinimumSize(500, 500);
    tableWidget->setAutoScroll(true);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(tableWidget, &QTableWidget::cellClicked, this, &FormWindow::onTableRowClicked);
}

void FormWindow::setupButtons() {
    loadButton = new QPushButton("Load Data", this);
    connect(loadButton, &QPushButton::clicked, this, &FormWindow::loadTableData);

    addButton = new QPushButton("Add", this);
    connect(addButton, &QPushButton::clicked, this, &FormWindow::didTapAddButton);

    editButton = new QPushButton("Edit", this);
    connect(editButton, &QPushButton::clicked, this, &FormWindow::didTapEditButton);

    deleteButton = new QPushButton("Delete", this);
    connect(deleteButton, &QPushButton::clicked, this, &FormWindow::didTapDeleteButton);

    deselectButton = new QPushButton("Deselect", this);
    connect(deselectButton, &QPushButton::clicked, this, &FormWindow::didTapDeselectButton);

    backButton = new QPushButton("Back to Menu", this);
    connect(backButton, &QPushButton::clicked, this, &FormWindow::backToMenu);

    if (AuthenticationManager::currentUserLogin == "student") {
        setupButtonsForStudent();
    } else if (AuthenticationManager::currentUserLogin == "lecturer") {
        setupButtonsForLecturer();
    }
}

void FormWindow::setupButtonsForStudent() {
    addButton->hide();
    editButton->hide();
    deleteButton->hide();
}

void FormWindow::setupButtonsForLecturer() {
    if (tableName != "mark") {
        addButton->hide();
        editButton->hide();
        deleteButton->hide();
    }
}

void FormWindow::setupTextEditResult() {
    textEditResult = new QTextEdit(this);
    textEditResult->setMaximumHeight(50);
    textEditResult->setReadOnly(true);
}

void FormWindow::onTableRowClicked(int row) {
    // Check if the row index is valid
    if (row < 0 || row >= tableWidget->rowCount())
        return;

    // Populate line edits with data from the selected row
    for (int col = 0; col < tableWidget->columnCount(); ++col) {
        QString data = tableWidget->item(row, col)->text();
        lineEdits.at(col)->setText(data);
    }
}

void FormWindow::loadTableData() {
    // Clear previous labels and lineEdits
    qDeleteAll(labels);
    labels.clear();
    qDeleteAll(lineEdits);
    lineEdits.clear();

    // Clear tableWidget
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(0);

    if (!DatabaseHelper::isDatabaseConnected()) {
        QMessageBox::critical(this, "Error", "Database not connected");
        return;
    }

    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    QString sqlstr = QString("SELECT * FROM %1").arg(tableName);

    query.prepare(sqlstr);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", query.lastError().text());
        return;
    }

    QSqlRecord record = query.record();
    int columnCount = record.count();

    // Set up labels and lineEdits
    for (int i = 0; i < columnCount; ++i) {
        QLabel *label = new QLabel(record.fieldName(i), this);
        QLineEdit *lineEdit = new QLineEdit(this);

        labels.append(label);
        lineEdits.append(lineEdit);

        labelsLayout->addWidget(label);
        lineEditsLayout->addWidget(lineEdit);
    }

    // Set up table headers
    tableWidget->setColumnCount(columnCount);
    QStringList headers;
    for (int i = 0; i < columnCount; ++i) {
        headers << record.fieldName(i);
    }
    tableWidget->setHorizontalHeaderLabels(headers);

    // Populate table rows
    int row = 0;
    tableWidget->setRowCount(query.size());
    while (query.next()) {
        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(query.value(col).toString());
            tableWidget->setItem(row, col, item);
        }
        ++row;
    }
}

void FormWindow::didTapAddButton() {
    textEditResult->setText("");

    QStringList values;
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text() == "") {
            QMessageBox::critical(this, "Empty field", "Fill in all the fields.");
            return;
        }
        values.append(lineEdit->text());
    }

    QStringList keys;
    for (QLabel* label : labels) {
        keys.append(label->text());
    }

    QString sqlstr = QString("INSERT INTO " + tableName + "(" + parameters(keys) + ")" + " VALUES (" + questionMarks(keys.size()) + ")");

    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    query.prepare(sqlstr);

    for (int i = 0; i < values.size(); ++i) {
        query.bindValue(i, values.at(i));
    }

    if (query.exec()) {
        loadTableData();
        textEditResult->setText("Data added successfully.");
    } else {
        QMessageBox::critical(this, "Error", query.lastError().text());
    }
}

void FormWindow::didTapEditButton() {
    textEditResult->setText("");

    // Check if a row is selected
    QList<QTableWidgetSelectionRange> selectedRanges = tableWidget->selectedRanges();
    if (selectedRanges.isEmpty()) {
        QMessageBox::critical(this, "No Selection", "No row selected. Please select a row to edit.");
        return;
    }

    int selectedRow = selectedRanges.first().topRow();

    QStringList values;
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text() == "") {
            QMessageBox::critical(this, "Empty field", "Fill in all the fields.");
            return;
        }
        values.append(lineEdit->text());
    }

    QStringList keys;
    for (QLabel* label : labels) {
        keys.append(label->text());
    }

    QStringList setStatements;
    for (int i = 0; i < keys.size(); ++i) {
        setStatements.append(keys.at(i) + " = ?");
    }

    QString primaryKey = keys.at(0); // Assuming the first column is the primary key
    QString primaryKeyValue = tableWidget->item(selectedRow, 0)->text();

    QString sqlstr = QString("UPDATE " + tableName + " SET " + setStatements.join(", ") + " WHERE " + primaryKey + " = ?");

    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    query.prepare(sqlstr);

    for (int i = 0; i < values.size(); ++i) {
        query.bindValue(i, values.at(i));
    }
    query.bindValue(values.size(), primaryKeyValue);

    if (query.exec()) {
        loadTableData();
        textEditResult->setText("Data updated successfully.");
    } else {
        QMessageBox::critical(this, "Error", query.lastError().text());
    }
}

void FormWindow::didTapDeleteButton() {
    textEditResult->setText("");

    // Check if a row is selected
    QList<QTableWidgetSelectionRange> selectedRanges = tableWidget->selectedRanges();
    if (selectedRanges.isEmpty()) {
        QMessageBox::critical(this, "No Selection", "No row selected. Please select a row to delete.");
        return;
    }

    int selectedRow = selectedRanges.first().topRow();

    QString primaryKey = labels.at(0)->text(); // Assuming the first column is the primary key
    QString primaryKeyValue = tableWidget->item(selectedRow, 0)->text();

    QString sqlstr = QString("DELETE FROM " + tableName + " WHERE " + primaryKey + " = ?");

    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    query.prepare(sqlstr);
    query.bindValue(0, primaryKeyValue);

    if (query.exec()) {
        loadTableData();
        textEditResult->setText("Row deleted successfully.");
    } else {
        QMessageBox::critical(this, "Error", query.lastError().text());
    }
}

void FormWindow::didTapDeselectButton() {
    for (QLineEdit* lineEdit : lineEdits) {
        lineEdit->clear();
    }

    tableWidget->clearSelection();
}

void FormWindow::backToMenu() {
    this->hide();
    menuWindow->show();
}

bool FormWindow::isNumeric(const QString &str) {
    QRegularExpression numeric("^-?\\d*\\.?\\d+$");
    return numeric.match(str).hasMatch();
}

QString FormWindow::questionMarks(int count) {
    QStringList res;
    for (int i = 0; i < count; ++i) {
        res.append("?");
    }
    return res.join(", ");
}

QString FormWindow::parameters(QStringList values) {
    QStringList res;
    for (int i = 0; i < values.size(); ++i) {
        res.append(values[i]);
    }
    return res.join(", ");
}
