// mapcreator.h
#pragma once
#include <stdexcept>
#include <QWidget>
#include <QSize>
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QPixmap>
#include "mapitem.h"
#include "utils.h"
#include "graphicsview.h"
//------------------------------------------------------------------------------
class TMapCreator : public QWidget {
    Q_OBJECT
private:
    constexpr static const char* OBJS_FILE     = "objects.txt";
    constexpr static const char* MAP_FILE      = "objects.txt";
    constexpr static const char* MAP_CONF_FILE = "config.ini";

public:
    typedef QList<utils::TObject> TObjectsList;
    typedef QList<QPixmap> TPixmapsList;

public:
    explicit TMapCreator(QString name, QSize size, QPixmap background,
            QString path, QString objPath, QWidget* parent = 0);
    explicit TMapCreator(QString path, QString objPath, QWidget* parent = 0);

public slots:
    void save();

private:
    QByteArray serealizeObj(TMapItem* item);
    void createConfFile();
    void openObjectFile();
    void openMapFiles();
    void configureMapCreator();
    void init();
    void closeFiles();

private:
    QString mName;
    QSize mSize;
    QPixmap mBackground;
    QDir mPath;
    QDir mObjectPath;
    QFile mFileConfig;
    QFile mFileObject;
    QFile mFileObjects;
    TGraphicsView* mView;
    TObjectsList mObjectsList;
    TPixmapsList mPixmapsList;
};
//------------------------------------------------------------------------------
