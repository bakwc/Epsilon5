#pragma once

class TApplication;

const qreal OBJECT_SCALE_UP = 10;
const qreal OBJECT_SCALE_DOWN = 1 / OBJECT_SCALE_UP;
const quint16 WORLD_BORDER_SIZE = 4 * OBJECT_SCALE_UP;
const size_t WORLD_BORDER_ID = -1;
const qreal VEHICLE_ENTER_DISTANCE = 10;


#define GApp ((TApplication*)qApp)
#define GWorld GApp->GetWorld()

enum ETeam {
    T_One,
    T_Second,
    T_Neutral
};
