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
    createMapFiles();
    openObjectFile();
    createConfFile();
    init();
}


void MapCreator::selectedItem(int item)
{
    const utils::Object &obj = _objsLst.at(item);
    qDebug() << obj.name;
    _view->setItem(obj.name, QSizeF(obj.width, obj.height), _objPix.at(item));
}


void MapCreator::createConfFile()
{
    QString str;
    str += "name=" + _name + '\n';
    str += "width=" + QString::number(_size.width()) + '\n';
    str += "height=" + QString::number(_size.height()) + '\n';

    _mConfig.write(str.toLocal8Bit());
}

void MapCreator::openObjectFile()
{
    _objs.setFileName(_objPath.absoluteFilePath(OBJS_FILE));
    if ( !_objs.open(QIODevice::ReadOnly | QIODevice::Text) )
        throw UException("Cannot open objects file");
}

void MapCreator::createMapFiles()
{
    // Create map dir
    if ( !_path.mkdir(_name) || !_path.cd(_name) )
        throw UException("Cannot create " + _name + "dir");

    // Create map files
    _mConfig.setFileName(_path.absoluteFilePath(MAP_CONF_FILE));
    _mObject.setFileName(_path.absoluteFilePath(MAP_FILE));

    if ( !_mConfig.open(QIODevice::ReadWrite | QIODevice::Text) ||
         !_mObject.open(QIODevice::ReadWrite | QIODevice::Text) )
        throw UException("Cannot create map files");
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

    // Create scene and setup it's size
    QGraphicsScene *_scene = new QGraphicsScene(0, 0, _size.width(), _size.height());
    _view = new GraphicsView(_scene);

    // Right panel for select created objects
    QListWidget *itemSelector = new QListWidget;
    itemSelector->insertItems(0, objNames);
    itemSelector->setMaximumWidth(100);
    itemSelector->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_view);
    layout->addWidget(itemSelector);
    setLayout(layout);

    connect(itemSelector, SIGNAL(currentRowChanged(int)), this, SLOT(selectedItem(int)));
}
