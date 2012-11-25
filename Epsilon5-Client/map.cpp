#include <QFile>
#include <QTextStream>
#include <QHash>
#include <QImage>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include "map.h"


TMap::TMap(const QString &fileName, QObject *parent) :
    QObject(parent)
{
    QFile file(QDir::currentPath() + "/" +fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //throw TException("Error opening file");
        //qDebug() << "Error loading file!!!";
    }
    QHash<QString, QString> parameters;
    QTextStream in(&file);
    QString line = "";
    while (!line.isNull()) {
        line = in.readLine();
        //qDebug() << line;
        if (line.isEmpty() || line[0] == '#') {
            continue;
        }
        QStringList acc = line.split("=");
        if (acc.size() != 2) {
            continue;
        }
        parameters.insert(acc[0], acc[1]);
    }
    Width = parameters["width"].toInt();
    Height = parameters["height"].toInt();
    QString imgFileName = QDir::currentPath() + "/" + parameters["background"];
    Background = new QImage(imgFileName);
    //qDebug() << imgFileName;
}

TMap::~TMap()
{
    if( Background )
        delete Background;
}

QImage TMap::GetFrame(int x, int y, const QSize& frameSize) {
    int centerX = Background->width() / 2;
    int centerY = Background->height() / 2;
    int newPekaPosX = centerX + x;
    int newPekaPosY = centerY + y;
    int cutX = newPekaPosX - frameSize.width() / 2;
    int cutY = newPekaPosY - frameSize.height() / 2;
    return Background->copy(cutX, cutY, frameSize.width(), frameSize.height());
    //return *Background;
}
