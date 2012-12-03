
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include "global.h"
#include "objectseditorform.hpp"
#include "ui_objectseditorform.h"

TObjectsEditorForm::TObjectsEditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TObjectsEditorForm)
{
    ui->setupUi(this);
    ui->settingsGroupBox->setLayout(ui->formLayout);
    ui->objectsGroupBox->setLayout(ui->ogVerticalLayout);
    setLayout(ui->objectsWidgetLayout);
    ui->widget->setLayout(ui->verticalLayout);
    ui->dataListWidget->clear();
    ui->objectsListWidget->clear();

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearAction()));

    // Set content menu
    ui->objectsListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->objectsListWidget, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(showObjectsListMenu(QPoint)));

    ui->dataListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->dataListWidget, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(showDataListMenu(QPoint)));

    ui->dataListWidget->setGridSize(QSize(200,100));
    ui->dataListWidget->setIconSize(ui->dataListWidget->gridSize());

    updateDataList();
}

TObjectsEditorForm::~TObjectsEditorForm()
{
    delete ui;
}

void TObjectsEditorForm::updateDataList()
{
    ui->dataListWidget->clear();

    QListWidgetItem* iw;
    // TODO: this should be moved to another place
    QDir dir(Global::Settings()->GetDataPath());
    QFileInfoList fInfo = dir.entryInfoList();
    auto it = fInfo.begin();
    for( ; it != fInfo.end(); ++it )
    {
        if( (*it).isFile() ) {
            const QString& absFile = (*it).absoluteFilePath();
            const QIcon& ico = genIconFromFile(absFile);
            iw = new QListWidgetItem(ico, QString());
            //ui->dataListWidget->setIconSize);
            ui->dataListWidget->addItem(iw);
        }
    }
}

QIcon TObjectsEditorForm::genIconFromFile(const QString &fileName)
{
    QPainter pt;
    //pt.drawImage(0,0,px.convertFromImage(QImage(fileName)));
    QImage img(fileName);
    qDebug() << img.size();
    return QIcon(QPixmap::fromImage(img.scaled(ui->dataListWidget->iconSize())));//, Qt::KeepAspectRatio)));
}

void TObjectsEditorForm::loadAction()
{
    qDebug() << Q_FUNC_INFO;
}

void TObjectsEditorForm::saveAction()
{
    qDebug() << Q_FUNC_INFO;
}

void TObjectsEditorForm::clearAction()
{
    ui->objectsListWidget->clear();
}

void TObjectsEditorForm::showObjectsListMenu(QPoint pos)
{
    QMenu menu;
    menu.addAction(tr("Load list..."), this, SLOT(loadAction()));
    menu.addAction(tr("Save list..."), this, SLOT(saveAction()));
    menu.addSeparator();
    menu.addAction(tr("Clear list"), this, SLOT(clearAction()));

    menu.exec(ui->objectsListWidget->mapToGlobal(pos));
}

void TObjectsEditorForm::showDataListMenu(QPoint pos)
{
    QMenu menu;
    menu.addAction(tr("Refresh"));

    if( menu.exec(ui->dataListWidget->mapToGlobal(pos)) )
        updateDataList();
}
