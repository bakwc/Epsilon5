#include "cocos2d.h"

#include "CCEGLView.h"
#include "AppDelegate.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

#include "GraphicsException.h"
#include "World/World.h"
#include "Network/NetworkService.h"
#include "Network/MessageProcessor.h"

using namespace CocosDenshion;
using namespace cocos2d;

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate()
try {
    SimpleAudioEngine::end();

    mNetwork->close();
} catch (Exception& e) {
    handleException(e);
}

bool AppDelegate::applicationDidFinishLaunching()
try {
    mWorld = std::make_shared<World>();
    auto processor = std::make_shared<MessageProcessor>(mWorld);
    mNetwork = std::make_shared<NetworkService>(processor);

    mNetwork->connect("193.169.33.254", 14567);

    Epsilon5::Auth message;
    message.set_name("Marvel");
    message.set_password("test");
    mNetwork->send(PacketType::PlayerAuth, message);

    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    pDirector->setDisplayStats(true);

    CCScene *pScene = GameScene::scene();
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
