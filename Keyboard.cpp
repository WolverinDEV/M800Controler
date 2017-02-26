//
// Created by wolverindev on 14.01.17.
//

#include "Keyboard.h"
#include "Packets.h"

#include <sstream>
#include <iomanip>

using namespace std;
void hexDump (void *addr, int len, int pad, void (*print)(string)) {
    int i;
    unsigned char buff[pad+1];
    unsigned char *pc = (unsigned char*)addr;

    if (len <= 0) {
        return;
    }

    stringstream line;
    line << uppercase << hex << setfill('0');
    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % pad) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                line << buff << endl;

            // Output the offset.
            line << setw(4) << i << "    ";
        }
        if(i % 8 == 0 && i % pad != 0){
            line << "| ";
        }

        // Now the hex code for the specific character.
        line << setw(2) << (int) pc[i] << " ";

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % pad] = '.';
        else
            buff[i % pad] = pc[i];
        buff[(i % pad) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % pad) != 0) {
        line << "   ";
        i++;
    }

    line << buff << endl;
    line << "Length: " << dec << len << " Addr: " << addr << endl;
    print(line.str());
}

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
    vector<pair<ColorKey, KeyColor>> copy = vector<pair<ColorKey, KeyColor>>(keys);
    int loop = 0;
    while(!copy.empty()){
        int size = min((int) copy.size(), 0x2A);
        PacketColorBulkKeyData cdata[size];
        for(int i = 0;i<size;i++){
            auto it = copy.begin();
            cdata[i] = PacketColorBulkKeyData{std::move(it->second), {0, 0, 0}, 0, 0x01, KeyColorType::STATIC, 0x00, std::move(it->first)}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09
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
        PacketColorBulkKeyData cdata[size];
        for(int i = 0;i<size;i++){
            auto it = copy.begin();
            cdata[i] = PacketColorBulkKeyData{it->normal, it->active, it->speed * 100, 0x00, KeyColorType::REACTIVE, 100, it->key}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09
            copy.erase(copy.begin(), copy.begin()+1);
        }
        sendKeyBulkData(state, size, cdata);
        loop ++;
    }
}

void Keyboard::setKeyMetaSlot(DisplayState state, ColorKey key, char slot) {
    vector<pair<ColorKey, char>> vec;
    vec.push_back({key, slot});
    setKeyMetaSlot(state, vec);
}

typedef pair<ColorKey, char> MetaPair;
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

void Keyboard::setKeyMetaSlot(DisplayState state, std::vector<std::pair<ColorKey, char>> keys) {
    PacketColorBulkKeyData cdata[keys.size()];
    int i = 0;
    for(auto it = keys.begin(); it != keys.end(); it++)
        cdata[i++] = PacketColorBulkKeyData{{0, 0, 0}, {0, 0, 0}, 0, it->second, KeyColorType::OFF, 0x00, it->first}; //Active:  0x2C, 0x01, 0x00 Sleep: 0x00, 0x00, 0x09
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

void Keyboard::sendKeyBulkData(DisplayState state, int n, PacketColorBulkKeyData *data) {
    int bufferSize = 0x04 + 0x01 + (n + 1) * sizeof(PacketColorBulkKeyData); //+1 for end delimiter
    unsigned char buffer[bufferSize];
    memset(buffer, 0, bufferSize);

    int index = 1;

    buffer[index++] = 0x0E; // |
    buffer[index++] = 0x00; // | Short (packetId)

    buffer[index++] = n; // | To override buffer
    buffer[index++] = state;

    for(int i = 0;i<n;i++){
        memcpy(buffer + index, &data[i], sizeof(PacketColorBulkKeyData));
        index += sizeof(PacketColorBulkKeyData);
    }

    hid_send_feature_report(this->handle, buffer, bufferSize);

}