#include "XmlSaxFilterer.h"

void XmlSaxFilterer::setData(const QString &input, WantedService wanted) {
    std::cerr << "SAX FILTERER" << std::endl;

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
            result += "\n\n";
    }
    return result;
}

bool XmlSaxFilterer::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &attribs) {
    if (qName == "Service") {
        currentService = Service();
        for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
            currentService.attributes[i] = attribs.value(i);
        }
    }
    return true;
}

bool XmlSaxFilterer::endElement(const QString &namespaceURI, const QString &localName, const QString &qName) {
    if (qName == "Service") {
        if (wantedService.isServiceSuitable(currentService)) {
            matchedServices.push_back(currentService);
        }
    }
    return true;
}

