#include <iostream>
#include <hidapi/hidapi.h>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include "Packets.h"
#include "Keyboard.h"
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

int main(){
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

    if(!hid_init()){
        cerr << "Cant init!" << endl;
    }

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
    char* buffer;
    srand(time(NULL));
    while(true){
        int size = 55; //2A default block

       // for(int i = 0;i<size;i++){
        DisplayState state = DisplayState::SLEEPING;
            keyboard->setStaticColor(state ,ColorKey::A, {rand() % 255, rand() % 255, rand() % 255});
        keyboard->setDisplayState(state);
       // }


/*
        buffer = new char[0x20];
        memset(buffer, 0, 0x20);
        buffer[0] = 0x0D;
        buffer[2] = 0x00;
        cout << "Wrote!" << hid_write(keyboard->getDevice(), (unsigned char*) buffer, 0x20) << endl;
        */
        usleep(1000*50);
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