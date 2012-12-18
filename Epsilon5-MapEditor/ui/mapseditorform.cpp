// mapseditorform.cpp
#include <QMenu>
#include <QColorDialog>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QStandardItemModel>
#include <QFileDialog>
#include "global.h"
#include "graphics/scene.h"
#include "graphics/sceneview.h"
#include "graphics/staticobject.h"
#include "graphics/respawnobject.h"
#include "mapseditorform.h"
#include "itemmodel_t.h"
#include "ui_mapseditorform.h"

#define ON_THE_FLY_APPLY 0
//------------------------------------------------------------------------------
TMapsEditorForm::TMapsEditorForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TMapsEditorForm)
    , mTeamValue(E_TeamNone)
    , mBrowserState(E_BrowserNone)
    , mMaps(new containers::TMapContainer(this))
    , mCurrentMap(0)
    , mCurrentObject(0)
    , mCurrentRespawn(0)
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
    ui->pageSettings->setLayout(ui->verticalLayout_6);
    ui->pageObjects->setLayout(ui->verticalLayout_5);
    ui->pageRespawns->setLayout(ui->verticalLayout_4);
    ui->toolBox->setCurrentWidget(ui->pageObjects);
    ui->teamButton->setText("");

    // Connect to content menus
    ui->mapsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->objectsView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->mapsView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showMapListContentMenu(QPoint)));
    connect(ui->objectsView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showSObjectsContentMenu(QPoint)));
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(showListViewContentMenu(QPoint)));

    // Connecting...
#if ON_THE_FLY_APPLY
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
#endif

    connect(ui->applyButton, SIGNAL(clicked()),
            this, SLOT(updateSettings()));
    connect(ui->applyButton2, SIGNAL(clicked()),
            this, SLOT(updateSettings()));
    connect(ui->applyButton3, SIGNAL(clicked()),
            this, SLOT(updateSettings()));
    connect(mScene, SIGNAL(moveItem(quint32, QPointF, qreal, bool)),
            this, SLOT(onItemMove(quint32, QPointF, qreal, bool)));
    connect(mScene, SIGNAL(clickItem(quint32,bool)),
            this, SLOT(onClickItem(quint32,bool)));

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

    ui->mapNameEdit->setText(mCurrentMap->name());
    ui->mapWidthBox->setValue(mCurrentMap->width());
    ui->mapHeightBox->setValue(mCurrentMap->height());

    QPixmap pm(32, 32);
    QPainter pt(&pm);
    mColor = mCurrentMap->color();
    pt.fillRect(pm.rect(), mColor);
    ui->colorButton->setIcon(QIcon(pm));

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
    } else if (ui->toolBox->currentWidget() == ui->pageRespawns) {
        mListViewMode = E_RespawnsMode;
        ui->labelCurrent->setText(tr("Current respawns:"));
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

    QPixmap pm(32, 32);
    QPainter pt(&pm);
    pt.fillRect(pm.rect(), mColor);
    ui->colorButton->setIcon(QIcon(pm));

    mCurrentMap->setName(ui->mapNameEdit->text().trimmed());
    mCurrentMap->setSize(
        QSize(ui->mapWidthBox->value(), ui->mapHeightBox->value()));
    mCurrentMap->setColor(mColor);
    updateMapView();
    updateScene();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateObjectSettings()
{
    if (!mCurrentMap || !mCurrentObject) {
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
    if (!mCurrentMap || !mCurrentRespawn) {
        return;
    }

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
    menu.addAction(tr("Open map folder..."), this, SLOT(openMapFolderAction()));
    menu.addAction(tr("Save all maps..."), this, SLOT(saveMapListAction()));
    menu.addSeparator();
    menu.addAction(tr("Add new map"), this, SLOT(addNewMapAction()));
    menu.addAction(tr("Save current map"), this, SLOT(saveMapAction()));
    if (ui->mapsView->currentIndex().isValid()) {
        menu.addAction(tr("Remove map"), this, SLOT(removeMapAction()));
    }
    menu.addSeparator();
    menu.addAction(tr("Refresh"), this, SLOT(refreshMapListAction()));
    menu.exec(ui->mapsView->mapToGlobal(point));
}
//------------------------------------------------------------------------------
void TMapsEditorForm::showSObjectsContentMenu(QPoint point)
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
    if (ui->toolBox->currentWidget() != ui->pageRespawns)
        return;

    QMenu menu;
    menu.addAction(tr("Add new respawn"), this, SLOT(addNewRespawn()));
    menu.exec(ui->listView->mapToGlobal(point));
}
//------------------------------------------------------------------------------
void TMapsEditorForm::openMapFolderAction()
{
    QString mapFolderName = QFileDialog::getExistingDirectory(this,
            tr("Open maps folder"), Global::Settings()->GetMapsPath());
    if( mapFolderName.isEmpty() )
        return;

    mScene->clear();
    mMaps->clearItems();
    QDir mapFolder(mapFolderName);
    const QStringList& list = mapFolder.entryList();
    auto it = list.constBegin();
    for( ; it != list.constEnd(); ++it )
    {
        if( !QFileInfo(mapFolder, (*it).trimmed()).isDir()
                || *it == "." || *it == "..") {
            continue;
        }

        try {
            mMaps->loadMapByName((*it).trimmed(), mapFolder);
        } catch (const UException& ex) {
            qDebug("%s", ex.what());
        }
    }

    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::saveMapListAction()
{
    auto it = mMaps->begin();
    for( ; it != mMaps->end(); ++it ) {
        containers::TMapItem& map = *it;
        map.validate();
        auto it2 = map.objects().begin();
        for( ; it2 != map.objects().end(); ++it2 ) {
            (*it2).validate();
        }

        auto it3 = map.respawns().begin();
        for( ; it3 != map.respawns().end(); ++it3 ) {
            (*it3).validate();
        }

        mMaps->saveMap(map, Global::Settings()->GetMapsPath());
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::refreshMapListAction()
{
    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::clearMapListAction()
{
    mCurrentMap = 0;
    mCurrentObject = 0;
    mCurrentRespawn = 0;
    mMaps->clearItems();
    mScene->clear();
    mSceneView->clear();
    mMapsViewModel->clear();
    mListViewModel->clear();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::addNewMapAction()
{
    containers::TMapItem map;
    mMaps->addItem(map);
    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::removeMapAction()
{
    mMaps->removeItem(TMapHelper::itemIdFromModelIndex(*mMaps, mMapsViewModel,
            ui->mapsView->currentIndex()));
    updateMapView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::saveMapAction()
{
    if( !mCurrentMap ) {
        return;
    }

    mCurrentMap->validate();
    containers::TObjectContainer& objects = mCurrentMap->objects();
    containers::TRespawnContainer& respawns = mCurrentMap->respawns();
    auto it2 = objects.begin();
    for( ; it2 != objects.end(); ++it2 ) {
        (*it2).validate();
    }

    auto it3 = respawns.begin();
    for( ; it3 != respawns.end(); ++it3 ) {
        (*it3).validate();
    }

    mMaps->saveMap(*mCurrentMap, Global::Settings()->GetMapsPath());
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
        return;
    }
    updateListView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_listView_doubleClicked(QModelIndex index)
{
    if( !index.isValid() )
        return;

    if( mListViewMode == E_ObjectsMode ) {
        containers::TObjectItem::TItemId objectId = TObjectHelper::itemIdFromModelIndex(
                mCurrentMap->objects(), mListViewModel, index);
        mCurrentMap->objects().removeItem(objectId);
    } else if (mListViewMode == E_RespawnsMode) {
        containers::TSObjectItem::TItemId respawnId = TRespawnHelper::itemIdFromModelIndex(
                mCurrentMap->respawns(), mListViewModel, index);
        mCurrentMap->respawns().removeItem(respawnId);
    }
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

    QPoint viewportCenter(mSceneView->viewport()->size().width() / 2,
            mSceneView->viewport()->size().height() / 2);

    // TODO: remove "respawn" text in future
    if( sObject->resourceName() == "respawn" ) {
        containers::TRespawnItem respawn;
        respawn.setResourceFile(sObject->resourceFile());
        respawn.setPos(mSceneView->mapToScene(viewportCenter).toPoint());
        mCurrentMap->respawns().addItem(respawn);
    } else {
        containers::TObjectItem object;
        object.setObjectId(sObject->objectId());
        object.setResourceFile(sObject->resourceFile());
        object.setPos(mSceneView->mapToScene(viewportCenter).toPoint());
        mCurrentMap->objects().addItem(object);
    }
    updateListView();
    updateScene();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_colorButton_clicked()
{
    if( !mCurrentMap )
        return;

    QColorDialog colorDlg(this);
    QColor color = colorDlg.getColor(mCurrentMap->color());
    if( !color.isValid() )
        return;

    mColor = color;
    updateMapSettings();
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
        TSObjectHelper::addItemToModel(*resIt, mSObjectsViewModel,
                QIcon(QPixmap((*resIt).resourceFile())));

        if( (*resIt).resourceName() == "respawn" ) {
            containers::TRespawnContainer& respawn = mCurrentMap->respawns();
            for (auto objIt = respawn.begin(); objIt != respawn.end(); ++objIt) {
                (*objIt).setResourceFile((*resIt).resourceFile());
            }
            continue;
        }

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
    if( !mCurrentMap )
        return;

    static QPointF ppp = QPointF(0, 0);
    static int dx = 2;

    ppp.setX(ppp.x() + dx);
    if (ppp.x() > mScene->width() / 3 || ppp.x() < -mScene->width() / 3) {
        dx = -dx;
    }
    mSceneView->centerOn(ppp);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::onClickItem(quint32 id, bool isRespawn)
{
    Q_UNUSED(id);
    if( isRespawn ) {
        mListViewMode = E_RespawnsMode;
        ui->toolBox->setCurrentWidget(ui->pageRespawns);
    } else {
        mListViewMode = E_ObjectsMode;
        ui->toolBox->setCurrentWidget(ui->pageObjects);
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::onItemMove(quint32 id, QPointF position,
        qreal angle, bool isRespawn)
{
    if (!mCurrentMap) {
        return;
    }

    if( !isRespawn ) {
        mListViewMode = E_ObjectsMode;
        containers::TObjectItem* object = mCurrentMap->objects().item(id);
        object->setPos(position.toPoint());
        object->setAngle(angle);
    } else {
        mListViewMode = E_RespawnsMode;
        containers::TRespawnItem* respawn = mCurrentMap->respawns().item(id);
        respawn->setPos(position.toPoint());
    }

    updateListView();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateMapView()
{
    mMapsViewModel->clear();
    for (auto it = mMaps->begin(); it != mMaps->end(); ++it) {
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
    if( !mCurrentMap )
        return;

    mListViewModel->clear();
    if (mListViewMode == E_ObjectsMode) {
        auto it = mCurrentMap->objects().constBegin();
        for (; it != mCurrentMap->objects().constEnd(); ++it) {
            TObjectHelper::addItemToModel((*it), mListViewModel,
                    QIcon(QPixmap((*it).resourceFile())));
        }
    } else if (mListViewMode == E_RespawnsMode) {
        auto it = mCurrentMap->respawns().constBegin();
        for (; it != mCurrentMap->respawns().constEnd(); ++it) {
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
    mSceneView->viewport()->repaint();

    auto it = mCurrentMap->objects().constBegin();
    for (; it != mCurrentMap->objects().constEnd(); ++it) {
        const containers::TObjectItem& object = *it;
        TStaticObject* mapObject = new TStaticObject(
                QPixmap(object.resourceFile()));
        mapObject->setPos(object.pos());
        mapObject->setObjectId(object.itemId());
        mapObject->setAngle(object.angle());
        mScene->addItem(mapObject);
    }

    auto it2 = mCurrentMap->respawns().constBegin();
    for (; it2 != mCurrentMap->respawns().constEnd(); ++it2) {
        const containers::TRespawnItem& respawn = *it2;
        TRespawnObject* mapObject = new TRespawnObject(
                QPixmap(respawn.resourceFile()));
        mapObject->setPos(respawn.pos());
        mapObject->setObjectId(respawn.itemId());
        mapObject->setSpawnRadius(respawn.spawnRadius());
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
void TMapsEditorForm::resetZoom()
{
    mSceneView->resetZoom();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::toggleGridAction()
{
    mSceneView->setGridVisible(!mSceneView->isGridVisible());
    mSceneView->viewport()->repaint();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::setDarkGrid()
{
    mSceneView->setGridColor(Qt::black);
    mSceneView->viewport()->repaint();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::setLightGrid()
{
    mSceneView->setGridColor(Qt::gray);
    mSceneView->viewport()->repaint();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::setBidGrid()
{
    mSceneView->setGridSize(100);
    mSceneView->viewport()->repaint();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::setSmallGrid()
{
    mSceneView->setGridSize(10);
    mSceneView->viewport()->repaint();
}
//------------------------------------------------------------------------------
void TMapsEditorForm::addNewRespawn()
{
    containers::TRespawnItem respawn;
    mCurrentMap->respawns().addItem(respawn);
    updateListView();
}
//------------------------------------------------------------------------------
