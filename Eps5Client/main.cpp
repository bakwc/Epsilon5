/**
 * @file
 * Основной файл приложения
 */
#include <QApplication>
#include "application.h"
#include "../Eps5Proto/Epsilon5.pb.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    if (!app.init())
        return 1;
    return app.exec();
}
