#pragma once
#include <QObject>
#include <QStandardItemModel>
//------------------------------------------------------------------------------
class TContainer : public QObject
{
    Q_OBJECT
public:
    TContainer(QObject* parent = 0);

protected:
    QStandardItemModel* mModel;
    quint32 mLastValidId;
};
//------------------------------------------------------------------------------
