//
// Created by wolverindev on 25.02.17.
//

#include "DumpParser.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;
namespace Dump {
    string readNextSegment(stringstream& stream){
        stringstream out;
        while(stream.good()){
            char next;
            stream.read(&next, 1);
            if(next == ' '){
                //cout << "Having '" << out.str() << "'" << endl;
                return out.str();
            }
            if(next == '\n' || next == '\t') continue;
            out << next;
        }
        return out.str();
    }

    char asChar(string hex){
        return std::stoul(hex, nullptr, 16);
    }

    DumpStructureData getDumpData(string dump){
        stringstream ss(dump);

        while(!readNextSegment(ss).empty()); //Skip index numbers

        int blockSize = 0;
        vector<char> dumpData;

        string currentChar;
        while(!(currentChar = readNextSegment(ss)).empty()){
            blockSize++;
            dumpData.push_back(asChar(currentChar));
        }

        for(int i = 0;i<blockSize;i++) readNextSegment(ss);
        readNextSegment(ss);

        int count = blockSize;

        int mainLoop = 1;
        while (mainLoop && ss.good()){
            while(!readNextSegment(ss).empty()); //Skip index numbers

            for(int i = 0;i<blockSize;i++){
                currentChar = readNextSegment(ss);
                if(currentChar.empty()){ /*cout << "Empty num ("<<currentChar<<")" << endl;*/ mainLoop = false; break; } //else cout << currentChar << " ";
                dumpData.push_back(asChar(currentChar));
                count++;
            }
            //cout << endl;
            readNextSegment(ss); //Delimiter between visual

            for(int i = 0;i<blockSize;i++) readNextSegment(ss);
            readNextSegment(ss); //Delimiter between visual
        }

        cout << "Blocks: " << blockSize << " (" << mainLoop << ")" << endl;
        cout << "Size:   " << count << " (Hex: " << hex << count << ")" << endl;

        char* buffer = new char[count];
        memcpy(buffer, &dumpData[0], count);
        return DumpStructureData{count, blockSize, buffer};
    }



    void hexDump (void *addr, int len, int pad, void (*print)(string));
    void hexDump (void *addr, int len, int pad) {
        hexDump(addr, len, pad, [](string msg){cout << msg << endl;});
    }
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
}