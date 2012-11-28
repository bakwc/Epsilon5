#include "createmapdialog.h"
#include "ui_createmapdialog.h"
#include <QFileDialog>

CreateMapDialog::CreateMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateMapDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(selectTexture(QString)), ui->texturePath, SLOT(setText(QString)));
}

CreateMapDialog::~CreateMapDialog()
{
    delete ui;
}

void CreateMapDialog::on_selectTextureButton_clicked()
{
    QString f = QFileDialog::getOpenFileName(this, "Open map texture");
    emit selectTexture(f);
}
