// mainwindow.h
#pragma once
#include <QMainWindow>
//------------------------------------------------------------------------------
class QAction;
class TSettings;
class TObjectsEditorForm;
class TMapsEditorForm;
//------------------------------------------------------------------------------
class TMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit TMainWindow(QWidget* parent = 0);
    ~TMainWindow();

public slots:
    void newAction();
    void openAction();
    void optionsAction();
    void objectsEditorAction();
    void mapsEditorAction();
    void fullscreenAction();

signals:
    void resized();

private:
    void connectMapCreator();
    void resizeEvent(QResizeEvent*);

private:
    QAction* mMapsEditorAction;
    TObjectsEditorForm* mObjectsEditorWidget;
    TMapsEditorForm* mMapsEditorWidget;
};
//------------------------------------------------------------------------------
