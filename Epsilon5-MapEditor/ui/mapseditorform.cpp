// mapseditorform.cpp
#include <QMenu>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QFileDialog>
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
    , mCurrentObject(0)
    , mCurrentRespawn(0)
    , mCurrentObjectList(0)
    , mCurrentRespawnsList(0)
    , mSObjects(0)
    , mLastModelIndex(QModelIndex())
    , mScene(new TScene(this))
    , mSceneView(new TSceneView(mScene, this))
    , mMapsViewModel(new QStandardItemModel(this))
    , mListViewModel(new QStandardItemModel(this))
    , mSObjectsViewModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    // Additional ui setups
    setLayout(ui->mainLayout);
    ui->browserGroupBox->setLayout(ui->horizontalLayout);
    ui->sceneGroupBox->setLayout(ui->sceneLayout);
    ui->sceneLayout->addWidget(mSceneView);
    ui->pageSettings->setLayout(ui->pageSettingsLayout);
    ui->pageObjects->setLayout(ui->pageObjectsLayout);
    ui->pageRespawns->setLayout(ui->gridLayout);
    ui->toolBox->setCurrentWidget(ui->pageObjects);
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
//    connect(ui->mapNameEdit, SIGNAL(editingFinished()),
//            this, SLOT(updateMapSettings()));
//    connect(ui->mapWidthBox, SIGNAL(editingFinished()),
//            this, SLOT(updateMapSettings()));
//    connect(ui->mapHeightBox, SIGNAL(editingFinished()),
//            this, SLOT(updateMapSettings()));
//    connect(ui->posXObjectBox, SIGNAL(editingFinished()),
//            this, SLOT(updateObjectSettings()));
//    connect(ui->posYObjectBox, SIGNAL(editingFinished()),
//            this, SLOT(updateObjectSettings()));
//    connect(ui->angleObjectBox, SIGNAL(editingFinished()),
//            this, SLOT(updateObjectSettings()));
//    connect(ui->idObjectEdit, SIGNAL(editingFinished()),
//            this, SLOT(updateObjectSettings()));
//    connect(ui->posXRespawnBox, SIGNAL(editingFinished()),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->posYRespawnBox, SIGNAL(editingFinished()),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->spawnRadRespawnBox, SIGNAL(editingFinished()),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->captRadRespawnBox, SIGNAL(editingFinished()),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->captTimeRespawnBox, SIGNAL(editingFinished()),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->isCapturableCheckBox, SIGNAL(toggled(bool)),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->isMainCheckBox, SIGNAL(toggled(bool)),
//            this, SLOT(updateRespawnSettings()));
//    connect(ui->teamButton, SIGNAL(clicked()),
//            this, SLOT(updateRespawnSettings()));
    connect(ui->applyButton, SIGNAL(clicked()),
            this, SLOT(updateSettings()));
    connect(ui->applyButton2, SIGNAL(clicked()),
            this, SLOT(updateSettings()));
    connect(ui->applyButton3, SIGNAL(clicked()),
            this, SLOT(updateSettings()));
    connect(mScene, SIGNAL(moveItem(quint32, QPointF, qreal)),
            this, SLOT(onItemMove(quint32, QPointF, qreal)));

    mSceneView->setFocus();

    ui->mapsView->setModel(mMapsViewModel);
    ui->listView->setModel(mListViewModel);
    ui->objectsView->setModel(mSObjectsViewModel);

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

    containers::TMapItem::TItemId mapId = TMapHelper::itemIdFromModelIndex(
                *mMaps, mMapsViewModel, index);

    mCurrentMap = mMaps->item(mapId);
    mCurrentObjectList = &mCurrentMap->objects();
    mCurrentRespawnsList = &mCurrentMap->respawns();

    ui->mapNameEdit->setText(mCurrentMap->name());
    ui->mapWidthBox->setValue(mCurrentMap->width());
    ui->mapHeightBox->setValue(mCurrentMap->height());

    if (ui->toolBox->currentWidget() == ui->pageObjects) {
        mListViewMode = E_ObjectsMode;
    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        mListViewMode = E_RespawnsMode;
    }

    loadSObjectsListAction();
    updateListView();
    updateScene();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_toolBox_currentChanged(int index)
{
    Q_UNUSED(index);
    if (ui->toolBox->currentWidget() == ui->pageObjects) {
        mListViewMode = E_ObjectsMode;
        ui->labelCurrent->setText(tr("Current objects:"));
        if (mCurrentMap) {
            mCurrentObjectList = &mCurrentMap->objects();
        }
    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        mListViewMode = E_RespawnsMode;
        ui->labelCurrent->setText(tr("Current respawns:"));
        if (mCurrentMap) {
            mCurrentRespawnsList = &mCurrentMap->respawns();
        }
    }

    updateListView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_teamButton_clicked()
{
    mTeamValue = mTeamValue == E_TeamNone ? E_TeamOne
                 : mTeamValue == E_TeamOne ? E_TeamTwo : E_TeamNone;
    updateTeamButton();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_backgroundButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,
            tr("Select background file..."), Global::Settings()->GetDataPath(),
            tr("PNG images (*.png)"));
    if (filename.isEmpty() || !QFile::exists(filename) || !mCurrentMap) {
        return;
    }

    mCurrentMap->setBackground(filename);
    mCurrentMap->setSize(QImage(filename).size());
    ui->mapWidthBox->setValue(mCurrentMap->width());
    ui->mapHeightBox->setValue(mCurrentMap->height());
    updateMapSettings();
}
//------------------------------------------------------------------------------
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
    if (!mCurrentMap) {
        return;
    }

    mCurrentMap->setName(ui->mapNameEdit->text().trimmed());
    mCurrentMap->setSize(
        QSize(ui->mapWidthBox->value(), ui->mapHeightBox->value()));
    updateMapView();
    updateScene();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateObjectSettings()
{
    if (!mCurrentMap || !mCurrentObjectList || !mCurrentObject) {
        return;
    }

    containers::TObjectItem* object = mCurrentObject;

    object->setX(ui->posXObjectBox->value());
    object->setY(ui->posYObjectBox->value());
    object->setAngle(ui->angleObjectBox->value());
    object->setObjectId(ui->idObjectEdit->text().toUInt());

    updateListView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateRespawnSettings()
{
    if (!mCurrentMap || !mCurrentRespawnsList || !mCurrentRespawn) {
        return;
    }
    return;

    containers::TRespawnItem* respawn = mCurrentRespawn;

    respawn->setPos(QPoint(ui->posXRespawnBox->value(), ui->posYRespawnBox->value()));
    respawn->setCapturable(ui->isCapturableCheckBox->isChecked());
    respawn->setMain(ui->isMainCheckBox->isChecked());
    respawn->setTeam((containers::ETeam) mTeamValue);
    respawn->setCaptureRadius(ui->captRadRespawnBox->value());
    respawn->setCaptureTime(ui->captTimeRespawnBox->value());
    respawn->setSpawnRadius(ui->spawnRadRespawnBox->value());

    updateListView();
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
                   SLOT(loadSObjectsListAction()));
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
    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::saveMapListAction()
{
    mMaps->saveMapList("maplist.txt", Global::Settings()->GetMapsPath());
}
//------------------------------------------------------------------------------
void TMapsEditorForm::refreshMapListAction()
{
    updateMapView();
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
    mMaps->removeItem(TMapHelper::itemIdFromModelIndex(*mMaps, mMapsViewModel,
            ui->mapsView->currentIndex()));
    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_listView_clicked(QModelIndex index)
{
    if (!mCurrentMap || !index.isValid()) {
        return;
    }

    if (ui->toolBox->currentWidget() == ui->pageObjects) {
        containers::TObjectContainer& objects = mCurrentMap->objects();
        containers::TObjectItem::TItemId objectId = TObjectHelper::itemIdFromModelIndex(
                    objects, mListViewModel, index);
        mCurrentObject = objects.item(objectId);

        ui->posXObjectBox->setValue(mCurrentObject->x());
        ui->posYObjectBox->setValue(mCurrentObject->y());
        ui->angleObjectBox->setValue(mCurrentObject->angle());
        ui->idObjectEdit->setText(QString().number(mCurrentObject->objectId()));
        mCurrentObjectList = &mCurrentMap->objects();
        return;
    }
    if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        containers::TRespawnContainer& respawns = mCurrentMap->respawns();
        containers::TRespawnItem::TItemId respawnId = TRespawnHelper::itemIdFromModelIndex(
                    respawns, mListViewModel, index);
        mCurrentRespawn = respawns.item(respawnId);

        ui->posXRespawnBox->setValue(mCurrentRespawn->x());
        ui->posYRespawnBox->setValue(mCurrentRespawn->y());
        ui->captRadRespawnBox->setValue(mCurrentRespawn->captureRadius());
        ui->spawnRadRespawnBox->setValue(mCurrentRespawn->spawnRadius());
        ui->captTimeRespawnBox->setValue(mCurrentRespawn->captureTime());
        ui->isCapturableCheckBox->setChecked(mCurrentRespawn->isCapturable());
        ui->isMainCheckBox->setChecked(mCurrentRespawn->isMain());

        updateTeamButton();
        mCurrentRespawnsList = &mCurrentMap->respawns();
        return;
    }
    updateListView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_listView_doubleClicked(QModelIndex index)
{
    if( !index.isValid() )
        return;

    containers::TObjectItem::TItemId objectId = TObjectHelper::itemIdFromModelIndex(
            mCurrentMap->objects(), mListViewModel, index);
    mCurrentMap->objects().removeItem(objectId);
    updateListView();
    updateScene();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_objectsView_doubleClicked(QModelIndex index)
{
    if( !index.isValid() )
        return;

    containers::TSObjectItem::TItemId soId = TSObjectHelper::itemIdFromModelIndex(
        mSObjects, mSObjectsViewModel, index);
    containers::TSObjectItem* sObject = mSObjects.item(soId);

    containers::TObjectItem object;
    object.setObjectId(sObject->objectId());
    object.setResourceFile(sObject->resourceFile());
    mCurrentMap->objects().addItem(object);
    updateListView();
    updateScene();
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
void TMapsEditorForm::refreshObjectsListAction()
{
}
//------------------------------------------------------------------------------
void TMapsEditorForm::loadSObjectsListAction()
{
    try {
        mSObjects.loadObjectList(
            Global::Settings()->GetObjectsPath() + "/objects.txt",
            Global::Settings()->GetObjectsPath());
    } catch (const UException& ex) {
        qDebug("%s", ex.what());
        return;
    }

    for (auto resIt = mSObjects.begin(); resIt != mSObjects.end(); ++resIt) {
        qDebug() << (*resIt).resourceFile() << (*resIt).width()
                 << (*resIt).height() << (*resIt).itemId() << (*resIt).objectId();
        TSObjectHelper::addItemToModel(*resIt, mSObjectsViewModel,
                QIcon(QPixmap((*resIt).resourceFile())));

        containers::TObjectContainer& objects = mCurrentMap->objects();
        for (auto objIt = objects.begin(); objIt != objects.end(); ++objIt) {
            if ((*objIt).objectId() != (*resIt).objectId()) {
                continue;
            }
            (*objIt).setResourceFile((*resIt).resourceFile());
        }
    }
    updateSObjectsView();
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

    containers::TObjectItem* object = mCurrentMap->objects().item(id);
    object->setPos(position.toPoint());
    object->setAngle(angle);

    updateListView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateMapView()
{
    mMapsViewModel->clear();
    for (auto it = mMaps->begin(); it != mMaps->end(); ++it) {
        qDebug() << "MapInfo:\n" << "name:" << (*it).name()
                 << ":" << (*it).width() << "x" << (*it).height();

        TMapHelper::addItemToModel((*it), mMapsViewModel,
                QIcon(QPixmap((*it).resourceFile())));
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateSObjectsView()
{
    mSObjectsViewModel->clear();
    for (auto it = mSObjects.begin(); it != mSObjects.end(); ++it) {
        TSObjectHelper::addItemToModel((*it), mSObjectsViewModel,
                QIcon(QPixmap((*it).resourceFile())));
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateListView()
{
    mListViewModel->clear();
    if (mListViewMode == E_ObjectsMode) {
        if (!mCurrentObjectList) {
            return;
        }

        auto it = mCurrentObjectList->constBegin();
        for (; it != mCurrentObjectList->constEnd(); ++it) {
            TObjectHelper::addItemToModel((*it), mListViewModel,
                    QIcon(QPixmap((*it).resourceFile())));
        }
    } else if (mListViewMode == E_RespawnsMode) {
        if (!mCurrentRespawnsList) {
            return;
        }

        auto it = mCurrentRespawnsList->constBegin();
        for (; it != mCurrentRespawnsList->constEnd(); ++it) {
            TRespawnHelper::addItemToModel((*it), mListViewModel,
                    QIcon(QPixmap((*it).resourceFile())));
        }
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateScene()
{
    if (!mCurrentMap) {
        return;
    }
    mScene->clear();

    mScene->sceneRect().setSize(mCurrentMap->size());
    mSceneView->setBackground(QPixmap(mCurrentMap->background()),
            mCurrentMap->size());

    auto it = mCurrentMap->objects().constBegin();
    for (; it != mCurrentMap->objects().constEnd(); ++it) {
        const containers::TObjectItem object = *it;
        TStaticObject* mapObject = new TStaticObject(
            QPixmap(object.resourceFile()));
        mapObject->setPos(object.pos());
        mapObject->setObjectId(object.itemId());
        mapObject->setAngle(object.angle());
        mScene->addItem(mapObject);
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateSettings()
{
    updateObjectSettings();
    updateRespawnSettings();
    updateMapSettings();
}
//------------------------------------------------------------------------------
