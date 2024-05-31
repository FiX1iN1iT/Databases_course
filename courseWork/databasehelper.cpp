#include "databasehelper.h"

bool DatabaseHelper::databaseConnected = false; // Инициализация статической переменной класса
QSqlError DatabaseHelper::lastDbError; // Инициализация статической переменной класса

bool DatabaseHelper::connectToDatabase(const QString &hostName, const QString &databaseName,
                                       const QString &userName, const QString &password) {
    // Добавление путей к драйверам баз данных (в данном случае для PostgreSQL)
    QCoreApplication::addLibraryPath("/opt/homebrew/opt/libpq/lib");

    // Подключаемся к базе данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL"); // Создание объекта базы данных для PostgreSQL
    db.setHostName(hostName); // Установка имени хоста
    db.setDatabaseName(databaseName); // Установка имени базы данных
    db.setUserName(userName); // Установка имени пользователя
    db.setPassword(password); // Установка пароля пользователя

    if (db.open()) {
        // Если подключение успешно, устанавливаем флаг успешного подключения
        qDebug() << "Connection successful.";
        databaseConnected = true;
        return true;
    } else {
        // Если произошла ошибка при подключении, сохраняем информацию об ошибке
        qDebug() << "Connection failed.";
        qDebug() << db.lastError().text();
        lastDbError = db.lastError();
        databaseConnected = false;
        return false;
    }
}


bool DatabaseHelper::isDatabaseConnected() {
    return databaseConnected; // Возвращаем текущее состояние флага подключения
}

QSqlError DatabaseHelper::lastError() {
    return lastDbError; // Возвращаем последнюю ошибку базы данных
}

QSqlDatabase DatabaseHelper::getDatabaseConnection() {
    // Получаем объект соединения с базой данных
    QSqlDatabase db = QSqlDatabase::database();

    // Проверяем, открыто ли соединение
    if (!db.isOpen()) {
        // Если соединение не открыто, выводим сообщение об ошибке
        qDebug() << "База данных не открыта. Ошибка: " << db.lastError().text();
    }

    return db; // Возвращаем объект базы данных
}
