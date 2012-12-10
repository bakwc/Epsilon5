#include "storage/st_objectcontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TObjectContainer::TObjectContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
TObjectContainer::TObjectContainer(const TObjectContainer& container)
    : QObject(container.parent())
    , TTContainer(container)
{
}
//------------------------------------------------------------------------------
TObjectContainer& TObjectContainer::operator =(const TObjectContainer& container)
{
    TTContainer::operator =(container);
    return *this;
}
//------------------------------------------------------------------------------
void TObjectContainer::loadObjectList(const QString& objectList)
{
    clearItems();

    QFile file(objectList);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(objectList));
    }

    QTextStream stream(&file);
    TObjectItem object;
    while (!stream.atEnd()) {
        if (!object.unpack(stream.readLine())) {
            continue;
        }
        addItem(object);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TObjectContainer::saveObjectList(const QString& objectList) const
{
    QFile file(objectList);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(objectList));
    }
    QTextStream stream(&file);
    auto it = constBegin();
    for (; it != constEnd(); ++it) {
        const TObjectItem& object = *it;
        if (!object.isValid() ) {
            continue;
        }
        stream << object.pack() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
