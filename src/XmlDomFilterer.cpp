#include "XmlDomFilterer.h"

void XmlDomFilterer::setData(const QString &input, WantedService wanted) {
    std::cerr << "DOM FILTERER" << std::endl;

    wantedService = wanted;
    matchedServices.clear();

    QDomDocument domDocument;
    domDocument.setContent(input);

    QDomElement rootElement = domDocument.documentElement();
    rootElement.tagName();

    QDomNode serviceNode = rootElement.firstChild();
    while (!serviceNode.isNull()) {
        const QDomNamedNodeMap &attribs = serviceNode.attributes();

        auto atribValue = [&attribs](std::string_view name) { return attribs.namedItem(QString::fromStdString(name.data())).nodeValue(); };

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
