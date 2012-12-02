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
    void Save(const QString& fname, bool keepOrigin = false);
    QString GetParameter(const QString& parameter);
    void SetParameter(const QString& parameter, const QString& value);
private:
    TParametersHash Parameters;
};
