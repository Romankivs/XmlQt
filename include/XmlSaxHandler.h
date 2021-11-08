#pragma once
#include <QXmlDefaultHandler>
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <optional>
#include <Service.h>

class XmlSaxHandler : public QXmlDefaultHandler
{
public:
    XmlSaxHandler() = default;
    void setData(const QString &input, WantedService wanted);
    QVector<Service> getResult();
    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &attribs) override;
    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName) override;
    bool fatalError(const QXmlParseException &exception) override;

private:
    Service currentService;
    WantedService wantedService;
    QVector<Service> matchedServices;
};