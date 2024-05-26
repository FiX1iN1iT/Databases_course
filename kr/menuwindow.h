#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(const QString &userType, QWidget *parent = nullptr);
    ~MenuWindow();

private:
    void setupUIForStudent();
    void setupUIForLecturer();
    void setupUIForAdmin();

    QString userType;
};

#endif // MENUWINDOW_H
