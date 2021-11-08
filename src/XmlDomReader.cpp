#include "XmlDomReader.h"

void XmlDomReader::setData(const QString &input, WantedService wanted) {
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
        auto atribValue = [&attribs](const QString &name){ return attribs.namedItem(name).nodeValue();};
        const auto currentService = Service(atribValue("Name"),
                                            atribValue("Annotation"),
                                            atribValue("Type"),
                                            atribValue("Version"),
                                            atribValue("Author"),
                                            atribValue("TermsAndConditionsOfUse"),
                                            atribValue("InformationWhenRegisteringUser")
        );
        if (wantedService.isServiceSuitable(currentService)) {
            matchedServices.push_back(currentService);
        }
        serviceNode = serviceNode.nextSibling();
    }
}
QVector<Service> XmlDomReader::getResult() {
    return matchedServices;
}
void XmlDomReader::error(const QString &msg) {
    qCritical() << msg;
    QMessageBox::critical(QApplication::activeWindow(), "Xml Error", msg);
}
