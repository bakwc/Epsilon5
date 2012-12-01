#pragma once

#include <QString>
#include <QList>
#include <QFile>
#include <exception>

namespace utils
{

struct Object {
    int id;
    int width;
    int height;
    bool dynamic;
    QString name;
};

struct MapLine {
    int x;
    int y;
    int angle;
    int id;
};

QList<Object> parseObjFile(QFile &f);
QList<MapLine> parseMapFile(QFile &f);

}
