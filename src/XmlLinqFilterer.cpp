#include "XmlLinqFilterer.h"
#include <iostream>
void XmlLinqFilterer::setData(const QString &input, WantedService wanted) {
    void* args[argumentsCount];
    MonoString* inp = mono_string_new(domain, input.toStdString().c_str());
    args[0] = inp;

    auto optToMonoStr = [](MonoDomain* domain, std::optional<QString> opt) -> MonoString* {
        if (!opt.has_value())
            return nullptr;
        const char* value = opt.value().toStdString().c_str();
        return mono_string_new(domain, value);
    };

    for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
        args[i + 1] = optToMonoStr(domain, wanted.attributes[i]);
    }

    mono_runtime_invoke(mSetData, linqFiltererObj, args, NULL);

    MonoString* res = (MonoString*)mono_runtime_invoke(mGetResult, linqFiltererObj, NULL, NULL);
    char* cRes = mono_string_to_utf8(res);
    result = QString(cRes);
    mono_free(cRes);
}

QString XmlLinqFilterer::getResult() {
    return result;
}

void XmlLinqFilterer::error(const QString &msg) {
    qCritical() << msg;
    exit(1);
}


MonoDomain* XmlLinqFilterer::domain = [](){
    mono_config_parse(NULL);
    MonoDomain* res = mono_jit_init(file.c_str());
    return res;
}();

MonoAssembly* XmlLinqFilterer::assembly = [](){
    MonoAssembly* res = mono_domain_assembly_open (domain, file.c_str());
    if (!res)
        error(QString::fromStdString(std::string("Can't open assembly: ")));
    return res;
}();

MonoImage* XmlLinqFilterer::image = [](){
    MonoImage* res = mono_assembly_get_image(assembly);
    if (!res)
        error("Can't load assembly image");
    return res;
}();

MonoClass* XmlLinqFilterer::linqFiltererClass = [](){
    MonoClass* res = mono_class_from_name (image, embNamespace.c_str(), className.c_str());
    if (!res)
        error("Class not found: " + QString::fromStdString(className));
    return res;
}();

MonoObject* XmlLinqFilterer::linqFiltererObj = [](){
    MonoObject* obj = mono_object_new (domain, linqFiltererClass);
    mono_runtime_object_init (obj);
    return obj;
}();

MonoMethod* XmlLinqFilterer::mSetData = [](){
    MonoMethod* m;
    void *iter = NULL;
    while ((m = mono_class_get_methods (linqFiltererClass, &iter))) {
        if (strcmp (mono_method_get_name (m), "SetData") == 0) {
            break;
        }
    }
    return m;
}();

MonoMethod* XmlLinqFilterer::mGetResult = [](){
    MonoMethod* m;
    void *iter = NULL;
    while ((m = mono_class_get_methods (linqFiltererClass, &iter))) {
        if (strcmp (mono_method_get_name (m), "GetResult") == 0) {
            break;
        }
    }
    return m;
}();