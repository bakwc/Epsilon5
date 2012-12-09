#pragma once
#include <QHash>
#include <QDir>
#include "../../utils/uexception.h"
#include "storage/st_item_t.h"
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
template<typename T, typename Tinfo>
class TTContainer
{
protected:
    typedef TTItem<Tinfo> TItem;
    typedef typename TItem::TItemId TItemId;
    typedef QHash<TItemId, T> THashContainer;
    typedef typename THashContainer::const_iterator const_iterator;
    typedef typename THashContainer::iterator iterator;

public:
    explicit TTContainer()
        : mContainer(new THashContainer)
        , mLastValidId(0)
    {}

    TTContainer(const TTContainer& container)
        : mContainer(container.mContainer)
        , mLastValidId(container.mLastValidId) {
    }

    TTContainer& operator=(const TTContainer& container) {
        mContainer = container.mContainer;
        mLastValidId = container.mLastValidId;
        return *this;
    }

    int count() const {
        return mContainer->count();
    }

    TItemId addItem(const T& item) {
        ++mLastValidId;
        mContainer->insert(mLastValidId, item);
        TItem& mod = mContainer->operator [](mLastValidId);
        mod.setItemId(mLastValidId);
        return mLastValidId;
    }

    void removeItem(const TItem& item) {
        removeItem(item.itemId());
    }

    void removeItem(TItemId id) {
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

    const TItem& operator[](TItemId id) const {
        return item(id);
    }

    TItem& operator[](TItemId id) {
        return mContainer->operator [](id);
    }

    const TItem* item(TItemId id) const {
        return mContainer[id];
    }

    TItem* item(TItemId id) {
        return &mContainer->operator [](id);
    }

    // TODO: add function to reenumerate item IDs

private:
    THashContainer* mContainer;
    TItemId mLastValidId;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
