#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>
#include "server.h"
#include "world.h"

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Application(int argc, char *argv[]);
    bool init();

signals:

public slots:

private:
    Server *_server;
    World *_world;
};

#endif // APPLICATION_H
