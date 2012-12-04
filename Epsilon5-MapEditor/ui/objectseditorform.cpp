// objectseditorform.cpp
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include "global.h"
#include "objectseditorform.h"
#include "ui_objectseditorform.h"
//------------------------------------------------------------------------------
TObjectsEditorForm::TObjectsEditorForm(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::TObjectsEditorForm) {
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
    ui->dataListWidget->setGridSize(QSize(200, 100));
    ui->dataListWidget->setIconSize(ui->dataListWidget->gridSize());
    ui->infoLabel->clear();
    connect(ui->dataListWidget, SIGNAL(clicked(QModelIndex)),
            this, SLOT(showImageInfo(QModelIndex)));
    connect(ui->dataListWidget, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(addButtonAction(QModelIndex)));
    ui->infoBox->setLayout(ui->verticalLayout_2);
    createDataList();
}
//------------------------------------------------------------------------------
TObjectsEditorForm::~TObjectsEditorForm() {
    delete ui;
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::createDataList() {
    mDataCache.clear();
    QDir dir(Global::Settings()->GetDataPath());
    QFileInfoList fInfo = dir.entryInfoList();
    for (auto it = fInfo.begin(); it != fInfo.end(); ++it) {
        if (!(*it).isFile()) {
            continue;
        }
        mDataCache.append((*it).absoluteFilePath(), ui->dataListWidget->iconSize());
    }
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::updateDataList() {
    ui->dataListWidget->clear();
    TImageCacheItem item;
    QString strId;
    QListWidgetItem* it;
    for (int i = 0; i < mDataCache.count(); ++i) {
        item = mDataCache[i];
        strId = QString().number(item.id);
        it = new QListWidgetItem(item.icon, strId);
        ui->dataListWidget->addItem(it);
    }
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::loadAction() {
    qDebug() << Q_FUNC_INFO;
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::saveAction() {
    qDebug() << Q_FUNC_INFO;
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::clearAction() {
    ui->objectsListWidget->clear();
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::showObjectsListMenu(QPoint pos) {
    QMenu menu;
    menu.addAction(tr("Load list..."), this, SLOT(loadAction()));
    menu.addAction(tr("Save list..."), this, SLOT(saveAction()));
    menu.addSeparator();
    menu.addAction(tr("Clear list"), this, SLOT(clearAction()));
    menu.exec(ui->objectsListWidget->mapToGlobal(pos));
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::showDataListMenu(QPoint pos) {
    QMenu menu;
    menu.addAction(tr("Refresh"));
    if (menu.exec(ui->dataListWidget->mapToGlobal(pos))) {
        createDataList();
        updateDataList();
    }
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::showImageInfo(QModelIndex index) {
    if (!index.isValid()) {
        return;
    }
    const TImageCacheItem& item = mDataCache[index.data().toUInt()];
    QImage img(item.fileName);
    ui->infoLabel->setText("<b>" + tr("Filename:") + "</b>&nbsp;"
            + item.fileName + "<br/><b>" + tr("Image size:") + "</b>&nbsp;"
            + QString().number(img.width()) + "x"
            + QString().number(img.height()));
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::on_addButton_clicked() {
    addButtonAction(ui->dataListWidget->currentIndex());
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::addButtonAction(QModelIndex index) {
    const TImageCacheItem& item = mDataCache[index.data().toUInt()];
    QListWidgetItem* it = new QListWidgetItem(item.icon, item.name);
    ui->objectsListWidget->addItem(it);
}
//------------------------------------------------------------------------------
