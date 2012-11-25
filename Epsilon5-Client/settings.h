#pragma once

#include <QObject>
#include <QString>
#include <QHash>

#include "../utils/usettings.h"

class TSettings: public USettings
{
    Q_OBJECT
public:
    TSettings(QObject* parent);
    QString GetNickname();
};
