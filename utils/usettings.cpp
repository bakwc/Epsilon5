#include <QFile>
#include <QTextStream>

#include "usettings.h"
#include "uexception.h"

#include <QDebug>

USettings::USettings(QObject *parent)
    : QObject(parent)
{
}

void USettings::Load(const QString& fname, const QStringList& required) {
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening file " + fname);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine().trimmed();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList acc = line.split("=");
        if (acc.size() != 2) {
            continue;
        }
        Parameters.insert(acc[0], acc[1]);
    }
    for (auto i = required.begin(); i != required.end(); i++) {
        if (Parameters.find(*i) == Parameters.end()) {
            throw UException("Required parameter " + *i + " not found");
        }
    }
}


UFromStringFormat USettings::GetParameter(const QString& parameter) {
    if (Parameters.find(parameter) == Parameters.end()) {
        throw UException("Parameter not found in config");
    }
    qDebug() << Parameters[parameter];
    return FromString(Parameters[parameter]);
}

