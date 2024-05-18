#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>

class QPushButton;
class LoginWindow;

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegistrationWindow(LoginWindow *loginWindow, QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void switchToLogin();
    void onUserTypeChanged(const QString &userType);

private:
    LoginWindow *loginWindow;
    QPushButton *switchButton;
    void createCommonFields();
    void createStudentFields();
    void createLecturerFields();
    void createAdminFields();
    void clearForm();
};

#endif // REGISTRATIONWINDOW_H
