#include "imagestorage.h"
#include <QDebug>

ImageStorage::ImageStorage(QObject *parent) :
    QObject(parent)
{
}

void ImageStorage::loadImage(const QString &imageName, const QString &filename)
{
    QImage *image = new QImage(filename);
    _images.insert(imageName, image);
}

void ImageStorage::loadAll()
{
    loadImage("player", "mad.png");
    loadImage("enemy", "peka.png");
    loadImage("bullet", "arbuz.png");
}

QImage *ImageStorage::getImage(const QString &imageName)
{
    auto it=_images.find(imageName);
    if (it==_images.end())
    {
        qDebug() << "Error! Image not found" << imageName;
        exit(1);
    }
    return it.value();
}
