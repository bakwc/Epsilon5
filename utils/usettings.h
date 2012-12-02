#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>

#include "ucast.h"

class USettings: public QObject
{
    Q_OBJECT
public:
    USettings(QObject* parent = 0);
    virtual ~USettings() {}
    void Load(const QString& fname, const QStringList& required = QStringList());
    UFromStringFormat GetParameter(const QString& parameter);
private:
    QHash<QString, QString> Parameters;
};
