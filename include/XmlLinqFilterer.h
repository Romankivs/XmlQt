#pragma once
#include <QString>
#include <QVector>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <filesystem>
#include "Service.h"
#include <mono/jit/jit.h>
#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/mono-config.h>

const std::string file = std::string(PROJECT_DIRECTORY) + std::string("/Embedded/LinqToXml.dll");
const std::string embNamespace = "LinqToXml";
const std::string className = "XmlLinqFilterer";

constexpr int argumentsCount = 8;

class XmlLinqFilterer {
public:
    XmlLinqFilterer() = default;
    void setData(const QString &input, WantedService wanted);
    QString getResult();
private:
    static void error(const QString &msg);

    QString result;
    //Mono
    static MonoDomain* domain;
    static MonoAssembly* assembly;
    static MonoImage* image;
    static MonoClass* linqFiltererClass;
    static MonoObject* linqFiltererObj;
    static MonoMethod *mSetData, *mGetResult;
};
