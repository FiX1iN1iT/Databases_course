#include "loginwindow.h"
#include "registrationwindow.h"

#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent),
    registrationWindow(nullptr)
{
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create user type combo box
    userTypeComboBox = new QComboBox(this);
    userTypeComboBox->addItem("Student");
    userTypeComboBox->addItem("Lecturer");
    userTypeComboBox->addItem("Admin");

    // Create login and password fields
    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Create switch button
    switchButton = new QPushButton("Switch to Registration", this);

    // Create form layout and add widgets
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("User Type:", userTypeComboBox);
    formLayout->addRow("Login:", loginLineEdit);
    formLayout->addRow("Password:", passwordLineEdit);

    // Add form layout and switch button to main layout
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(switchButton);

    // Connect switch button signal to slot
    connect(switchButton, &QPushButton::clicked, this, &LoginWindow::switchToRegistration);
}

LoginWindow::~LoginWindow()
{
    if (registrationWindow) {
        delete registrationWindow;
    }
}

void LoginWindow::switchToRegistration()
{
    if (!registrationWindow) {
        registrationWindow = new RegistrationWindow(this);
    }
    registrationWindow->show();
    this->hide();
}
