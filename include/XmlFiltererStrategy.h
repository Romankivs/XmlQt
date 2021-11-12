#pragma once
#include <QObject>
#include <QString>
#include <Service.h>

class XmlFiltererStrategy : public QObject {
    Q_OBJECT
public:
    virtual void setData(const QString &input, WantedService wanted) = 0;
    virtual QString getResult() = 0;
};
