//
// Created by wolverindev on 26.02.17.
//

#include "KeyboardPainting.h"

namespace Mapping {
    ColorKey** buildMapping() {
        ColorKey** keys = (ColorKey**) malloc(23*sizeof(void*));

        keys[0] = new ColorKey[6];
        keys[0][0] = ColorKey::HOTKEY_0;
        keys[0][1] = ColorKey::HOTKEY_1;
        keys[0][2] = ColorKey::HOTKEY_2;
        keys[0][3] = ColorKey::HOTKEY_3;
        keys[0][4] = ColorKey::HOTKEY_4;
        keys[0][5] = ColorKey::HOTKEY_5;

        keys[1] = new ColorKey[6];
        keys[1][0] = ColorKey::KEY_ESC;
        keys[1][1] = ColorKey::KEY_ZIRKUMFLEX;
        keys[1][2] = ColorKey::KEY_TAB;
        keys[1][3] = ColorKey::KEY_CAPSLOCK;
        keys[1][4] = ColorKey::CAPS;
        keys[1][5] = ColorKey::CTRL;

        keys[2] = new ColorKey[6];
        keys[2][0] = ColorKey::KEY_1;
        keys[2][1] = ColorKey::EMPTY;
        keys[2][2] = ColorKey::EMPTY;
        keys[2][3] = ColorKey::EMPTY;
        keys[2][4] = ColorKey::KEY_SMALER_THEN;
        keys[2][5] = ColorKey::WINDOWS_KEY;

        keys[3] = new ColorKey[6];
        keys[3][0] = ColorKey::FUNCTIONAL_1;
        keys[3][1] = ColorKey::KEY_2;
        keys[3][2] = ColorKey::Q;
        keys[3][3] = ColorKey::A;
        keys[3][4] = ColorKey::Z;
        keys[3][5] = ColorKey::EMPTY;

        keys[4] = new ColorKey[6];
        keys[4][0] = ColorKey::FUNCTIONAL_2;
        keys[4][1] = ColorKey::KEY_3;
        keys[4][2] = ColorKey::W;
        keys[4][3] = ColorKey::S;
        keys[4][4] = ColorKey::X;
        keys[4][5] = ColorKey::ALT;

        keys[5] = new ColorKey[6];
        keys[5][0] = ColorKey::FUNCTIONAL_3;
        keys[5][1] = ColorKey::KEY_4;
        keys[5][2] = ColorKey::E;
        keys[5][3] = ColorKey::D;
        keys[5][4] = ColorKey::C;
        keys[5][5] = ColorKey::EMPTY; //Space

        keys[6] = new ColorKey[6];
        keys[6][0] = ColorKey::FUNCTIONAL_4;
        keys[6][1] = ColorKey::KEY_5;
        keys[6][2] = ColorKey::R;
        keys[6][3] = ColorKey::F;
        keys[6][4] = ColorKey::V;
        keys[6][5] = ColorKey::EMPTY; //Space

        keys[7] = new ColorKey[6];
        keys[7][0] = ColorKey::FUNCTIONAL_5;
        keys[7][1] = ColorKey::KEY_6;
        keys[7][2] = ColorKey::T;
        keys[7][3] = ColorKey::G;
        keys[7][4] = ColorKey::B;
        keys[7][5] = ColorKey::EMPTY; //Space

        keys[8] = new ColorKey[6];
        keys[8][0] = ColorKey::FUNCTIONAL_6;
        keys[8][1] = ColorKey::KEY_7;
        keys[8][2] = ColorKey::Y;
        keys[8][3] = ColorKey::H;
        keys[8][4] = ColorKey::N;
        keys[8][5] = ColorKey::EMPTY; //Space

        keys[9] = new ColorKey[6];
        keys[9][0] = ColorKey::FUNCTIONAL_7;
        keys[9][1] = ColorKey::KEY_8;
        keys[9][2] = ColorKey::U;
        keys[9][3] = ColorKey::J;
        keys[9][4] = ColorKey::M;
        keys[9][5] = ColorKey::EMPTY; //Space

        keys[10] = new ColorKey[6];
        keys[10][0] = ColorKey::FUNCTIONAL_8;
        keys[10][1] = ColorKey::KEY_9;
        keys[10][2] = ColorKey::I;
        keys[10][3] = ColorKey::K;
        keys[10][4] = ColorKey::KEY_COMMA;
        keys[10][5] = ColorKey::ALT_GR;

        keys[11] = new ColorKey[6];
        keys[11][0] = ColorKey::EMPTY;
        keys[11][1] = ColorKey::KEY_0;
        keys[11][2] = ColorKey::O;
        keys[11][3] = ColorKey::L;
        keys[11][4] = ColorKey::KEY_POINT;
        keys[11][5] = ColorKey::EMPTY;

        keys[12] = new ColorKey[6];
        keys[12][0] = ColorKey::FUNCTIONAL_9;
        keys[12][1] = ColorKey::KEY_SS;
        keys[12][2] = ColorKey::P;
        keys[12][3] = ColorKey::KEY_OE;
        keys[12][4] = ColorKey::KEY_MINUS;
        keys[12][5] = ColorKey::TOGGLE_KEY;


        keys[13] = new ColorKey[6];
        keys[13][0] = ColorKey::FUNCTIONAL_10;
        keys[13][1] = ColorKey::KEY_GRAVIS;
        keys[13][2] = ColorKey::KEY_UE;
        keys[13][3] = ColorKey::KEY_AE;
        keys[13][4] = ColorKey::KEY_MINUS;
        keys[13][5] = ColorKey::TOGGLE_KEY;

        keys[14] = new ColorKey[6];
        keys[14][0] = ColorKey::FUNCTIONAL_11;
        keys[14][1] = ColorKey::EMPTY;
        keys[14][2] = ColorKey::KEY_PLUS;
        keys[14][3] = ColorKey::KEY_HASHTAG;
        keys[14][4] = ColorKey::EMPTY;
        keys[14][5] = ColorKey::KEY_LIST;

        keys[15] = new ColorKey[6];
        keys[15][0] = ColorKey::FUNCTIONAL_12;
        keys[15][1] = ColorKey::KEY_BACKSPACE;
        keys[15][2] = ColorKey::KEY_ENTER;
        keys[15][3] = ColorKey::KEY_ENTER;
        keys[15][4] = ColorKey::CAPS_RIGHT;
        keys[15][5] = ColorKey::CTRL_RIGHT;





        keys[16] = new ColorKey[6];
        keys[16][0] = ColorKey::KEY_PRINT;
        keys[16][1] = ColorKey::INSERT;
        keys[16][2] = ColorKey::DEL;
        keys[16][3] = ColorKey::EMPTY;
        keys[16][4] = ColorKey::EMPTY;
        keys[16][5] = ColorKey::ARROW_LEFT;

        keys[17] = new ColorKey[6];
        keys[17][0] = ColorKey::KEY_ROLL;
        keys[17][1] = ColorKey::HOME;
        keys[17][2] = ColorKey::END;
        keys[17][3] = ColorKey::EMPTY;
        keys[17][4] = ColorKey::ARROW_UP;
        keys[17][5] = ColorKey::ARROW_DOWN;

        keys[18] = new ColorKey[6];
        keys[18][0] = ColorKey::KEY_PAUSE;
        keys[18][1] = ColorKey::PIC_UP;
        keys[18][2] = ColorKey::PIC_DOWN;
        keys[18][3] = ColorKey::EMPTY;
        keys[18][4] = ColorKey::EMPTY;
        keys[18][5] = ColorKey::ARROW_RIGHT;


        keys[19] = new ColorKey[6];
        keys[19][0] = ColorKey::EMPTY;
        keys[19][1] = ColorKey::EMPTY; //The num key... unknowns its
        keys[19][2] = ColorKey::NUM_7;
        keys[19][3] = ColorKey::NUM_4;
        keys[19][4] = ColorKey::NUM_1;
        keys[19][5] = ColorKey::NUM_0;

        keys[20] = new ColorKey[6];
        keys[20][0] = ColorKey::EMPTY;
        keys[20][1] = ColorKey::NUM_SLASH;
        keys[20][2] = ColorKey::NUM_8;
        keys[20][3] = ColorKey::NUM_5;
        keys[20][4] = ColorKey::NUM_2;
        keys[20][5] = ColorKey::NUM_0;

        keys[21] = new ColorKey[6];
        keys[21][0] = ColorKey::EMPTY;
        keys[21][1] = ColorKey::NUM_STAR;
        keys[21][2] = ColorKey::NUM_9;
        keys[21][3] = ColorKey::NUM_6;
        keys[21][4] = ColorKey::NUM_3;
        keys[21][5] = ColorKey::NUM_COMMA;

        keys[22] = new ColorKey[6];
        keys[22][0] = ColorKey::EMPTY;
        keys[22][1] = ColorKey::NUM_MINUS;
        keys[22][2] = ColorKey::NUM_PLUS;
        keys[22][3] = ColorKey::NUM_PLUS;
        keys[22][4] = ColorKey::NUM_ENTER;
        keys[22][5] = ColorKey::NUM_ENTER;
        return keys;
    }

    ColorKey** rowMapping = buildMapping();
}