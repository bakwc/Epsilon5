#ifndef OBJECTSEDITORFORM_HPP
#define OBJECTSEDITORFORM_HPP

#include <QWidget>
#include "imagecache.hpp"

class QMenu;

namespace Ui {
class TObjectsEditorForm;
}

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

private:
    Ui::TObjectsEditorForm *ui;
    QMenu* mObjectsMenu;
    TImageCache mCache;
};

#endif // OBJECTSEDITORFORM_HPP
