#pragma once

#include <QXmlDefaultHandler>
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <optional>
#include <Service.h>

constexpr size_t SERVICE_ATTRIBUTES_COUNT = 7;

class XmlSaxHandler : public QXmlDefaultHandler
{
public:
    explicit XmlSaxHandler(QObject *parent = 0);
    void setData(const QString &input, WantedService wanted);
    QVector<Service> getResult();
    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &attribs) override;
    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName) override;
    bool characters(const QString &str) override;
    bool fatalError(const QXmlParseException &exception) override;

private:
    Service currentService;
    WantedService wantedService;
    QVector<Service> matchedServices;
};