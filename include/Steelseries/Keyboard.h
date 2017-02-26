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
#include <map>
#include "Definitions.h"
#include "USBPackets.h"

using namespace std;
namespace Steelseries {
    namespace M800 {
        struct KeyData {
            ColoredKey key;
            KeyColorType type;
            KeyColor color;

            template <typename T>
            T* as(){
                return (T*) this;
            }
        };

        struct ReactiveKeyData : public KeyData{
            KeyColor reactiveColor;
            float speed; //in ms
        };

        class Keyboard {

            public:
                Keyboard(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number);

                bool isValid();


                void setStaticColor(DisplayState state, ColoredKey key, KeyColor color);

                void setStaticColor(DisplayState state, int size, std::pair<ColoredKey, KeyColor> keys, ...);

                void setStaticColor(DisplayState state, std::vector<std::pair<ColoredKey, KeyColor>> keys);


                void setReactiveColor(DisplayState state, std::vector<ReactiveKey> keys);

                void setKeyMetaSlot(DisplayState state, ColoredKey key, char slot);

                void setKeyMetaSlot(DisplayState state, int size, std::pair<ColoredKey, char> keys, ...);

                void setKeyMetaSlot(DisplayState state, std::vector<std::pair<ColoredKey, char>> keys);

                void setDisplayState(DisplayState state);

                KeyData* getKey(ColoredKey key);

                hid_device* getDevice(){
                    return handle;
                }

                void sendKeyBulkData(DisplayState state, int n, Steelseries::USB::Packets::PacketKeyDataEntry* data);
            private:
                template <typename T>
                T* changeKeyType(ColoredKey key, KeyColorType);

                hid_device* handle = nullptr;
                map<ColoredKey, KeyData*> keys;
        };
    }
}
