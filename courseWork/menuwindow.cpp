#include "menuwindow.h"

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

    if (userType == "student") {
        menuLabel->setText("Студент");
    } else if (userType == "lecturer") {
        menuLabel->setText("Преподаватель");
    } else if (userType == "admin") {
        menuLabel->setText("Администратор");
    }
    setupUI();

    // Create back button
    backButton = new QPushButton("Назад", this);
    mainLayout->addWidget(backButton);

    // Connect back button signal to slot
    connect(backButton, &QPushButton::clicked, this, &MenuWindow::backToWelcome);
}

MenuWindow::~MenuWindow() {}

void MenuWindow::openFormWindow() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        QString tableName = button->text().toLower();
        FormWindow *formWindow = new FormWindow(tableName, this);
        formWindow->show();
    }
}

void MenuWindow::backToWelcome() {
    this->hide();
    welcomeWindow->show();
}

void MenuWindow::setupUI() {
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    QStringList buttons = AuthenticationManager::getAllowedMenuButtons();
    for (const QString &buttonText : buttons) {
        QPushButton *button = new QPushButton(buttonText, this);
        connect(button, &QPushButton::clicked, this, &MenuWindow::openFormWindow);
        mainLayout->addWidget(button);
    }
}
