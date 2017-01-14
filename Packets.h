//
// Created by wolverindev on 14.01.17.
//

#pragma once

#include "Definitions.h"

#define PacketData __attribute__((packed))

/*
 * One key (Size: 0x0C):
	ÿÿÿ...,....@
	Main color:
		0x00 R
		0x01 G
		0x02 B
	Second color: (0 0 0  when unused)
		0x00 R
		0x01 G
		0x02 B
	Unknown[8]
		0x06 -> most 0x2C
		0x07 -> most 0x01  |
		0x08 -> most 0x00  | Short?
		0x09 -> Color type |
		0x0A -> most 0x00  | Short
	key:
		0x0B (Isnt equal to VK)
 */



struct Packet {
    short packetId;
} PacketData;

struct PacketColorBulkKeyData {
    KeyColor mainColor;
    KeyColor secondaryColor;
    char unknown;
    char unknown0;
    char unknown1;
    KeyColorType type;
    char unknown3;
    ColorKey key;
} PacketData;

struct PacketDisplayState : Packet {
    char state;
    PacketDisplayState(DisplayState state){
        packetId = 0x0D;
        this->state = state;
    }
} PacketData;