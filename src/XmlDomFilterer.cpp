#include "XmlDomFilterer.h"

void XmlDomFilterer::setData(const QString &input, WantedService wanted) {
    wantedService = wanted;
    matchedServices.clear();

    QDomDocument domDocument;
    if (!domDocument.setContent(input)) {
        error("Bad Xml File");
        return;
    }

    QDomElement rootElement = domDocument.documentElement();
    if (rootElement.tagName() != "FacultyNetworkInformationSystems") {
        error("Bad root tag: " + rootElement.tagName());
        return;
    }

    QDomNode serviceNode = rootElement.firstChild();
    while (!serviceNode.isNull()) {
        if (serviceNode.toElement().tagName() != "Service") {
            error("Tag not equal to Service: " + serviceNode.toElement().tagName());
            return;
        }
        if (serviceNode.attributes().count() != SERVICE_ATTRIBUTES_COUNT) {
            error("Wrong service attributes number");
            return;
        }
        const QDomNamedNodeMap& attribs = serviceNode.attributes();

        auto atribValue = [&attribs](std::string_view name){ return attribs.namedItem(QString::fromStdString(name.data())).nodeValue();};

        auto currentService = Service();
        for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
            currentService.attributes[i] = atribValue(magic_enum::enum_name(ServiceAttributes(i)));
        }

        if (wantedService.isServiceSuitable(currentService)) {
            matchedServices.push_back(currentService);
        }
        serviceNode = serviceNode.nextSibling();
    }
}
QString XmlDomFilterer::getResult() {
    QString result;
    for (size_t i = 0; i < matchedServices.size(); ++i) {
        result += matchedServices[i].getInfo();
        if (i != matchedServices.size() - 1)
            result += "\n\n";
    }
    return result;
}

void XmlDomFilterer::error(const QString &msg) {
    qCritical() << msg;
    QMessageBox::critical(QApplication::activeWindow(), "Xml Error", msg);
}
