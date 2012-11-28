#ifndef CREATEMAPDIALOG_H
#define CREATEMAPDIALOG_H

#include <QDialog>
#include <QString>
#include <QSize>
#include <QImage>

namespace Ui {
class CreateMapDialog;
}

class CreateMapDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CreateMapDialog(QWidget *parent = 0);
    ~CreateMapDialog();

    QString mapName() { return _name; }
    QSize   mapSize() { return _size; }
    QImage  mapBackground() { return _back; }

signals:
    void selectTexture(QString t);
    
private slots:
    void on_selectTextureButton_clicked();
    void accept();

private:
    Ui::CreateMapDialog *ui;
    QString     _name;
    QSize       _size;
    QImage      _back;
};

#endif // CREATEMAPDIALOG_H
