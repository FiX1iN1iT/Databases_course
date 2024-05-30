#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>

class QComboBox;
class QLineEdit;
class QPushButton;
class WelcomeWindow;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(WelcomeWindow *welcomeWindow, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void backToWelcome();
    void performLogin();

private:
    WelcomeWindow *welcomeWindow;
    QComboBox *userTypeComboBox;
    // QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *backButton;
    QPushButton *loginButton;
};

#endif // LOGINWINDOW_H
