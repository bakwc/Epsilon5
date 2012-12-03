// configurationdialog.h
#pragma once
#include <QDialog>
//------------------------------------------------------------------------------
namespace Ui {
class TConfigurationDialog;
}
//------------------------------------------------------------------------------
class TConfigurationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TConfigurationDialog(QWidget *parent = 0);
    ~TConfigurationDialog();

private slots:
    void on_dataButton_clicked();
    void on_mapsButton_clicked();
    void on_objectsButton_clicked();
    void accept();

private:
    Ui::TConfigurationDialog *ui;
};
//------------------------------------------------------------------------------
