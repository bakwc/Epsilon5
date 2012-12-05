#pragma once
#include <QWidget>
#include <QModelIndex>
#include "imagecache.h"
#include "containers/stuctures.h"
//------------------------------------------------------------------------------
class QMenu;
class QStandardItemModel;
//------------------------------------------------------------------------------
namespace Ui
{
class TObjectsEditorForm;
}
//------------------------------------------------------------------------------
class TObjectsEditorForm : public QWidget
{
    Q_OBJECT
public:
    explicit TObjectsEditorForm(QWidget* parent = 0);
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
    void addButtonAction(QModelIndex index);

    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_objectsListView_clicked(QModelIndex index);
    void on_settingsApplyButton_clicked();

private:
    Ui::TObjectsEditorForm* ui;
    TImageCache mDataCache;
    QStandardItemModel* mObjects;
    quint32 mLastUsedId;
};
//------------------------------------------------------------------------------
