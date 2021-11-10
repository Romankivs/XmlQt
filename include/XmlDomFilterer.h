#pragma once
#include <QVector>
#include <QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <iostream>
#include "XmlFiltererStrategy.h"

class XmlDomFilterer : public XmlFiltererStrategy {
public:
    XmlDomFilterer() = default;
    void setData(const QString &input, WantedService wanted) override;
    QString getResult() override;
private:
    void error(const QString &msg);

    WantedService wantedService;
    QVector<Service> matchedServices;
};

