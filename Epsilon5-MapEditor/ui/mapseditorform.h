// mapseditorform.h
#pragma once
#include <QWidget>
//------------------------------------------------------------------------------
class TMapContainer;
class QGraphicsScene;
class QGraphicsView;
//------------------------------------------------------------------------------
namespace Ui {
class TMapsEditorForm;
}
//------------------------------------------------------------------------------
class TMapsEditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit TMapsEditorForm(QWidget *parent = 0);
    ~TMapsEditorForm();

protected:
    void resizeEvent(QResizeEvent *);

private:
    Ui::TMapsEditorForm *ui;
    TMapContainer* mMaps;
    QGraphicsScene* mScene;
    QGraphicsView* mView;
};
//------------------------------------------------------------------------------
