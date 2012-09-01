/**
 * @file
 *  Файл с описанием класса MainDisplay
 */
#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QMainWindow>
#include <QGLWidget>
#include <QtOpenGL>
#include "../Eps5World/drawableObject.h"


/**
 * @brief
 *  Отвечает за оторисовку игрового мира
 */
class MainDisplay : public QGLWidget
{
    Q_OBJECT
    
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();

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
private:
    QImage *_currentFrame;
};

#endif // MAINDISPLAY_H
