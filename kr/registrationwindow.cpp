#include "registrationwindow.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

RegistrationWindow::RegistrationWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create main layout
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

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
    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(1)->layout());
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
    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(1)->layout());

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

    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(1)->layout());

    QLineEdit *chatIDField = new QLineEdit(this);
    formLayout->addRow("Chat ID:", chatIDField);

    QLineEdit *courseIDField = new QLineEdit(this);
    formLayout->addRow("Course ID:", courseIDField);
}

void RegistrationWindow::createLecturerFields()
{
    createCommonFields();

    QFormLayout *formLayout = qobject_cast<QFormLayout *>(centralWidget()->layout()->itemAt(1)->layout());

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
