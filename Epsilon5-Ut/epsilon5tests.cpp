#include <QtTest/QtTest>

#include "../Epsilon5-Server/calcs.h"

class Epsilon5Tests: public QObject
{
    Q_OBJECT
private slots:
    void GetDirectionTests();
};

void Epsilon5Tests::GetDirectionTests() {
    {
        QPointF a(0, 0);
        QPointF b(1, 0);
        QCOMPARE(GetDirection(a, b), QPointF(1, 0));
    }
    {
        QPointF a(2, 1);
        QPointF b(1, 1);
        QCOMPARE(GetDirection(a, b), QPointF(-1, 0));
    }
    {
        QPointF a(-2, 0);
        QPointF b(-3, 0);
        QCOMPARE(GetDirection(a, b), QPointF(-1, 0));
    }
}


QTEST_MAIN(Epsilon5Tests)
#include "epsilon5tests.moc"
