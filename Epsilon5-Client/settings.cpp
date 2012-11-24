#include <QFile>
#include <QTextStream>
#include <QStringList>

#include "settings.h"

TSettings::TSettings(QObject *parent)
    : QObject(parent)
{
    load("settings.ini");
}

void TSettings::load(const QString& fname) {
    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //throw TException("Error opening file");
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList acc = line.split("=");
        if (acc.size() != 2) {
            continue;
        }
        Parameters.insert(acc[0], acc[1]);
    }
    // TODO: check for parameters
}

QString TSettings::GetNickname() {
    if (Parameters.find("port") == Parameters.end()) {
        //throw TException("Parameter not found in config");
    }
    return Parameters["nickname"];
}
