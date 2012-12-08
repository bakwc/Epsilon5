#pragma once
#include <QHash>
#include <QStandardItemModel>
#include "../../utils/uexception.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
template<typename T>
class TTContainer
{
protected:
    typedef quint32 THashId;
    typedef QHash<THashId, T> THashContainer;
    typedef typename THashContainer::const_iterator const_iterator;
    typedef typename THashContainer::iterator iterator;
public:
    explicit TTContainer()
        : mContainer(new THashContainer)
        , mLastValidId(0)
        , mModel(new QStandardItemModel)
    {}
    TTContainer(const TTContainer& container)
        : mContainer(container.mContainer)
        , mLastValidId(container.mLastValidId)
        , mModel(new QStandardItemModel)
    {
        // Deep copy of model
        for (int i = 0; i < container.mModel->rowCount(); ++i) {
            QStandardItem* item = container.mModel->item(i);
            mModel->appendRow(item->clone());
        }
    }
    ~TTContainer()
    {
        if( !mModel )
            return;

        delete mModel;
    }

    int count() const {
        return mContainer->count();
    }

    THashId addItem(const T& item) {
        mContainer->insert(mLastValidId, item);
        return mLastValidId;
    }

    void removeItem(const T& item) {
        removeItem(item.id());
    }

    void removeItem(THashId id) {
        if (!mContainer->contains(id))
            throw UException(QString(Q_FUNC_INFO)
                    .append(":: not valid id passed:'%1'").arg(id));
        mContainer->remove(id);
    }

    void clearItems() {
        mContainer->clear();
        mLastValidId = 0;
    }

    // TODO: make add/remove functions for list of items

    const_iterator constBegin() const {
        return mContainer->constBegin();
    }

    const_iterator constEnd() const {
        return mContainer->constEnd();
    }

    iterator begin() {
        return mContainer->begin();
    }

    iterator end() {
        return mContainer->end();
    }

    const T& operator[](THashId id) const {
        return mContainer[id];
    }

    T& operator[](THashId id) {
        return mContainer[id];
    }

    QStandardItemModel* model() const {
        return mModel;
    }

    QStandardItemModel* model() {
        return mModel;
    }

protected:
    void addToModel(THashId id, const QString& text = QString(),
            const QIcon& icon = QIcon()) {
        QStandardItem* viewItem = QStandardItem(icon, text);
        viewItem->setData(id);
        mModel->appendRow(viewItem);
    }

    void refreshModel() {
        QStandardItem* viewItem;
        T item;
        for( int i = 0; i < mModel->rowCount(); ++i )
        {
            viewItem = mModel->item(i);
            if( !mContainer->contains(viewItem->data().toUInt()) ) {
                mModel->removeRow(i);
                --i;
            }
        }
    }

private:
    THashContainer* mContainer;
    THashId mLastValidId;
    QStandardItemModel* mModel;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
