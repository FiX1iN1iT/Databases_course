#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QMainWindow>

class RegistrationWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegistrationWindow(QWidget *parent = nullptr);
    ~RegistrationWindow();

private slots:
    void onUserTypeChanged(const QString &userType);

private:
    void createCommonFields();
    void createStudentFields();
    void createLecturerFields();
    void createAdminFields();
    void clearForm();
};

#endif // REGISTRATIONWINDOW_H
