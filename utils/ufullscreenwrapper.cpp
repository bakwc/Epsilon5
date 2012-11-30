#include <QtGlobal>
#include <QDebug>
#include <QDesktopWidget>

#ifdef Q_WS_X11
#include <X11/extensions/Xrandr.h>
#endif

#ifdef Q_WS_WIN32
#include <Windows.h>
DEVMODE devMode;
#endif

#include "ufullscreenwrapper.h"

using namespace utils;
//------------------------------------------------------------------------------
Rotation originRotation = RR_Rotate_0;
short originSizeId = 0;
//------------------------------------------------------------------------------
UFullscreenWrapper::UFullscreenWrapper(QWidget* parent)
    : m_parent(parent)
{
}
//------------------------------------------------------------------------------
UFullscreenWrapper::DisplayModes UFullscreenWrapper::enumModes()
{
    DisplayModes displayModes;
#ifdef Q_WS_X11
    int num_modes;
    Display *dpy = XOpenDisplay(NULL);
    XRRScreenSize* xrrs = XRRSizes(dpy, 0, &num_modes);

    for(int i = 0; i < num_modes; ++i)
        displayModes.append(DisplayMode(xrrs[i].width, xrrs[i].height));
#endif
    return displayModes;
}
//------------------------------------------------------------------------------
bool UFullscreenWrapper::changeToMode(int width, int height)
{
    return changeToMode(DisplayMode(width, height));
}
//------------------------------------------------------------------------------
int UFullscreenWrapper::findModeId(int width, int height)
{
    const DisplayModes& dms = enumModes();
    for(int i = 0; i < dms.count(); ++i) {
        if(dms.at(i).width() == width && dms.at(i).height() == height)
            return i;
    }
    return -1;
}
//------------------------------------------------------------------------------
bool UFullscreenWrapper::changeToMode(const DisplayMode &mode)
{
#ifdef Q_WS_WIN32
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
    devMode.dmPelsWidth = (unsigned long) mode.width();
    devMode.dmPelsHeight = (unsigned long) mode.height();
    if(ChangeDisplaySettings(&devMode, CDS_TEST) != DISP_CHANGE_SUCCESSFUL)
        return false;
    if(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        return false;
#endif
#ifdef Q_WS_X11
    Display *dpy = XOpenDisplay(NULL);
    Window root = RootWindow(dpy, 0);
    XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
    originSizeId = XRRConfigCurrentConfiguration(conf, &originRotation);

    int sizeId = findModeId(mode.width(), mode.height());
    if( sizeId < 0 )
        return false;

    if(BadValue == XRRSetScreenConfig(
        dpy, conf, root, sizeId, RR_Rotate_0, CurrentTime)
    )
        return false;
#endif
    if( !m_parent )
        return true;

    m_parent->setWindowState(m_parent->windowState() | Qt::WindowFullScreen);
    m_parent->setFixedSize(mode.width(), mode.height());
    m_parent->activateWindow();
    return true;
}
//------------------------------------------------------------------------------
bool UFullscreenWrapper::restoreMode()
{
#ifdef Q_WS_WIN32
    if(ChangeDisplaySettings(NULL, 0) != DISP_CHANGE_SUCCESSFUL)
        return false;
#endif
#ifdef Q_WS_X11
    Display *dpy = XOpenDisplay(NULL);
    Window root = RootWindow(dpy, 0);
    XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
    if(BadValue == XRRSetScreenConfig(
        dpy, conf, root, originSizeId, originRotation, CurrentTime)
    )
        return false;
#endif
    if( !m_parent )
        return true;

    m_parent->setWindowState(m_parent->windowState() & ~Qt::WindowFullScreen);
    m_parent->setFixedSize(m_parent->baseSize());
    m_parent->activateWindow();
    return true;
}
//------------------------------------------------------------------------------
