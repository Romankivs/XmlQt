#include "Service.h"

Service::Service(QVector<QString> attributes) {
    Q_ASSERT(attributes.size() == SERVICE_ATTRIBUTES_COUNT);
    attributes = attributes;
}

QString Service::getInfo() const {
    QString result;
    for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
        std::string_view s = magic_enum::enum_name(ServiceAttributes(i));
        result += QString::fromStdString(s.data()) + ": " + attributes[i];
        if (i != SERVICE_ATTRIBUTES_COUNT - 1)
            result += '\n';
    }
    return result;
}

bool WantedService::isServiceSuitable(const Service &service) const {
    auto compareWithWanted = [](const QString &value, const std::optional<QString> &opt) -> bool {
        return bool(opt) ? value == opt.value() : true;
    };
    for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
        if (!compareWithWanted(service.attributes[i], attributes[i]))
            return false;
    }
    return true;
}
