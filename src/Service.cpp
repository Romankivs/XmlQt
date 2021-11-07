#include "Service.h"
Service::Service(QString name, QString annotation, QString type,
                 QString version, QString author, QString termsAndConditionsOfUse,
                 QString informationWhenRegisteringUser) :
                 name(name), annotation(annotation), type(type),
                 version(version), author(author), termsAndConditionsOfUse(termsAndConditionsOfUse),
                 informationWhenRegisteringUser(informationWhenRegisteringUser) {
}
QString Service::getInfo() {
    return  "Name: " + name + '\n' +
            "Annotation: " + annotation + '\n' +
            "Type: " + type + '\n' +
            "Version: " + version + '\n' +
            "Author: " + author + '\n' +
            "TermsAndConditionsOfUse: " + termsAndConditionsOfUse + '\n' +
            "InformationWhenRegisteringUser: " + informationWhenRegisteringUser;
}

bool WantedService::isServiceSuitable(const Service &service) {
    auto compareWithWanted = [](const QString &value, const std::optional<QString> &opt) -> bool {
        return bool(opt) ? value == opt.value() : true;
    };
    if (!compareWithWanted(service.name, name) ||
        !compareWithWanted(service.annotation, annotation) ||
        !compareWithWanted(service.informationWhenRegisteringUser, informationWhenRegisteringUser) ||
        !compareWithWanted(service.termsAndConditionsOfUse, termsAndConditionsOfUse) ||
        !compareWithWanted(service.author, author) ||
        !compareWithWanted(service.type, type) ||
        !compareWithWanted(service.version, version)
        ) {
        return false;
    }
    return true;
}
