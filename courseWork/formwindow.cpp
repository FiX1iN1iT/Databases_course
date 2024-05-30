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
    setupTableWidget();
    setupButtons();
    setupTextEditResult();

    formLayout->addLayout(labelsLayout);
    formLayout->addLayout(lineEditsLayout);

    menuLayout->addLayout(formLayout);
    menuLayout->addWidget(loadButton);
    menuLayout->addWidget(backButton);

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

    formLayout = new QHBoxLayout();
    labelsLayout = new QVBoxLayout();
    lineEditsLayout = new QVBoxLayout();
}

void FormWindow::setupTableWidget() {
    tableWidget = new QTableWidget(this);
    tableWidget->setMinimumSize(500, 500);
    tableWidget->setAutoScroll(true);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSortingEnabled(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void FormWindow::setupButtons() {
    loadButton = new QPushButton("Load Data", this);
    connect(loadButton, &QPushButton::clicked, this, &FormWindow::loadTableData);

    backButton = new QPushButton("Back to Menu", this);
    connect(backButton, &QPushButton::clicked, this, &FormWindow::backToMenu);
}

void FormWindow::setupTextEditResult() {
    textEditResult = new QTextEdit(this);
    textEditResult->setMaximumHeight(50);
    textEditResult->setReadOnly(true);
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

void FormWindow::backToMenu() {
    this->hide();
    menuWindow->show();
}
