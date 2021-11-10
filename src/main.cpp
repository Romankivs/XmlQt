#include <QApplication>
#include <QFile>
#include "XmlLinqFilterer.h"
#include <iostream>
#include "MainWindow.h"
#include "magic_enum.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    XmlLinqFilterer filt;
    std::cerr << "MAGIC_ENUM:" << magic_enum::is_magic_enum_supported << std::endl;
    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    QString stringInput = stream.readAll();
    WantedService service;
    service.attributes[ServiceAttributes::Version] = "1.0";
    filt.setData(stringInput, service);

    std::cerr << filt.getResult().toStdString();

    MainWindow window;
    window.show();
    return QApplication::exec();

}
