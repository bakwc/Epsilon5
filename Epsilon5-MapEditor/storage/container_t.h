#pragma once
#include <QHash>
#include <QStandardItemModel>
#include "../../utils/uexception.h"
#include "storage/item_t.h"
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
        ++mLastValidId;
        mContainer->insert(mLastValidId, item);
        T& mod = mContainer->operator [](mLastValidId);
        mod.setId(mLastValidId);
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
        refreshModel();
    }

    void clearItems() {
        mContainer->clear();
        mLastValidId = 0;
        refreshModel();
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

    const T& operator[](QModelIndex viewIndex) const {
        const QStandardItem* viewItem = mModel->itemFromIndex(viewIndex);
        return mContainer[viewItem->data().toUInt()];
    }

    T& operator[](QModelIndex viewIndex) {
        QStandardItem* viewItem = mModel->itemFromIndex(viewIndex);
        return mContainer->operator [](viewItem->data().toUInt());
    }

    const T& item(QModelIndex viewIndex) const {
        return operator[](viewIndex);
    }

    T& item(QModelIndex viewIndex) {
        return operator[](viewIndex);
    }

    QStandardItemModel* model() const {
        return mModel;
    }

    QStandardItemModel* model() {
        return mModel;
    }

    void setItemInfo(const QModelIndex& index, const QString& text = QString(),
            const QIcon& icon = QIcon()) {
        QStandardItem* viewItem = mModel->itemFromIndex(index);
        viewItem->setIcon(icon);
        viewItem->setText(text);
    }

    void updateView()
    {
        QModelIndex index;
        for( int i = 0; i < mModel->rowCount(); ++i )
        {
            index = mModel->index(i, 0);
            setItemInfo(index, item(index).pack(), item(index).previewIcon());
        }
    }

protected:
    void addToModel(THashId id, const QString& text = QString(),
            const QIcon& icon = QIcon()) {
        QStandardItem* viewItem = new QStandardItem(icon, text);
        viewItem->setData(id);
        viewItem->setEditable(false);
        mModel->appendRow(viewItem);
    }
protected:
    void refreshModel() {
        QStandardItem* viewItem;
        T item;
        for( int i = 0; i < mModel->rowCount(); ++i )
        {
            viewItem = mModel->item(i);
            if( !mContainer->contains(viewItem->data().toUInt()) ) {
                mModel->removeRow(i);
                --i;
                continue;
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
