#include "authenticationmanager.h"

AuthenticationManager::AuthenticationManager(QObject *parent) : QObject(parent) {}

QString AuthenticationManager::currentUserLogin;

QStringList AuthenticationManager::getAllowedMenuButtons() {
    QStringList allowedButtons = {};

    if (currentUserLogin == "student") {
        allowedButtons = {"Course", "Discipline", "Lecturer", "Materials", "Chat", "Mark"};
    } else if (currentUserLogin == "lecturer") {
        allowedButtons = {"Course", "Discipline", "Student", "Materials", "Chat", "Mark"};
    } else if (currentUserLogin == "admin") {
        allowedButtons = {"Course", "Discipline", "Lecturer", "Student", "Materials", "Chat", "Mark"};
    }

    return allowedButtons;
}
