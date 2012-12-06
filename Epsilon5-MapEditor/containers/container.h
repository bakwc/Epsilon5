// container.h
#pragma once
#include <QObject>
#include <QStandardItemModel>
//------------------------------------------------------------------------------
template<typename Tmodel, typename Titem>
class TContainer : public QStandardItemModel
{
//    Q_OBJECT
public:
    TContainer(QObject* parent = 0);
    Titem* item(int row, int column = 0) const;
    QAbstractItemModel* model() const;

protected:
//    QStandardItemModel* mModel;
    Tmodel* mModel;
    quint32 mLastValidId;
};
//------------------------------------------------------------------------------
