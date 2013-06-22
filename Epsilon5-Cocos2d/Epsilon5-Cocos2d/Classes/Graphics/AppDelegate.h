#pragma once

#include <memory>

#include "cocos2d.h"

class Context;

class AppDelegate : private cocos2d::CCApplication
{
public:
    AppDelegate(Context* context);
    virtual ~AppDelegate();

    virtual bool applicationDidFinishLaunching() override;
    virtual void applicationDidEnterBackground() override;
    virtual void applicationWillEnterForeground() override;

private:
    Context* mContext;
};
