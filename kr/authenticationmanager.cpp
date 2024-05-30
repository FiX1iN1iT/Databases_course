#include "authenticationmanager.h"

AuthenticationManager::AuthenticationManager(QObject *parent) : QObject(parent) {}

QString AuthenticationManager::currentUserLogin;

QStringList AuthenticationManager::getAllowedButtons() {
    QStringList allowedButtons = {};

    if (currentUserLogin == "booking_department") {
        allowedButtons = {"Бронирование", "Гости", "Оплата", "Бронь номеров"};
    } else if (currentUserLogin == "accommodation_service") {
        allowedButtons = {"Номера"};
    } else if (currentUserLogin == "sales_department") {
        allowedButtons = {"Бронирование", "Гости", "Оплата", "Услуги"};
    }

    return allowedButtons;
}
