#pragma once

#include <QString>
#include <QList>
#include <QFile>

namespace utils
{

struct Object {
    int id;
    int width;
    int height;
    bool dynamic;
    QString name;
};

QList<Object> parseObjFile(QFile &f);

}
