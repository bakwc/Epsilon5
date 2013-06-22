#include "main.h"

#include "CCEGLView.h"

#include "Graphics/AppDelegate.h"
#include "Context.h"

using namespace cocos2d;

// uncomment below line, open debug console
#define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    std::unique_ptr<Context> context(new Context);
    
    AppDelegate app(context.get());
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(480, 320);

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
