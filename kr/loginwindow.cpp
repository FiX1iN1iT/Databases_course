#include "loginwindow.h"
#include "welcomewindow.h"

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>

LoginWindow::LoginWindow(WelcomeWindow *welcomeWindow, QWidget *parent)
    : QMainWindow(parent), welcomeWindow(welcomeWindow)
{
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create title label
    QLabel *titleLabel = new QLabel("Login Form", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    // Add title label to main layout
    mainLayout->addWidget(titleLabel);

    // Create user type combo box
    userTypeComboBox = new QComboBox(this);
    userTypeComboBox->addItem("Student");
    userTypeComboBox->addItem("Lecturer");
    userTypeComboBox->addItem("Admin");

    // Create login and password fields
    loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Create form layout and add widgets
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("User Type:", userTypeComboBox);
    formLayout->addRow("Login:", loginLineEdit);
    formLayout->addRow("Password:", passwordLineEdit);

    // Add form layout to main layout
    mainLayout->addLayout(formLayout);

    // Create back button
    backButton = new QPushButton("Back to Welcome", this);
    mainLayout->addWidget(backButton);

    // Connect back button signal to slot
    connect(backButton, &QPushButton::clicked, this, &LoginWindow::backToWelcome);
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::backToWelcome()
{
    this->hide();
    welcomeWindow->show();
}
