// createmapdialog.cpp
#include <QFileDialog>
#include "createmapdialog.h"
#include "ui_createmapdialog.h"
//------------------------------------------------------------------------------
TCreateMapDialog::TCreateMapDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CreateMapDialog) {
    ui->setupUi(this);
    connect(this, SIGNAL(selectTexture(QString)),
            ui->texturePath, SLOT(setText(QString)));
    connect(this, SIGNAL(selectPath(QString)),
            ui->path, SLOT(setText(QString)));
    connect(this, SIGNAL(selectObjPath(QString)),
            ui->objPath, SLOT(setText(QString)));
}
//------------------------------------------------------------------------------
TCreateMapDialog::~TCreateMapDialog() {
    delete ui;
}
//------------------------------------------------------------------------------
QString TCreateMapDialog::mapName() {
    return ui->name->text();
}
//------------------------------------------------------------------------------
QSize TCreateMapDialog::mapSize() {
    return QSize(ui->width->text().toInt(), ui->height->text().toInt());
}
//------------------------------------------------------------------------------
QPixmap TCreateMapDialog::mapBackground() {
    return QPixmap(ui->texturePath->text());
}
//------------------------------------------------------------------------------
QString TCreateMapDialog::mapPath() {
    return ui->path->text();
}
//------------------------------------------------------------------------------
QString TCreateMapDialog::mapObjsPath() {
    return ui->objPath->text();
}
//------------------------------------------------------------------------------
void TCreateMapDialog::on_selectTextureButton_clicked() {
    QFileDialog fd;
    QString f = fd.getOpenFileName(this, "Open map texture");
    emit selectTexture(f);
}
//------------------------------------------------------------------------------
void TCreateMapDialog::on_selectPathButton_clicked() {
    QFileDialog fd;
    QString f = fd.getExistingDirectory(this,
                "Set directory where will be create map's' folder");
    emit selectPath(f);
}
//------------------------------------------------------------------------------
void TCreateMapDialog::on_objPathButton_clicked() {
    QFileDialog fd;
    QString f = fd.getExistingDirectory(this, "Set objects folder");
    emit selectObjPath(f);
}
//------------------------------------------------------------------------------
