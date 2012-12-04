// configuration.cpp
#include <QFileDialog>
#include "global.h"
#include "configurationdialog.h"
#include "ui_configurationdialog.h"
//------------------------------------------------------------------------------
TConfigurationDialog::TConfigurationDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::TConfigurationDialog) {
    ui->setupUi(this);
    setWindowTitle(tr("Configuration"));
    setLayout(ui->verticalLayout);
    ui->verticalLayout->addWidget(ui->groupBox);
    ui->groupBox->setLayout(ui->gridLayout);
    ui->dataEdit->setEnabled(false);
    ui->mapsEdit->setEnabled(false);
    ui->objectsEdit->setEnabled(false);
    ui->dataEdit->setText(Global::Settings()->GetDataPath());
    ui->mapsEdit->setText(Global::Settings()->GetMapsPath());
    ui->objectsEdit->setText(Global::Settings()->GetObjectsPath());
}
//------------------------------------------------------------------------------
TConfigurationDialog::~TConfigurationDialog() {
    delete ui;
}
//------------------------------------------------------------------------------
void TConfigurationDialog::on_dataButton_clicked() {
    ui->dataEdit->setText(QFileDialog::getExistingDirectory(this,
            tr("Choose source data folder"),
            Global::Settings()->GetDataPath()));
}
//------------------------------------------------------------------------------
void TConfigurationDialog::on_mapsButton_clicked() {
    ui->mapsEdit->setText(QFileDialog::getExistingDirectory(this,
            tr("Choose source maps folder"),
            Global::Settings()->GetMapsPath()));
}
//------------------------------------------------------------------------------
void TConfigurationDialog::on_objectsButton_clicked() {
    ui->objectsEdit->setText(QFileDialog::getExistingDirectory(this,
            tr("Choose source objects folder"),
            Global::Settings()->GetObjectsPath()));
}
//------------------------------------------------------------------------------
void TConfigurationDialog::accept() {
    qDebug("Saving configuration...");
    Global::Settings()->SetDataPath(ui->dataEdit->text().trimmed());
    Global::Settings()->SetMapsPath(ui->mapsEdit->text().trimmed());
    Global::Settings()->SetObjectsPath(ui->objectsEdit->text().trimmed());
    done(0);
}
//------------------------------------------------------------------------------
