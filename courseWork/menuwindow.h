#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QPushButton>

class WelcomeWindow;
class FormWindow;

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
