// global.h
#pragma once
#include "settings.h"
//------------------------------------------------------------------------------
struct Global {
    static TSettings* Settings() {
        static TSettings settings;
        return &settings;
    }
};
//------------------------------------------------------------------------------
