#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QQueue>
#include <QHash>
#include "../Epsilon5-Proto/Epsilon5.pb.h"

class TApplication;
class QGraphicsScene;
class TMap;
class TObjects;
class TImageStorage;

class View : public QGraphicsView
{
    Q_OBJECT

    QGraphicsScene*     Scene;

public:
    explicit View(TApplication *app, QWidget *parent = 0);
    void Init();
    ~View();
    
signals:
    
public slots:

private:
    TApplication*       App;
    TImageStorage*      Images;
    TMap*               Map;
    TObjects*           Objects;
    Epsilon5::Control   Control;
    QQueue<Epsilon5::World> PacketQueue;
    const Epsilon5::World*  CurrentWorld;
    QHash<size_t, QString>  PlayerNames;
};

#endif // VIEW_H
