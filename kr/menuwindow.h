#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

class WelcomeWindow;
class QPushButton;

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(WelcomeWindow *welcomeWindow, const QString &userType, QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void backToWelcome();

private:
    void setupUIForStudent();
    void setupUIForLecturer();
    void setupUIForAdmin();

    WelcomeWindow *welcomeWindow;
    QString userType;
    QPushButton *backButton;
};

#endif // MENUWINDOW_H
