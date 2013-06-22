#include "GameScene.h"

#include "GraphicsException.h"
#include "World/World.h"
#include "World/Controller.h"

using namespace cocos2d;

CCScene* GameScene::scene(World* world, Controller* controller) {
    CCScene* scene = CCScene::create();
    checkGraphics(scene);

    GameScene* layer = GameScene::create();
    checkGraphics(layer);

    layer->mWorld = world;
    layer->mController = controller;

    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
try {
    checkGraphics(CCLayer::init());

    this->setAccelerometerEnabled(true);
    this->setTouchEnabled(true);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    mCenter = ccp(size.width/2, size.height/2);

    mBackground = CCSprite::create("peka.png");
    checkGraphics(mBackground);

    mBackground->setPosition(mCenter);

    this->addChild(mBackground, 0);

    this->schedule(schedule_selector(GameScene::tick), 0.1f);
    /*
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        this,
        menu_selector(GameScene::menuCloseCallback));
    checkGraphics(pCloseItem);

    pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    checkGraphics(pMenu);

    this->addChild(pMenu, 1);

    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    checkGraphics(pLabel);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition(ccp(size.width / 2, size.height - 50));

    this->addChild(pLabel, 1);

    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    checkGraphics(pSprite);

    pSprite->setPosition(ccp(size.width/2, size.height/2));

    this->addChild(pSprite, 0);
    */
    return true;
} catch (Exception& e) {
    handleException(e);
    return false;
}

void GameScene::onEnter() {
    CCLayer::onEnter();
    mWorld->setUpdateFunc(std::bind(&GameScene::update, this));
}

void GameScene::onExit() {
    CCLayer::onExit();
    mWorld->setUpdateFunc(std::function<void()>());
}

void GameScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
    mController->updateTouch(true);
}

void GameScene::ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
    auto touch = static_cast<cocos2d::CCTouch*>(touches->anyObject());
    CCPoint point = touch->getLocation();
    mController->updateAngle(point.x - mCenter.x, point.y - mCenter.y);
}

void GameScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
    mController->updateTouch(false);
}

void GameScene::ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
    mController->updateTouch(false);
}

void GameScene::didAccelerate(cocos2d::CCAcceleration* acceleration) {
    mController->updateAcceleration(acceleration);
}

void GameScene::menuCloseCallback(CCObject* pSender)
try {
    CCDirector::sharedDirector()->end();
} catch (Exception& e) {
    handleException(e);
}

void GameScene::update()
try {
} catch (Exception& e) {
    handleException(e);
}

void GameScene::tick(float dt)
try {
    mController->tick();
} catch (Exception& e) {
    handleException(e);
}
