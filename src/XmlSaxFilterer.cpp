#include "XmlSaxFilterer.h"

void XmlSaxFilterer::setData(const QString &input, WantedService wanted) {
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

QString XmlSaxFilterer::getResult() {
    QString result;
    for (size_t i = 0; i < matchedServices.size(); ++i) {
        result += matchedServices[i].getInfo();
        if (i != matchedServices.size() - 1)
            result += '\n';
    }
    return result;
}

bool XmlSaxFilterer::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &attribs) {
    if (qName == "Service") {
        if (attribs.count() != SERVICE_ATTRIBUTES_COUNT) {
            qCritical() << "Wrong service attributes number";
            return false;
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

bool XmlSaxFilterer::endElement(const QString &namespaceURI, const QString &localName, const QString &qName) {
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

bool XmlSaxFilterer::fatalError(const QXmlParseException &exception) {
    qCritical() << "Fatal error parsing xml on line" << exception.lineNumber() << ':'
                << exception.message();
    QMessageBox::critical(QApplication::activeWindow(), "Xml Error", exception.message());
    return false;
}
