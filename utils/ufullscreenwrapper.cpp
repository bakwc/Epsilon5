#include <QtGlobal>
#include <QDesktopWidget>

#ifdef Q_WS_X11
//#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#endif

#include "ufullscreenwrapper.h"

UFullscreenWrapper::UFullscreenWrapper(QWidget* parent)
    : m_parent(parent)
{
}

UFullscreenWrapper::DisplayModes UFullscreenWrapper::enumModes()
{
    int num_modes;
    QDesktopWidget dw;
    Display *dpy = XOpenDisplay(NULL);
    Window root = RootWindow(dpy, 0);
    XRRScreenSize* xrrs = XRRSizes(dpy, dw.screenNumber(m_parent), &num_modes);

    DisplayModes displayModes;
    for( int i = 0; i < num_modes; ++i )
    {
        displayModes.append(DisplayMode(xrrs[i].width, xrrs[i].height));
    }

    return displayModes;
}

void UFullscreenWrapper::changeToMode(int width, int height, int bpp)
{
    changeToMode(DisplayMode(width, height, bpp));
}

void UFullscreenWrapper::changeToMode(const DisplayMode &mode)
{
}
