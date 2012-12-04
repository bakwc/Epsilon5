// mapcreator.cpp
#include <QDebug>
#include <QStringList>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include "../utils/uexception.h"
#include "graphicsview.h"
#include "mapitem.h"
#include "mapcreator.h"
//------------------------------------------------------------------------------
TMapCreator::TMapCreator(QString name, QSize size, QPixmap background,
        QString path, QString objPath, QWidget* parent)
    : QWidget(parent)
    , mName(name)
    , mSize(size)
    , mBackground(background)
    , mPath(path)
    , mObjectPath(objPath) {
    // Create map dir
    if (!mPath.mkdir(mName) || !mPath.cd(mName)) {
        throw UException("Cannot create " + mName + "dir");
    }
    openMapFiles();
    openObjectFile();
    createConfFile();
    init();
    closeFiles();
}
//------------------------------------------------------------------------------
TMapCreator::TMapCreator(QString path, QString objPath, QWidget* parent)
    : QWidget(parent)
    , mPath(path)
    , mObjectPath(objPath) {
    openMapFiles();
    openObjectFile();
    configureMapCreator();
    init();
    // Create items on scene
    QList<utils::TMapLine> ml = utils::parseMapFile(mFileObject);
    foreach(auto m, ml) {
        mView->addMapItem(m);
    }
    closeFiles();
}
//------------------------------------------------------------------------------
void TMapCreator::save() {
    QList<QGraphicsItem*> itemLst = mView->scene()->items();
    QByteArray arr;
    for (int i = 0; i < itemLst.size(); ++i) {
        TMapItem* mItem = dynamic_cast<TMapItem*>(itemLst.at(i));
        arr += serializeObj(mItem);
    }
    mFileObject.write(arr);
    if (!mFileObject.flush()) {
        qDebug() << "Save error";
    }
}
//------------------------------------------------------------------------------
QByteArray TMapCreator::serializeObj(TMapItem* item) {
    QByteArray arr;
    arr.append(QByteArray::number(item->posX()) + ':');
    arr.append(QByteArray::number(item->posY()) + ':');
    arr.append(QByteArray::number(item->angle()) + ':');
    arr.append(QByteArray::number(item->id()) + '\n');
    return arr;
}
//------------------------------------------------------------------------------
void TMapCreator::createConfFile() {
    QString str;
    str += "name=" + mName + '\n';
    str += "width=" + QString::number(mSize.width()) + '\n';
    str += "height=" + QString::number(mSize.height()) + '\n';
    mFileConfig.write(str.toLocal8Bit());
    mFileConfig.flush();
}
//------------------------------------------------------------------------------
void TMapCreator::openObjectFile() {
    mFileObjects.setFileName(mObjectPath.absoluteFilePath(OBJS_FILE));
    if (!mFileObjects.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw UException("Cannot open objects file");
    }
}
//------------------------------------------------------------------------------
void TMapCreator::openMapFiles() {
    mFileConfig.setFileName(mPath.absoluteFilePath(MAP_CONF_FILE));
    mFileObject.setFileName(mPath.absoluteFilePath(MAP_FILE));
    if (!mFileConfig.open(QIODevice::ReadWrite | QIODevice::Text) ||
            !mFileObject.open(QIODevice::ReadWrite | QIODevice::Text)) {
        throw UException("Cannot create map files");
    }
}
//------------------------------------------------------------------------------
void TMapCreator::configureMapCreator() {
    int q = 0; // validate
    while (!mFileConfig.atEnd()) {
        QString line = mFileConfig.readLine();
        QStringList l = line.split('=');
        if (l.at(0) == "name") {
            mName = l.at(1);
            q += 1;
        } else if (l.at(0) == "width") {
            mSize.setWidth(l.at(1).toInt());
            q += 10;
        } else if (l.at(0) == "height") {
            mSize.setHeight(l.at(1).toInt());
            q += 100;
        }
    }
    if (q != 111) {
        throw UException("Invalid config file");
    }
}
//------------------------------------------------------------------------------
void TMapCreator::init() {
    // Parse objects file and fill name and pixmap list
    mObjectsList = utils::parseObjFile(mFileObjects);
    QStringList objNames;
    foreach(const utils::TObject & obj, mObjectsList) {
        objNames << obj.name;
        mPixmapsList << QPixmap(mObjectPath.absoluteFilePath(obj.name));
    }
    // Create scene and setup
    mScene = new QGraphicsScene(0, 0, mSize.width(), mSize.height(), this);
    mView = new TGraphicsView(mScene, mObjectsList, mPixmapsList, parentWidget());
    // Right panel for select created objects
    QListWidget* itemSelector = new QListWidget(this);
    itemSelector->insertItems(0, objNames);
    itemSelector->setMaximumWidth(100);
    itemSelector->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(mView);
    layout->addWidget(itemSelector);
    setLayout(layout);
    connect(itemSelector, SIGNAL(currentRowChanged(int)),
            mView, SLOT(selectedItem(int)));
}
//------------------------------------------------------------------------------
void TMapCreator::closeFiles() {
    mFileConfig.close();
    mFileObject.close();
    mFileObjects.close();
}
//------------------------------------------------------------------------------
