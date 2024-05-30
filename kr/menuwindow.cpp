#include "menuwindow.h"
#include "formwindow.h"
#include "welcomewindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>

MenuWindow::MenuWindow(WelcomeWindow *welcomeWindow, const QString &userType, QWidget *parent)
    : QMainWindow(parent), welcomeWindow(welcomeWindow), userType(userType)
{
    // Create main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create menu label
    QLabel *menuLabel = new QLabel(this);
    menuLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(menuLabel);

    // Setup UI based on user type
    if (userType == "student") {
        menuLabel->setText("Student Menu");
        setupUIForStudent();
    } else if (userType == "lecturer") {
        menuLabel->setText("Lecturer Menu");
        setupUIForLecturer();
    } else if (userType == "admin") {
        menuLabel->setText("Admin Menu");
        setupUIForAdmin();
    }

    // Create back button
    backButton = new QPushButton("Back to Welcome", this);
    mainLayout->addWidget(backButton);

    // Connect back button signal to slot
    connect(backButton, &QPushButton::clicked, this, &MenuWindow::backToWelcome);
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::openFormWindow()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString tableName = button->text().toLower();
        FormWindow *formWindow = new FormWindow(tableName, this);
        formWindow->show();
    }
}

void MenuWindow::backToWelcome()
{
    this->hide();
    welcomeWindow->show();
}

void MenuWindow::setupUIForStudent()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    QStringList buttons = {"Discipline", "Lecturer", "Materials", "Chat", "Mark"};
    for (const QString &buttonText : buttons) {
        QPushButton *button = new QPushButton(buttonText, this);
        connect(button, &QPushButton::clicked, this, &MenuWindow::openFormWindow);
        mainLayout->addWidget(button);
    }
}

void MenuWindow::setupUIForLecturer()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    QStringList buttons = {"Discipline", "Student", "Materials", "Chat", "Mark"};
    for (const QString &buttonText : buttons) {
        QPushButton *button = new QPushButton(buttonText, this);
        connect(button, &QPushButton::clicked, this, &MenuWindow::openFormWindow);
        mainLayout->addWidget(button);
    }
}

void MenuWindow::setupUIForAdmin()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    QStringList buttons = {"Discipline", "Lecturer", "Student", "Materials", "Chat", "Mark"};
    for (const QString &buttonText : buttons) {
        QPushButton *button = new QPushButton(buttonText, this);
        connect(button, &QPushButton::clicked, this, &MenuWindow::openFormWindow);
        mainLayout->addWidget(button);
    }
}
