//
// Created by wolverindev on 25.02.17.
//

#include "string"
namespace Dump {
    struct DumpStructureData {
        const int dumpLength;
        const int rowWidth;
        const char* dumpData;
    };

    extern DumpStructureData getDumpData(std::string dump);

    extern void hexDump(void* addr, int length, int numLength = 16);
}