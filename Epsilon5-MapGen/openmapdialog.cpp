#include "openmapdialog.h"
#include "ui_openmapdialog.h"
#include <QFileDialog>

OpenMapDialog::OpenMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenMapDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(mapFolderSignal(QString)), ui->mapFolder, SLOT(setText(QString)));
    connect(this, SIGNAL(objFolderSignal(QString)), ui->objFolder, SLOT(setText(QString)));
}

OpenMapDialog::~OpenMapDialog()
{
    delete ui;
}

QString OpenMapDialog::mapDir()
{
    return ui->mapFolder->text();
}

QString OpenMapDialog::objDir()
{
    return ui->objFolder->text();
}

void OpenMapDialog::on_toolButton_clicked()
{
    QString f = QFileDialog::getExistingDirectory(this, "Set map directory");
    emit mapFolderSignal(f);
}

void OpenMapDialog::on_toolButton_2_clicked()
{
    QString f = QFileDialog::getExistingDirectory(this, "Set objects directory");
    emit objFolderSignal(f);
}
