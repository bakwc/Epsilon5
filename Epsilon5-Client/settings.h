#pragma once

#include <QObject>
#include <QString>
#include <QHash>

class TSettings: public QObject
{
    Q_OBJECT
public:
    TSettings(QObject* parent);
    void load(const QString& fname);
    QString GetNickname();
private:
    QHash<QString, QString> Parameters;
};
