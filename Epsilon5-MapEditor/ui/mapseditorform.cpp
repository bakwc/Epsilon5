// mapseditorform.cpp
#include <QMenu>
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "containers/mapcontainer.h"
#include "global.h"
#include "mapseditorform.h"
#include "ui_mapseditorform.h"
//------------------------------------------------------------------------------
TMapsEditorForm::TMapsEditorForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TMapsEditorForm)
    , mMaps(new TMapContainer(this))
    , mScene(new QGraphicsScene(this))
    , mView(new QGraphicsView(mScene, this))
{
    ui->setupUi(this);

    // Additional ui setups
    setLayout(ui->mainLayout);
    ui->browserGroupBox->setLayout(ui->horizontalLayout);
    ui->sceneGroupBox->setLayout(ui->sceneLayout);
    ui->sceneLayout->addWidget(mView);
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

    // Just for testing...
    mScene->addSimpleText("Testing");
    mMaps->setBaseDirectory(Global::Settings()->GetMapsPath());
    mMaps->loadFromFile("maplist.txt");
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
void TMapsEditorForm::setObjectsModel(QAbstractItemModel *model)
{
    ui->objectsView->setModel(model);
}
//------------------------------------------------------------------------------
void TMapsEditorForm::on_mapsView_clicked(QModelIndex index)
{
    ui->mapNameEdit->setText(mMaps->mapName(index));
    ui->mapWidthBox->setValue(mMaps->mapWidth(index));
    ui->mapHeightBox->setValue(mMaps->mapHeight(index));

    if( ui->toolBox->currentWidget() == ui->pageObjects )
    {
        ui->listView->setModel(mMaps->objectModel(index));

    }
    else if( ui->toolBox->currentWidget() == ui->pageRespawns )
    {
        ui->listView->setModel(mMaps->respawnModel(index));
    }
}
//------------------------------------------------------------------------------
void TMapsEditorForm::updateMapSettings()
{
    QModelIndex index = ui->mapsView->currentIndex();
    if( !index.isValid() )
        return;

    mMaps->setMapName(index, ui->mapNameEdit->text().trimmed());
    mMaps->setMapWidth(index, ui->mapWidthBox->value());
    mMaps->setMapHeight(index, ui->mapHeightBox->value());
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
