#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "formwindow.h"
#include "welcomewindow.h"
#include "authenticationmanager.h"

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

class WelcomeWindow;

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(WelcomeWindow *welcomeWindow, const QString &userType, QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void openFormWindow();
    void backToWelcome();

private:
    void setupUI();

    WelcomeWindow *welcomeWindow;
    QString userType;
    QPushButton *backButton;
};

#endif // MENUWINDOW_H
