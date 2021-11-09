#include <QApplication>
#include <QPushButton>
#include <QFile>
#include "XmlSaxHandler.h"
#include "XmlDomReader.h"
#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

#include "XmlLinqFilterer.h"

int main(int argc, char *argv[]) {
    /*QApplication a(argc, argv);
    XmlSaxHandler handler;
    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    QString stringInput = stream.readAll();
    WantedService wanted;
    wanted.version = "1.0";
    handler.setData(stringInput, wanted);

    XmlDomReader dom;
    dom.setData(stringInput, wanted);

    auto res = handler.getResult();
    for (auto x : res) {
        std::cerr << x.getInfo().toStdString() << std::endl;
        std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    }
    std::cerr << "DOM: " << std::endl;
    res = dom.getResult();
    for (auto x : res) {
        std::cerr << x.getInfo().toStdString() << std::endl;
        std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    }

    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();*/

    /*MonoDomain *domain;
    argc = 1;
    char *argvReplace[] = {
            (char*) "/home/sviat/CLionProjects/XmlQt/Embedded/LinqToXml.dll",
            NULL};
    argv = argvReplace;
    const char *file = argv[0];

    mono_config_parse(NULL);

    domain = mono_jit_init(file);
    if (!domain)
        exit(1);

    MonoAssembly *assembly = mono_domain_assembly_open (domain, file);
    if (!assembly)
        exit(2);

    MonoImage* image =  mono_assembly_get_image (assembly);
    MonoClass *klass;
    MonoObject *obj;
    klass = mono_class_from_name (image, "LinqToXml", "XmlLinqFilterer");
    if (!klass) {
        fprintf (stderr, "Can't find LinqToXml type in assembly %s\n", mono_image_get_filename (image));
        exit (3);
    }
    obj = mono_object_new (domain, klass);
    mono_runtime_object_init (obj);

    // retrieve all the methods we need
    MonoMethod* m, *setData, *getResult;
    void *iter = NULL;
    while ((m = mono_class_get_methods (klass, &iter))) {
        if (strcmp (mono_method_get_name (m), "SetData") == 0) {
            setData = m;
        } else if (strcmp (mono_method_get_name (m), "GetResult") == 0) {
            getResult = m;
        }
    }

    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    std::string stringInput = stream.readAll().toStdString();
    const char* cInput = stringInput.c_str();

    void* args[8];
    MonoString* inp = mono_string_new(domain, cInput);
    args[0] = inp;
    std::string version = "1.0";
    MonoString* ver = mono_string_new(domain, version.c_str());
    for (int i = 1; i < 8; ++i)
    {
        args[i] = nullptr;
    }
    args[4] = ver;
    mono_runtime_invoke(setData, obj, args ,NULL);

    MonoString* result = (MonoString*)mono_runtime_invoke(getResult, obj, NULL, NULL);
    char* cRes = mono_string_to_utf8(result);
    std::cerr << cRes << std::endl;
    mono_free(cRes);
    mono_jit_cleanup(domain);*/

    XmlLinqFilterer filt;
    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    QString stringInput = stream.readAll();
    WantedService service;
    service.version = "1.0";
    filt.setData(stringInput, service);
    std::cerr << filt.getResult().toStdString();
    getchar();
    getchar();
}
