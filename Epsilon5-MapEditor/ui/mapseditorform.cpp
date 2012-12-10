// mapseditorform.cpp
#include <QMenu>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStandardItemModel>
#include "global.h"
#include "graphics/scene.h"
#include "graphics/sceneview.h"
#include "graphics/staticobject.h"
#include "mapseditorform.h"
#include "itemmodel_t.h"
#include "ui_mapseditorform.h"
//------------------------------------------------------------------------------
TMapsEditorForm::TMapsEditorForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TMapsEditorForm)
    , mTeamValue(E_TeamNone)
    , mBrowserState(E_BrowserFull)
    , mMaps(new containers::TMapContainer(this))
    , mCurrentMap(0)
    , mResObjects(0)
    , mScene(new TScene(this))
    , mSceneView(new TSceneView(mScene, this))
    , mMapsViewModel(new QStandardItemModel(this))
    , mListViewModel(new QStandardItemModel(this))
    , mObjectsViewModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // Additional ui setups
    setLayout(ui->mainLayout);
    ui->browserGroupBox->setLayout(ui->horizontalLayout);
    ui->sceneGroupBox->setLayout(ui->sceneLayout);
    ui->sceneLayout->addWidget(mSceneView);
//    ui->mapsView->setModel(mMaps->model());
    ui->pageSettings->setLayout(ui->pageSettingsLayout);
    ui->pageObjects->setLayout(ui->pageObjectsLayout);
    ui->pageRespawns->setLayout(ui->gridLayout);
    ui->teamButton->setText("");

    // Connect to content menus
    ui->mapsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->objectsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->mapsView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMapListContentMenu(QPoint)));
    connect(ui->objectsView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showObjectsContentMenu(QPoint)));
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showListViewContentMenu(QPoint)));

    // Connecting...
    connect(ui->mapNameEdit, SIGNAL(editingFinished()),
            this, SLOT(updateMapSettings()));
    connect(ui->mapWidthBox, SIGNAL(editingFinished()),
            this, SLOT(updateMapSettings()));
    connect(ui->mapHeightBox, SIGNAL(editingFinished()),
            this, SLOT(updateMapSettings()));
    connect(ui->posXObjectBox, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->posYObjectBox, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->angleObjectBox, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->idObjectEdit, SIGNAL(editingFinished()),
            this, SLOT(updateObjectSettings()));
    connect(ui->posXRespawnBox, SIGNAL(editingFinished()),
            this, SLOT(updateRespawnSettings()));
    connect(ui->posYRespawnBox, SIGNAL(editingFinished()),
            this, SLOT(updateRespawnSettings()));
    connect(ui->spawnRadRespawnBox, SIGNAL(editingFinished()),
            this, SLOT(updateRespawnSettings()));
    connect(ui->captRadRespawnBox, SIGNAL(editingFinished()),
            this, SLOT(updateRespawnSettings()));
    connect(ui->captTimeRespawnBox, SIGNAL(editingFinished()),
            this, SLOT(updateRespawnSettings()));
    connect(ui->isCapturableCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(updateRespawnSettings()));
    connect(ui->isMainCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(updateRespawnSettings()));
    connect(ui->teamButton, SIGNAL(clicked()),
            this, SLOT(updateRespawnSettings()));

    mSceneView->setFocus();

//    ui->objectsView->setModel(mResObjects.model());
    ui->mapsView->setModel(mMapsViewModel);
    ui->listView->setModel(mListViewModel);
    ui->objectsView->setModel(mObjectsViewModel);

    // Just for testing...
//    mMaps->setBaseDirectory(Global::Settings()->GetMapsPath());
    try {
        mMaps->loadMapList("maplist.txt", Global::Settings()->GetMapsPath());
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }
    updateMapView();

//    startTimer(10);
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

//    mCurrentMap = &mMaps->item(index);

//    ui->mapNameEdit->setText(mCurrentMap->name());
//    ui->mapWidthBox->setValue(mCurrentMap->width());
//    ui->mapHeightBox->setValue(mCurrentMap->height());
//    if (ui->toolBox->currentWidget() == ui->pageObjects) {
//        ui->listView->setModel(mCurrentMap->objects().model());
//    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
//        ui->listView->setModel(mCurrentMap->respawns().model());
//    }

//    loadObjectsListAction();
//    initScene(index);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_toolBox_currentChanged(int index)
{
    Q_UNUSED(index);
    if (ui->mapsView->currentIndex().row() < 0) {
        return;
    }
    if (ui->toolBox->currentWidget() == ui->pageObjects) {
//        ui->listView->setModel(mMaps->item(ui->mapsView->currentIndex())
//                .objects().model());   // Connect to content menus
        ui->mapsView->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(ui->mapsView, SIGNAL(customContextMenuRequested(QPoint)),
                this, SLOT(showMapListContentMenu(QPoint)));
    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
//        ui->listView->setModel(mMaps->item(ui->mapsView->currentIndex())
//                .respawns().model());
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_teamButton_clicked()
{
    mTeamValue = mTeamValue == E_TeamNone ? E_TeamOne
            : mTeamValue == E_TeamOne ? E_TeamTwo : E_TeamNone;
    updateTeamButton();
}

void TMapsEditorForm::updateTeamButton()
{
    if (mTeamValue == E_TeamOne) {
        ui->teamButton->setText("1");
        return;
    }
    if (mTeamValue == E_TeamTwo) {
        ui->teamButton->setText("2");
        return;
    }

    ui->teamButton->setText("");
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateMapSettings()
{
    QModelIndex index = ui->mapsView->currentIndex();
    if (!index.isValid()) {
        return;
    }
//    mMaps->item(index).setName(ui->mapNameEdit->text().trimmed());
//    mMaps->item(index).setSize(ui->mapWidthBox->value(), ui->mapHeightBox->value());

//    mMaps->updateView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateObjectSettings()
{
    QModelIndex mapIndex = ui->mapsView->currentIndex();
    QModelIndex index = ui->listView->currentIndex();
    if (!mapIndex.isValid() || !index.isValid()) {
        return;
    }

//    containers::TObjectItem& object = mMaps->item(mapIndex).objects().item(index);
//    object.setX(ui->posXObjectBox->value());
//    object.setY(ui->posYObjectBox->value());
//    object.setAngle(ui->angleObjectBox->value());
//    object.setObjectId(ui->idObjectEdit->text().toUInt());

//    mMaps->item(mapIndex).objects().updateView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateRespawnSettings()
{
    QModelIndex mapIndex = ui->mapsView->currentIndex();
    QModelIndex index = ui->listView->currentIndex();
    if (!mapIndex.isValid() || !index.isValid()) {
        return;
    }

//    containers::TRespawnItem& respawn = mMaps->item(mapIndex).respawns().item(index);
//    respawn.setPos(QPoint(ui->posXRespawnBox->value(), ui->posYRespawnBox->value()));
//    respawn.setCapturable(ui->isCapturableCheckBox->isChecked());
//    respawn.setMain(ui->isMainCheckBox->isChecked());
//    respawn.setTeam((containers::ETeam) mTeamValue);
//    respawn.setCaptureRadius(ui->captRadRespawnBox->value());
//    respawn.setCaptureTime(ui->captTimeRespawnBox->value());
//    respawn.setSpawnRadius(ui->spawnRadRespawnBox->value());

//    mMaps->item(mapIndex).respawns().updateView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::showMapListContentMenu(QPoint point)
{
    QMenu menu;
    menu.addAction(tr("Load maplist..."), this, SLOT(loadMapListAction()));
    menu.addAction(tr("Save maplist..."), this, SLOT(saveMapListAction()));
    menu.addSeparator();
    menu.addAction(tr("New map"), this, SLOT(newMapListAction()));
    if (ui->mapsView->currentIndex().isValid()) {
        menu.addAction(tr("Delete map"), this, SLOT(deleteMapListAction()));
    }
    menu.addSeparator();
    menu.addAction(tr("Refresh"), this, SLOT(refreshMapListAction()));
    menu.exec(ui->mapsView->mapToGlobal(point));
}
//------------------------------------------------------------------------------
void TMapsEditorForm::showObjectsContentMenu(QPoint point)
{
    QMenu menu;
    menu.addAction(tr("Load source objects list..."), this,
                   SLOT(loadObjectsListAction()));
    menu.addSeparator();
    menu.addAction(tr("Refresh"), this, SLOT(refreshObjectsListAction()));
    menu.exec(ui->objectsView->mapToGlobal(point));
}
//------------------------------------------------------------------------------
void TMapsEditorForm::showListViewContentMenu(QPoint point)
{
    Q_UNUSED(point);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::loadMapListAction()
{
    mMaps->clearItems();
    try {
        mMaps->loadMapList("maplist.txt", Global::Settings()->GetMapsPath());
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
    }
//    mMaps->updateView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::saveMapListAction()
{
    mMaps->saveMapList("maplist.txt", Global::Settings()->GetMapsPath());
}
//------------------------------------------------------------------------------
void TMapsEditorForm::refreshMapListAction()
{
    auto it = mMaps->begin();
    for (; it != mMaps->end(); ++it) {
//        containers::TMapItem& map = *it;
//        map.validate();
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::  newMapListAction()
{
    containers::TMapItem map;
    mMaps->addItem(map);
    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::deleteMapListAction()
{
//    mMaps->removeItem();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_listView_clicked(QModelIndex index)
{
    if (ui->toolBox->currentWidget() == ui->pageObjects) {
//        const containers::TObjectItem& object = mMaps->item(
//                    ui->mapsView->currentIndex()).objects().item(index);

//        ui->posXObjectBox->setValue(object.x());
//        ui->posYObjectBox->setValue(object.y());
//        ui->angleObjectBox->setValue(object.angle());
//        ui->idObjectEdit->setText(QString().number(object.objectId()));
        return;
    }
    if (ui->toolBox->currentWidget() == ui->pageRespawns) {
//        const containers::TRespawnItem& respawn = mMaps->item(
//                    ui->mapsView->currentIndex()).respawns().item(index);

//        ui->posXRespawnBox->setValue(respawn.x());
//        ui->posYRespawnBox->setValue(respawn.y());
//        ui->captRadRespawnBox->setValue(respawn.captureRadius());
//        ui->spawnRadRespawnBox->setValue(respawn.spawnRadius());
//        ui->captTimeRespawnBox->setValue(respawn.captureTime());
//        ui->isCapturableCheckBox->setChecked(respawn.isCapturable());
//        ui->isMainCheckBox->setChecked(respawn.isMain());

//        mTeamValue = respawn.team() - 1;
        updateTeamButton();
        return;
    }

//    mMaps->updateView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::toggleBrowserBox()
{
    if (mBrowserState == E_BrowserFull) {
        ui->browserGroupBox->show();
        ui->mapsView->show();
        ui->line->show();
        ui->line_2->show();
        ui->labelMapsList->show();
        ui->label->show();
        ui->toolBox->show();
        ui->objectsView->show();
        ui->browserGroupBox->setMaximumWidth(400);
        ui->browserGroupBox->setMinimumWidth(600);
        mBrowserState = E_BrowserHalf;
        return;
    }
    if (mBrowserState == E_BrowserHalf) {
        ui->browserGroupBox->show();
        ui->mapsView->hide();
        ui->line->hide();
        ui->line_2->hide();
        ui->labelMapsList->hide();
        ui->label->hide();
        ui->toolBox->hide();
        ui->objectsView->hide();
        ui->browserGroupBox->setMaximumWidth(300);
        ui->browserGroupBox->setMinimumWidth(200);
        mBrowserState = E_BrowserNone;
        return;
    }
    if (mBrowserState == E_BrowserNone) {
        ui->browserGroupBox->hide();
        ui->mapsView->hide();
        ui->line->hide();
        ui->line_2->hide();
        ui->labelMapsList->hide();
        ui->label->hide();
        ui->toolBox->hide();
        ui->objectsView->hide();
        mBrowserState = E_BrowserFull;
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F1) {
        toggleBrowserBox();
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::initScene(const QModelIndex& index)
{
    if (!index.isValid()) {
        return;
    }
    mScene->clear();

//    containers::TMapItem& map = mMaps->item(index);
//    mScene->sceneRect().setSize(map.size());
//    mSceneView->setSceneRect(0, 0, mScene->width(), mScene->height());
    mSceneView->setSceneRect(-mScene->width() / 2, -mScene->height() / 2,
            mScene->width() / 2, mScene->height() / 2);
    mSceneView->centerOn(0, 0);
//    mSceneView->centerOn(mScene->width()/2, mScene->height()/2);
//    mScene->setBackground(QPixmap(map.background()));
//    mSceneView->setBackground(QPixmap(map.background()));
//    connect(mScene, SIGNAL(viewportMoved(const QPointF*)),
//            mSceneView, SLOT(moveCenterOn(const QPointF*)));

//    auto it = map.objects().constBegin();
//    for (; it != map.objects().constEnd(); ++it) {
//        const containers::TObjectItem object = *it;
//        qDebug() << object.pos() << object.resourceFile();
//        TStaticObject* mapObject = new TStaticObject(
//            QPixmap(object.resourceFile()));
//        mapObject->setPos(object.pos());
//        mapObject->setObjectId(object.itemId());
////        connect(mapObject, SIGNAL(moved(quint32)), this, SLOT(onItemMove(quint32)));
//        mScene->addItem(mapObject);
//    }

//    connect(mScene, SIGNAL(moveItem(QGraphicsItem*)), this, SLOT(onItemMove(QGraphicsItem*)));
    connect(mScene, SIGNAL(moveItem(quint32, QPointF, qreal)),
            this, SLOT(onItemMove(quint32, QPointF, qreal)));
}
//------------------------------------------------------------------------------
void TMapsEditorForm::refreshObjectsListAction()
{

}
//------------------------------------------------------------------------------
void TMapsEditorForm::loadObjectsListAction()
{
//    ui->objectsView->setModel(mResObjects.model());
//    mResObjects.loadObjectList(
//        Global::Settings()->GetObjectsPath() + "/objects.txt",
//        Global::Settings()->GetObjectsPath(), true);

//    QStandardItem* item;
//    QModelIndex objectIndex;
//    for (int i = 0; i < mResObjects.model()->rowCount(); ++i) {
//        objectIndex = mResObjects.model()->index(i, 0);
//        item = mResObjects.model()->itemFromIndex(objectIndex);
//        containers::TObjectItem& resObject = mResObjects[item->data().toUInt()];
//        mResObjects.setItemInfo(objectIndex,
//                QIcon(QPixmap(resObject.resourceFile())));

//        containers::TObjectContainer& objects = mMaps->item(
//                    ui->mapsView->currentIndex()).objects();
//        auto it = objects.begin();
//        for (; it != objects.end(); ++it) {
//            if ((*it).objectId() != resObject.objectId()) {
//                continue;
//            }

//            (*it).setResourceFile(resObject.resourceFile());
//        }
//    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::timerEvent(QTimerEvent*)
{
    static QPointF ppp = QPointF(0, 0);
    static int dx = 2;

    ppp.setX(ppp.x() + dx);
    if (ppp.x() > mScene->width() / 3 || ppp.x() < -mScene->width() / 3) {
        dx = -dx;
    }
    qDebug() << ppp;
    mSceneView->centerOn(ppp);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::onItemMove(quint32 id, QPointF position, qreal angle)
{
    if (!mCurrentMap) {
        return;
    }

    auto it = mCurrentMap->objects().begin();
    for (; it != mCurrentMap->objects().end(); ++it) {
//        containers::TObjectItem& object = (*it);
//        if (object.itemId() == id) {
//            object.setPos(position.toPoint());
//            object.setAngle(angle);
//        }
    }
//    mCurrentMap->objects().updateView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateMapView()
{
    mMapsViewModel->clear();
    auto it = mMaps->begin();
    for(; it != mMaps->end(); ++it)
    {
//        containers::TMapItem& map = (*it);
//        QStandardItem* vi = new QStandardItem;
//        vi->setText(map.pack());
//        vi->setData(map.itemId());
//        mMapsViewModel->appendRow(vi);
        TTItemModelHelper<containers::TMapContainer, containers::TMapItem>::addItemToModel((*it), mMapsViewModel);
    }
}
//------------------------------------------------------------------------------
