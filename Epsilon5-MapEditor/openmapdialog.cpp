// openmapdialog.cpp
#include <QFileDialog>
#include "openmapdialog.h"
#include "ui_openmapdialog.h"
//------------------------------------------------------------------------------
TOpenMapDialog::TOpenMapDialog(QWidget* parent)
    : QDialog(parent)
    , mUi(new Ui::OpenMapDialog) {
    mUi->setupUi(this);
    connect(this, SIGNAL(mapFolderSignal(QString)),
            mUi->mapFolder, SLOT(setText(QString)));
    connect(this, SIGNAL(objFolderSignal(QString)),
            mUi->objFolder, SLOT(setText(QString)));
}
//------------------------------------------------------------------------------
TOpenMapDialog::~TOpenMapDialog() {
    delete mUi;
}
//------------------------------------------------------------------------------
QString TOpenMapDialog::mapDir() {
    return mUi->mapFolder->text();
}
//------------------------------------------------------------------------------
QString TOpenMapDialog::objDir() {
    return mUi->objFolder->text();
}
//------------------------------------------------------------------------------
void TOpenMapDialog::on_toolButton_clicked() {
    QString f = QFileDialog::getExistingDirectory(this, "Set map directory");
    emit mapFolderSignal(f);
}
//------------------------------------------------------------------------------
void TOpenMapDialog::on_toolButton_2_clicked() {
    QString f = QFileDialog::getExistingDirectory(this, "Set objects directory");
    emit objFolderSignal(f);
}
//------------------------------------------------------------------------------
