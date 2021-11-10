#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName("Xml Analyzer");
    a.setWindowIcon(QIcon(QString(PROJECT_DIRECTORY)
                          + QString("/icons/appIcon.jpg")));
    MainWindow window;
    window.show();
    return QApplication::exec();

}
