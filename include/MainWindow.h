#pragma once
#include "ComboBoxPopulator.h"
#include "XmlDomFilterer.h"
#include "XmlLinqFilterer.h"
#include "XmlSaxFilterer.h"
#include <QCheckBox>
#include <QComboBox>
#include <QFileDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QPointer>
#include <QRadioButton>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QVector>

#include <libxml2/libxml/DOCBparser.h>
#include <libxml2/libxml/HTMLtree.h>
#include <libxml2/libxml/catalog.h>
#include <libxml2/libxml/debugXML.h>
#include <libxml2/libxml/uri.h>
#include <libxml2/libxml/xinclude.h>
#include <libxml2/libxml/xmlIO.h>
#include <libxml2/libxml/xmlmemory.h>
#include <libxslt/transform.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/xsltutils.h>

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

    QMenuBar *menuBar;
    QGroupBox *apiGroupBox;
    QGroupBox *filterGroupBox;
    QRadioButton *saxButton, *domButton, *linqButton;
    QCheckBox *checkBoxes[SERVICE_ATTRIBUTES_COUNT];
    QLabel *labels[SERVICE_ATTRIBUTES_COUNT];
    QComboBox *comboBoxes[SERVICE_ATTRIBUTES_COUNT];
    QTextEdit *textEditor;
    QWidget *mainWidget;

    QPointer<XmlFiltererStrategy> filterer;

    QString currentFileName;
    QString input;
    bool illFormedInput;
};
