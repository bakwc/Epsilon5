#include "../utils/uexception.h"
#include "imagestorage.h"

TImageStorage::TImageStorage(QObject* parent) :
    QObject(parent) {
}

void TImageStorage::LoadAll() {
    LoadImage("player", "resources/mad.png");
    LoadImage("enemy", "resources/peka.png");
    LoadImage("arbuz", "resources/arbuz.png");
    LoadImage("bullet", "resources/bullet.png");
    LoadImage("flag_t1", "resources/flag_t1.png");
    LoadImage("flag_t2", "resources/flag_t2.png");
    LoadImage("flag_tn", "resources/flag_tn.png");

    LoadImage("peka_t1", "resources/peka_t1");
    LoadImage("peka_t2", "resources/peka_t2");

    LoadImage("menu-connect", "resources/menu-connect.png");
    LoadImage("menu-connect-h", "resources/menu-connect-h.png");
    LoadImage("menu-exit", "resources/menu-exit.png");
    LoadImage("menu-exit-h", "resources/menu-exit-h.png");
}

const QImage& TImageStorage::GetImage(const QString& imageName) {
    auto it = Images.find(imageName);
    if (it == Images.end()) {
        throw UException("Image not found!");
    }
    return *it.value();
}

void TImageStorage::LoadImage(const QString& imageName, const QString& filename) {
    QImage* image = new QImage(filename);
    if (image->isNull()) {
        throw UException(QString("Loading failed: ") + filename);
    }
    Images.insert(imageName, image);
}

TImageStorage::~TImageStorage() {
    for (auto i = Images.begin(); i != Images.end(); i++) {
        delete i.value();
    }
}
