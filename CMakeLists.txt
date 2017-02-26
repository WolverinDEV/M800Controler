cmake_minimum_required(VERSION 3.6)
project(M800Controler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fpermissive")

link_libraries(hidapi-hidraw usb)

set(SOURCE_FILES main.cpp
		Definitions.h
		Keyboard.cpp Keyboard.h
		Packets.h
		DumpParser.cpp DumpParser.h)
add_executable(M800Controler ${SOURCE_FILES})