#include <QFile>
#include <QTextStream>
#include <QStringList>
#include "../utils/uexception.h"
#include "objects.h"

TObjects::TObjects(QObject *parent)
    : QObject(parent)
{
}

void TObjects::LoadObjects(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Error opening file " + fileName);
    }
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList objParams = line.split(":");
        if (objParams.size() != 5) {
            throw UException("Error loading objects from " + fileName);
        }
        QString objName = objParams[4];

        bool ok = true;
        size_t id = objParams[0].toInt(&ok);
        if (!ok) {
            throw UException("Error loading objects from " + fileName);
        }

        QImage *image = new QImage("objects/" + objName + ".png");
        Images.insert(objName, image);
        ImagesById.insert(id, image);
    }
}

QImage* TObjects::GetImageById(size_t id) {
    if (ImagesById.find(id) == ImagesById.end()) {
        throw UException("Image not found. Image id:" + QString::number(id));
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
