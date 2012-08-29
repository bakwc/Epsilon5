#include <QApplication>
#include "maindisplay.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDisplay w;
    w.show();
    
    return a.exec();
}
