#include <QtGlobal>
#include <QDesktopWidget>

#ifdef Q_WS_X11
//#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#endif

#ifdef Q_WS_WIN32
#include <Windows.h>
DEVMODE devMode;
#endif

#include "ufullscreenwrapper.h"

UFullscreenWrapper::UFullscreenWrapper(QWidget* parent)
    : m_parent(parent)
{
}

UFullscreenWrapper::DisplayModes UFullscreenWrapper::enumModes()
{
    DisplayModes displayModes;
#ifdef Q_WS_X11
    int num_modes;
    QDesktopWidget dw;
    Display *dpy = XOpenDisplay(NULL);
    Window root = RootWindow(dpy, 0);
    XRRScreenSize* xrrs = XRRSizes(dpy, dw.screenNumber(m_parent), &num_modes);

    for( int i = 0; i < num_modes; ++i )
    {
        displayModes.append(DisplayMode(xrrs[i].width, xrrs[i].height));
    }
#endif
    return displayModes;
}

bool UFullscreenWrapper::changeToMode(int width, int height, int bpp)
{
    return changeToMode(DisplayMode(width, height, bpp));
}

bool UFullscreenWrapper::changeToMode(const DisplayMode &mode)
{
#ifdef Q_OS_WIN32
    EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode);
    devMode.dmPelsWidth = (unsigned long) mode.width();
    devMode.dmPelsHeight = (unsigned long) mode.height();
    if(ChangeDisplaySettings(&devMode, CDS_TEST) != DISP_CHANGE_SUCCESSFUL)
        return false;
    if(ChangeDisplaySettings(&devMode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        return false;
#endif
    m_parent->setWindowState(m_parent->windowState() | Qt::WindowFullScreen);
    m_parent->setFixedSize(mode.width(), mode.height());
    return true;
}

bool UFullscreenWrapper::restoreMode()
{
#ifdef Q_OS_WIN32
    if(ChangeDisplaySettings(NULL, 0) == DISP_CHANGE_SUCCESSFUL)
        return false;
#endif
    m_parent->setWindowState(m_parent->windowState() & Qt::WindowFullScreen);
    m_parent->setFixedSize(m_parent->baseSize());
    return true;
}
