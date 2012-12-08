// mapseditorform.cpp
#include <QMenu>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "global.h"
#include "graphics/scene.h"
#include "graphics/sceneview.h"
#include "graphics/staticobject.h"
#include "mapseditorform.h"
#include "ui_mapseditorform.h"
//------------------------------------------------------------------------------
TMapsEditorForm::TMapsEditorForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TMapsEditorForm)
    , mMaps(new containers::TMapContainer(this))
    , mScene(new TScene(this))
    , mSceneView(new TSceneView(mScene, this))
{
    ui->setupUi(this);
    // Additional ui setups
    setLayout(ui->mainLayout);
    ui->browserGroupBox->setLayout(ui->horizontalLayout);
    ui->sceneGroupBox->setLayout(ui->sceneLayout);
    ui->sceneLayout->addWidget(mSceneView);
    ui->mapsView->setModel(mMaps->model());
    ui->pageSettings->setLayout(ui->pageSettingsLayout);
    ui->pageObjects->setLayout(ui->pageObjectsLayout);
    ui->pageRespawns->setLayout(ui->gridLayout);
    // Connect to content menus
    ui->mapsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->mapsView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMapListContentMenu(QPoint)));
    // Connecting...
    connect(ui->mapNameEdit, SIGNAL(editingFinished()),
            this, SLOT(updateMapSettings()));
    connect(ui->posXObjectBox, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->posYObjectBox, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->angleObjectBox, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->idObjectEdit, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    // Just for testing...
//    mMaps->setBaseDirectory(Global::Settings()->GetMapsPath());
    try {
        mMaps->loadMapList("maplist.txt", Global::Settings()->GetMapsPath());
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }
}
//------------------------------------------------------------------------------
TMapsEditorForm::~TMapsEditorForm()
{
    delete ui;
}
//------------------------------------------------------------------------------
void TMapsEditorForm::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::setObjectsModel(QAbstractItemModel* model)
{
    ui->objectsView->setModel(model);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_mapsView_clicked(QModelIndex index)
{
    if (!index.isValid()) {
        return;
    }
    ui->mapNameEdit->setText(mMaps->mapName(index));
    ui->mapWidthBox->setValue(mMaps->mapWidth(index));
    ui->mapHeightBox->setValue(mMaps->mapHeight(index));
    if (ui->toolBox->currentWidget() == ui->pageObjects) {
        ui->listView->setModel(mMaps->objectModel(index));
    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        ui->listView->setModel(mMaps->respawnModel(index));
    }
    initScene(index);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_toolBox_currentChanged(int index)
{
    Q_UNUSED(index);
    if (ui->mapsView->currentIndex().row() < 0) {
        return;
    }
    if (ui->toolBox->currentWidget() == ui->pageObjects) {
        ui->listView->setModel(mMaps->objectModel(ui->mapsView->currentIndex()));
    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        ui->listView->setModel(mMaps->respawnModel(ui->mapsView->currentIndex()));
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateMapSettings()
{
    QModelIndex index = ui->mapsView->currentIndex();
    if (!index.isValid()) {
        return;
    }
    mMaps->setMapName(index, ui->mapNameEdit->text().trimmed());
    mMaps->setMapWidth(index, ui->mapWidthBox->value());
    mMaps->setMapHeight(index, ui->mapHeightBox->value());
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateObjectSettings()
{
    QModelIndex mapIndex = ui->mapsView->currentIndex();
    QModelIndex index = ui->listView->currentIndex();
    if (!mapIndex.isValid() || !index.isValid()) {
        return;
    }
    mMaps->objects(mapIndex)->setX(index, ui->posXObjectBox->value());
    mMaps->objects(mapIndex)->setX(index, ui->posYObjectBox->value());
    mMaps->objects(mapIndex)->setAngle(index, ui->angleObjectBox->value());
    mMaps->objects(mapIndex)->setId(index, ui->idObjectEdit->text().toUInt());
}
//------------------------------------------------------------------------------
void TMapsEditorForm::showMapListContentMenu(QPoint point)
{
    QMenu menu;
    menu.addAction(tr("Load maplist..."));
    menu.addAction(tr("Save maplist..."), this, SLOT(saveMapListAction()));
    menu.addSeparator();
    menu.addAction(tr("Refresh"));
    menu.exec(ui->mapsView->mapToGlobal(point));
}
//------------------------------------------------------------------------------
void TMapsEditorForm::saveMapListAction()
{
    mMaps->saveToFile("maplist.txt");
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_listView_clicked(QModelIndex index)
{
    if (ui->toolBox->currentWidget() == ui->pageObjects) {
        ui->posXObjectBox->setValue(
            mMaps->objects(ui->mapsView->currentIndex())->x(index));
        ui->posYObjectBox->setValue(
            mMaps->objects(ui->mapsView->currentIndex())->y(index));
        ui->angleObjectBox->setValue(
            mMaps->objects(ui->mapsView->currentIndex())->angle(index));
        ui->idObjectEdit->setText(QString().number(
                    mMaps->objects(ui->mapsView->currentIndex())->id(index)));
        return;
    }
    if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        return;
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::initScene(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }
    oldcontainers::TMapObjectContainer* objects = mMaps->objects(index);
    mScene->sceneRect().setSize(QSize(mMaps->mapWidth(index), mMaps->mapHeight(index)));
    //mSceneView->maximumViewportSize()
    mSceneView->setSceneRect(0, 0, mScene->width(), mScene->height());
    QModelIndex objectIndex;
    for (int i = 0; i < objects->count(); ++i) {
        TStaticObject* mapObject = new TStaticObject();
        objectIndex = objects->model()->index(i, 0);
        mapObject->setPos(QPointF(objects->x(objectIndex), objects->y(objectIndex)));
        //mapObject->setPixmap();
        mScene->addItem(mapObject);
    }
}
