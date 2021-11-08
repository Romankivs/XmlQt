#pragma once
#include <QVector>
#include <QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <iostream>
#include "Service.h"

class XmlDomReader {
public:
    XmlDomReader() = default;
    void setData(const QString &input, WantedService wanted);
    QVector<Service> getResult();
private:
    void error(const QString &msg);

    WantedService wantedService;
    QVector<Service> matchedServices;
};

