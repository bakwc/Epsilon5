#ifndef MAPPAINTER_H
#define MAPPAINTER_H

#include <QWidget>
#include <QSize>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QStringList>
#include "graphicsview.h"
#include "utils.h"
#include <stdexcept>
#include <QPixmap>
#include "mapitem.h"


class MapCreator : public QWidget
{
    Q_OBJECT

    constexpr static const char* OBJS_FILE     = "objects.txt";
    constexpr static const char* MAP_FILE      = "objects.txt";
    constexpr static const char* MAP_CONF_FILE = "config.ini";

public:
    explicit MapCreator(QString name, QSize size, QPixmap background, QString path,
                        QString objPath, QWidget *parent = 0);
    
signals:
    
public slots:
    void save();
    
private:
    QString _name;
    QSize   _size;
    QPixmap  _background;
    QDir    _path, _objPath;
    QFile   _mConfig, _mObject, _objs;

    GraphicsView    *_view;
    QList<utils::Object> _objsLst;
    QList<QPixmap>      _objPix;

private:
    QByteArray serealizeObj(MapItem *item);
    void createConfFile();
    void openObjectFile();
    void createMapFiles();
    void init();
};

#endif // MAPPAINTER_H
