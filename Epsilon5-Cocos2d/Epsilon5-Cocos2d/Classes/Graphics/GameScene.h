#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class GameScene : public cocos2d::CCLayer {
public:
    virtual bool init();

    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);

    void menuCloseCallback(CCObject* pSender);
};
