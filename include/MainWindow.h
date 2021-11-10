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
    void loadXml();
    void populateComboBoxes();
    void filterXml();

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

    QString input;
    bool illFormedInput;
};
