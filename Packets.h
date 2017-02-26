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
    unsigned short speed;
    char metadataIndex; //Only used when color shift etc.
    KeyColorType type;
    unsigned char unknown3;
    ColorKey key;
} PacketData;

struct PacketDisplayState : Packet {
    char state;
    PacketDisplayState(DisplayState state){
        packetId = 0x0D;
        this->state = state;
    }
} PacketData;

struct PacketColorEntry {
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    KeyColor asColor(){
        return {red, green, blue};
    }

    char b3;
    short speed; //Time before playing or next playing (int 10 ms  (10 = 100ms)) must be > 200 i think
    char index; //index

    char b7;
} PacketData;

struct PacketColorData : Packet {
    PacketColorData(){
        packetId = 0x0B;
        memset(startColors, 0, 6);
        memset(entries, 0, 16*sizeof(PacketColorEntry));
        b1 = 0xff;
        memset(b2, 0, 11);
        memset(zeroDelimiter, 0, 8);
    }

    short metaId;
    PacketColorEntry entries[16]; //Max transfared 11 lol

    char startColors[6]; // F0 0F F0 0F F0 0F -> FF FF FF |  00 00 00 00 00 00 -> 00 00 00

    KeyColor getStartColor(){
        return {(startColors[0] & 0xF0) | (startColors[1] & 0xF), (startColors[2] & 0xF0) | (startColors[3] & 0xF), (startColors[4] & 0xF0) | (startColors[5] & 0xF)};
    }
    void setStartColor(KeyColor color){
        startColors[0] = (color.r >> 4) << 4;
        startColors[1] = color.r & 0xF;

        startColors[2] = (color.g >> 4) << 4;
        startColors[3] = color.g & 0xF;

        startColors[4] = (color.b >> 4) << 4;
        startColors[5] = color.b & 0xF;
    }

    char b1; //FF?

    char b2[11]; //mostly zero

    short entryCount;

    short maxTime;

    char zeroDelimiter[8];

} PacketData;