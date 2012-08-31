/**
 * @file
 *  Файл с описанием класса MainDisplay
 */
#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QMainWindow>
#include "../Eps5World/drawableObject.h"

namespace Ui {
class MainDisplay;
}

/**
 * @brief Класс MainDisplay
 *  Отвечает за оторисовку игрового мира
 */
class MainDisplay : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainDisplay(QWidget *parent = 0);
    ~MainDisplay();
public slots:

    /**
     * @brief redraw
     *  Отрисовывает переданные ей объекты
     * @param objects
     *  Объекты для отрисовки
     */
    void redraw(const DrawableObjects &objects);
private:
    Ui::MainDisplay *ui;
};

#endif // MAINDISPLAY_H
