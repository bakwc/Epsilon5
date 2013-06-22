#include "cocos2d.h"

#include "CCEGLView.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

#include "GraphicsException.h"
#include "Epsilon5.pb.h"
#include "Context.h"
#include "Network/NetworkService.h"
#include "Settings.h"

using namespace CocosDenshion;
using namespace cocos2d;

AppDelegate::AppDelegate(Context* context) : mContext(context) {
}

AppDelegate::~AppDelegate()
try {
    SimpleAudioEngine::end();

    mContext->get<NetworkService>()->close();
} catch (Exception& e) {
    handleException(e);
}

bool AppDelegate::applicationDidFinishLaunching()
try {
    auto service = mContext->get<NetworkService>();
    auto settings = mContext->get<Settings>();
    service->connect(settings->get("Host"), settings->get("Port"));

    Epsilon5::Auth message;
    message.set_name(settings->getString("UserName"));
    message.set_password(settings->getString("Password"));
    service->send(PacketType::PlayerAuth, message);

    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    pDirector->setDisplayStats(true);

    CCScene *pScene = GameScene::scene(mContext->get<World>(), mContext->get<Controller>());
    pDirector->runWithScene(pScene);
    return true;
} catch (Exception& e) {
    handleException(e);
    return false;
}

void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
