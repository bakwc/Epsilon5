#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class World;
class NetworkService;
class Controller;

class GameScene : public cocos2d::CCLayer {
public:
    virtual bool init();

    static cocos2d::CCScene* scene(World* world, Controller* controller);
    CREATE_FUNC(GameScene);

    virtual void onEnter() override;
    virtual void onExit() override;

    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) override;
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) override;
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) override;
    virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event) override;
    virtual void didAccelerate(cocos2d::CCAcceleration* acceleration) override;

    void menuCloseCallback(CCObject* pSender);
    void update();
    void tick(float dt);

private:
    World* mWorld;
    Controller* mController;
    cocos2d::CCSprite* mBackground;
    cocos2d::CCPoint mCenter;
};
