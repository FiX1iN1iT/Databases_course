#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>

class QPushButton;
class LoginWindow;
class RegistrationWindow;

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void openLoginWindow();
    void openRegistrationWindow();

private:
    QPushButton *loginButton;
    QPushButton *registrationButton;
    LoginWindow *loginWindow;
    RegistrationWindow *registrationWindow;
};

#endif // WELCOMEWINDOW_H
