#pragma once
#include "Service.h"
#include <QApplication>
#include <QDebug>
#include <QDomDocument>
#include <QMessageBox>
#include <QString>
#include <QVector>

class ComboBoxPopulator {
public:
    ComboBoxPopulator() = default;
    void setData(const QString &input);
    QVector<QVector<QString>> getResult();
    bool checkIfErrorOccured();

private:
    void error(const QString &msg);
    bool errorOccured;
    QVector<QVector<QString>> result;
};
