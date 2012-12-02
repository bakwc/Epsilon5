#include "mapcreator.h"
#include <QDebug>
#include "graphicsview.h"
#include "mapitem.h"
#include <QStringList>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "../utils/uexception.h"


MapCreator::MapCreator(QString name, QSize size, QPixmap background, QString path, QString objPath, QWidget *parent) :
    QWidget(parent), _name(name), _size(size), _background(background), _path(path), _objPath(objPath)
{
    // Create map dir
    if ( !_path.mkdir(_name) || !_path.cd(_name) )
        throw UException("Cannot create " + _name + "dir");

    openMapFiles();
    openObjectFile();
    createConfFile();
    init();
}

MapCreator::MapCreator(QString path, QString objPath, QWidget *parent) :
    QWidget(parent), _path(path), _objPath(objPath)
{
    openMapFiles();
    openObjectFile();
    configureMapCreator();
    init();

    // Create items on scene
    QList<utils::MapLine> ml = utils::parseMapFile(_mObject);
    foreach(auto m, ml)
        _view->addMapItem(m);
}


void MapCreator::save()
{
    QList<QGraphicsItem*> itemLst = _view->scene()->items();
    QByteArray arr;

    for (int i=0; i < itemLst.size(); ++i) {
        MapItem *mItem = dynamic_cast<MapItem*>(itemLst.at(i));
        arr += serealizeObj(mItem);
    }

    _mObject.write(arr);
    if (!_mObject.flush())
        qDebug() << "Save error";
}

QByteArray MapCreator::serealizeObj(MapItem *item)
{
    QByteArray arr;
    arr.append(QByteArray::number(item->posX()) + ':');
    arr.append(QByteArray::number(item->posY()) + ':');
    arr.append(QByteArray::number(item->angle()) + ':');
    arr.append(QByteArray::number(item->id()) + '\n');
    return arr;
}


void MapCreator::createConfFile()
{
    QString str;
    str += "name=" + _name + '\n';
    str += "width=" + QString::number(_size.width()) + '\n';
    str += "height=" + QString::number(_size.height()) + '\n';

    _mConfig.write(str.toLocal8Bit());
    _mConfig.flush();
}

void MapCreator::openObjectFile()
{
    _objs.setFileName(_objPath.absoluteFilePath(OBJS_FILE));
    if ( !_objs.open(QIODevice::ReadOnly | QIODevice::Text) )
        throw UException("Cannot open objects file");
}

void MapCreator::openMapFiles()
{
    _mConfig.setFileName(_path.absoluteFilePath(MAP_CONF_FILE));
    _mObject.setFileName(_path.absoluteFilePath(MAP_FILE));

    if ( !_mConfig.open(QIODevice::ReadWrite | QIODevice::Text) ||
         !_mObject.open(QIODevice::ReadWrite | QIODevice::Text) )
        throw UException("Cannot create map files");
}

void MapCreator::configureMapCreator()
{
    int q = 0; // validate
    while(!_mConfig.atEnd()) {
        QString line = _mConfig.readLine();
        QStringList l = line.split('=');

        if (l.at(0) == "name") {
            _name = l.at(1);
            q += 1;
        } else if (l.at(0) == "width") {
            _size.setWidth(l.at(1).toInt());
            q += 10;
        } else if (l.at(0) == "height") {
            _size.setHeight(l.at(1).toInt());
            q += 100;
        }
    }

    if (q != 111)
        throw UException("Invalid config file");
}


void MapCreator::init()
{
    // Parse objects file and fill name and pixmap list
    _objsLst = utils::parseObjFile(_objs);
    QStringList objNames;
    foreach(const utils::Object &obj, _objsLst) {
        objNames << obj.name;
        _objPix << QPixmap(_objPath.absoluteFilePath(obj.name));
    }

    // Create scene and setup
    QGraphicsScene *_scene = new QGraphicsScene(0, 0, _size.width(), _size.height());
    _view = new GraphicsView(_scene, _objsLst, _objPix);

    // Right panel for select created objects
    QListWidget *itemSelector = new QListWidget;
    itemSelector->insertItems(0, objNames);
    itemSelector->setMaximumWidth(100);
    itemSelector->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_view);
    layout->addWidget(itemSelector);
    setLayout(layout);

    connect(itemSelector, SIGNAL(currentRowChanged(int)), _view, SLOT(selectedItem(int)));
}
