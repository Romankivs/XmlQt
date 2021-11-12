#pragma once
#include "XmlFiltererStrategy.h"
#include <QApplication>
#include <QDebug>
#include <QDomDocument>
#include <QMessageBox>
#include <QVector>
#include <iostream>

class XmlDomFilterer : public XmlFiltererStrategy {
public:
    XmlDomFilterer() = default;
    void setData(const QString &input, WantedService wanted) override;
    QString getResult() override;

private:
    WantedService wantedService;
    QVector<Service> matchedServices;
};
