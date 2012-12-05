// utils.h
#pragma once
#include <QString>
#include <QList>
#include <QFile>
#include <exception>
//------------------------------------------------------------------------------
namespace utils
{
//------------------------------------------------------------------------------
struct TObject {
    int id;
    int width;
    int height;
    bool dynamic;
    QString name;
};
//------------------------------------------------------------------------------
struct TMapLine {
    int x;
    int y;
    int angle;
    int id;
};
//------------------------------------------------------------------------------
QList<TObject> parseObjFile(QFile& f);
QList<TMapLine> parseMapFile(QFile& f);
//------------------------------------------------------------------------------
}
//------------------------------------------------------------------------------
