#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "menuwindow.h"
#include "databasehelper.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>

class MenuWindow;

class FormWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormWindow(const QString &tableName, MenuWindow *menuWindow, QWidget *parent = nullptr);
    ~FormWindow();

private slots:
    void onTableRowClicked(int row);
    void loadTableData();
    void didTapAddButton();
    void didTapEditButton();
    void didTapDeleteButton();
    void didTapDeselectButton();
    void backToMenu();

private:
    void setup();
    void setupLayouts();
    void setupTitleLabel();
    void setupTableWidget();
    void setupButtons();
    void setupTextEditResult();

    QString tableName;

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *formLayout;
    QVBoxLayout *buttonsLayout;
    QVBoxLayout *labelsLayout;
    QVBoxLayout *lineEditsLayout;
    QVBoxLayout *menuLayout;

    QLabel *titleLabel;
    QTableWidget *tableWidget;
    QPushButton *loadButton;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *deselectButton;

    QPushButton *backButton;
    QTextEdit *textEditResult;

    QVector<QLabel*> labels;
    QVector<QLineEdit*> lineEdits;

    MenuWindow *menuWindow;
};

#endif // FORMWINDOW_H
