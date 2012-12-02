// openmapdialog.cpp
#include <QFileDialog>
#include "openmapdialog.h"
#include "ui_openmapdialog.h"
//------------------------------------------------------------------------------
OpenMapDialog::OpenMapDialog(QWidget* parent)
    : QDialog(parent)
    , mUi(new Ui::OpenMapDialog) {
    mUi->setupUi(this);
    connect(this, SIGNAL(mapFolderSignal(QString)),
            mUi->mapFolder, SLOT(setText(QString)));
    connect(this, SIGNAL(objFolderSignal(QString)),
            mUi->objFolder, SLOT(setText(QString)));
}
//------------------------------------------------------------------------------
OpenMapDialog::~OpenMapDialog() {
    delete mUi;
}
//------------------------------------------------------------------------------
QString OpenMapDialog::mapDir() {
    return mUi->mapFolder->text();
}
//------------------------------------------------------------------------------
QString OpenMapDialog::objDir() {
    return mUi->objFolder->text();
}
//------------------------------------------------------------------------------
void OpenMapDialog::on_toolButton_clicked() {
    QString f = QFileDialog::getExistingDirectory(this, "Set map directory");
    emit mapFolderSignal(f);
}
//------------------------------------------------------------------------------
void OpenMapDialog::on_toolButton_2_clicked() {
    QString f = QFileDialog::getExistingDirectory(this, "Set objects directory");
    emit objFolderSignal(f);
}
//------------------------------------------------------------------------------
