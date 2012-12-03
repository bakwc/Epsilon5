#include "objectseditorform.hpp"
#include "ui_objectseditorform.h"

TObjectsEditorForm::TObjectsEditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TObjectsEditorForm)
{
    ui->setupUi(this);
}

TObjectsEditorForm::~TObjectsEditorForm()
{
    delete ui;
}
