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
public:
    typedef quint32 TItemId;

public:
    TTItem(const T& info = T())
        : mValid(false)
        , mId(0)
        , mResourceFile()
        , mPreviewIcon()
        , mInfo(info) {
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

    TItemId id() const {
        return mId;
    }

    void setId(TItemId id) {
        mId = id;
    }

    bool isValid() const {
        return mValid;
    }

    const QIcon& previewIcon() const {
        return mPreviewIcon;
    }

    void setPreviewIcon(const QPixmap& pixmap) {
        mPreviewIcon = QIcon(QPixmap(pixmap));
    }

    QString resourceFile() const {
        return mResourceFile;
    }

    void setResourceFile(const QString& resourceFile) {
        mResourceFile = resourceFile;
    }

    const T& info() const {
        return mInfo;
    }

protected:
    T& info() {
        return mInfo;
    }

protected:
    bool mValid;
    TItemId mId;
    QString mResourceFile;
    QIcon mPreviewIcon;
    T mInfo;
};
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
