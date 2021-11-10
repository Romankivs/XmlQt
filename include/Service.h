#pragma once
#include <QString>
#include <QVector>
#include <QStringView>
#include "magic_enum.hpp"

enum ServiceAttributes
{
    Name = 0,
    Annotation = 1,
    Type = 2,
    Version = 3,
    Author = 4,
    TermsAndConditionsOfUse = 5,
    InformationWhenRegisteringUser = 6
};

constexpr size_t SERVICE_ATTRIBUTES_COUNT = magic_enum::enum_count<ServiceAttributes>();

struct Service
{
    Service() = default;
    Service(QVector<QString> attributes);
    QString getInfo() const;
    QVector<QString> attributes = QVector<QString>(SERVICE_ATTRIBUTES_COUNT);
};

struct WantedService
{
    WantedService() = default;
    bool isServiceSuitable(const Service &service) const;
    QVector<std::optional<QString>> attributes = QVector<std::optional<QString>>(SERVICE_ATTRIBUTES_COUNT);
};