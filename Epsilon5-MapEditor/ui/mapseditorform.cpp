// mapseditorform.cpp
#include "containers/mapcontainer.h"
#include "global.h"
#include "mapseditorform.h"
#include "ui_mapseditorform.h"
//------------------------------------------------------------------------------
TMapsEditorForm::TMapsEditorForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TMapsEditorForm)
    , mMaps(new TMapContainer(this))
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    ui->browserGroupBox->setLayout(ui->horizontalLayout);

    mMaps->setBaseDirectory(Global::Settings()->GetMapsPath());
    //mMaps->loadMapFromFile("");
    mMaps->loadFromFile(Global::Settings()->GetMapsPath() + "/maplist.txt");
    ui->mapsView->setModel(mMaps->model());
}
//------------------------------------------------------------------------------
TMapsEditorForm::~TMapsEditorForm()
{
    delete ui;
}
//------------------------------------------------------------------------------
