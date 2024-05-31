#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "welcomewindow.h"
#include "menuwindow.h"
#include "databasehelper.h"
#include "authenticationmanager.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

#include <QSqlDatabase>
#include <QSqlError>
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
    QLineEdit *passwordLineEdit;
    QPushButton *backButton;
    QPushButton *loginButton;
};

#endif // LOGINWINDOW_H
