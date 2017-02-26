//
// Created by wolverindev on 26.02.17.
//
#include <iostream>
#include <CXXTerminal/Terminal.h>
#include <CXXTerminal/QuickTerminal.h>
#include <unistd.h>
#include <algorithm>
#include <string>
#include "include/Steelseries/Keyboard.h"

using namespace std;
using namespace Steelseries::M800;

string toLower(string message){
    std::transform(message.begin(), message.end(), message.begin(), ::tolower);
    return message;
}

Keyboard* keyboard = nullptr;
int main(int ac, char** av){
    Terminal::setup();
    if(!Terminal::isActive()){
        cerr << "Cant setup Terminal!" << endl;
        return 2;
    }

    writeMessage("§aWelcome to the Steelseries M800 keyboard controler!");
    if(getuid() != 0){
        writeMessage("§cPlease run this program with administrative permissions!");
        return 3;
    }
    writeMessage("§aLoading keyboard!");
    keyboard = new Keyboard(0x1038, 0x1600, nullptr);
    if(!keyboard->isValid()){
        writeMessage("§cCould not find keyboard!");
        writeMessage("§aShould i list all avariable devices? [Y/n]");
        string answer;
        while((answer = toLower(Terminal::getInstance()->readLine("> "))).compare("y") != 0 && answer.compare("n") != 0 && !answer.empty()) writeMessage("§cInvalid input");
        if(answer.compare("y") == 0 || answer.empty()){
            writeMessage("\n");
            struct hid_device_info *devs, *cur_dev;
            devs = hid_enumerate(0x0, 0x0);
            cur_dev = devs;
            char buffer[1024];
            while (cur_dev) {
                sprintf(buffer,"§aDevice '§b%ls§a' from §6%ls\n"
                               "  §7VendorID      : §a%04hx\n"
                               "  §7ProductID     : §a%04hx\n"
                               "  §7Path          : §a%s\n"
                               "  §7Serial Number : §a%ls\n\n",
                       cur_dev->product_string, cur_dev->manufacturer_string, cur_dev->vendor_id, cur_dev->product_id, cur_dev->path, cur_dev->serial_number);
                writeMessage(buffer);
                cur_dev = cur_dev->next;
            }
            hid_free_enumeration(devs);
        }
        writeMessage("§cExiting!");
        delete keyboard;
        return 4;
    }
    writeMessage("§aKeyboard loaded!");

    writeMessage("§aType help for viewing the command overview");

    while(Terminal::isActive()){
        string message = Terminal::getInstance()->readLine("> ");
        string lmessage = toLower(message);
        if(lmessage.compare("end") == 0 || lmessage.compare("exit") == 0){
            writeMessage("§cExiting!");
            delete keyboard;
            return 0;
        }//TODO
        writeMessage("Recived message: " + message);
    }
}