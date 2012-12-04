// imagecache.hpp
#include <QFileInfo>
#include <QPainter>
#include "imagecache.h"
//------------------------------------------------------------------------------
TImageCache::TImageCache(QObject* parent)
    : QObject(parent) {
}
//------------------------------------------------------------------------------
void TImageCache::append(const QString& fileName, const QSize& size) {
    generateIcons(QStringList(fileName), size);
}
//------------------------------------------------------------------------------
void TImageCache::clear() {
    mImages.clear();
}
//------------------------------------------------------------------------------
void TImageCache::generateIcons(const QStringList& fileNames, const QSize& size) {
    TImageCacheItem item;
    auto it = fileNames.constBegin();
    for (; it != fileNames.constEnd(); ++it) {
        const QString& file = (*it);
        item.fileName = file.trimmed();
        item.icon = generatePreviewIcon(item.fileName, size);
        item.name = QFileInfo(file).baseName();
        item.id = mImages.count();
        mImages.append(item);
    }
}
//------------------------------------------------------------------------------
QIcon TImageCache::generatePreviewIcon(const QString& fileName, const QSize& size) {
    QImage img(fileName);
    if (img.isNull()) {
        return nullIcon(size);
    }
    return QIcon(QPixmap::fromImage(img.scaled(size)));
}
//------------------------------------------------------------------------------
int TImageCache::count() {
    return mImages.count();
}
//------------------------------------------------------------------------------
TImageCacheItem TImageCache::operator [](int id) {
    return mImages.value(id);
}
//------------------------------------------------------------------------------
QIcon TImageCache::nullIcon(const QSize& size) {
    QPixmap px(size);
    QPainter p(&px);
    QRect rect(QPoint(0, 0), size);
    p.fillRect(rect, Qt::gray);
    p.drawRoundRect(rect);
    return QIcon(px);
}
//------------------------------------------------------------------------------
