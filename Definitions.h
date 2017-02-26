/**
 * ATTANTION: This file is only for the german keyboard. English or other types are maybe not working fully working!
 */
#pragma once

#include <string>

enum DisplayState {
    ACTIVE,
    SLEEPING
};

enum ColorKey : unsigned char {
    LOGO,

    A = 0x04,
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
    KEY_FIRST = A,
    KEY_LAST = Z,

    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    NUMBER_FIRST = KEY_1,
    NUMBER_LAST = KEY_0,

    KEY_ENTER,
    KEY_ESC,
    KEY_BACKSPACE,
    KEY_TAB,

    UNKNOWN,

    KEY_SS,
    KEY_GRAVIS, //`

    KEY_UE,
    KEY_PLUS,
    UNKNOWN1,
    KEY_HASHTAG,
    KEY_OE,
    KEY_AE,
    KEY_ZIRKUMFLEX, //^
    KEY_COMMA,
    KEY_POINT,
    KEY_MINUS,
    KEY_CAPSLOCK,

    FUNCTIONAL_1,
    FUNCTIONAL_2,
    FUNCTIONAL_3,
    FUNCTIONAL_4,
    FUNCTIONAL_5,
    FUNCTIONAL_6,
    FUNCTIONAL_7,
    FUNCTIONAL_8,
    FUNCTIONAL_9,
    FUNCTIONAL_10,
    FUNCTIONAL_11,
    FUNCTIONAL_12,
    FUNCTIONAL_FIRST = FUNCTIONAL_1,
    FUNCTIONAL_LAST = FUNCTIONAL_12,

    KEY_PRINT,
    KEY_ROLL,
    KEY_PAUSE,

    INSERT = 0x49,
    HOME,
    PIC_UP,
    DEL,
    END,
    PIC_DOWN,

    ARROW_RIGHT = 0x4F,
    ARROW_LEFT,
    ARROW_DOWN,
    ARROW_UP,

    UNKNOWN3,
    NUM_SLASH,
    NUM_STAR,
    NUM_MINUS,
    NUM_PLUS,
    NUM_ENTER,

    NUM_1 = 0x59,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    NUM_0,
    NUM_FIRST = NUM_1,
    NUM_LAST = NUM_0,

    NUM_COMMA,
    KEY_SMALER_THEN,

    KEY_LIST, //Name?

    CKEY_LAST = KEY_LIST,
    CKEY_FIRST = LOGO,

    CTRL = 0xE0,
    CAPS,
    ALT,
    WINDOWS_KEY,
    CTRL_RIGHT,
    CAPS_RIGHT,
    ALT_GR,
    UNKNOWN7,

    HOTKEY_0 = 0xE8,
    HOTKEY_1,
    HOTKEY_2,
    HOTKEY_3,
    HOTKEY_4,
    HOTKEY_5,
    HOTKEY_FIRST = HOTKEY_0,
    HOTKEY_LAST = HOTKEY_5,

    TOGGLE_KEY = 0xEF, //(The steelseries switch key)

    EMPTY = 0xFF
};

struct KeyColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    KeyColor&operator+=(KeyColor color){
        r += color.r;
        g += color.g;
        b += color.b;
        return *this;
    }

    KeyColor&operator-=(KeyColor color){
        r -= color.r;
        g -= color.g;
        b -= color.b;
        return *this;
    }

    KeyColor operator-(KeyColor color){
        KeyColor copy = {r, g, b};
        return copy -= color;
    }

    KeyColor&operator>>(int rounds){
        for(int i = 0;i<rounds;i++){
            auto oldR = r;
            auto oldG = g;
            auto oldB = b;
            this->r = oldB;
            this->g = oldR;
            this->b = oldG;
        }
    }

    std::string asString(){
        return "{"+std::to_string(r)+", "+std::to_string(g) +", "+std::to_string(b) +"}";
    }
};

struct ReactiveKey {
    ColorKey key;
    KeyColor normal;
    KeyColor active;
    float speed; //Speed in seconds
};

enum KeyColorType : unsigned char {
    OFF,
    STATIC,
    REACTIVE = 0x08
};