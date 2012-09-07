#ifndef IMAGESTORAGE_H
#define IMAGESTORAGE_H

#include <QObject>
#include <QImage>
#include <QString>
#include <QMap>

class ImageStorage : public QObject
{
    Q_OBJECT
public:
    explicit ImageStorage(QObject *parent = 0);
    void loadAll();
    QImage *getImage(const QString &imageName);
    void loadImage(const QString &imageName, const QString &filename);
signals:
    
private:
    QMap<QString, QImage*> _images;
};

#endif // IMAGESTORAGE_H
