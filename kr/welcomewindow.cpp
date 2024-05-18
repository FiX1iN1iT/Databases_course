#include "welcomewindow.h"
#include "loginwindow.h"
#include "registrationwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug> // For debugging

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent),
    loginWindow(nullptr),
    registrationWindow(nullptr)
{
    // Create main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create welcome label
    QLabel *welcomeLabel = new QLabel("Welcome to the Application", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(welcomeLabel);

    // Create login button
    loginButton = new QPushButton("Login", this);
    mainLayout->addWidget(loginButton);

    // Create registration button
    registrationButton = new QPushButton("Register", this);
    mainLayout->addWidget(registrationButton);

    // Connect buttons to slots
    connect(loginButton, &QPushButton::clicked, this, &WelcomeWindow::openLoginWindow);
    connect(registrationButton, &QPushButton::clicked, this, &WelcomeWindow::openRegistrationWindow);
}

WelcomeWindow::~WelcomeWindow()
{
    // Clean up allocated windows
    if (loginWindow) delete loginWindow;
    if (registrationWindow) delete registrationWindow;
}

void WelcomeWindow::openLoginWindow()
{
    if (!loginWindow) {
        loginWindow = new LoginWindow(this);
    }
    loginWindow->show();
    this->hide();
}

void WelcomeWindow::openRegistrationWindow()
{
    if (!registrationWindow) {
        registrationWindow = new RegistrationWindow(this);
    }
    registrationWindow->show();
    this->hide();
}
