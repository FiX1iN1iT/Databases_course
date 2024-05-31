#include "welcomewindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent)
    : QMainWindow(parent),
    loginWindow(nullptr)
{
    // Create main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create welcome label
    QLabel *welcomeLabel = new QLabel("АС образовательного учреждения\nдистанционного обучения", this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    mainLayout->addWidget(welcomeLabel);

    // Create login button
    loginButton = new QPushButton("Авторизация", this);
    mainLayout->addWidget(loginButton);

    closePushButton = new QPushButton("Выход", this);
    mainLayout->addWidget(closePushButton);

    // Connect buttons to slots
    connect(loginButton, &QPushButton::clicked, this, &WelcomeWindow::openLoginWindow);
    connect(closePushButton, &QPushButton::clicked, this, &WelcomeWindow::didTapClosePushButton);
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

void WelcomeWindow::didTapClosePushButton() {
    close();
}
