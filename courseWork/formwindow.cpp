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
    setupSearchLineEdit();

    formLayout->addLayout(labelsLayout);
    formLayout->addLayout(lineEditsLayout);

    buttonsLayout->addWidget(loadButton);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(deselectButton);
    buttonsLayout->addWidget(makeReportPushButton);
    buttonsLayout->addWidget(backButton);

    menuLayout->addWidget(titleLabel);
    menuLayout->addLayout(formLayout);
    menuLayout->addLayout(buttonsLayout);

    searchHLayout->addWidget(searchLineEdit);
    searchHLayout->addWidget(searchPushButton);

    rightVLayout->addLayout(searchHLayout);
    rightVLayout->addWidget(tableWidget);

    contentLayout->addLayout(menuLayout);
    contentLayout->addLayout(rightVLayout);

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

    searchHLayout = new QHBoxLayout();
    rightVLayout = new QVBoxLayout();
}

void FormWindow::setupTitleLabel() {
    titleLabel = new QLabel(tableName.toUpper(), this);
    titleLabel->setAlignment(Qt::AlignCenter);
}

void FormWindow::setupFormLineEdits() {
    lineEdits.at(0)->setReadOnly(true);
    lineEdits.at(0)->setPlaceholderText("Автоматически");

    searchLineEdit->setPlaceholderText("Поиск по полю " + labels.at(1)->text());
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
    loadButton = new QPushButton("Загрузить данные", this);
    connect(loadButton, &QPushButton::clicked, this, &FormWindow::loadTableData);

    addButton = new QPushButton("Добавить", this);
    connect(addButton, &QPushButton::clicked, this, &FormWindow::didTapAddButton);

    editButton = new QPushButton("Изменить", this);
    connect(editButton, &QPushButton::clicked, this, &FormWindow::didTapEditButton);

    deleteButton = new QPushButton("Удалить", this);
    connect(deleteButton, &QPushButton::clicked, this, &FormWindow::didTapDeleteButton);

    deselectButton = new QPushButton("Снять выбор", this);
    connect(deselectButton, &QPushButton::clicked, this, &FormWindow::didTapDeselectButton);

    searchPushButton = new QPushButton("Поиск", this);
    connect(searchPushButton, &QPushButton::clicked, this, &FormWindow::didTapSearchPushButton);

    backButton = new QPushButton("Назад", this);
    connect(backButton, &QPushButton::clicked, this, &FormWindow::backToMenu);

    makeReportPushButton = new QPushButton("Отчет", this);
    connect(makeReportPushButton, &QPushButton::clicked, this, &FormWindow::didTapMakeReportPushButton);

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
    if (tableName != "оценка") {
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

void FormWindow::setupSearchLineEdit() {
    searchLineEdit = new QLineEdit(this);
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

void FormWindow::populateComboBox(QComboBox *comboBox, const QString &relatedTableName) {
    QSqlQuery query1(DatabaseHelper::getDatabaseConnection());
    query1.prepare(QString("SELECT ID, название FROM " + relatedTableName));

    QSqlQuery query2(DatabaseHelper::getDatabaseConnection());
    query2.prepare(QString("SELECT ID, ФИО FROM " + relatedTableName));

    if (query1.exec()) {
        while (query1.next()) {
            QString id = query1.value(0).toString();
            QString title = query1.value(1).toString();
            comboBox->addItem(title, id);
        }
    } else if (query2.exec()) {
        while (query2.next()) {
            QString id = query2.value(0).toString();
            QString fio = query2.value(1).toString();
            comboBox->addItem(fio, id);
        }
    } else {
        QMessageBox::critical(this, "Ошибка", query1.lastError().text());
    }
}


void FormWindow::loadTableData() {
    // Clear previous labels and lineEdits
    qDeleteAll(labels);
    labels.clear();
    qDeleteAll(lineEdits);
    lineEdits.clear();
    qDeleteAll(comboBoxes);
    comboBoxes.clear();

    // Clear tableWidget
    tableWidget->clear();
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(0);

    if (!DatabaseHelper::isDatabaseConnected()) {
        QMessageBox::critical(this, "Ошибка", "База данных не подключена");
        return;
    }

    QSqlQuery query(DatabaseHelper::getDatabaseConnection());
    QString sqlstr = QString("SELECT * FROM %1").arg(tableName);

    query.prepare(sqlstr);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
        return;
    }

    QSqlRecord record = query.record();
    int columnCount = record.count();

    // Set up labels and lineEdits
    for (int i = 0; i < columnCount; ++i) {
        QLabel *label = new QLabel(record.fieldName(i), this);
        labels.append(label);
        labelsLayout->addWidget(label);

        QLineEdit *lineEdit = new QLineEdit(this);
        lineEdits.append(lineEdit);
        lineEditsLayout->addWidget(lineEdit);

        if (record.fieldName(i).startsWith("ID", Qt::CaseInsensitive) && i != 0) {
            QComboBox *comboBox = new QComboBox(this);

            QString foreign = record.fieldName(i).split("_")[1];
            populateComboBox(comboBox, foreign);
            comboBoxes.append(comboBox);

            lineEdit->setText("1");
            lineEdit->hide();
            connect(comboBox, &QComboBox::currentIndexChanged, this, [this, i](const int &index) {
                lineEdits.at(i)->setText(QString::number(index + 1));
            });

            int comboBoxIndex = comboBoxes.size() - 1;

            connect(lineEdit, &QLineEdit::textChanged, this, [this, comboBoxIndex](const QString &text) {
                int index = comboBoxes.at(comboBoxIndex)->findData(text);
                if (index != -1) {
                    comboBoxes.at(comboBoxIndex)->setCurrentIndex(index);
                }
            });

            lineEditsLayout->addWidget(comboBox);
        }
    }

    setupFormLineEdits();

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
    for (int i = 0; i < lineEdits.size(); ++i) {
        QLineEdit* lineEdit = lineEdits.at(i);
        if (lineEdit->text() != "" && i == 0) {
            QMessageBox::critical(this, "ID", "Сбросьте выбор записи.");
            return;
        }
        if (lineEdit->text() == "" && i != 0) {
            QMessageBox::critical(this, "Пустое поле", "Заполните все поля.");
            return;
        }
        if (i != 0) {
            values.append(lineEdit->text());
        }
    }

    QStringList keys;
    for (int i = 1; i < labels.size(); ++i) {
        QLabel* label = labels.at(i);
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
        textEditResult->setText("Запись успешно добавлена.");
    } else {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
    }
}

void FormWindow::didTapEditButton() {
    textEditResult->setText("");

    // Check if a row is selected
    QList<QTableWidgetSelectionRange> selectedRanges = tableWidget->selectedRanges();
    if (selectedRanges.isEmpty()) {
        QMessageBox::critical(this, "Нет выбора", "Выберите ячейку, чтобы изменить запись.");
        return;
    }

    int selectedRow = selectedRanges.first().topRow();

    QStringList values;
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit->text() == "") {
            QMessageBox::critical(this, "Пустое поле", "Заполните все поля.");
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
        textEditResult->setText("Запись успешно обновлена.");
    } else {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
    }
}

void FormWindow::didTapDeleteButton() {
    textEditResult->setText("");

    // Check if a row is selected
    QList<QTableWidgetSelectionRange> selectedRanges = tableWidget->selectedRanges();
    if (selectedRanges.isEmpty()) {
        QMessageBox::critical(this, "Нет выбора", "Выберите ячейку, чтобы изменить запись.");
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
        textEditResult->setText("Запись успешно удалена.");
    } else {
        QMessageBox::critical(this, "Ошибка", query.lastError().text());
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

void FormWindow::didTapSearchPushButton() {
    QString title = searchLineEdit->text();
    // Clear any previous selection
    tableWidget->clearSelection();

    // Loop through the rows of the tableWidget
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        // Assuming the title is stored in the first column (index 0)
        QTableWidgetItem *item = tableWidget->item(row, 1);
        // if (item && item->text().contains(title, Qt::CaseInsensitive)) {
        if (item && item->text() == title) {
            // Select the matching row
            tableWidget->selectRow(row);
            // Optionally, scroll to the selected row
            tableWidget->scrollToItem(item);
            return;
        }
    }

    // If no match is found, you can optionally show a message
    QMessageBox::information(this, "Ошибка", "Нет похожих записей.");
}

void FormWindow::didTapMakeReportPushButton() {
    QString reportText = "Отчет о " + tableName + ":\n\n";

    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 0; col < tableWidget->columnCount(); ++col) {
            reportText += labels.at(col)->text() + ": ";
            reportText += tableWidget->item(row, col)->text();
            reportText += "\n";
        }
        reportText += "\n";
    }

    QString fileName = "/Users/a123/Downloads/report.txt";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << reportText;
        file.close();
        QMessageBox::information(this, "Успех", "Отчет успешно сохранен в файле " + fileName);
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось создать файл для сохранения отчета.");
    }
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
