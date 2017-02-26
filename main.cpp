#include <iostream>
#include <hidapi/hidapi.h>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <typeinfo>
#include "include/Steelseries/USBPackets.h"
#include "include/Steelseries/Keyboard.h"
#include "include/Steelseries/KeyboardPainting.h"

using namespace std;
using namespace Steelseries::M800;
using namespace Steelseries::USB::Packets;

Keyboard* keyboard;

void doFanciStuff(DisplayState state){
    std::vector<std::pair<ColoredKey, KeyColor>> newMap;

    KeyColor color = {rand() % 256,rand() % 256,rand() % 256};


    for(ColoredKey key = ColoredKey::FUNCTIONAL_FIRST; key <= ColoredKey::FUNCTIONAL_LAST; key = key + 1)
        newMap.push_back({key, color});
    /**
        * Update the num pad
        */

    for(ColoredKey key = ColoredKey::NUM_1; key <= ColoredKey::NUM_0; key = key + 1)
        newMap.push_back({key, color});

    for(ColoredKey key = ColoredKey::NUM_SLASH; key <= ColoredKey::NUM_ENTER; key = key + 1)
        newMap.push_back({key, color});
    newMap.push_back({ColoredKey::NUM_COMMA, color});

    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Updating the hotkeys
     */
    for(ColoredKey key = ColoredKey::HOTKEY_FIRST; key <= ColoredKey::HOTKEY_LAST; key = key + 1)
        newMap.push_back({key, color});


    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Update the mid layer!
     */

    for(ColoredKey key = ColoredKey::ARROW_RIGHT; key <= ColoredKey::ARROW_UP; key = key + 1)
        newMap.push_back({key, color});

    for(ColoredKey key = ColoredKey::KEY_PRINT; key <= ColoredKey::KEY_PAUSE; key = key + 1)
        newMap.push_back({key, color});

    for(ColoredKey key = ColoredKey::INSERT; key <= ColoredKey::PIC_DOWN; key = key + 1)
        newMap.push_back({key, color});



    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Special character keys
     */

    for(ColoredKey key = ColoredKey::KEY_SS; key <= ColoredKey::KEY_MINUS; key = key + 1)
        newMap.push_back({key, color});
    newMap.push_back({ColoredKey::KEY_SMALER_THEN, color});

    /**
     * Update all normal characters
     */

    for(ColoredKey key = ColoredKey::NUMBER_FIRST; key <= ColoredKey::NUMBER_LAST; key = key + 1)
        newMap.push_back({key, color});

    for(ColoredKey key = ColoredKey::A; key <= ColoredKey::Z; key = key + 1)
        newMap.push_back({key, color});


    /**
     * Text changing keys
     */

    for(ColoredKey key = ColoredKey::KEY_ENTER; key <= ColoredKey::KEY_TAB; key = key + 1)
        if(key != KEY_ESC)
            newMap.push_back({key, color});
    newMap.push_back({ColoredKey ::KEY_CAPSLOCK, color});
    newMap.push_back({ColoredKey ::CAPS_RIGHT, color});
    newMap.push_back({ColoredKey ::CAPS, color});


    color = {rand() % 256,rand() % 256,rand() % 256};
    /**
     * Update all command keys
     */

    newMap.push_back({ColoredKey::CTRL, color});
    newMap.push_back({ColoredKey::CTRL_RIGHT, color});
    newMap.push_back({ColoredKey::ALT, color});
    newMap.push_back({ColoredKey::ALT_GR, color});
    newMap.push_back({ColoredKey::KEY_LIST, color});
    newMap.push_back({ColoredKey::KEY_ESC, color});


    /**
     * Updateing the last (system depend) stuff
     */
    newMap.push_back({ColoredKey::WINDOWS_KEY, color});
    newMap.push_back({ColoredKey::LOGO, color});
    newMap.push_back({ColoredKey::TOGGLE_KEY, color});

    keyboard->setStaticColor(state ,newMap);
}


void printData(PacketFadeColorData& pdata){
    cout << "--------------------------------------" << endl;
    cout << "PacketID:    " << hex << pdata.packetId << dec << endl;
    cout << "Metaslot:    " << pdata.metaId << endl;
    cout << "Entry size:  " << pdata.entryCount << endl;
    cout << "Max time:    " << pdata.maxTime << endl;

    int currentSpeed = 0;
    KeyColor current = pdata.getStartColor();
    for(int i = 0;i<pdata.entryCount;i++){
        currentSpeed+=pdata.entries[i].speed;
        current -= pdata.entries[i].getColor();
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

    // Enumerate and print the HID devices on the system
    struct hid_device_info *devs, *cur_dev;

    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;
    while (cur_dev) {
        printf("Device '%ls' from %ls\n"
               "  VendorID      : %04hx\n"
               "  ProductID     : %04hx\n"
               "  Path          : %s\n"
               "  Serial Number : %ls\n",
               cur_dev->product_string, cur_dev->manufacturer_string, cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
        printf("\n");
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    hid_init();
    keyboard = new Keyboard(0x1038, 0x1600, nullptr); //Logitech havnt a serial number....
    if(!keyboard->isValid()){
        delete keyboard;
        cerr << "Invalid keyboard" << endl;
        usleep(100);
        return 2;
    }

    srand(time(NULL));
    int round = 0;

    auto keyMapping = Mapping::buildMapping();
    int keysColumnsSize = 23;
    int keysRowSize = 6;
    int bulkSize = 3;


    KeyColor mapping[] = {{0xff,0,0},{0x80,0x10,0x10},{0x30,0x00,0x0}}; //,{0xff,0,0},{0xff,0,0},{0,0,0xff}, {0,0,0xff}, {0xff,0,0xff},{0xff,0,0xff}

    int rowMapping[] {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1};
    int rowMappingSize = 12;

    int animationLoopedCounter = 0;
    while(true){
        DisplayState state = DisplayState::ACTIVE;
        //std::vector<ReactiveKey> newMap;
        std::vector<std::pair<ColoredKey, KeyColor>> newMap;

        if(animationLoopedCounter%5<3){
            //Shift the columns
            for(int i = 0;i<keysColumnsSize;i++){
                for(int y = 0;y<6;y++) {
                    ColoredKey key = keyMapping[i][y];
                    if(key != ColoredKey::EMPTY){
                        newMap.push_back({key, (i+round)%keysColumnsSize > (bulkSize-1) ? KeyColor{0,0,0} : mapping[(i+round)%keysColumnsSize]});
                    }
                }
            }
            newMap.push_back({ColoredKey::LOGO, mapping[0]});
            if((round-1)%keysColumnsSize == 0 && round != 1){
                for(int i = 0;i<bulkSize;i++)
                    mapping[i] >> 1;
                animationLoopedCounter++; if(animationLoopedCounter %5>=3) round = 0;
            }
        } else {
            //Shift the rows!
            for(int i = 0;i<keysRowSize;i++){
                for(int x = 0;x<keysColumnsSize;x++){
                    ColoredKey key = keyMapping[x][keysRowSize-i-1];
                    if(key != ColoredKey::EMPTY){
                        if(i < rowMapping[round%rowMappingSize])
                            newMap.push_back({key, {0xff,0,0}});
                        else
                            newMap.push_back({key, {0x00,0,0}});
                    }
                }
            }
            if(round%rowMappingSize  == 0 && round != 0){ animationLoopedCounter++; if(animationLoopedCounter%5<3) round = 0;}
        }



        //for(ColorKey key = ColorKey::A; key <= ColorKey::Z; key = key + 1)
        //    newMap.push_back({key, color, color1, 1.5});

        keyboard->setStaticColor(state, newMap);

        //doFanciStuff(DisplayState::ACTIVE);
        keyboard->setDisplayState(state);

        round++;
        usleep(1000*200); //Min 10.000
    }

    hid_exit();
    return 0;
}