#include "imagestorage.h"

TImageStorage::TImageStorage(QObject *parent) :
    QObject(parent)
{
}

void TImageStorage::LoadAll() {
    LoadImage("player", "mad.png");
    LoadImage("enemy", "peka.png");
    LoadImage("bullet", "arbuz.png");
}

const QImage& TImageStorage::GetImage(const QString& imageName) {
    auto it = Images.find(imageName);
    if (it == Images.end()) {
        // TODO: throw exception here
    }
    return *it.value();
}

void TImageStorage::LoadImage(const QString& imageName, const QString& filename)
{
    QImage *image = new QImage(filename);
    Images.insert(imageName, image);
}

TImageStorage::~TImageStorage() {
    for (auto i = Images.begin(); i != Images.end(); i++) {
        delete i.value();
    }
}
