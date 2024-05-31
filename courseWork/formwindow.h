#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include "menuwindow.h"
#include "databasehelper.h"
#include "authenticationmanager.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>
#include <QRegularExpression>
#include <QComboBox>

#include <QFile>
#include <QTextStream>

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
    void didTapSearchPushButton();
    void didTapMakeReportPushButton();
    void backToMenu();

private:
    void setup();
    void setupLayouts();
    void setupTitleLabel();
    void setupFormLineEdits();
    void setupTableWidget();
    void setupButtons();
    void setupButtonsForStudent();
    void setupButtonsForLecturer();
    void setupTextEditResult();
    void setupSearchLineEdit();
    void populateComboBox();

    void populateComboBox(QComboBox *comboBox, const QString &relatedTableName);

    bool isNumeric(const QString &str);
    QString questionMarks(int count);
    QString parameters(QStringList values);

    QString tableName;

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QHBoxLayout *contentLayout;
    QHBoxLayout *formLayout;
    QVBoxLayout *buttonsLayout;
    QVBoxLayout *labelsLayout;
    QVBoxLayout *lineEditsLayout;
    QVBoxLayout *menuLayout;
    QHBoxLayout *searchHLayout;
    QVBoxLayout *rightVLayout;

    QLabel *titleLabel;
    QTableWidget *tableWidget;
    QPushButton *loadButton;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *deselectButton;
    QPushButton *makeReportPushButton;

    QPushButton *backButton;
    QTextEdit *textEditResult;

    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;

    QVector<QLabel*> labels;
    QVector<QLineEdit*> lineEdits;
    QVector<QComboBox*> comboBoxes;

    MenuWindow *menuWindow;
};

#endif // FORMWINDOW_H
