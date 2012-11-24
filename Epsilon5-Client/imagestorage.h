#pragma once

#include <QObject>
#include <QImage>
#include <QHash>

class TImageStorage : public QObject
{
    Q_OBJECT
public:
    TImageStorage(QObject *parent = 0);
    ~TImageStorage();
    void LoadAll();
    const QImage& GetImage(const QString& imageName);
private:
    void LoadImage(const QString& imageName, const QString& fileName);
private:
    QHash<QString, QImage*> Images;
};
