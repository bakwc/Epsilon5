#pragma once
#include <QString>
#include <QIcon>
//------------------------------------------------------------------------------
namespace containers
{
//------------------------------------------------------------------------------
template<typename T>
class TTItem
{
protected:
    typedef quint32 TItemId;
public:
    TTItem()
        : mValid(true)
        , mId(0)
        , mResourceFile()
        , mPreviewIcon()
        , mInfo(T()) {
    }
    TTItem(const TTItem& item)
        : mValid(item.mValid)
        , mId(item.mId)
        , mResourceFile(item.mResourceFile)
        , mPreviewIcon(item.mPreviewIcon)
        , mInfo(item.mInfo)
    {}
    TTItem& operator =(const TTItem& item) {
        mValid = item.mValid;
        mInfo = item.mInfo;
        return *this;
    }

    bool isValid() const {
        return mValid;
    }

protected:
    const T& info() const {
        return mInfo;
    }

    T& info() {
        return mInfo;
    }

private:
    bool mValid;
    TItemId mId;
    QString mResourceFile;
    QIcon mPreviewIcon;
    T mInfo;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
