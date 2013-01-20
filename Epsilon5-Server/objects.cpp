#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "../utils/uexception.h"
#include "../utils/ucast.h"
#include "../utils/ucolonsep.h"
#include "objects.h"

#include <QDebug>

TObjects::TObjects(QObject *parent) :
    QObject(parent)
{
}

void TObjects::LoadObjects(const QString &fileName) {
    UColonSep sep;
    sep.Load(fileName);

    for (size_t i = 0; i < sep.Rows(); i++) {
        try {
        size_t id = sep.Get(i, 0);
        QPoint pos;
        pos.setX(sep.Get(i, 1));
        pos.setY(sep.Get(i, 2));
        bool isDynamic = sep.Get(i, 3);
        Objects.insert(id, pos);
        ObjectsIsDyn.insert(id, isDynamic);
        } catch (const UException& e) {
            qDebug() << "Problems with loading file: " << fileName;
        }
    }
}

QPoint TObjects::GetObjectSize(size_t id) {
    if (Objects.find(id) == Objects.end()) {
        throw UException(QString("Object not found: #") + ToString(id));
    }
    return Objects[id];
}

bool TObjects::IsDynamicObject(size_t id) {
    if (ObjectsIsDyn.find(id) == ObjectsIsDyn.end()) {
        throw UException(QString("Object not found: #") + ToString(id));
    }
    return ObjectsIsDyn[id];
}
