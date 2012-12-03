// imagecache.hpp
#include <QFileInfo>
#include "imagecache.hpp"
//------------------------------------------------------------------------------
TImageCache::TImageCache(QObject *parent)
    : QObject(parent)
{
}
//------------------------------------------------------------------------------
void TImageCache::append(const QString &fileName, const QSize& size)
{
    generateIcons(QStringList(fileName), size);
}
//------------------------------------------------------------------------------
void TImageCache::clear()
{
    mImages.clear();
}
//------------------------------------------------------------------------------
void TImageCache::generateIcons(const QStringList &fileNames, const QSize& size)
{
    TImageCacheItem item;
    auto it = fileNames.constBegin();
    for( ; it != fileNames.constEnd(); ++it )
    {
        const QString& file = (*it);
        item.fileName = file.trimmed();
        item.icon = generatePreviewIcon(item.fileName, size);
        item.name = QFileInfo(file).baseName();
        item.id = mImages.count();
        mImages.append(item);
    }
}
//------------------------------------------------------------------------------
QIcon TImageCache::generatePreviewIcon(const QString& fileName, const QSize& size)
{
    return QIcon(QPixmap::fromImage(QImage(fileName).scaled(size)));
}
//------------------------------------------------------------------------------
int TImageCache::count()
{
    return mImages.count();
}
//------------------------------------------------------------------------------
TImageCacheItem TImageCache::operator [](int id)
{
    return mImages[id];
}
