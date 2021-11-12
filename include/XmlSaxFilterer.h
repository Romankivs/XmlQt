#pragma once
#include "XmlFiltererStrategy.h"
#include <QApplication>
#include <QMessageBox>
#include <QXmlDefaultHandler>
#include <iostream>
#include <optional>

class XmlSaxFilterer : public QXmlDefaultHandler, public XmlFiltererStrategy {
public:
    XmlSaxFilterer() = default;
    ~XmlSaxFilterer(){};
    void setData(const QString &input, WantedService wanted) override;
    QString getResult() override;
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