#include "loginwindow.h"

LoginWindow::LoginWindow(WelcomeWindow *welcomeWindow, QWidget *parent)
    : QMainWindow(parent), welcomeWindow(welcomeWindow)
{
    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create title label
    QLabel *titleLabel = new QLabel("Авторизация", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    // Add title label to main layout
    mainLayout->addWidget(titleLabel);

    // Create user type combo box
    userTypeComboBox = new QComboBox(this);
    userTypeComboBox->addItem("student");
    userTypeComboBox->addItem("lecturer");
    userTypeComboBox->addItem("admin");

    // Create login and password fields
    // loginLineEdit = new QLineEdit(this);
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // Create form layout and add widgets
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Логин:", userTypeComboBox);
    // formLayout->addRow("Login:", loginLineEdit);
    formLayout->addRow("Пароль:", passwordLineEdit);

    // Add form layout to main layout
    mainLayout->addLayout(formLayout);

    // Create login button
    loginButton = new QPushButton("Войти", this);
    mainLayout->addWidget(loginButton);

    // Connect back button signal to slot
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::performLogin);

    // Create back button
    backButton = new QPushButton("Назад", this);
    mainLayout->addWidget(backButton);

    // Connect back button signal to slot
    connect(backButton, &QPushButton::clicked, this, &LoginWindow::backToWelcome);
}

LoginWindow::~LoginWindow() {}

void LoginWindow::performLogin() {
    // Show MenuWindow based on user type
    QString userType = userTypeComboBox->currentText();
    QString password = passwordLineEdit->text();

    if (DatabaseHelper::connectToDatabase("localhost", "course", userType, password)) {
        AuthenticationManager::currentUserLogin = userType;
        MenuWindow *menuWindow = new MenuWindow(welcomeWindow, userType, this);
        menuWindow->show();
        this->hide();
    } else {
        QMessageBox::critical(this, "Ошибка", DatabaseHelper::lastError().text());
    }
}

void LoginWindow::backToWelcome()
{
    this->hide();
    welcomeWindow->show();
}
