#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include "loginwindow.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

class LoginWindow;

class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void openLoginWindow();

private:
    QPushButton *loginButton;
    LoginWindow *loginWindow;
};

#endif // WELCOMEWINDOW_H
