//
// Created by wolverindev on 14.01.17.
//

#include "Keyboard.h"
#include "Packets.h"

using namespace std;
Keyboard::Keyboard(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number) : handle(nullptr) {
    handle = hid_open(vendor_id, product_id, serial_number);
}

bool Keyboard::isValid() {
    if(!handle)
        return false;
    return true;
}

void Keyboard::setStaticColor(DisplayState state, ColorKey key, KeyColor color) {
    vector<pair<ColorKey, KeyColor>> vec;
    vec.push_back({key, color});
    setStaticColor(state, vec);
}

typedef pair<ColorKey, KeyColor> ColorPair;
void Keyboard::setStaticColor(DisplayState state, int size, ColorPair keys, ...) {
    vector<pair<ColorKey, KeyColor>> ckeys;
    va_list zeiger;
    va_start(zeiger, keys);
    for(int i = 0;i<size;i++){
        ckeys.push_back(va_arg(zeiger, ColorPair));
    }
    va_end(zeiger);
    setStaticColor(state, ckeys);
}

void Keyboard::setStaticColor(DisplayState state, vector<pair<ColorKey, KeyColor>> keys) {
    PacketColorBulkKeyData cdata[keys.size()];
    int i = 0;
    for(auto it = keys.begin(); it != keys.end(); it++)
        cdata[i++] = PacketColorBulkKeyData{it->second, {0, 0, 0}, 0x00, 0x00, 0x00, KeyColorType::STATIC, 0x00, it->first}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09

    int bufferSize = 0x04 + (keys.size() + 1) * sizeof(PacketColorBulkKeyData); //+1 for end delimiter
    unsigned char buffer[bufferSize];
    memset(buffer, 0, bufferSize);

    int index = 0;

    buffer[index++] = 0x0E; // |
    buffer[index++] = 0x00; // | Short (packetId)

    //TODO other id for sleeping mode!
    buffer[index++] = 0x2A; // | subId
    buffer[index++] = state;

    for(int i = 0;i<keys.size();i++){
        memcpy(buffer + index, &cdata[i], sizeof(PacketColorBulkKeyData));
        index += sizeof(PacketColorBulkKeyData);
    }

    hid_send_feature_report(this->handle, buffer, bufferSize);
}

void Keyboard::setDisplayState(DisplayState state) {
    int bufferSize = sizeof(PacketDisplayState) + 1;
    unsigned char buffer[bufferSize];
    memset(buffer, 0, bufferSize);

    PacketDisplayState pack(state);
    memcpy(buffer, &pack, sizeof(PacketDisplayState));

    hid_write(this->handle, buffer, bufferSize);
}