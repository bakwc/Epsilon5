#ifndef OBJECTSEDITORFORM_HPP
#define OBJECTSEDITORFORM_HPP

#include <QWidget>

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

private slots:
    void loadAction();
    void saveAction();
    void clearAction();
    void showObjectsListMenu(QPoint pos);
    void showDataListMenu(QPoint pos);

private:

    QIcon genIconFromFile( const QString& fileName );

private:
    Ui::TObjectsEditorForm *ui;
    QMenu* mObjectsMenu;
};

#endif // OBJECTSEDITORFORM_HPP
