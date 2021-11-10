#include <QApplication>
#include <QPushButton>
#include <QFile>
#include "XmlLinqFilterer.h"
#include <iostream>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    XmlLinqFilterer filt;

    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    QString stringInput = stream.readAll();
    WantedService service;
    service.version = "1.0";
    filt.setData(stringInput, service);

    std::cerr << filt.getResult().toStdString();

    MainWindow window;
    window.show();
    return QApplication::exec();

}
