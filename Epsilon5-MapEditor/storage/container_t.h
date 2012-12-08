#pragma once
#include <QHash>
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
    {}
    TTContainer(const TTContainer& container)
        : mContainer(container.mContainer)
        , mLastValidId(container.mLastValidId)
    {}

    void count() {
        mContainer->count();
    }

    THashId addItem(const T& item) {
        mContainer->insert(mLastValidId, item);
        return mLastValidId;
    }

    void removeItem(THashId id, const T& item) {
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

private:
    THashContainer* mContainer;
    THashId mLastValidId;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
