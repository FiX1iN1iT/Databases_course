#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

class QComboBox;
class QLineEdit;
class QPushButton;
class RegistrationWindow;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void switchToRegistration();

private:
    QComboBox *userTypeComboBox;
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *switchButton;
    RegistrationWindow *registrationWindow;
};

#endif // LOGINWINDOW_H
