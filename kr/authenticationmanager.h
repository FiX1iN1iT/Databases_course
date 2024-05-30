#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <QObject>
#include <QString>
#include <QStringList>

class AuthenticationManager : public QObject
{
    Q_OBJECT

public:
    explicit AuthenticationManager(QObject *parent = nullptr);
    static QString currentUserLogin;
    static QStringList getAllowedButtons();
};

#endif // AUTHENTICATIONMANAGER_H
