#include "menu.h"
#include "application.h"

const qint8 Y_OFFSET = 20;

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
    for (TMenuItem* menuItem : Items)
    {
      menuItem->paint(p);
    }
}

bool isInsideImage(const QPoint& point, const QRect& imageRect)
{
  return imageRect.contains(point, true);
}

void TMenuItem::paint(QPainter* p)
{
    QPoint cursorPos = Application()->GetMainDisplay()->GetCursorPos();

    QPoint pos = Application()->GetMainDisplay()->GetCenter() + Pos;
    pos.setX(pos.x() - Image.width() / 2);
    pos.setY(pos.y() - Image.height() / 2);

    QRect imageRect = Image.rect();
    imageRect.translate(pos.x(), pos.y());

    p->drawImage(pos, isInsideImage(cursorPos, imageRect) ? ImageHover : Image);
}

bool TMenuItem::event(QEvent* ev)
{
    if (ev->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mEv = (QMouseEvent*)ev;

        QPoint pos = Application()->GetMainDisplay()->GetCenter() + Pos;
        pos.setX(pos.x() - Image.width() / 2);
        pos.setY(pos.y() - Image.height() / 2);
        const QPoint& p = mEv->pos();

        QRect imageRect = Image.rect();
        imageRect.translate(pos.x(), pos.y());

        if (isInsideImage(p, imageRect))
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
                                      QPoint(0, -64),
                                      this));
    connect(item, SIGNAL(Clicked()), Application()->GetNetwork(), SLOT(Start()));

    item = AddMenuItem(new TMenuItem(
                                          Images->GetImage("menu-exit"),
                                          Images->GetImage("menu-exit-h"),
                                          QPoint(0, 64),
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
