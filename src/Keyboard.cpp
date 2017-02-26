//
// Created by wolverindev on 14.01.17.
//

#include "../include/Steelseries/Keyboard.h"

#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace Steelseries::M800;
using namespace Steelseries::USB::Packets;

using namespace std;
Keyboard::Keyboard(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number) : handle(nullptr) {
    handle = hid_open(vendor_id, product_id, serial_number);
}

bool Keyboard::isValid() {
    if(!handle)
        return false;
    return true;
}

void Keyboard::setStaticColor(DisplayState state, ColoredKey key, KeyColor color) {
    vector<pair<ColoredKey, KeyColor>> vec;
    vec.push_back({key, color});
    setStaticColor(state, vec);
}

typedef pair<ColoredKey, KeyColor> ColorPair;
void Keyboard::setStaticColor(DisplayState state, int size, ColorPair keys, ...) {
    vector<pair<ColoredKey, KeyColor>> ckeys;
    va_list zeiger;
    va_start(zeiger, keys);
    for(int i = 0;i<size;i++){
        ckeys.push_back(va_arg(zeiger, ColorPair));
    }
    va_end(zeiger);
    setStaticColor(state, ckeys);
}

void Keyboard::setStaticColor(DisplayState state, vector<pair<ColoredKey, KeyColor>> keys) {
    vector<pair<ColoredKey, KeyColor>> copy = vector<pair<ColoredKey, KeyColor>>(keys);
    int loop = 0;
    while(!copy.empty()){
        int size = min((int) copy.size(), 0x2A);
        PacketKeyDataEntry cdata[size];
        for(int i = 0;i<size && !copy.empty();i++){
            auto it = copy.begin();
            auto key = this->changeKeyType<KeyData>(it->first, KeyColorType::STATIC);
            if(key->color != it->second){
                cdata[i] = PacketKeyDataEntry{it->second, {0, 0, 0}, 0, 0x01, KeyColorType::STATIC, 0x00, it->first}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09
                key->color = it->second;
            } else i--;
            copy.erase(copy.begin(), copy.begin()+1);
        }
        sendKeyBulkData(state, size, cdata);
        loop ++;
    }
}

void Keyboard::setReactiveColor(DisplayState state, std::vector<ReactiveKey> keys) {
    vector<ReactiveKey> copy = vector<ReactiveKey>(keys);
    int loop = 0;
    while(!copy.empty()){
        int size = min((int) copy.size(), 0x2A);
        PacketKeyDataEntry cdata[size];
        for(int i = 0;i<size && !copy.empty();i++){
            auto it = copy.begin();
            auto key = this->changeKeyType<ReactiveKeyData>(it->key, KeyColorType::REACTIVE);
            if(key->color != it->normal || key->reactiveColor != it->active || key->speed != it->speed){
                key->color = it->normal;
                key->reactiveColor = it->active;
                key->speed = it->speed;
                cdata[i] = PacketKeyDataEntry{it->normal, it->active, (uint16_t) floor(it->speed * 100), 0x00, KeyColorType::REACTIVE, 0x00, it->key}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09
            } else i--;
            copy.erase(copy.begin(), copy.begin()+1);
        }
        sendKeyBulkData(state, size, cdata);
        loop ++;
    }
}

void Keyboard::setKeyMetaSlot(DisplayState state, ColoredKey key, char slot) {
    vector<pair<ColoredKey, char>> vec;
    vec.push_back({key, slot});
    setKeyMetaSlot(state, vec);
}

typedef pair<ColoredKey, char> MetaPair;
void Keyboard::setKeyMetaSlot(DisplayState state, int size, MetaPair keys, ...) {
    vector<MetaPair> ckeys;
    va_list zeiger;
    va_start(zeiger, keys);
    for(int i = 0;i<size;i++){
        ckeys.push_back(va_arg(zeiger, MetaPair));
    }
    va_end(zeiger);
    setKeyMetaSlot(state, ckeys);
}

void Keyboard::setKeyMetaSlot(DisplayState state, std::vector<std::pair<ColoredKey, char>> keys) {
    PacketKeyDataEntry cdata[keys.size()];
    int i = 0;
    for(auto it = keys.begin(); it != keys.end(); it++)
        cdata[i++] = PacketKeyDataEntry{{0, 0, 0}, {0, 0, 0}, 0, it->second, KeyColorType::OFF, 0x00, it->first}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09
    sendKeyBulkData(state, keys.size(), cdata);
}

void Keyboard::setDisplayState(DisplayState state) {
    int bufferSize = sizeof(PacketDisplayState) + 1 ;
    unsigned char buffer[bufferSize];
    memset(buffer, 0, bufferSize);

    PacketDisplayState pack(state);
    memcpy(buffer, &pack, sizeof(PacketDisplayState));

    hid_write(this->handle, buffer,bufferSize);
}

void Keyboard::sendKeyBulkData(DisplayState state, int n, PacketKeyDataEntry *data) {
    int bufferSize = 0x04 + n * sizeof(PacketKeyDataEntry); //+1 for end delimiter
    uint8_t buffer[bufferSize];
    memset(buffer, 0, bufferSize);

    int index = 0;

    buffer[index++] = 0x0E; // |
    buffer[index++] = 0x00; // | Short (packetId)

    buffer[index++] = (uint8_t) n; // | Override length? Keyboard must have 4 or more sections
    buffer[index++] = state;

    for(int i = 0;i<n;i++){
        memcpy(buffer + index, &data[i], sizeof(PacketKeyDataEntry));
        index += sizeof(PacketKeyDataEntry);
    }

    hid_send_feature_report(this->handle, buffer, bufferSize);
}


KeyData* Keyboard::getKey(ColoredKey key) {
    if(this->keys.count(key) == 0){
        KeyData* data = new KeyData;
        data->key = key;
        data->color = {0,0,0};
        data->type = KeyColorType::OFF;
        this->keys[key] = data;
    }
    return this->keys[key];
}

template <typename T>
T* Keyboard::changeKeyType(ColoredKey key, KeyColorType type){
    KeyData* data = getKey(key);
    if(data->type != type || data->as<T>() == nullptr){
        T* _new = new T;
        KeyData* knew = (KeyData*) _new;
        knew->type = type;
        knew->key = key;
        knew->color = data->color;
        this->keys[key] = knew;
        delete data;
        data = knew;
    }
    return data->as<T>();
}