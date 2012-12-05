// openmapdialog.h
#pragma once
#include <QDialog>
#include <QString>
//------------------------------------------------------------------------------
namespace Ui
{
class OpenMapDialog;
}
//------------------------------------------------------------------------------
class TOpenMapDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TOpenMapDialog(QWidget* parent = 0);
    ~TOpenMapDialog();

    QString mapDir();
    QString objDir();

signals:
    void mapFolderSignal(QString str);
    void objFolderSignal(QString str);

private slots:
    void on_mapFolderButton_clicked();
    void on_objectsFolderButton_clicked();

private:
    Ui::OpenMapDialog* mUi;
};
//------------------------------------------------------------------------------
