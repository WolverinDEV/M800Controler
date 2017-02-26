//
// Created by wolverindev on 26.02.17.
//

#include "../include/Steelseries/KeyboardPainting.h"

namespace Mapping {
    ColoredKey** buildMapping() {
        ColoredKey** keys = (ColoredKey**) malloc(23*sizeof(void*));

        keys[0] = new ColoredKey[6];
        keys[0][0] = ColoredKey::HOTKEY_0;
        keys[0][1] = ColoredKey::HOTKEY_1;
        keys[0][2] = ColoredKey::HOTKEY_2;
        keys[0][3] = ColoredKey::HOTKEY_3;
        keys[0][4] = ColoredKey::HOTKEY_4;
        keys[0][5] = ColoredKey::HOTKEY_5;

        keys[1] = new ColoredKey[6];
        keys[1][0] = ColoredKey::KEY_ESC;
        keys[1][1] = ColoredKey::KEY_ZIRKUMFLEX;
        keys[1][2] = ColoredKey::KEY_TAB;
        keys[1][3] = ColoredKey::KEY_CAPSLOCK;
        keys[1][4] = ColoredKey::CAPS;
        keys[1][5] = ColoredKey::CTRL;

        keys[2] = new ColoredKey[6];
        keys[2][0] = ColoredKey::KEY_1;
        keys[2][1] = ColoredKey::EMPTY;
        keys[2][2] = ColoredKey::EMPTY;
        keys[2][3] = ColoredKey::EMPTY;
        keys[2][4] = ColoredKey::KEY_SMALER_THEN;
        keys[2][5] = ColoredKey::WINDOWS_KEY;

        keys[3] = new ColoredKey[6];
        keys[3][0] = ColoredKey::FUNCTIONAL_1;
        keys[3][1] = ColoredKey::KEY_2;
        keys[3][2] = ColoredKey::Q;
        keys[3][3] = ColoredKey::A;
        keys[3][4] = ColoredKey::Z;
        keys[3][5] = ColoredKey::EMPTY;

        keys[4] = new ColoredKey[6];
        keys[4][0] = ColoredKey::FUNCTIONAL_2;
        keys[4][1] = ColoredKey::KEY_3;
        keys[4][2] = ColoredKey::W;
        keys[4][3] = ColoredKey::S;
        keys[4][4] = ColoredKey::X;
        keys[4][5] = ColoredKey::ALT;

        keys[5] = new ColoredKey[6];
        keys[5][0] = ColoredKey::FUNCTIONAL_3;
        keys[5][1] = ColoredKey::KEY_4;
        keys[5][2] = ColoredKey::E;
        keys[5][3] = ColoredKey::D;
        keys[5][4] = ColoredKey::C;
        keys[5][5] = ColoredKey::EMPTY; //Space

        keys[6] = new ColoredKey[6];
        keys[6][0] = ColoredKey::FUNCTIONAL_4;
        keys[6][1] = ColoredKey::KEY_5;
        keys[6][2] = ColoredKey::R;
        keys[6][3] = ColoredKey::F;
        keys[6][4] = ColoredKey::V;
        keys[6][5] = ColoredKey::EMPTY; //Space

        keys[7] = new ColoredKey[6];
        keys[7][0] = ColoredKey::FUNCTIONAL_5;
        keys[7][1] = ColoredKey::KEY_6;
        keys[7][2] = ColoredKey::T;
        keys[7][3] = ColoredKey::G;
        keys[7][4] = ColoredKey::B;
        keys[7][5] = ColoredKey::EMPTY; //Space

        keys[8] = new ColoredKey[6];
        keys[8][0] = ColoredKey::FUNCTIONAL_6;
        keys[8][1] = ColoredKey::KEY_7;
        keys[8][2] = ColoredKey::Y;
        keys[8][3] = ColoredKey::H;
        keys[8][4] = ColoredKey::N;
        keys[8][5] = ColoredKey::EMPTY; //Space

        keys[9] = new ColoredKey[6];
        keys[9][0] = ColoredKey::FUNCTIONAL_7;
        keys[9][1] = ColoredKey::KEY_8;
        keys[9][2] = ColoredKey::U;
        keys[9][3] = ColoredKey::J;
        keys[9][4] = ColoredKey::M;
        keys[9][5] = ColoredKey::EMPTY; //Space

        keys[10] = new ColoredKey[6];
        keys[10][0] = ColoredKey::FUNCTIONAL_8;
        keys[10][1] = ColoredKey::KEY_9;
        keys[10][2] = ColoredKey::I;
        keys[10][3] = ColoredKey::K;
        keys[10][4] = ColoredKey::KEY_COMMA;
        keys[10][5] = ColoredKey::ALT_GR;

        keys[11] = new ColoredKey[6];
        keys[11][0] = ColoredKey::EMPTY;
        keys[11][1] = ColoredKey::KEY_0;
        keys[11][2] = ColoredKey::O;
        keys[11][3] = ColoredKey::L;
        keys[11][4] = ColoredKey::KEY_POINT;
        keys[11][5] = ColoredKey::EMPTY;

        keys[12] = new ColoredKey[6];
        keys[12][0] = ColoredKey::FUNCTIONAL_9;
        keys[12][1] = ColoredKey::KEY_SS;
        keys[12][2] = ColoredKey::P;
        keys[12][3] = ColoredKey::KEY_OE;
        keys[12][4] = ColoredKey::KEY_MINUS;
        keys[12][5] = ColoredKey::TOGGLE_KEY;


        keys[13] = new ColoredKey[6];
        keys[13][0] = ColoredKey::FUNCTIONAL_10;
        keys[13][1] = ColoredKey::KEY_GRAVIS;
        keys[13][2] = ColoredKey::KEY_UE;
        keys[13][3] = ColoredKey::KEY_AE;
        keys[13][4] = ColoredKey::KEY_MINUS;
        keys[13][5] = ColoredKey::TOGGLE_KEY;

        keys[14] = new ColoredKey[6];
        keys[14][0] = ColoredKey::FUNCTIONAL_11;
        keys[14][1] = ColoredKey::EMPTY;
        keys[14][2] = ColoredKey::KEY_PLUS;
        keys[14][3] = ColoredKey::KEY_HASHTAG;
        keys[14][4] = ColoredKey::EMPTY;
        keys[14][5] = ColoredKey::KEY_LIST;

        keys[15] = new ColoredKey[6];
        keys[15][0] = ColoredKey::FUNCTIONAL_12;
        keys[15][1] = ColoredKey::KEY_BACKSPACE;
        keys[15][2] = ColoredKey::KEY_ENTER;
        keys[15][3] = ColoredKey::KEY_ENTER;
        keys[15][4] = ColoredKey::CAPS_RIGHT;
        keys[15][5] = ColoredKey::CTRL_RIGHT;





        keys[16] = new ColoredKey[6];
        keys[16][0] = ColoredKey::KEY_PRINT;
        keys[16][1] = ColoredKey::INSERT;
        keys[16][2] = ColoredKey::DEL;
        keys[16][3] = ColoredKey::EMPTY;
        keys[16][4] = ColoredKey::EMPTY;
        keys[16][5] = ColoredKey::ARROW_LEFT;

        keys[17] = new ColoredKey[6];
        keys[17][0] = ColoredKey::KEY_ROLL;
        keys[17][1] = ColoredKey::HOME;
        keys[17][2] = ColoredKey::END;
        keys[17][3] = ColoredKey::EMPTY;
        keys[17][4] = ColoredKey::ARROW_UP;
        keys[17][5] = ColoredKey::ARROW_DOWN;

        keys[18] = new ColoredKey[6];
        keys[18][0] = ColoredKey::KEY_PAUSE;
        keys[18][1] = ColoredKey::PIC_UP;
        keys[18][2] = ColoredKey::PIC_DOWN;
        keys[18][3] = ColoredKey::EMPTY;
        keys[18][4] = ColoredKey::EMPTY;
        keys[18][5] = ColoredKey::ARROW_RIGHT;


        keys[19] = new ColoredKey[6];
        keys[19][0] = ColoredKey::EMPTY;
        keys[19][1] = ColoredKey::EMPTY; //The num key... unknowns its
        keys[19][2] = ColoredKey::NUM_7;
        keys[19][3] = ColoredKey::NUM_4;
        keys[19][4] = ColoredKey::NUM_1;
        keys[19][5] = ColoredKey::NUM_0;

        keys[20] = new ColoredKey[6];
        keys[20][0] = ColoredKey::EMPTY;
        keys[20][1] = ColoredKey::NUM_SLASH;
        keys[20][2] = ColoredKey::NUM_8;
        keys[20][3] = ColoredKey::NUM_5;
        keys[20][4] = ColoredKey::NUM_2;
        keys[20][5] = ColoredKey::NUM_0;

        keys[21] = new ColoredKey[6];
        keys[21][0] = ColoredKey::EMPTY;
        keys[21][1] = ColoredKey::NUM_STAR;
        keys[21][2] = ColoredKey::NUM_9;
        keys[21][3] = ColoredKey::NUM_6;
        keys[21][4] = ColoredKey::NUM_3;
        keys[21][5] = ColoredKey::NUM_COMMA;

        keys[22] = new ColoredKey[6];
        keys[22][0] = ColoredKey::EMPTY;
        keys[22][1] = ColoredKey::NUM_MINUS;
        keys[22][2] = ColoredKey::NUM_PLUS;
        keys[22][3] = ColoredKey::NUM_PLUS;
        keys[22][4] = ColoredKey::NUM_ENTER;
        keys[22][5] = ColoredKey::NUM_ENTER;
        return keys;
    }

    ColoredKey** rowMapping = buildMapping();
}