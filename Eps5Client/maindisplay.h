#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QMainWindow>

namespace Ui {
class MainDisplay;
}

class MainDisplay : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();
    
private:
    Ui::MainDisplay *ui;
};

#endif // MAINDISPLAY_H
