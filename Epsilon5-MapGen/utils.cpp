#include "utils.h"

namespace utils
{
QList<Object> parseObjFile(QFile &f)
{
    QList<Object> objs;

    while(!f.atEnd()) {
        Object obj;
        QByteArray arr = f.readLine();
        QList<QByteArray> arrList = arr.split(':');

        obj.id = arrList.at(0).toInt();
        obj.width = arrList.at(1).toInt();
        obj.height = arrList.at(2).toInt();
        obj.dynamic = arrList.at(3).toInt();
        QString str = arrList.at(4);
        obj.name = str.mid(0, str.indexOf('\n'));

        objs.push_back(obj);
    }

    return objs;
}
}
