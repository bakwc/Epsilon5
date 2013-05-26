#include "menu.h"
#include "application.h"


TMenu::TMenu(TImageStorage* images, QObject* parent)
    : QObject(parent)
    , Images(images)
{

}

TMenuItem* TMenu::AddMenuItem(TMenuItem* item)
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
    QPoint cursorpos = Application()->GetMainDisplay()->GetCursorPos();
    QPoint pos = Application()->GetMainDisplay()->GetCenter() + Pos;
    pos.setX(pos.x() - Image.width() / 2);
    pos.setY(pos.y() - Image.height() / 2);
    if (cursorpos.x() > pos.x() && cursorpos.y() > pos.y()
            && cursorpos.x() < pos.x() + Image.width()
            && cursorpos.y() < pos.y() + Image.height())
    {
        p->drawImage(pos, ImageHover);
    } else {
        p->drawImage(pos, Image);
    }
}

bool TMenuItem::event(QEvent* ev)
{
    if (ev->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mEv = (QMouseEvent*)ev;

        QPoint pos = Application()->GetMainDisplay()->GetCenter() + Pos;
        pos.setX(pos.x() - Image.width() / 2);
        pos.setY(pos.y() - Image.height() / 2);
        QPoint p = mEv->pos();

        if (p.x() > pos.x() && p.x() < pos.x() + Image.width()
                && p.y() > pos.y() && p.y() < pos.y() + Image.height())
        {
            emit Clicked();
            Application()->GetMainDisplay()->update();
        }
    }

    return QObject::event(ev);
}

TApplication *TMenuItem::Application()
{
    return (TApplication*)qApp;
}

TApplication* TMenu::Application() {
    return (TApplication*)qApp;
}

void TMenu::Init()
{
    TMenuItem* item = AddMenuItem(new TMenuItem(
                                      Images->GetImage("menu-connect"),
                                      Images->GetImage("menu-connect-h"),
                                      QPoint(0, -50),
                                      this));
    connect(item, SIGNAL(Clicked()), Application()->GetNetwork(), SLOT(Start()));

    item = AddMenuItem(new TMenuItem(
                                          Images->GetImage("menu-exit"),
                                          Images->GetImage("menu-exit-h"),
                                          QPoint(0, 50),
                                          this));
    connect(item, SIGNAL(Clicked()), Application(), SLOT(quit()));
}

bool TMenu::event(QEvent *ev)
{
    if (Application()->GetState() == ST_MainMenu) {
        for (int i = 0; i != Items.size(); ++i) {
            qApp->sendEvent(Items[i], ev);
        }
    }
    return false;
}
