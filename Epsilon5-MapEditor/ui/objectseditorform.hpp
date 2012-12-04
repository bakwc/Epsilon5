#pragma once

#include <QWidget>
#include <QModelIndex>
#include "imagecache.hpp"
#include "containers/object.h"
//------------------------------------------------------------------------------
class QMenu;
//------------------------------------------------------------------------------
namespace Ui {
class TObjectsEditorForm;
}
//------------------------------------------------------------------------------
class TObjectsEditorForm : public QWidget
{
    Q_OBJECT
public:
    explicit TObjectsEditorForm(QWidget *parent = 0);
    ~TObjectsEditorForm();

public slots:
    void updateDataList();
    void createDataList();

private slots:
    void loadAction();
    void saveAction();
    void clearAction();
    void showObjectsListMenu(QPoint pos);
    void showDataListMenu(QPoint pos);
    void showImageInfo(QModelIndex index);
    void on_addButton_clicked();
    void addButtonAction(QModelIndex index);

private:
    Ui::TObjectsEditorForm *ui;
    QMenu* mObjectsMenu;
    TImageCache mDataCache;
    TObjectContainer mObjects;
};
//------------------------------------------------------------------------------
