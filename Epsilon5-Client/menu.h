#pragma once

#include <QObject>
#include <QPainter>
#include <QVector>
#include <QString>
#include <QStaticText>
#include <QPoint>

class TApplication;
class TMenu;

class TMenuItem : public QObject
{
    Q_OBJECT
public:
    TMenuItem(QString str, const QPoint& pos, QObject *obj = 0) :
        QObject(obj), Str(str), Pos(pos) {}

    void paint(QPainter* p);

protected:
    bool event(QEvent*);

signals:
    void Clicked();
private:
    QStaticText Str;
    QPoint Pos;

    static QSize Size;
};

class TMenu : public QObject
{
    Q_OBJECT
public:
    explicit TMenu(QObject *parent = 0);
    void paint(QPainter *p);
    TApplication* Application();

    void Init();
    bool event(QEvent*ev);

private:
    TMenuItem* AddMenuItem(TMenuItem* item);
    QVector<TMenuItem*> Items;
};
