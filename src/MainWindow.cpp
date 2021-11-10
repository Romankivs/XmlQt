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
        labels[i] = new QLabel(magic_enum::enum_name(ServiceAttributes(i)).data());
        comboBoxes[i] = new QComboBox();

        layout->addWidget(checkBoxes[i], i, 0);
        layout->addWidget(labels[i], i, 1);
        layout->addWidget(comboBoxes[i], i, 2);

        connect(checkBoxes[i], &QCheckBox::clicked, this, &MainWindow::filterXml);
        connect(comboBoxes[i], &QComboBox::activated, this, &MainWindow::filterXml);
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
                                                    "Xml (*.xml)");
    if (fileName.isEmpty())
        return;

    QFile xmlData(fileName);
    xmlData.open(QFile::ReadOnly);
    QTextStream stream(&xmlData);
    input = stream.readAll();

    populateComboBoxes();
    filterXml();
}
void MainWindow::populateComboBoxes() {
    ComboBoxPopulator populator;
    populator.setData(input);
    QVector<QVector<QString>> r = populator.getResult();

    for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
        comboBoxes[i]->clear();
        for (int j = 0; j < r[i].size(); ++j) {
            comboBoxes[i]->insertItem(j, r[i][j]);
        }
    }
}
void MainWindow::filterXml() {
    if (input.isEmpty())
        return;

    WantedService wanted;
    for (int i = 0; i < SERVICE_ATTRIBUTES_COUNT; ++i) {
        if (checkBoxes[i]->isChecked()) {
            wanted.attributes[i] = comboBoxes[i]->currentText();
        }
    }

    XmlDomFilterer filterer;
    filterer.setData(input, wanted);
    QString displayText = filterer.getResult();
    textEditor->setText(displayText);
}
