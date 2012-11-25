#pragma once

enum EPlayerStatus {
    PS_NotConnected,
    PS_AuthWait,
    PS_Spawned,
    PS_Dead
};

enum EPacketType {
    PT_World,
    PT_Control,
    PT_PlayerAuth,
    PT_PlayerInfo
};
