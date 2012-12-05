// objectseditorform.cpp
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QImage>
#include <QDebug>
#include <QDir>
#include <QMenu>
#include <QVariant>
#include <QStandardItemModel>
#include "global.h"
#include "objectseditorform.h"
#include "ui_objectseditorform.h"
//------------------------------------------------------------------------------
TObjectsEditorForm::TObjectsEditorForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TObjectsEditorForm)
    , mObjects(new QStandardItemModel(this))
    , mLastUsedId(0) {
    ui->setupUi(this);
    ui->settingsGroupBox->setLayout(ui->formLayout);
    ui->objectsGroupBox->setLayout(ui->ogVerticalLayout);
    setLayout(ui->objectsWidgetLayout);
    ui->widget->setLayout(ui->verticalLayout);
    ui->dataListWidget->clear();

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearAction()));

    // Set content menu
    ui->objectsListView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->objectsListView, SIGNAL(customContextMenuRequested(QPoint)),
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

    // Connect some widgets to apply settings button
    connect(ui->heightBox, SIGNAL(editingFinished()),
            this, SLOT(on_settingsApplyButton_clicked()));
    connect(ui->widthBox, SIGNAL(editingFinished()),
            this, SLOT(on_settingsApplyButton_clicked()));
    connect(ui->nameBox->lineEdit(), SIGNAL(returnPressed()),
            this, SLOT(on_settingsApplyButton_clicked()));

    connect(ui->objectsListView, SIGNAL(activated(QModelIndex)),
            this, SLOT(on_objectsListView_clicked(QModelIndex)));

    ui->objectsListView->setModel(mObjects);
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
void TObjectsEditorForm::clearAction() {
    mObjects->clear();
    ui->nameBox->lineEdit()->clear();
    ui->idEdit->clear();
    ui->widthBox->clear();
    ui->heightBox->clear();
    ui->dynamicBox->setChecked(false);
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::showObjectsListMenu(QPoint pos) {
    QMenu menu;
    menu.addAction(tr("Load list..."), this, SLOT(loadAction()));
    menu.addAction(tr("Save list..."), this, SLOT(saveAction()));
    menu.addSeparator();
    menu.addAction(tr("Clear list"), this, SLOT(clearAction()));
    menu.exec(ui->objectsListView->mapToGlobal(pos));
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

    TObjectItem obj;
    obj.id = mLastUsedId++ + 100;
    obj.name = item.name.trimmed();
    obj.isDynamic = false;
    obj.width = item.sourceWidth;
    obj.height = item.sourceHeight;
    obj.isValid = false;
    obj.fileName = item.fileName;

    QVariant itemData;
    itemData.setValue(obj);

    QStandardItem* ito = new QStandardItem(item.icon, item.name);
    ito->setBackground(QBrush(Qt::darkRed));
    ito->setEditable(false);
    ito->setData(itemData);

    mObjects->appendRow(ito);
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::on_deleteButton_clicked() {
    QModelIndex index = ui->objectsListView->currentIndex();
    if( !index.isValid() )
        return;

    mObjects->removeRow(index.row());
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::on_objectsListView_clicked(QModelIndex index)
{
    QStandardItem* item = mObjects->item(index.row());
    const TObjectItem& itemData = item->data().value<TObjectItem>();
    ui->idEdit->setText(QString().number(itemData.id));
    ui->nameBox->lineEdit()->setText(itemData.name);
    ui->widthBox->setValue(itemData.width);
    ui->heightBox->setValue(itemData.height);
    ui->dynamicBox->setChecked(itemData.isDynamic);
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::on_settingsApplyButton_clicked()
{
    QModelIndex index = ui->objectsListView->currentIndex();
    if( !index.isValid() )
        return;

    if( ui->nameBox->lineEdit()->text().isEmpty() ) {
        ui->nameBox->lineEdit()->setFocus();
        return;
    }

    QStandardItem* item = mObjects->item(index.row());

    TObjectItem obj;
    obj.id = ui->idEdit->text().toUInt();
    obj.name = ui->nameBox->lineEdit()->text().trimmed();
    obj.isDynamic = ui->dynamicBox->isChecked();
    obj.width = ui->widthBox->text().toUInt();
    obj.height = ui->heightBox->text().toUInt();
    obj.isValid = true;
    obj.fileName = item->data().value<TObjectItem>().fileName;

    QVariant itemData;
    itemData.setValue(obj);

    item->setText(obj.name);
    item->setData(itemData);
    item->setBackground(QBrush(Qt::darkGreen));
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::loadAction() {
    qDebug() << Q_FUNC_INFO;
//    QString objectsFile = QFileDialog::getSaveFileName(this,
//            tr("Save objects list to..."),
//            Global::Settings()->GetObjectsPath(), tr("Text files (*.txt)"));
//    if( objectsFile.isEmpty() )
//        return;
}
//------------------------------------------------------------------------------
void TObjectsEditorForm::saveAction() {
    QString objectsFile(Global::Settings()->GetObjectsPath() + "/objects.txt");

    QFile file(objectsFile, this);
    file.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream stream(&file);
    QString fToName;
    for( int i = 0; i < mObjects->rowCount(); ++i )
    {
        const QStandardItem* item = mObjects->item(i);
        const TObjectItem& itemData = item->data().value<TObjectItem>();

        if( !itemData.isValid )
            continue;

        fToName = Global::Settings()->GetObjectsPath();
        fToName.append("/").append(itemData.name).append(".png");
        if(!QFile::copy(itemData.fileName, fToName)) {
            continue;
        }

        stream << QString().number(itemData.id)
            << ":" << QString().number(itemData.width)
            << ":" << QString().number(itemData.height)
            << ":" << QString().number(itemData.isDynamic)
            << ":" << itemData.name.trimmed()
            << "\n";
    }
    file.flush();
    file.close();
}
//------------------------------------------------------------------------------
