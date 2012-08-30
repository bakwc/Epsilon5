#include <QApplication>
#include "maindisplay.h"
#include "../Eps5Proto/Epsilon5.pb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDisplay w;
    w.show();
    
    return a.exec();
}
