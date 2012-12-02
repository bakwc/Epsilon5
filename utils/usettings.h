#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QHash>
#include <QMap>

class USettings: public QObject
{
    Q_OBJECT
public:
    typedef QHash<QString, QString> TParametersHash;

public:
    USettings(QObject* parent = 0);
    virtual ~USettings() {}
    void Load(const QString& fname, const QStringList& required = QStringList());
    void LoadDefaults(const TParametersHash& paramsList);
    QString GetParameter(const QString& parameter);
private:
    TParametersHash Parameters;
};
