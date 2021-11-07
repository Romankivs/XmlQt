#pragma once
#include <QString>

struct Service
{
    Service() = default;
    Service(QString name, QString annotation, QString type,
            QString version, QString author, QString termsAndConditionsOfUse,
            QString informationWhenRegisteringUser);
    QString getInfo();
    QString name;
    QString annotation;
    QString type;
    QString version;
    QString author;
    QString termsAndConditionsOfUse;
    QString informationWhenRegisteringUser;
};

struct WantedService
{
    bool isServiceSuitable(const Service &service);
    std::optional<QString> name;
    std::optional<QString> annotation;
    std::optional<QString> type;
    std::optional<QString> version;
    std::optional<QString> author;
    std::optional<QString> termsAndConditionsOfUse;
    std::optional<QString> informationWhenRegisteringUser;
};