#ifndef OPENMAPDIALOG_H
#define OPENMAPDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class OpenMapDialog;
}

class OpenMapDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OpenMapDialog(QWidget *parent = 0);
    ~OpenMapDialog();

    QString mapDir();
    QString objDir();

signals:
    void mapFolderSignal(QString str);
    void objFolderSignal(QString str);
    
private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::OpenMapDialog *ui;
};

#endif // OPENMAPDIALOG_H
