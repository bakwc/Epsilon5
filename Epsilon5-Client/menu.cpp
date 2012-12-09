#include "menu.h"
#include <QStaticText>
#include "application.h"
#include <QEvent>
#include <QMouseEvent>
#include <QBrush>
#include <QDebug>

QSize TMenuItem::Size = QSize(100, 50);

TMenu::TMenu(QObject *parent)
    : QObject(parent)
{

}

TMenuItem *TMenu::AddMenuItem(TMenuItem *item)
{
    Items.push_back(item);
    return item;
}

void TMenu::paint(QPainter* p)
{
    p->fillRect(0, 0, 1920, 1080, Qt::black);
    for (int i = 0; i != Items.size(); ++i) {
        Items[i]->paint(p);
    }
}


void TMenuItem::paint(QPainter* p)
{
    p->setFont(QFont("Arial", 22));
    p->setBrush(QBrush(Qt::white));
    p->setPen(Qt::white);
    p->drawStaticText(Pos, Str);
}

bool TMenuItem::event(QEvent* ev)
{
    if (ev->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mEv = (QMouseEvent*)ev;

        QPoint p = mEv->pos();

        if (p.x() > Pos.x() && p.x() < Pos.x() + Size.width()
                && p.y() > Pos.y() && p.y() < Pos.y() + Size.height()) {
            emit Clicked();
        }
    }

    return QObject::event(ev);
}

TApplication* TMenu::Application() {
    return (TApplication*)qApp;
}

void TMenu::Init()
{
    QPoint center = Application()->GetMainDisplay()->GetCenter();
    TMenuItem *item = AddMenuItem(new TMenuItem("Connect", QPoint(center.x(), center.y() - 50), this));
    connect(item, SIGNAL(Clicked()), Application()->GetNetwork(), SLOT(Start()));

    item = AddMenuItem(new TMenuItem("Exit", QPoint(center.x(), center.y() + 50), this));
    connect(item, SIGNAL(Clicked()), Application(), SLOT(quit()));
}

bool TMenu::event(QEvent *ev)
{
    for (int i = 0; i != Items.size(); ++i) {
        qApp->sendEvent(Items[i], ev);
    }
    return false;
}
