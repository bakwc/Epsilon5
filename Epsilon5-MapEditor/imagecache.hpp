// imagecache.h
#include <QObject>
#include <QIcon>
#include <QVector>
#include <QStringList>
//------------------------------------------------------------------------------
struct TImageCacheItem
{
    QString fileName;
    QString name;
    QIcon icon;
    quint32 id;
    quint32 sourceWidth;
    quint32 sourceHeight;
};
//------------------------------------------------------------------------------
class TImageCache : public QObject
{
    Q_OBJECT
public:
    typedef QVector<TImageCacheItem> TImageCacheVector;

public:
    explicit TImageCache(QObject *parent = 0);
    void append(const QString& fileName, const QSize& size = QSize(64,64));
    void clear();
    void generateIcons(const QStringList& fileNames, const QSize& size);
    int count();

    TImageCacheItem operator[](int id);

private:
    QIcon generatePreviewIcon(const QString& fileName,
                const QSize& size);

private:
    TImageCacheVector mImages;
};
//------------------------------------------------------------------------------
