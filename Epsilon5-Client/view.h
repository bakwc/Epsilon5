#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QQueue>
#include <QHash>
#include <QSet>
#include "../Epsilon5-Proto/Epsilon5.pb.h"

class TApplication;
class QGraphicsScene;
class TMap;
class TObjects;
class TImageStorage;
class TScene;

class View : public QGraphicsView
{
    Q_OBJECT

    TScene* Scene;

public:
    explicit View(TApplication *app, QWidget *parent = 0);
    void Init();
    ~View();



    void timerEvent(QTimerEvent *);
    
signals:
    
public slots:
    void RedrawWorld();

private:
    TApplication*       App;
    TImageStorage*      Images;
    TMap*               Map;
    TObjects*           Objects;
    Epsilon5::Control   Control;
    QQueue<Epsilon5::World> PacketQueue;
    const Epsilon5::World*  CurrentWorld;
    QHash<size_t, QString>  PlayerNames;
    ///
    QSet<qint32>           PlayerContains;
    QSet<qint32>           ObjectContains;
};

#endif // VIEW_H
