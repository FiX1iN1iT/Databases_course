#include "formwindow.h"
#include "menuwindow.h"
#include "databasehelper.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

FormWindow::FormWindow(const QString &tableName, MenuWindow *menuWindow, QWidget *parent)
    : QMainWindow(parent), tableName(tableName), menuWindow(menuWindow)
{
    setupUI();
    loadTableData();
}

FormWindow::~FormWindow()
{
}

// void FormWindow::setupUI()
// {
//     centralWidget = new QWidget(this);
//     setCentralWidget(centralWidget);

//     mainLayout = new QVBoxLayout(centralWidget);
//     contentLayout = new QHBoxLayout();
//     menuLayout = new QVBoxLayout();

//     formLayout = new QHBoxLayout();
//     labelsLayout = new QVBoxLayout();
//     lineEditsLayout = new QVBoxLayout();

//     formLayout->addLayout(labelsLayout);
//     formLayout->addLayout(lineEditsLayout);

//     tableWidget = new QTableWidget(this);

//     loadButton = new QPushButton("Load Data", this);
//     connect(loadButton, &QPushButton::clicked, this, &FormWindow::loadTableData);

//     backButton = new QPushButton("Back to Menu", this);
//     connect(backButton, &QPushButton::clicked, this, &FormWindow::backToMenu);

//     menuLayout->addLayout(formLayout);
//     menuLayout->addWidget(loadButton);
//     menuLayout->addWidget(backButton);

//     contentLayout->addLayout(menuLayout);
//     contentLayout->addWidget(tableWidget);

//     mainLayout->addLayout(contentLayout);
// }

void FormWindow::setupUI()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);
    formLayout = new QHBoxLayout();
    labelsLayout = new QVBoxLayout();
    lineEditsLayout = new QVBoxLayout();

    formLayout->addLayout(labelsLayout);
    formLayout->addLayout(lineEditsLayout);

    tableWidget = new QTableWidget(this);

    loadButton = new QPushButton("Load Data", this);
    connect(loadButton, &QPushButton::clicked, this, &FormWindow::loadTableData);

    backButton = new QPushButton("Back to Menu", this);
    connect(backButton, &QPushButton::clicked, this, &FormWindow::backToMenu);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(tableWidget);
    mainLayout->addWidget(loadButton);
    mainLayout->addWidget(backButton);
}

void FormWindow::loadTableData()
{
    qDebug() << "1";
    // Clear previous labels and lineEdits
    qDeleteAll(labels);
    labels.clear();
    qDeleteAll(lineEdits);
    lineEdits.clear();

    // Clear tableWidget
    tableWidget->clear();
    qDebug() << "2";

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

    qDebug() << "3";

    // Set up labels and lineEdits
    for (int i = 0; i < columnCount; ++i) {
        QLabel *label = new QLabel(record.fieldName(i), this);
        QLineEdit *lineEdit = new QLineEdit(this);

        labels.append(label);
        lineEdits.append(lineEdit);

        labelsLayout->addWidget(label);
        lineEditsLayout->addWidget(lineEdit);
    }

    qDebug() << "4";

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
            tableWidget->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
        ++row;
    }
    qDebug() << "5";
}

void FormWindow::backToMenu()
{
    this->hide();
    menuWindow->show();
}
