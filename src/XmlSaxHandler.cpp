#include "XmlSaxHandler.h"

XmlSaxHandler::XmlSaxHandler(QObject *parent) {
}

void XmlSaxHandler::setData(const QString &input, WantedService wanted) {
    currentService = Service();
    wantedService = wanted;
    matchedServices.clear();

    QXmlSimpleReader reader;
    QXmlInputSource source;
    source.setData(input);
    reader.setContentHandler(this);
    reader.setErrorHandler(this);
    reader.parse(source);
}

QVector<Service> XmlSaxHandler::getResult() {
    return matchedServices;
}

bool XmlSaxHandler::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &attribs) {
    if (qName == "Service") {
        if (attribs.count() != SERVICE_ATTRIBUTES_COUNT) {
            std::cerr <<"Wrong service attributes number" << std::endl;
            return false;
        }
        for (size_t i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {

        }
        currentService = Service(attribs.value(0), attribs.value(1),
                                 attribs.value(2), attribs.value(3),
                                 attribs.value(4), attribs.value(5),
                                 attribs.value(6)
                                 );
    }
    else if (qName != "FacultyNetworkInformationSystems") {
        return false;
    }
    return true;
}

bool XmlSaxHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName) {
    if (qName == "Service") {
        if (wantedService.isServiceSuitable(currentService)) {
            matchedServices.push_back(currentService);
        }
    }
    else if (qName != "FacultyNetworkInformationSystems") {
        return false;
    }
    return true;
}

bool XmlSaxHandler::characters(const QString &str) {
    return QXmlDefaultHandler::characters(str);
}

bool XmlSaxHandler::fatalError(const QXmlParseException &exception) {
    qCritical() << "Fatal error parsing xml on line" << exception.lineNumber() << ':'
                << exception.message();
    QMessageBox::critical(QApplication::activeWindow(), "Xml Error", exception.message());
    return false;
}
