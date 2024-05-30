#include "welcomewindow.h"
#include "loginwindow.h"
#include "registrationwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug> // For debugging

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent),
    loginWindow(nullptr)
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

    // Connect buttons to slots
    connect(loginButton, &QPushButton::clicked, this, &WelcomeWindow::openLoginWindow);
}

WelcomeWindow::~WelcomeWindow() {
    if (loginWindow) {
        delete loginWindow;
    }
}

void WelcomeWindow::openLoginWindow() {
    if (!loginWindow) {
        loginWindow = new LoginWindow(this);
    }
    loginWindow->show();
    this->hide();
}
