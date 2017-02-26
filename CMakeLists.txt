cmake_minimum_required(VERSION 3.6)
project(M800Controler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

link_libraries(hidapi-hidraw usb /usr/local/lib/libCXXTerminal.so)

set(SOURCE_FILES main.cpp
		include/Steelseries/Definitions.h
		src/Keyboard.cpp include/Steelseries/Keyboard.h
		include/Steelseries/USBPackets.h
		include/Steelseries/KeyboardPainting.h src/KeyboardMapping.cpp
		debug/DumpParser.cpp debug/DumpParser.h)
add_executable(M800Controler ${SOURCE_FILES})