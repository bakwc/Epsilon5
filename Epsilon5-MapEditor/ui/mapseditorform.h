// mapseditorform.h
#pragma once
#include <QWidget>
//------------------------------------------------------------------------------
class TMapContainer;
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

private:
    Ui::TMapsEditorForm *ui;
    TMapContainer* mMaps;
};
//------------------------------------------------------------------------------
