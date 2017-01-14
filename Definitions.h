//
// Created by wolverindev on 14.01.17.
//
#pragma once

/*
	A: 0x04
	B: 0x05
	...
	Y: 0x1C
	Z: 0x1D
	INSERT: 0x49
	HOME: 0x4A
	PIC_UP: 0x4A
	DEL: 0x4B
	END: 0x4C
	PIC_DOWN: 0x4D
	ARROW_RIGHT: 0x4F
	ARROW_LEFT: 0x50
	ARROW_DOWN: 0x51
	ARROW_UP: 0x52
	NUM_1: 0x59
	NUM_9: 0x61
	NUM_0: 0x62
 */

enum DisplayState {
    ACTIVE,
    SLEEPING
};

enum ColorKey : unsigned char {
    UNKNOWN_0,
    UNKNOWN_1,
    UNKNOWN_2,
    UNKNOWN_3,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    INSERT = 0x49,
    HOME,
    PIC_UP,
    DEL,
    END,
    PIC_DOWN,

    //Unknwon

    ARROW_RIGHT = 0x4F,
    ARROW_LEFT,
    ARROW_DOWN,
    ARROW_UP,

    NUM_1 = 0x59,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    NUM_0
};

struct KeyColor {
    char r;
    char g;
    char b;
};

enum KeyColorType : unsigned char {
    OFF,
    STATIC,
    REACTIVE = 0x08
};