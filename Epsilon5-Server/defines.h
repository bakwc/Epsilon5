#pragma once

const qreal OBJECT_SCALE_UP = 10;
const qreal OBJECT_SCALE_DOWN = 1 / OBJECT_SCALE_UP;
const quint16 WORLD_BORDER_SIZE = 4 * OBJECT_SCALE_UP;
const size_t WORLD_BORDER_ID = -1;
const size_t WORLD_FULL_PACKET_RESEND_COUNT = 80; // Resend full packet after N regular packets

