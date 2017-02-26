//
// Created by wolverindev on 14.01.17.
//
#pragma once
#include <iostream>
#include <hidapi/hidapi.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include "Definitions.h"
#include "Packets.h"

class Keyboard {

    public:
        Keyboard(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number);

        bool isValid();


        void setStaticColor(DisplayState state, ColorKey key, KeyColor color);

        void setStaticColor(DisplayState state, int size, std::pair<ColorKey, KeyColor> keys, ...);

        void setStaticColor(DisplayState state, std::vector<std::pair<ColorKey, KeyColor>> keys);


        void setReactiveColor(DisplayState state, std::vector<ReactiveKey> keys);

        void setKeyMetaSlot(DisplayState state, ColorKey key, char slot);

        void setKeyMetaSlot(DisplayState state, int size, std::pair<ColorKey, char> keys, ...);

        void setKeyMetaSlot(DisplayState state, std::vector<std::pair<ColorKey, char>> keys);

        void setDisplayState(DisplayState state);


        hid_device* getDevice(){
            return handle;
        }

        void sendKeyBulkData(DisplayState state, int n, PacketKeyDataEntry* data);
    private:
        hid_device* handle = nullptr;
};
