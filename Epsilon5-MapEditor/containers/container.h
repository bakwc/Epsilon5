// container.h
#pragma once
#include <QObject>
#include <QStandardItemModel>
//------------------------------------------------------------------------------
namespace oldcontainers
{
//------------------------------------------------------------------------------
class TContainer : public QObject
{
    Q_OBJECT
public:
    TContainer(QObject* parent = 0);
    TContainer(const TContainer& container);
    ~TContainer();
    TContainer& operator =(const TContainer& container);

    QStandardItemModel* model() const;
    void clear();
    int count() const;

protected:
    QStandardItemModel* mModel;
    quint32 mLastValidId;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
