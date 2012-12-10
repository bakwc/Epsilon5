#include "st_sourceobjectcontainer.h"
//------------------------------------------------------------------------------
using namespace containers;
//------------------------------------------------------------------------------
TSObjectContainer::TSObjectContainer(QObject* parent)
    : QObject(parent)
    , TTContainer()
{
}
//------------------------------------------------------------------------------
TSObjectContainer::TSObjectContainer(const TSObjectContainer& container)
    : QObject(container.parent())
    , TTContainer(container)
{
}
//------------------------------------------------------------------------------
TSObjectContainer& TSObjectContainer::operator =(const TSObjectContainer& container)
{
    TTContainer::operator =(container);
    return *this;
}
//------------------------------------------------------------------------------
void TSObjectContainer::loadObjectList(const QString& objectList,
        const QDir& baseDirectory)
{
    clearItems();

    QFile file(objectList);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(objectList));
    }
    QTextStream stream(&file);
    TSObjectItem object;
    while (!stream.atEnd()) {
        if (!object.unpack(stream.readLine())) {
            continue;
        }
        if (!object.resourceName().isEmpty()) {
            object.setResourceFile(baseDirectory.absolutePath() + "/"
                    + object.resourceName() + ".png");
        }
        addItem(object);
    }
    file.close();
}
//------------------------------------------------------------------------------
void TSObjectContainer::saveObjectList(const QString& objectList) const
{
    QFile file(objectList);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        throw UException(QString(Q_FUNC_INFO)
                .append(":: open file error: '%1'").arg(objectList));
    }
    QTextStream stream(&file);
    auto it = constBegin();
    for (; it != constEnd(); ++it) {
        const TSObjectItem& object = (*it);
        if (!object.isValid()) {
            continue;
        }
        stream << object.pack() << "\n";
    }
    file.close();
}
//------------------------------------------------------------------------------
