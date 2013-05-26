#pragma once

#include <QObject>
#include <QHash>
#include <QImage>
#include <QFile>
#include <QTextStream>
#include <QStringList>

class TObjects : public QObject {
    Q_OBJECT
public:
    explicit TObjects(QObject* parent = 0);
    ~TObjects();
    void LoadObjects(const QString& fileName);
    QImage* GetImageById(size_t id);
    QImage* GetImageByName(const QString& imageName);
private:
    QHash<QString, QImage*> Images;
    QHash<size_t, QImage*> ImagesById;
};
