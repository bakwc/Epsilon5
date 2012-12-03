#ifndef OBJECTSEDITORFORM_HPP
#define OBJECTSEDITORFORM_HPP

#include <QWidget>

namespace Ui {
class TObjectsEditorForm;
}

class TObjectsEditorForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit TObjectsEditorForm(QWidget *parent = 0);
    ~TObjectsEditorForm();
    
private:
    Ui::TObjectsEditorForm *ui;
};

#endif // OBJECTSEDITORFORM_HPP
