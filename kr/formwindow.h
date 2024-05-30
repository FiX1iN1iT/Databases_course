#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QSqlDatabase>

class MenuWindow;

class FormWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FormWindow(const QString &tableName, MenuWindow *menuWindow, QWidget *parent = nullptr);
    ~FormWindow();

private slots:
    void loadTableData();
    void backToMenu();

private:
    void setupUI();

    QString tableName;

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    // QHBoxLayout *contentLayout;
    QHBoxLayout *formLayout;
    QVBoxLayout *labelsLayout;
    QVBoxLayout *lineEditsLayout;
    // QVBoxLayout *menuLayout;
    QTableWidget *tableWidget;
    QPushButton *loadButton;
    QPushButton *backButton;

    QVector<QLabel*> labels;
    QVector<QLineEdit*> lineEdits;

    MenuWindow *menuWindow;
};

#endif // FORMWINDOW_H
