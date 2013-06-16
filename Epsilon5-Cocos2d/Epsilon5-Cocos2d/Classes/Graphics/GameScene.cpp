#include "GameScene.h"

#include "GraphicsException.h"

using namespace cocos2d;

CCScene* GameScene::scene() {
    CCScene* scene = CCScene::create();
    checkGraphics(scene);

    GameScene* layer = GameScene::create();
    checkGraphics(layer);

    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
try {
    checkGraphics(CCLayer::init());

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

    return true;
} catch (Exception& e) {
    handleException(e);
    return false;
}

void GameScene::menuCloseCallback(CCObject* pSender)
try {
    CCDirector::sharedDirector()->end();
} catch (Exception& e) {
    handleException(e);
}
