#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>

class QComboBox;
class QPushButton;
class WelcomeWindow;

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegistrationWindow(WelcomeWindow *welcomeWindow, QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void backToWelcome();
    void onUserTypeChanged(const QString &userType);
    void performRegistration();

private:
    void clearForm();
    void createCommonFields();
    void createStudentFields();
    void createLecturerFields();
    void createAdminFields();

    WelcomeWindow *welcomeWindow;
    QPushButton *backButton;
    QPushButton *registerButton;

    QComboBox *userTypeComboBox;
};

#endif // REGISTRATIONWINDOW_H
