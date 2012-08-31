#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QMainWindow>
#include "../Eps5World/drawableObject.h"

namespace Ui {
class MainDisplay;
}

class MainDisplay : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();
public slots:
    void redraw(const DrawableObjects &objects);
private:
    Ui::MainDisplay *ui;
};

#endif // MAINDISPLAY_H
