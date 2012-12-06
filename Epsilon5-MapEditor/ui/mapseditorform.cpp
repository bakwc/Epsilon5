// mapseditorform.cpp
#include <QResizeEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "containers/mapcontainer.h"
#include "global.h"
#include "mapseditorform.h"
#include "ui_mapseditorform.h"
//------------------------------------------------------------------------------
TMapsEditorForm::TMapsEditorForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TMapsEditorForm)
    , mMaps(new TMapContainer(this))
    , mScene(new QGraphicsScene(this))
    , mView(new QGraphicsView(mScene, this))
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    ui->browserGroupBox->setLayout(ui->horizontalLayout);
    ui->sceneGroupBox->setLayout(ui->sceneLayout);

    ui->sceneLayout->addWidget(mView);
    mScene->addSimpleText("Testing");

    mMaps->setBaseDirectory(Global::Settings()->GetMapsPath());
    mMaps->loadFromFile(Global::Settings()->GetMapsPath() + "/maplist.txt");
    ui->mapsView->setModel(mMaps->model());


}
//------------------------------------------------------------------------------
TMapsEditorForm::~TMapsEditorForm()
{
    delete ui;
}
//------------------------------------------------------------------------------
void TMapsEditorForm::resizeEvent(QResizeEvent *event)
{

}
//------------------------------------------------------------------------------
