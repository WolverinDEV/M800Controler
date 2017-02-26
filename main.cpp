#include <iostream>
#include <hidapi/hidapi.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include "Packets.h"
#include "Keyboard.h"
#include "DumpParser.h"
#define MAX_STR 255

using namespace std;

Keyboard* keyboard;

void printInfo(){
    wchar_t wstr[MAX_STR];
    hid_get_manufacturer_string(keyboard->getDevice(), wstr, MAX_STR);
    cout << "Print" << endl;
    printf("Manufacturer String: %ls\n", wstr);

    // Read the Product String
    hid_get_product_string(keyboard->getDevice(), wstr, MAX_STR);
    printf("Product String: %ls\n", wstr);

    // Read the Serial Number String
    hid_get_serial_number_string(keyboard->getDevice(), wstr, MAX_STR);
    printf("Serial Number String: (%d) %ls\n", wstr[0], wstr);

    // Read Indexed String 1
    hid_get_indexed_string(keyboard->getDevice(), 1, wstr, MAX_STR);
    printf("Indexed String 1: %ls\n", wstr);
}

int writeCommand(char* buffer, int length){
    return hid_send_feature_report(keyboard->getDevice(), (unsigned char*) buffer, length);
}

void printColor(KeyColor color){
    cout << "Color(r: " << hex << (unsigned int) color.r << " g: " << (unsigned int) color.g << " b: " << (unsigned int) color.b << ")" << endl;
}

void doFanciStuff(DisplayState state){
    std::vector<std::pair<ColorKey, KeyColor>> newMap;

    KeyColor color = {rand() % 256,rand() % 256,rand() % 256};


    for(ColorKey key = ColorKey::FUNCTIONAL_FIRST; key <= ColorKey::FUNCTIONAL_LAST; key = key + 1)
        newMap.push_back({key, color});
    /**
        * Update the num pad
        */

    for(ColorKey key = ColorKey::NUM_1; key <= ColorKey::NUM_0; key = key + 1)
        newMap.push_back({key, color});

    for(ColorKey key = ColorKey::NUM_SLASH; key <= ColorKey::NUM_ENTER; key = key + 1)
        newMap.push_back({key, color});
    newMap.push_back({ColorKey::NUM_COMMA, color});

    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Updating the hotkeys
     */
    for(ColorKey key = ColorKey::HOTKEY_FIRST; key <= ColorKey::HOTKEY_LAST; key = key + 1)
        newMap.push_back({key, color});


    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Update the mid layer!
     */

    for(ColorKey key = ColorKey::ARROW_RIGHT; key <= ColorKey::ARROW_UP; key = key + 1)
        newMap.push_back({key, color});

    for(ColorKey key = ColorKey::KEY_PRINT; key <= ColorKey::KEY_PAUSE; key = key + 1)
        newMap.push_back({key, color});

    for(ColorKey key = ColorKey::INSERT; key <= ColorKey::PIC_DOWN; key = key + 1)
        newMap.push_back({key, color});



    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Special character keys
     */

    for(ColorKey key = ColorKey::KEY_SS; key <= ColorKey::KEY_MINUS; key = key + 1)
        newMap.push_back({key, color});
    newMap.push_back({ColorKey::KEY_SMALER_THEN, color});

    /**
     * Update all normal characters
     */

    for(ColorKey key = ColorKey::NUMBER_FIRST; key <= ColorKey::NUMBER_LAST; key = key + 1)
        newMap.push_back({key, color});

    for(ColorKey key = ColorKey::A; key <= ColorKey::Z; key = key + 1)
        newMap.push_back({key, color});


    /**
     * Text changing keys
     */

    for(ColorKey key = ColorKey::KEY_ENTER; key <= ColorKey::KEY_TAB; key = key + 1)
        if(key != KEY_ESC)
            newMap.push_back({key, color});
    newMap.push_back({ColorKey ::KEY_CAPSLOCK, color});
    newMap.push_back({ColorKey ::CAPS_RIGHT, color});
    newMap.push_back({ColorKey ::CAPS, color});


    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Update all command keys
     */

    newMap.push_back({ColorKey::CTRL, color});
    newMap.push_back({ColorKey::CTRL_RIGHT, color});
    newMap.push_back({ColorKey::ALT, color});
    newMap.push_back({ColorKey::ALT_GR, color});
    newMap.push_back({ColorKey::KEY_LIST, color});
    newMap.push_back({ColorKey::KEY_ESC, color});


    /**
     * Updateing the last (system depend) stuff
     */
    newMap.push_back({ColorKey::WINDOWS_KEY, color});
    newMap.push_back({ColorKey::LOGO, color});
    newMap.push_back({ColorKey::TOGGLE_KEY, color});

    keyboard->setStaticColor(state ,newMap);
}

/*
 F8 00 00 00 DE 01 01 00
 08 08 08 00 DE 01 02 00
 F8 F8 00 00 ED 01 03 00
 7B 00 85 00 21 00 00 00

  */
void printData(PacketColorData& pdata){
    cout << "--------------------------------------" << endl;
    cout << "PacketID:    " << hex << pdata.packetId << dec << endl;
    cout << "Metaslot:    " << pdata.metaId << endl;
    cout << "Entry size:  " << pdata.entryCount << endl;
    cout << "Max time:    " << pdata.maxTime << endl;

    int currentSpeed = 0;
    KeyColor current = pdata.getStartColor();
    for(int i = 0;i<pdata.entryCount;i++){
        currentSpeed+=pdata.entries[i].speed;
        current -= pdata.entries[i].asColor();
        cout << "Entry[" << i << "]:" << endl;
        cout << "     Index : " << (int) pdata.entries[i].index << endl;
        cout << "     Speed : " << (int) pdata.entries[i].speed << " (" << ((float) pdata.entries[i].speed / pdata.maxTime) << " -> "<<((float) currentSpeed / pdata.maxTime)<<")" << endl;
        cout << "     Red   : " << (int) pdata.entries[i].red << endl;
        cout << "     Green : " << (int) pdata.entries[i].green << endl;
        cout << "     Blue  : " << (int) pdata.entries[i].blue << endl;
        cout << "     B3    : " << (int) pdata.entries[i].b3 << endl;
        cout << "     B7    : " << (int) pdata.entries[i].b7 << endl;
        cout << "     Cal color: " << current.asString() << endl;

    }
    cout << "End: " << current.asString() << endl;
    cout << ":" << pdata.getStartColor().asString() << endl;
}

int main(){
    cout << static_cast<ColorKey>(200) << endl;
    /*
    string dump =
                    "00000000  0B 00 00 00 7B 00 00 00 21 00 01 00 85 00 00 00  . . . . { . . . ! . . . \u0085 . . .  \n"
                            "00000010  21 00 02 00 00 7B 00 00 21 00 03 00 00 85 00 00  ! . . . . { . . ! . . . . \u0085 . .  \n"
                            "00000020  21 00 04 00 00 00 7B 00 21 00 05 00 00 00 85 00  ! . . . . . { . ! . . . . . \u0085 .  \n"
                            "00000030  21 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ! . . . . . . . . . . . . . . .  \n"
                            "00000040  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000050  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000060  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000070  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000080  00 00 00 00 00 00 00 00 00 00 FF 00 4C 07 F1 01  . . . . . . . . . . ÿ . L . ñ .  \n"
                            "00000090  00 00 00 00 A5 00 06 00 C6 00 00 00 00 00 00 00  . . . . ¥ . . . Æ . . . . . . .  \n"
                            "000000A0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000000B0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000000C0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000000D0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000000E0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000000F0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000100  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000110  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000120  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000130  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000140  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000150  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000160  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000170  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000180  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000190  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000001A0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000001B0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000001C0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000001D0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000001E0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "000001F0  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  . . . . . . . . . . . . . . . .  \n"
                            "00000200  00 00                                            . .                              ";
    auto ddata = Dump::getDumpData(dump);
    //Dump::hexDump((void*) data.dumpData, data.dumpLength, data.rowWidth);
    PacketColorData pdata;
    memcpy(&pdata, ddata.dumpData, sizeof(pdata));
    printData(pdata);
    if(true) return 0;
    */

    if(getuid() != 0){
        cerr << "Cant access hid's" << endl;
        return 1;
    }

    //auto hwid = hid_open(0x1770, 0xff00, 0);
    int res;
    unsigned char buf[65];

    int i;


    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev) {
        printf("Device Found\n  type: %04hx %04hx\n  path: %s\n  serial_number: %ls",
               cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        printf("  Manufacturer: %ls\n", cur_dev->manufacturer_string);
        printf("  Product:      %ls\n", cur_dev->product_string);
        printf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    hid_init();
    keyboard = new Keyboard(0x1038, 0x1600, 0);
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    cout << "Open" << endl;
    if(!keyboard->isValid()){
        cerr << "Invalid keyboard" << endl;
        return -1;
    }
    // Read the Manufacturer String


    /*
    // Toggle LED (cmd 0x80). The first byte is the report number (0x0).
    buf[0] = 0x0;
    buf[1] = 0x80;
    res = hid_write(handle, buf, 65);

    // Request state (cmd 0x81). The first byte is the report number (0x0).
    buf[0] = 0x0;
    buf[1] = 0x81;
    res = hid_write(handle, buf, 65);
*/

    cout << NUM_FIRST  << "- " << NUM_1 << endl;
    char* buffer;
    srand(time(NULL));
    int round = 0;
    while(true){
        DisplayState state = DisplayState::ACTIVE;

       // for(int i = 0;i<size;i++){a
        /*
        int time = 33;
        PacketColorData data = pdata;

        data.setStartColor({133,132,132});
        data.entries[0] = PacketColorEntry{0x00, 132, 132, 0,  time, 1, 0};
        data.entries[5] = PacketColorEntry{0x01+122, 0x01+123, 0x01, 0, time, 0, 0};

        KeyColor start = {0x00,0x00,0x00};
        KeyColor current = {start.r, start.g, start.b};
        KeyColor op;
        printColor(current);

        op = {0x01, 0x00, 0x00};
        data.entries[0] = PacketColorEntry{op.r, op.g, op.b, 0, time, 1, 0};
        current -= op;
        printColor(current);

        op = {0xff, 0x00, 0x0};
        data.entries[1] = PacketColorEntry{op.r, op.g, op.b, 0, time, 2, 0};
        current -= op;
        printColor(current);

        op = {0xff, 0x00, 0x00};
        data.entries[2] = PacketColorEntry{op.r, op.g, op.b, 0, time, 3, 0};
        current -= op;
        printColor(current);

        /*
        op = {0x00, 0xff, 0x01};
        data.entries[3] = PacketColorEntry{op.r, op.g, op.b, 0, time, 4, 0};
        current -= op;
        printColor(current);

        op = {0x01, 0x01, 0x00};
        data.entries[4] = PacketColorEntry{op.r, op.g, op.b, 0, time, 0, 0};
        current -= op;
        printColor(current);


        data.entryCount = 3;
        data.maxTime = time * data.entryCount;

        data.metaId = 1;

        //data.setStartColor(start);
        hid_send_feature_report(keyboard->getDevice(), (unsigned char*) &data, sizeof(data));
        printData(data);
        //keyboard->setStaticColor(state ,ColorKey::A, {rand() % 255, rand() % 255, rand() % 255});
        keyboard->setKeyMetaSlot(state, ColorKey::B, 1);
        */

        std::vector<ReactiveKey> newMap;
        KeyColor color = {255,0,0};
        KeyColor color1 = {0,255,0};
        for(ColorKey key = ColorKey::A; key <= ColorKey::Z; key = key + 1)
            newMap.push_back({key, color, color1, 1.5});

        keyboard->setReactiveColor(state, newMap);
        //doFanciStuff(DisplayState::ACTIVE);
        keyboard->setDisplayState(state);
/*
        buffer = new char[0x20];
        memset(buffer, 0, 0x20);
        buffer[0] = 0x0D;
        buffer[2] = 0x00;
        cout << "Wrote!" << hid_write(keyboard->getDevice(), (unsigned char*) buffer, 0x20) << endl;
        */
        round++;
        usleep(1000*800); //Min 10.000
    }

    /*
    buffer = new unsigned char[0x20];
    memset(buffer, 0, 0x20);
    buffer[0] = 0x0D;

    cout << "Wrote!" << hid_send_feature_report(handle,buffer, 0x20) << endl;
    cout << "Read:" << endl;
    // Read requested state
    res = hid_get_feature_report(handle, buffer, 0x20);
    */
    // Finalize the hidapi library
    cout << "Done!" << endl;
    res = hid_exit();

    return 0;
}