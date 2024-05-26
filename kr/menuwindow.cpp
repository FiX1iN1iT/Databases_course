#include "menuwindow.h"
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
    if (userType == "Student") {
        menuLabel->setText("Student Menu");
        setupUIForStudent();
    } else if (userType == "Lecturer") {
        menuLabel->setText("Lecturer Menu");
        setupUIForLecturer();
    } else if (userType == "Admin") {
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

void MenuWindow::backToWelcome()
{
    this->hide();
    welcomeWindow->show();
}

void MenuWindow::setupUIForStudent()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    // Add student-specific buttons
    QPushButton *viewGradesButton = new QPushButton("View Grades", this);
    mainLayout->addWidget(viewGradesButton);

    QPushButton *enrollCoursesButton = new QPushButton("Enroll in Courses", this);
    mainLayout->addWidget(enrollCoursesButton);
}

void MenuWindow::setupUIForLecturer()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    // Add lecturer-specific buttons
    QPushButton *viewScheduleButton = new QPushButton("View Schedule", this);
    mainLayout->addWidget(viewScheduleButton);

    QPushButton *manageCoursesButton = new QPushButton("Manage Courses", this);
    mainLayout->addWidget(manageCoursesButton);
}

void MenuWindow::setupUIForAdmin()
{
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout *>(centralWidget()->layout());

    // Add admin-specific buttons
    QPushButton *manageUsersButton = new QPushButton("Manage Users", this);
    mainLayout->addWidget(manageUsersButton);

    QPushButton *viewReportsButton = new QPushButton("View Reports", this);
    mainLayout->addWidget(viewReportsButton);
}
