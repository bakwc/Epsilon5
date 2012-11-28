#ifndef MAPPAINTER_H
#define MAPPAINTER_H

#include <QWidget>
#include <QSize>
#include <QImage>

class MapPainter : public QWidget
{
    Q_OBJECT
public:
    explicit MapPainter(QString name, QSize size, QImage background, QWidget *parent = 0);
    
signals:
    
public slots:
    
private:
    QString _name;
    QSize   _size;
    QImage  _background;
};

#endif // MAPPAINTER_H
