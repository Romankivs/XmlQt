#pragma once
#include <QString>
#include <QVector>
#include <QDomDocument>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include "Service.h"

class ComboBoxPopulator {
public:
    ComboBoxPopulator() = default;
    void setData(const QString &input);
    QVector<QVector<QString>> getResult();
private:
    void error(const QString &msg);

    QVector<QVector<QString>> result;
};

