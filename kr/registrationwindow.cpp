#include "registrationwindow.h"
#include "loginwindow.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

RegistrationWindow::RegistrationWindow(LoginWindow *loginWindow, QWidget *parent)
    : QMainWindow(parent), loginWindow(loginWindow)
{
    // Create main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // Create title label
    QLabel *titleLabel = new QLabel("Registration Form", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);

    // Add title label to main layout
    mainLayout->addWidget(titleLabel);

    // Create user type selection
    QComboBox *userTypeComboBox = new QComboBox(this);
    userTypeComboBox->addItem("Student");
    userTypeComboBox->addItem("Lecturer");
    userTypeComboBox->addItem("Admin");

    mainLayout->addWidget(userTypeComboBox);

    // Create form layout
    QFormLayout *formLayout = new QFormLayout();
    mainLayout->addLayout(formLayout);

    // Connect signal for user type change
    connect(userTypeComboBox, &QComboBox::currentTextChanged, this, &RegistrationWindow::onUserTypeChanged);

    // Create initial form (Student)
    onUserTypeChanged(userTypeComboBox->currentText());

    // Create switch button
    switchButton = new QPushButton("Switch to Login", this);
    mainLayout->addWidget(switchButton);

    // Connect switch button signal to slot
    connect(switchButton, &QPushButton::clicked, this, &RegistrationWindow::switchToLogin);
}

RegistrationWindow::~RegistrationWindow()
{
}

void RegistrationWindow::onUserTypeChanged(const QString &userType)
{
    clearForm();

    if (userType == "Student") {
        createStudentFields();
    } else if (userType == "Lecturer") {
        createLecturerFields();
    } else if (userType == "Admin") {
        createAdminFields();
    }
}

void RegistrationWindow::clearForm()
{
    // Clear existing form fields
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());
    QFormLayout *formLayout = qobject_cast<QFormLayout *>(mainLayout->itemAt(2)->layout());
    if (!formLayout) return;

    while (formLayout->count() > 0) {
        QLayoutItem *item = formLayout->takeAt(0);
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void RegistrationWindow::createCommonFields()
{
    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(2)->layout());

    QLineEdit *usernameField = new QLineEdit(this);
    formLayout->addRow("FIO:", usernameField);

    QLineEdit *emailField = new QLineEdit(this);
    formLayout->addRow("Email:", emailField);

    QLineEdit *loginField = new QLineEdit(this);
    formLayout->addRow("Login:", loginField);

    QLineEdit *passwordField = new QLineEdit(this);
    // passwordField->setEchoMode(QLineEdit::Password);
    formLayout->addRow("Password:", passwordField);
}

void RegistrationWindow::createStudentFields()
{
    createCommonFields();

    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(2)->layout());

    QLineEdit *chatIDField = new QLineEdit(this);
    formLayout->addRow("Chat ID:", chatIDField);

    QLineEdit *courseIDField = new QLineEdit(this);
    formLayout->addRow("Course ID:", courseIDField);
}

void RegistrationWindow::createLecturerFields()
{
    createCommonFields();

    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(2)->layout());

    QLineEdit *chatIDField = new QLineEdit(this);
    formLayout->addRow("Chat ID:", chatIDField);

    QLineEdit *courseIDField = new QLineEdit(this);
    formLayout->addRow("Course ID:", courseIDField);
}

void RegistrationWindow::createAdminFields()
{
    createCommonFields();

    // QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(1)->layout());

    // QLineEdit *adminIDField = new QLineEdit(this);
    // formLayout->addRow("Admin ID:", adminIDField);

    // QLineEdit *roleField = new QLineEdit(this);
    // formLayout->addRow("Role:", roleField);
}

void RegistrationWindow::switchToLogin()
{
    this->hide();
    loginWindow->show();
}
