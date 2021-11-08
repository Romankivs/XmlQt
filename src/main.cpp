#include <QApplication>
#include <QPushButton>
#include <QFile>
#include "XmlSaxHandler.h"
#include "XmlDomReader.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
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
    return QApplication::exec();
}
