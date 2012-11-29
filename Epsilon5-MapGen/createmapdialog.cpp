#include "createmapdialog.h"
#include "ui_createmapdialog.h"
#include <QFileDialog>

CreateMapDialog::CreateMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateMapDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(selectTexture(QString)), ui->texturePath, SLOT(setText(QString)));
    connect(this, SIGNAL(selectPath(QString)), ui->path, SLOT(setText(QString)));
    connect(this, SIGNAL(selectObjPath(QString)), ui->objPath, SLOT(setText(QString)));
}

CreateMapDialog::~CreateMapDialog()
{
    delete ui;
}

QString CreateMapDialog::mapName()
{
    return ui->name->text();
}

QSize CreateMapDialog::mapSize()
{
    return QSize(ui->width->text().toInt(), ui->height->text().toInt());
}

QImage CreateMapDialog::mapBackground()
{
    return QImage(ui->texturePath->text());
}

QString CreateMapDialog::mapPath()
{
    return ui->path->text();
}

QString CreateMapDialog::mapObjsPath()
{
    return ui->objPath->text();
}

void CreateMapDialog::on_selectTextureButton_clicked()
{
    QString f = QFileDialog::getOpenFileName(this, "Open map texture");
    emit selectTexture(f);
}

void CreateMapDialog::on_selectPathButton_clicked()
{
    QString f = QFileDialog::getExistingDirectory(this, "Set directory where will be create map's' folder");
    emit selectPath(f);
}

void CreateMapDialog::on_objPathButton_clicked()
{
    QString f = QFileDialog::getExistingDirectory(this, "Set directory where will be create map's' folder");
    emit selectObjPath(f);
}
