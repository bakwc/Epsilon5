#include "../utils/uexception.h"
#include "../utils/ucolonsep.h"
#include "objects.h"

TObjects::TObjects(QObject* parent)
    : QObject(parent) {
}

void TObjects::LoadObjects(const QString& fileName) {
    UColonSep sep;
    sep.Load(fileName);

    for (size_t i = 0; i < sep.Rows(); i++) {
        QString objName = sep.Get(i, 4);
        size_t id = sep.Get(i, 0);
        QImage* image = new QImage("objects/" + objName + ".png");
        Images.insert(objName, image);
        ImagesById.insert(id, image);
    }
}

QImage* TObjects::GetImageById(size_t id) {
    if (ImagesById.find(id) == ImagesById.end()) {
        throw UException("Image not found");
    }
    return ImagesById[id];
}

QImage* TObjects::GetImageByName(const QString& imageName) {
    if (Images.find(imageName) == Images.end()) {
        throw UException("Image not found");
    }
    return Images[imageName];
}

TObjects::~TObjects() {
    for (auto i = Images.begin(); i != Images.end(); i++) {
        delete i.value();
    }
}
