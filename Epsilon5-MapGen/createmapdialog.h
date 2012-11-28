#ifndef CREATEMAPDIALOG_H
#define CREATEMAPDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class CreateMapDialog;
}

class CreateMapDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateMapDialog(QWidget *parent = 0);
    ~CreateMapDialog();

signals:
    void selectTexture(QString t);
    
private slots:
    void on_selectTextureButton_clicked();

private:
    Ui::CreateMapDialog *ui;
};

#endif // CREATEMAPDIALOG_H
