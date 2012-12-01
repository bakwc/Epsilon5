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
    QString::number(10);

    createMapFiles();
    openObjectFile();
    createConfFile();
    init();
}


void MapCreator::save()
{
    QList<QGraphicsItem*> itemLst = _view->scene()->items();
    QByteArray arr;
    qDebug() << Q_FUNC_INFO;

    for (int i=0; i < itemLst.size(); ++i) {
        qDebug() << "dyn_cast";
        MapItem *mItem = dynamic_cast<MapItem*>(itemLst.at(i));
        qDebug() << "serealize";
        arr += serealizeObj(mItem);
        qDebug() << "write";
    }

    qDebug() << Q_FUNC_INFO << "end";

    _mObject.write(arr);
    if (!_mObject.flush())
        qDebug() << "Save error";
    _mObject.close();
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
    _mConfig.close();

//    _mObject.write("DATA");
//    _mObject.flush();
//    _mObject.close();
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
