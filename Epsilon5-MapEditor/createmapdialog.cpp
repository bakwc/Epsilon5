// createmapdialog.cpp
#include <QDebug>
#include <QFileDialog>
#include "global.h"
#include "createmapdialog.h"
#include "ui_createmapdialog.h"
//------------------------------------------------------------------------------
TCreateMapDialog::TCreateMapDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::CreateMapDialog)
{
    ui->setupUi(this);
    connect(this, SIGNAL(selectTexture(QString)),
            ui->texturePath, SLOT(setText(QString)));
    connect(this, SIGNAL(selectPath(QString)),
            ui->path, SLOT(setText(QString)));
    connect(this, SIGNAL(selectObjPath(QString)),
            ui->objPath, SLOT(setText(QString)));
    // Get from configuration
    ui->path->text() = Global::Settings()->GetMapsPath();
    ui->objPath->text() = Global::Settings()->GetObjectsPath();
}
//------------------------------------------------------------------------------
TCreateMapDialog::~TCreateMapDialog()
{
    delete ui;
}
//------------------------------------------------------------------------------
QString TCreateMapDialog::mapName()
{
    return ui->name->text();
}
//------------------------------------------------------------------------------
QSize TCreateMapDialog::mapSize()
{
    return QSize(ui->width->text().toInt(), ui->height->text().toInt());
}
//------------------------------------------------------------------------------
QPixmap TCreateMapDialog::mapBackground()
{
    return QPixmap(ui->texturePath->text());
}
//------------------------------------------------------------------------------
QString TCreateMapDialog::mapPath()
{
    return ui->path->text();
}
//------------------------------------------------------------------------------
QString TCreateMapDialog::mapObjsPath()
{
    return ui->objPath->text();
}
//------------------------------------------------------------------------------
void TCreateMapDialog::on_selectTextureButton_clicked()
{
    QFileDialog fd;
    QString f = fd.getOpenFileName(this, tr("Open map texture"),
                Global::Settings()->GetDataPath());
    Global::Settings()->SetDataPath(fd.directory().absolutePath());
    emit selectTexture(f);
}
//------------------------------------------------------------------------------
void TCreateMapDialog::on_selectPathButton_clicked()
{
    QString f = QFileDialog::getExistingDirectory(this,
                tr("Set directory where will be create maps folder"),
                Global::Settings()->GetMapsPath());
    Global::Settings()->SetMapsPath(f);
    emit selectPath(f);
}
//------------------------------------------------------------------------------
void TCreateMapDialog::on_objPathButton_clicked()
{
    QFileDialog fd;
    QString f = fd.getExistingDirectory(this,
                tr("Set objects folder"), Global::Settings()->GetObjectsPath());
    Global::Settings()->SetObjectsPath(fd.directory().absolutePath());
    emit selectObjPath(f);
}
//------------------------------------------------------------------------------
