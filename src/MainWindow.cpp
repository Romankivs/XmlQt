#include "MainWindow.h"

MainWindow::MainWindow() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    createMenu();
    createApiGroupBox();
    createFilterGroupBox();

    setMenuBar(menuBar);

    auto* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(apiGroupBox);
    mainLayout->addWidget(filterGroupBox, 1);
    mainWidget->setLayout(mainLayout);

    XmlLinqFilterer filt;

    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    QString stringInput = stream.readAll();
    WantedService service;
    service.version = "1.0";
    filt.setData(stringInput, service);

    input = filt.getResult();
    textEditor->setText(input);
}

void MainWindow::createMenu() {
    menuBar = new QMenuBar(this);
    QMenu* file = new QMenu("File");
    menuBar->addMenu(file);
    auto* loadXmlAction = file->addAction("Load XML");
    connect(loadXmlAction, &QAction::triggered, this, &MainWindow::loadXml);
    auto* transformHtmlAction = file->addAction("Transform to HTML");
}

void MainWindow::createApiGroupBox() {
    apiGroupBox = new QGroupBox("Choose API", this);
    auto* layout = new QHBoxLayout();
    apiGroupBox->setLayout(layout);
    saxButton = new QRadioButton("SAX");
    domButton = new QRadioButton("DOM");
    linqButton = new QRadioButton("LINQ");
    layout->addWidget(saxButton);
    layout->addWidget(domButton);
    layout->addWidget(linqButton);
}
void MainWindow::createFilterGroupBox() {
    filterGroupBox = new QGroupBox("Filtering", this);
    auto* layout = new QGridLayout();
    filterGroupBox->setLayout(layout);
    for (int i = 0; i < numberOfAttributes; ++i) {
        checkBoxes[i] = new QCheckBox();
        labels[i] = new QLabel("Test");
        comboBoxes[i] = new QComboBox();
        layout->addWidget(checkBoxes[i], i, 0);
        layout->addWidget(labels[i], i, 1);
        layout->addWidget(comboBoxes[i], i, 2);
    }
    textEditor = new QTextEdit();
    textEditor->setReadOnly(true);
    layout->addWidget(textEditor, 0, 3, numberOfAttributes, 1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 2);
    layout->setColumnStretch(2, 10);
    layout->setColumnStretch(3, 30);
}

void MainWindow::loadXml() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open XmlFile"),
                                                    PROJECT_DIRECTORY,
                                                    tr("Xml (*.xml)"));
    QFile xmlData("/home/sviat/CLionProjects/XmlQt/input.xml");
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    input = stream.readAll();
    textEditor->setText(input);
}
