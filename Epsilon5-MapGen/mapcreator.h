#ifndef MAPPAINTER_H
#define MAPPAINTER_H

#include <QWidget>
#include <QSize>
#include <QImage>
#include <QDir>
#include <QFile>
#include <QGraphicsScene>

class MapCreator : public QWidget
{
    Q_OBJECT

    constexpr static const char* OBJS_FILE     = "objects.txt";
    constexpr static const char* MAP_FILE      = "objects.txt";
    constexpr static const char* MAP_CONF_FILE = "config.ini";

public:
    explicit MapCreator(QString name, QSize size, QImage background, QString path, QString objPath, QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QString _name;
    QSize   _size;
    QImage  _background;
    QDir    _path, _objPath;
    QFile   _mConfig, _mObject, _objs;

    QGraphicsScene  *_scene;

    QByteArray createConfFile();
};

#endif // MAPPAINTER_H
