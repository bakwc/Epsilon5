#pragma once

#include <memory>

#include "cocos2d.h"

class Context;

class AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();

private:
    std::shared_ptr<Context> mContext;
};
