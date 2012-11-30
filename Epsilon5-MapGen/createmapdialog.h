#ifndef CREATEMAPDIALOG_H
#define CREATEMAPDIALOG_H

#include <QDialog>
#include <QString>
#include <QSize>
#include <QPixmap>

namespace Ui {
class CreateMapDialog;
}

class CreateMapDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateMapDialog(QWidget *parent = 0);
    ~CreateMapDialog();

    QString mapName();
    QSize   mapSize();
    QPixmap  mapBackground();
    QString mapPath();
    QString mapObjsPath();

signals:
    void selectTexture(QString t);
    void selectPath(QString t);
    void selectObjPath(QString t);
    
private slots:
    void on_selectTextureButton_clicked();

    void on_selectPathButton_clicked();

    void on_objPathButton_clicked();

private:
    Ui::CreateMapDialog *ui;
};

#endif // CREATEMAPDIALOG_H
