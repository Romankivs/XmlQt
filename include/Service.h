#pragma once
#include <QString>

enum ServiceAttributes
{
    Name = 0,
    Annotation,
    Type,
    Version,
    Author,
    TermsAndConditionsOfUse,
    InformationWhenRegisteringUser
};

constexpr size_t SERVICE_ATTRIBUTES_COUNT = 7;

struct Service
{
    Service() = default;
    Service(QString name, QString annotation, QString type,
            QString version, QString author, QString termsAndConditionsOfUse,
            QString informationWhenRegisteringUser);
    QString getInfo() const;
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
    bool isServiceSuitable(const Service &service) const;
    std::optional<QString> name;
    std::optional<QString> annotation;
    std::optional<QString> type;
    std::optional<QString> version;
    std::optional<QString> author;
    std::optional<QString> termsAndConditionsOfUse;
    std::optional<QString> informationWhenRegisteringUser;
};