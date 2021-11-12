#pragma once
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QCheckBox>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMenuBar>
#include <QVector>
#include <QPointer>
#include <QString>
#include <QRadioButton>
#include <QFileDialog>
#include "XmlSaxFilterer.h"
#include "XmlDomFilterer.h"
#include "XmlLinqFilterer.h"
#include "ComboBoxPopulator.h"

#include <libxml2/libxml/xmlmemory.h>
#include <libxml2/libxml/debugXML.h>
#include <libxml2/libxml/HTMLtree.h>
#include <libxml2/libxml/xmlIO.h>
#include <libxml2/libxml/DOCBparser.h>
#include <libxml2/libxml/xinclude.h>
#include <libxml2/libxml/catalog.h>
#include <libxml2/libxml/uri.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

constexpr int numberOfAttributes = 7;


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
private:
    void createMenu();
    void createApiGroupBox();
    void createFilterGroupBox();
    void populateComboBoxes();
    void loadXml();
    void filterXml();
    void transformXmlToHtml();

    QMenuBar* menuBar;
    QGroupBox* apiGroupBox;
    QGroupBox* filterGroupBox;
    QRadioButton *saxButton, *domButton, *linqButton;
    QCheckBox* checkBoxes[numberOfAttributes];
    QLabel* labels[numberOfAttributes];
    QComboBox* comboBoxes[numberOfAttributes];
    QTextEdit* textEditor;
    QWidget* mainWidget;

    QPointer<XmlFiltererStrategy> filterer;

    QString currentFileName;

    QString input;
    bool illFormedInput;
};
