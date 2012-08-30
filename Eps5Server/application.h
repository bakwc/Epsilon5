#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // APPLICATION_H
