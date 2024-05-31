#include "authenticationmanager.h"

AuthenticationManager::AuthenticationManager(QObject *parent) : QObject(parent) {}

QString AuthenticationManager::currentUserLogin;

QStringList AuthenticationManager::getAllowedMenuButtons() {
    QStringList allowedButtons = {};

    if (currentUserLogin == "student") {
        allowedButtons = {"Курс", "Дисциплина", "Преподаватель", "Материалы", "Чат", "Оценка"};
    } else if (currentUserLogin == "lecturer") {
        allowedButtons = {"Курс", "Дисциплина", "Студент", "Материалы", "Чат", "Оценка"};
    } else if (currentUserLogin == "admin") {
        allowedButtons = {"Курс", "Дисциплина", "Преподаватель", "Студент", "Материалы", "Чат", "Оценка"};
    }

    return allowedButtons;
}
