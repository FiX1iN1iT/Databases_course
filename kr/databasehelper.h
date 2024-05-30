#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>
#include <QSqlError>
#include <QSqlDatabase>

class DatabaseHelper
{
public:
    static bool connectToDatabase(const QString &hostName, const QString &databaseName,
                                  const QString &userName, const QString &password);
    // Метод для проверки состояния подключения к базе данных
    static bool isDatabaseConnected();

    // Метод для получения последней ошибки базы данных
    static QSqlError lastError();

    // Метод для получения объекта соединения с базой данных
    static QSqlDatabase getDatabaseConnection();

private:
    // Статическая переменная для отслеживания состояния подключения
    static bool databaseConnected;

    // Статическая переменная для хранения последней ошибки базы данных
    static QSqlError lastDbError;

    // База данных
    static QSqlDatabase db;
};

#endif // DATABASEHELPER_H
