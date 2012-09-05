/**
 * @file
 *  Файл с описанием класса MainDisplay
 */
#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include "../Eps5World/drawableObject.h"
#include "../Eps5Proto/Epsilon5.pb.h"

/**
 * @brief
 *  Отвечает за оторисовку игрового мира
 */
class MainDisplay : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

    /**
     * @brief
     * @return
     *  Текущее состояния клавиатуры (нажатые/отпущенные кнопки)
     */
    inline Epsilon5::Control *controlStatus() { return _controlStatus; }

    /**
     * @brief
     *  Запускает отрисовку графики
     */
    void start();
signals:

    /**
     * @brief
     *  Сигнал вызывается когда необходимо получить объекты для отрисовки
     */
    void requestRedrawObjects();

public slots:

    /**
     * @brief
     *  Отрисовывает переданные ей объекты
     * @param objects
     *  Объекты для отрисовки
     */
    void redraw(const DrawableObjects &objects);
private:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
private:
    QImage *_currentFrame;
    Epsilon5::Control *_controlStatus;
    QImage *_peka;
    QImage *_mad;
};

#endif // MAINDISPLAY_H
