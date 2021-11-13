#include "ComboBoxPopulator.h"

void ComboBoxPopulator::setData(const QString &input) {
    result.clear();
    errorOccured = false;

    for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
        result.push_back(QVector<QString>());
    }

    QDomDocument domDocument;
    if (!domDocument.setContent(input)) {
        error("Bad Xml File");
        return;
    }

    QDomElement rootElement = domDocument.documentElement();
    if (rootElement.tagName() != "FacultyNetworkInformationServices") {
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
        const QDomNamedNodeMap &attribs = serviceNode.attributes();

        auto atribValue = [&attribs](std::string_view name) -> QString {
            return attribs.namedItem(QString::fromStdString(name.data())).nodeValue();
        };

        for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
            QString atr = atribValue(magic_enum::enum_name(ServiceAttributes(i)));
            if (!result[i].contains(atr)) {
                result[i].push_back(atr);
            }
        }
        serviceNode = serviceNode.nextSibling();
    }
}

QVector<QVector<QString>> ComboBoxPopulator::getResult() {
    return result;
}

void ComboBoxPopulator::error(const QString &msg) {
    errorOccured = true;
    qCritical() << msg;
    QMessageBox::critical(QApplication::activeWindow(), "Xml Error", msg);
}
bool ComboBoxPopulator::checkIfErrorOccured() {
    return errorOccured;
}
