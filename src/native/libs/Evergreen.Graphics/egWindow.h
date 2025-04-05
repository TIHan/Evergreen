#pragma once

#define EG_EXPORT __declspec(dllexport)

typedef int EgWindowBool;

typedef struct {
	void* internal;
} EgWindow;

typedef struct {
    float x;
    float y;
} EgWindowVector2;

#define EgWindowKey_SCANCODE_MASK (1<<30)
#define EgWindow_SCANCODE_TO_KEYCODE(X)  (X | EgWindowKey_SCANCODE_MASK)

typedef enum
{
    EgWindow_SCANCODE_UNKNOWN = 0,

    /**
     *  \name Usage page 0x07
     *
     *  These values are from usage page 0x07 (USB keyboard page).
     */
     /* @{ */

    EgWindow_SCANCODE_A = 4,
    EgWindow_SCANCODE_B = 5,
    EgWindow_SCANCODE_C = 6,
    EgWindow_SCANCODE_D = 7,
    EgWindow_SCANCODE_E = 8,
    EgWindow_SCANCODE_F = 9,
    EgWindow_SCANCODE_G = 10,
    EgWindow_SCANCODE_H = 11,
    EgWindow_SCANCODE_I = 12,
    EgWindow_SCANCODE_J = 13,
    EgWindow_SCANCODE_K = 14,
    EgWindow_SCANCODE_L = 15,
    EgWindow_SCANCODE_M = 16,
    EgWindow_SCANCODE_N = 17,
    EgWindow_SCANCODE_O = 18,
    EgWindow_SCANCODE_P = 19,
    EgWindow_SCANCODE_Q = 20,
    EgWindow_SCANCODE_R = 21,
    EgWindow_SCANCODE_S = 22,
    EgWindow_SCANCODE_T = 23,
    EgWindow_SCANCODE_U = 24,
    EgWindow_SCANCODE_V = 25,
    EgWindow_SCANCODE_W = 26,
    EgWindow_SCANCODE_X = 27,
    EgWindow_SCANCODE_Y = 28,
    EgWindow_SCANCODE_Z = 29,

    EgWindow_SCANCODE_1 = 30,
    EgWindow_SCANCODE_2 = 31,
    EgWindow_SCANCODE_3 = 32,
    EgWindow_SCANCODE_4 = 33,
    EgWindow_SCANCODE_5 = 34,
    EgWindow_SCANCODE_6 = 35,
    EgWindow_SCANCODE_7 = 36,
    EgWindow_SCANCODE_8 = 37,
    EgWindow_SCANCODE_9 = 38,
    EgWindow_SCANCODE_0 = 39,

    EgWindow_SCANCODE_RETURN = 40,
    EgWindow_SCANCODE_ESCAPE = 41,
    EgWindow_SCANCODE_BACKSPACE = 42,
    EgWindow_SCANCODE_TAB = 43,
    EgWindow_SCANCODE_SPACE = 44,

    EgWindow_SCANCODE_MINUS = 45,
    EgWindow_SCANCODE_EQUALS = 46,
    EgWindow_SCANCODE_LEFTBRACKET = 47,
    EgWindow_SCANCODE_RIGHTBRACKET = 48,
    EgWindow_SCANCODE_BACKSLASH = 49, /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout, REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout, NUMBER SIGN and TILDE in a UK
                                  *   Windows layout, DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout, NUMBER SIGN and
                                  *   APOSTROPHE in a German layout, GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout, and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
    EgWindow_SCANCODE_NONUSHASH = 50, /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key, but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So, as an implementor, unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently,
                                  *   you should generate EgWindow_SCANCODE_BACKSLASH
                                  *   instead of this code. As a user, you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
    EgWindow_SCANCODE_SEMICOLON = 51,
    EgWindow_SCANCODE_APOSTROPHE = 52,
    EgWindow_SCANCODE_GRAVE = 53, /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards, GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout, SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards, SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards), CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards), SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout, COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards, and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German, German, or French Mac
                              *   layout on ANSI keyboards.
                              */
    EgWindow_SCANCODE_COMMA = 54,
    EgWindow_SCANCODE_PERIOD = 55,
    EgWindow_SCANCODE_SLASH = 56,

    EgWindow_SCANCODE_CAPSLOCK = 57,

    EgWindow_SCANCODE_F1 = 58,
    EgWindow_SCANCODE_F2 = 59,
    EgWindow_SCANCODE_F3 = 60,
    EgWindow_SCANCODE_F4 = 61,
    EgWindow_SCANCODE_F5 = 62,
    EgWindow_SCANCODE_F6 = 63,
    EgWindow_SCANCODE_F7 = 64,
    EgWindow_SCANCODE_F8 = 65,
    EgWindow_SCANCODE_F9 = 66,
    EgWindow_SCANCODE_F10 = 67,
    EgWindow_SCANCODE_F11 = 68,
    EgWindow_SCANCODE_F12 = 69,

    EgWindow_SCANCODE_PRINTSCREEN = 70,
    EgWindow_SCANCODE_SCROLLLOCK = 71,
    EgWindow_SCANCODE_PAUSE = 72,
    EgWindow_SCANCODE_INSERT = 73, /**< insert on PC, help on some Mac keyboards (but
                                   does send code 73, not 117) */
    EgWindow_SCANCODE_HOME = 74,
    EgWindow_SCANCODE_PAGEUP = 75,
    EgWindow_SCANCODE_DELETE = 76,
    EgWindow_SCANCODE_END = 77,
    EgWindow_SCANCODE_PAGEDOWN = 78,
    EgWindow_SCANCODE_RIGHT = 79,
    EgWindow_SCANCODE_LEFT = 80,
    EgWindow_SCANCODE_DOWN = 81,
    EgWindow_SCANCODE_UP = 82,

    EgWindow_SCANCODE_NUMLOCKCLEAR = 83, /**< num lock on PC, clear on Mac keyboards
                                     */
    EgWindow_SCANCODE_KP_DIVIDE = 84,
    EgWindow_SCANCODE_KP_MULTIPLY = 85,
    EgWindow_SCANCODE_KP_MINUS = 86,
    EgWindow_SCANCODE_KP_PLUS = 87,
    EgWindow_SCANCODE_KP_ENTER = 88,
    EgWindow_SCANCODE_KP_1 = 89,
    EgWindow_SCANCODE_KP_2 = 90,
    EgWindow_SCANCODE_KP_3 = 91,
    EgWindow_SCANCODE_KP_4 = 92,
    EgWindow_SCANCODE_KP_5 = 93,
    EgWindow_SCANCODE_KP_6 = 94,
    EgWindow_SCANCODE_KP_7 = 95,
    EgWindow_SCANCODE_KP_8 = 96,
    EgWindow_SCANCODE_KP_9 = 97,
    EgWindow_SCANCODE_KP_0 = 98,
    EgWindow_SCANCODE_KP_PERIOD = 99,

    EgWindow_SCANCODE_NONUSBACKSLASH = 100, /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones,
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout, REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout, and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German, German, or French
                                        *   layout. */
    EgWindow_SCANCODE_APPLICATION = 101, /**< windows contextual menu, compose */
    EgWindow_SCANCODE_POWER = 102, /**< The USB document says this is a status flag,
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
    EgWindow_SCANCODE_KP_EQUALS = 103,
    EgWindow_SCANCODE_F13 = 104,
    EgWindow_SCANCODE_F14 = 105,
    EgWindow_SCANCODE_F15 = 106,
    EgWindow_SCANCODE_F16 = 107,
    EgWindow_SCANCODE_F17 = 108,
    EgWindow_SCANCODE_F18 = 109,
    EgWindow_SCANCODE_F19 = 110,
    EgWindow_SCANCODE_F20 = 111,
    EgWindow_SCANCODE_F21 = 112,
    EgWindow_SCANCODE_F22 = 113,
    EgWindow_SCANCODE_F23 = 114,
    EgWindow_SCANCODE_F24 = 115,
    EgWindow_SCANCODE_EXECUTE = 116,
    EgWindow_SCANCODE_HELP = 117,    /**< AL Integrated Help Center */
    EgWindow_SCANCODE_MENU = 118,    /**< Menu (show menu) */
    EgWindow_SCANCODE_SELECT = 119,
    EgWindow_SCANCODE_STOP = 120,    /**< AC Stop */
    EgWindow_SCANCODE_AGAIN = 121,   /**< AC Redo/Repeat */
    EgWindow_SCANCODE_UNDO = 122,    /**< AC Undo */
    EgWindow_SCANCODE_CUT = 123,     /**< AC Cut */
    EgWindow_SCANCODE_COPY = 124,    /**< AC Copy */
    EgWindow_SCANCODE_PASTE = 125,   /**< AC Paste */
    EgWindow_SCANCODE_FIND = 126,    /**< AC Find */
    EgWindow_SCANCODE_MUTE = 127,
    EgWindow_SCANCODE_VOLUMEUP = 128,
    EgWindow_SCANCODE_VOLUMEDOWN = 129,
    /* not sure whether there's a reason to enable these */
    /*     EgWindow_SCANCODE_LOCKINGCAPSLOCK = 130,  */
    /*     EgWindow_SCANCODE_LOCKINGNUMLOCK = 131, */
    /*     EgWindow_SCANCODE_LOCKINGSCROLLLOCK = 132, */
    EgWindow_SCANCODE_KP_COMMA = 133,
    EgWindow_SCANCODE_KP_EQUALSAS400 = 134,

    EgWindow_SCANCODE_INTERNATIONAL1 = 135, /**< used on Asian keyboards, see
                                            footnotes in USB doc */
    EgWindow_SCANCODE_INTERNATIONAL2 = 136,
    EgWindow_SCANCODE_INTERNATIONAL3 = 137, /**< Yen */
    EgWindow_SCANCODE_INTERNATIONAL4 = 138,
    EgWindow_SCANCODE_INTERNATIONAL5 = 139,
    EgWindow_SCANCODE_INTERNATIONAL6 = 140,
    EgWindow_SCANCODE_INTERNATIONAL7 = 141,
    EgWindow_SCANCODE_INTERNATIONAL8 = 142,
    EgWindow_SCANCODE_INTERNATIONAL9 = 143,
    EgWindow_SCANCODE_LANG1 = 144, /**< Hangul/English toggle */
    EgWindow_SCANCODE_LANG2 = 145, /**< Hanja conversion */
    EgWindow_SCANCODE_LANG3 = 146, /**< Katakana */
    EgWindow_SCANCODE_LANG4 = 147, /**< Hiragana */
    EgWindow_SCANCODE_LANG5 = 148, /**< Zenkaku/Hankaku */
    EgWindow_SCANCODE_LANG6 = 149, /**< reserved */
    EgWindow_SCANCODE_LANG7 = 150, /**< reserved */
    EgWindow_SCANCODE_LANG8 = 151, /**< reserved */
    EgWindow_SCANCODE_LANG9 = 152, /**< reserved */

    EgWindow_SCANCODE_ALTERASE = 153,    /**< Erase-Eaze */
    EgWindow_SCANCODE_SYSREQ = 154,
    EgWindow_SCANCODE_CANCEL = 155,      /**< AC Cancel */
    EgWindow_SCANCODE_CLEAR = 156,
    EgWindow_SCANCODE_PRIOR = 157,
    EgWindow_SCANCODE_RETURN2 = 158,
    EgWindow_SCANCODE_SEPARATOR = 159,
    EgWindow_SCANCODE_OUT = 160,
    EgWindow_SCANCODE_OPER = 161,
    EgWindow_SCANCODE_CLEARAGAIN = 162,
    EgWindow_SCANCODE_CRSEL = 163,
    EgWindow_SCANCODE_EXSEL = 164,

    EgWindow_SCANCODE_KP_00 = 176,
    EgWindow_SCANCODE_KP_000 = 177,
    EgWindow_SCANCODE_THOUSANDSSEPARATOR = 178,
    EgWindow_SCANCODE_DECIMALSEPARATOR = 179,
    EgWindow_SCANCODE_CURRENCYUNIT = 180,
    EgWindow_SCANCODE_CURRENCYSUBUNIT = 181,
    EgWindow_SCANCODE_KP_LEFTPAREN = 182,
    EgWindow_SCANCODE_KP_RIGHTPAREN = 183,
    EgWindow_SCANCODE_KP_LEFTBRACE = 184,
    EgWindow_SCANCODE_KP_RIGHTBRACE = 185,
    EgWindow_SCANCODE_KP_TAB = 186,
    EgWindow_SCANCODE_KP_BACKSPACE = 187,
    EgWindow_SCANCODE_KP_A = 188,
    EgWindow_SCANCODE_KP_B = 189,
    EgWindow_SCANCODE_KP_C = 190,
    EgWindow_SCANCODE_KP_D = 191,
    EgWindow_SCANCODE_KP_E = 192,
    EgWindow_SCANCODE_KP_F = 193,
    EgWindow_SCANCODE_KP_XOR = 194,
    EgWindow_SCANCODE_KP_POWER = 195,
    EgWindow_SCANCODE_KP_PERCENT = 196,
    EgWindow_SCANCODE_KP_LESS = 197,
    EgWindow_SCANCODE_KP_GREATER = 198,
    EgWindow_SCANCODE_KP_AMPERSAND = 199,
    EgWindow_SCANCODE_KP_DBLAMPERSAND = 200,
    EgWindow_SCANCODE_KP_VERTICALBAR = 201,
    EgWindow_SCANCODE_KP_DBLVERTICALBAR = 202,
    EgWindow_SCANCODE_KP_COLON = 203,
    EgWindow_SCANCODE_KP_HASH = 204,
    EgWindow_SCANCODE_KP_SPACE = 205,
    EgWindow_SCANCODE_KP_AT = 206,
    EgWindow_SCANCODE_KP_EXCLAM = 207,
    EgWindow_SCANCODE_KP_MEMSTORE = 208,
    EgWindow_SCANCODE_KP_MEMRECALL = 209,
    EgWindow_SCANCODE_KP_MEMCLEAR = 210,
    EgWindow_SCANCODE_KP_MEMADD = 211,
    EgWindow_SCANCODE_KP_MEMSUBTRACT = 212,
    EgWindow_SCANCODE_KP_MEMMULTIPLY = 213,
    EgWindow_SCANCODE_KP_MEMDIVIDE = 214,
    EgWindow_SCANCODE_KP_PLUSMINUS = 215,
    EgWindow_SCANCODE_KP_CLEAR = 216,
    EgWindow_SCANCODE_KP_CLEARENTRY = 217,
    EgWindow_SCANCODE_KP_BINARY = 218,
    EgWindow_SCANCODE_KP_OCTAL = 219,
    EgWindow_SCANCODE_KP_DECIMAL = 220,
    EgWindow_SCANCODE_KP_HEXADECIMAL = 221,

    EgWindow_SCANCODE_LCTRL = 224,
    EgWindow_SCANCODE_LSHIFT = 225,
    EgWindow_SCANCODE_LALT = 226, /**< alt, option */
    EgWindow_SCANCODE_LGUI = 227, /**< windows, command (apple), meta */
    EgWindow_SCANCODE_RCTRL = 228,
    EgWindow_SCANCODE_RSHIFT = 229,
    EgWindow_SCANCODE_RALT = 230, /**< alt gr, option */
    EgWindow_SCANCODE_RGUI = 231, /**< windows, command (apple), meta */

    EgWindow_SCANCODE_MODE = 257,    /**< I'm not sure if this is really not covered
                                 *   by any of the above, but since there's a
                                 *   special EgWindow_KMOD_MODE for it I'm adding it here
                                 */

                                 /* @} *//* Usage page 0x07 */

                                 /**
                                  *  \name Usage page 0x0C
                                  *
                                  *  These values are mapped from usage page 0x0C (USB consumer page).
                                  *  See https://usb.org/sites/default/files/hut1_2.pdf
                                  *
                                  *  There are way more keys in the spec than we can represent in the
                                  *  current scancode range, so pick the ones that commonly come up in
                                  *  real world usage.
                                  */
                                  /* @{ */

    EgWindow_SCANCODE_AUDIONEXT = 258,
    EgWindow_SCANCODE_AUDIOPREV = 259,
    EgWindow_SCANCODE_AUDIOSTOP = 260,
    EgWindow_SCANCODE_AUDIOPLAY = 261,
    EgWindow_SCANCODE_AUDIOMUTE = 262,
    EgWindow_SCANCODE_MEDIASELECT = 263,
    EgWindow_SCANCODE_WWW = 264,             /**< AL Internet Browser */
    EgWindow_SCANCODE_MAIL = 265,
    EgWindow_SCANCODE_CALCULATOR = 266,      /**< AL Calculator */
    EgWindow_SCANCODE_COMPUTER = 267,
    EgWindow_SCANCODE_AC_SEARCH = 268,       /**< AC Search */
    EgWindow_SCANCODE_AC_HOME = 269,         /**< AC Home */
    EgWindow_SCANCODE_AC_BACK = 270,         /**< AC Back */
    EgWindow_SCANCODE_AC_FORWARD = 271,      /**< AC Forward */
    EgWindow_SCANCODE_AC_STOP = 272,         /**< AC Stop */
    EgWindow_SCANCODE_AC_REFRESH = 273,      /**< AC Refresh */
    EgWindow_SCANCODE_AC_BOOKMARKS = 274,    /**< AC Bookmarks */

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
     /* @{ */

    EgWindow_SCANCODE_BRIGHTNESSDOWN = 275,
    EgWindow_SCANCODE_BRIGHTNESSUP = 276,
    EgWindow_SCANCODE_DISPLAYSWITCH = 277, /**< display mirroring/dual display
                                           switch, video mode switch */
    EgWindow_SCANCODE_KBDILLUMTOGGLE = 278,
    EgWindow_SCANCODE_KBDILLUMDOWN = 279,
    EgWindow_SCANCODE_KBDILLUMUP = 280,
    EgWindow_SCANCODE_EJECT = 281,
    EgWindow_SCANCODE_SLEEP = 282,           /**< SC System Sleep */

    EgWindow_SCANCODE_APP1 = 283,
    EgWindow_SCANCODE_APP2 = 284,

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
     /* @{ */

    EgWindow_SCANCODE_AUDIOREWIND = 285,
    EgWindow_SCANCODE_AUDIOFASTFORWARD = 286,

    /* @} *//* Usage page 0x0C (additional media keys) */

    /**
     *  \name Mobile keys
     *
     *  These are values that are often used on mobile phones.
     */
     /* @{ */

    EgWindow_SCANCODE_SOFTLEFT = 287, /**< Usually situated below the display on phones and
                                      used as a multi-function feature key for selecting
                                      a software defined function shown on the bottom left
                                      of the display. */
    EgWindow_SCANCODE_SOFTRIGHT = 288, /**< Usually situated below the display on phones and
                                       used as a multi-function feature key for selecting
                                       a software defined function shown on the bottom right
                                       of the display. */
    EgWindow_SCANCODE_CALL = 289, /**< Used for accepting phone calls. */
    EgWindow_SCANCODE_ENDCALL = 290, /**< Used for rejecting phone calls. */

    /* @} *//* Mobile keys */

    /* Add any other keys here. */

    EgWindow_NUM_SCANCODES = 512 /**< not a key, just marks the number of scancodes
                                 for array bounds */
} EgWindow_Scancode;

typedef enum
{
    EgWindowKey_UNKNOWN = 0,

    EgWindowKey_RETURN = '\r',
    EgWindowKey_ESCAPE = '\x1B',
    EgWindowKey_BACKSPACE = '\b',
    EgWindowKey_TAB = '\t',
    EgWindowKey_SPACE = ' ',
    EgWindowKey_EXCLAIM = '!',
    EgWindowKey_QUOTEDBL = '"',
    EgWindowKey_HASH = '#',
    EgWindowKey_PERCENT = '%',
    EgWindowKey_DOLLAR = '$',
    EgWindowKey_AMPERSAND = '&',
    EgWindowKey_QUOTE = '\'',
    EgWindowKey_LEFTPAREN = '(',
    EgWindowKey_RIGHTPAREN = ')',
    EgWindowKey_ASTERISK = '*',
    EgWindowKey_PLUS = '+',
    EgWindowKey_COMMA = ',',
    EgWindowKey_MINUS = '-',
    EgWindowKey_PERIOD = '.',
    EgWindowKey_SLASH = '/',
    EgWindowKey_0 = '0',
    EgWindowKey_1 = '1',
    EgWindowKey_2 = '2',
    EgWindowKey_3 = '3',
    EgWindowKey_4 = '4',
    EgWindowKey_5 = '5',
    EgWindowKey_6 = '6',
    EgWindowKey_7 = '7',
    EgWindowKey_8 = '8',
    EgWindowKey_9 = '9',
    EgWindowKey_COLON = ':',
    EgWindowKey_SEMICOLON = ';',
    EgWindowKey_LESS = '<',
    EgWindowKey_EQUALS = '=',
    EgWindowKey_GREATER = '>',
    EgWindowKey_QUESTION = '?',
    EgWindowKey_AT = '@',

    /*
       Skip uppercase letters
     */

    EgWindowKey_LEFTBRACKET = '[',
    EgWindowKey_BACKSLASH = '\\',
    EgWindowKey_RIGHTBRACKET = ']',
    EgWindowKey_CARET = '^',
    EgWindowKey_UNDERSCORE = '_',
    EgWindowKey_BACKQUOTE = '`',
    EgWindowKey_a = 'a',
    EgWindowKey_b = 'b',
    EgWindowKey_c = 'c',
    EgWindowKey_d = 'd',
    EgWindowKey_e = 'e',
    EgWindowKey_f = 'f',
    EgWindowKey_g = 'g',
    EgWindowKey_h = 'h',
    EgWindowKey_i = 'i',
    EgWindowKey_j = 'j',
    EgWindowKey_k = 'k',
    EgWindowKey_l = 'l',
    EgWindowKey_m = 'm',
    EgWindowKey_n = 'n',
    EgWindowKey_o = 'o',
    EgWindowKey_p = 'p',
    EgWindowKey_q = 'q',
    EgWindowKey_r = 'r',
    EgWindowKey_s = 's',
    EgWindowKey_t = 't',
    EgWindowKey_u = 'u',
    EgWindowKey_v = 'v',
    EgWindowKey_w = 'w',
    EgWindowKey_x = 'x',
    EgWindowKey_y = 'y',
    EgWindowKey_z = 'z',

    EgWindowKey_CAPSLOCK = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CAPSLOCK),

    EgWindowKey_F1 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F1),
    EgWindowKey_F2 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F2),
    EgWindowKey_F3 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F3),
    EgWindowKey_F4 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F4),
    EgWindowKey_F5 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F5),
    EgWindowKey_F6 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F6),
    EgWindowKey_F7 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F7),
    EgWindowKey_F8 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F8),
    EgWindowKey_F9 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F9),
    EgWindowKey_F10 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F10),
    EgWindowKey_F11 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F11),
    EgWindowKey_F12 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F12),

    EgWindowKey_PRINTSCREEN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_PRINTSCREEN),
    EgWindowKey_SCROLLLOCK = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SCROLLLOCK),
    EgWindowKey_PAUSE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_PAUSE),
    EgWindowKey_INSERT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_INSERT),
    EgWindowKey_HOME = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_HOME),
    EgWindowKey_PAGEUP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_PAGEUP),
    EgWindowKey_DELETE = '\x7F',
    EgWindowKey_END = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_END),
    EgWindowKey_PAGEDOWN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_PAGEDOWN),
    EgWindowKey_RIGHT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_RIGHT),
    EgWindowKey_LEFT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_LEFT),
    EgWindowKey_DOWN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_DOWN),
    EgWindowKey_UP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_UP),

    EgWindowKey_NUMLOCKCLEAR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_NUMLOCKCLEAR),
    EgWindowKey_KP_DIVIDE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_DIVIDE),
    EgWindowKey_KP_MULTIPLY = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MULTIPLY),
    EgWindowKey_KP_MINUS = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MINUS),
    EgWindowKey_KP_PLUS = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_PLUS),
    EgWindowKey_KP_ENTER = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_ENTER),
    EgWindowKey_KP_1 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_1),
    EgWindowKey_KP_2 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_2),
    EgWindowKey_KP_3 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_3),
    EgWindowKey_KP_4 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_4),
    EgWindowKey_KP_5 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_5),
    EgWindowKey_KP_6 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_6),
    EgWindowKey_KP_7 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_7),
    EgWindowKey_KP_8 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_8),
    EgWindowKey_KP_9 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_9),
    EgWindowKey_KP_0 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_0),
    EgWindowKey_KP_PERIOD = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_PERIOD),

    EgWindowKey_APPLICATION = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_APPLICATION),
    EgWindowKey_POWER = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_POWER),
    EgWindowKey_KP_EQUALS = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_EQUALS),
    EgWindowKey_F13 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F13),
    EgWindowKey_F14 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F14),
    EgWindowKey_F15 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F15),
    EgWindowKey_F16 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F16),
    EgWindowKey_F17 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F17),
    EgWindowKey_F18 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F18),
    EgWindowKey_F19 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F19),
    EgWindowKey_F20 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F20),
    EgWindowKey_F21 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F21),
    EgWindowKey_F22 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F22),
    EgWindowKey_F23 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F23),
    EgWindowKey_F24 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_F24),
    EgWindowKey_EXECUTE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_EXECUTE),
    EgWindowKey_HELP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_HELP),
    EgWindowKey_MENU = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_MENU),
    EgWindowKey_SELECT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SELECT),
    EgWindowKey_STOP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_STOP),
    EgWindowKey_AGAIN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AGAIN),
    EgWindowKey_UNDO = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_UNDO),
    EgWindowKey_CUT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CUT),
    EgWindowKey_COPY = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_COPY),
    EgWindowKey_PASTE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_PASTE),
    EgWindowKey_FIND = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_FIND),
    EgWindowKey_MUTE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_MUTE),
    EgWindowKey_VOLUMEUP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_VOLUMEUP),
    EgWindowKey_VOLUMEDOWN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_VOLUMEDOWN),
    EgWindowKey_KP_COMMA = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_COMMA),
    EgWindowKey_KP_EQUALSAS400 =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_EQUALSAS400),

    EgWindowKey_ALTERASE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_ALTERASE),
    EgWindowKey_SYSREQ = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SYSREQ),
    EgWindowKey_CANCEL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CANCEL),
    EgWindowKey_CLEAR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CLEAR),
    EgWindowKey_PRIOR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_PRIOR),
    EgWindowKey_RETURN2 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_RETURN2),
    EgWindowKey_SEPARATOR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SEPARATOR),
    EgWindowKey_OUT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_OUT),
    EgWindowKey_OPER = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_OPER),
    EgWindowKey_CLEARAGAIN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CLEARAGAIN),
    EgWindowKey_CRSEL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CRSEL),
    EgWindowKey_EXSEL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_EXSEL),

    EgWindowKey_KP_00 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_00),
    EgWindowKey_KP_000 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_000),
    EgWindowKey_THOUSANDSSEPARATOR =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_THOUSANDSSEPARATOR),
    EgWindowKey_DECIMALSEPARATOR =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_DECIMALSEPARATOR),
    EgWindowKey_CURRENCYUNIT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CURRENCYUNIT),
    EgWindowKey_CURRENCYSUBUNIT =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CURRENCYSUBUNIT),
    EgWindowKey_KP_LEFTPAREN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_LEFTPAREN),
    EgWindowKey_KP_RIGHTPAREN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_RIGHTPAREN),
    EgWindowKey_KP_LEFTBRACE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_LEFTBRACE),
    EgWindowKey_KP_RIGHTBRACE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_RIGHTBRACE),
    EgWindowKey_KP_TAB = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_TAB),
    EgWindowKey_KP_BACKSPACE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_BACKSPACE),
    EgWindowKey_KP_A = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_A),
    EgWindowKey_KP_B = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_B),
    EgWindowKey_KP_C = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_C),
    EgWindowKey_KP_D = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_D),
    EgWindowKey_KP_E = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_E),
    EgWindowKey_KP_F = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_F),
    EgWindowKey_KP_XOR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_XOR),
    EgWindowKey_KP_POWER = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_POWER),
    EgWindowKey_KP_PERCENT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_PERCENT),
    EgWindowKey_KP_LESS = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_LESS),
    EgWindowKey_KP_GREATER = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_GREATER),
    EgWindowKey_KP_AMPERSAND = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_AMPERSAND),
    EgWindowKey_KP_DBLAMPERSAND =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_DBLAMPERSAND),
    EgWindowKey_KP_VERTICALBAR =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_VERTICALBAR),
    EgWindowKey_KP_DBLVERTICALBAR =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_DBLVERTICALBAR),
    EgWindowKey_KP_COLON = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_COLON),
    EgWindowKey_KP_HASH = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_HASH),
    EgWindowKey_KP_SPACE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_SPACE),
    EgWindowKey_KP_AT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_AT),
    EgWindowKey_KP_EXCLAM = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_EXCLAM),
    EgWindowKey_KP_MEMSTORE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMSTORE),
    EgWindowKey_KP_MEMRECALL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMRECALL),
    EgWindowKey_KP_MEMCLEAR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMCLEAR),
    EgWindowKey_KP_MEMADD = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMADD),
    EgWindowKey_KP_MEMSUBTRACT =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMSUBTRACT),
    EgWindowKey_KP_MEMMULTIPLY =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMMULTIPLY),
    EgWindowKey_KP_MEMDIVIDE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_MEMDIVIDE),
    EgWindowKey_KP_PLUSMINUS = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_PLUSMINUS),
    EgWindowKey_KP_CLEAR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_CLEAR),
    EgWindowKey_KP_CLEARENTRY = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_CLEARENTRY),
    EgWindowKey_KP_BINARY = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_BINARY),
    EgWindowKey_KP_OCTAL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_OCTAL),
    EgWindowKey_KP_DECIMAL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_DECIMAL),
    EgWindowKey_KP_HEXADECIMAL =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KP_HEXADECIMAL),

    EgWindowKey_LCTRL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_LCTRL),
    EgWindowKey_LSHIFT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_LSHIFT),
    EgWindowKey_LALT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_LALT),
    EgWindowKey_LGUI = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_LGUI),
    EgWindowKey_RCTRL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_RCTRL),
    EgWindowKey_RSHIFT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_RSHIFT),
    EgWindowKey_RALT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_RALT),
    EgWindowKey_RGUI = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_RGUI),

    EgWindowKey_MODE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_MODE),

    EgWindowKey_AUDIONEXT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIONEXT),
    EgWindowKey_AUDIOPREV = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIOPREV),
    EgWindowKey_AUDIOSTOP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIOSTOP),
    EgWindowKey_AUDIOPLAY = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIOPLAY),
    EgWindowKey_AUDIOMUTE = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIOMUTE),
    EgWindowKey_MEDIASELECT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_MEDIASELECT),
    EgWindowKey_WWW = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_WWW),
    EgWindowKey_MAIL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_MAIL),
    EgWindowKey_CALCULATOR = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CALCULATOR),
    EgWindowKey_COMPUTER = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_COMPUTER),
    EgWindowKey_AC_SEARCH = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_SEARCH),
    EgWindowKey_AC_HOME = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_HOME),
    EgWindowKey_AC_BACK = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_BACK),
    EgWindowKey_AC_FORWARD = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_FORWARD),
    EgWindowKey_AC_STOP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_STOP),
    EgWindowKey_AC_REFRESH = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_REFRESH),
    EgWindowKey_AC_BOOKMARKS = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AC_BOOKMARKS),

    EgWindowKey_BRIGHTNESSDOWN =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_BRIGHTNESSDOWN),
    EgWindowKey_BRIGHTNESSUP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_BRIGHTNESSUP),
    EgWindowKey_DISPLAYSWITCH = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_DISPLAYSWITCH),
    EgWindowKey_KBDILLUMTOGGLE =
    EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KBDILLUMTOGGLE),
    EgWindowKey_KBDILLUMDOWN = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KBDILLUMDOWN),
    EgWindowKey_KBDILLUMUP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_KBDILLUMUP),
    EgWindowKey_EJECT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_EJECT),
    EgWindowKey_SLEEP = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SLEEP),
    EgWindowKey_APP1 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_APP1),
    EgWindowKey_APP2 = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_APP2),

    EgWindowKey_AUDIOREWIND = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIOREWIND),
    EgWindowKey_AUDIOFASTFORWARD = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_AUDIOFASTFORWARD),

    EgWindowKey_SOFTLEFT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SOFTLEFT),
    EgWindowKey_SOFTRIGHT = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_SOFTRIGHT),
    EgWindowKey_CALL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_CALL),
    EgWindowKey_ENDCALL = EgWindow_SCANCODE_TO_KEYCODE(EgWindow_SCANCODE_ENDCALL)
} EgWindowKey;

typedef enum {
    EgWindowKeyEventFlags_UP        = 0b001,
    EgWindowKeyEventFlags_DOWN      = 0b010,
    EgWindowKeyEventFlags_REPEAT    = 0b110
} EgWindowKeyEventFlags;

typedef struct {
    EgWindowKey key;
    EgWindowKeyEventFlags flags;
} EgWindowKeyEvent;

typedef enum {
    EgWindowMouseButtonEventFlags_UP    = 0b001,
    EgWindowMouseButtonEventFlags_DOWN  = 0b010
} EgWindowMouseButtonEventFlags;

typedef struct {
    unsigned char buttonIndex;
    EgWindowVector2 position;
    EgWindowMouseButtonEventFlags flags;
} EgWindowMouseButtonEvent;

typedef enum {
    EgWindowMouseWheelEventFlags_UP     = 0b001,
    EgWindowMouseWheelEventFlags_DOWN   = 0b010
} EgWindowMouseWheelEventFlags;

typedef struct {
    EgWindowMouseWheelEventFlags flags;
} EgWindowMouseWheelEvent;

typedef struct {
    EgWindowVector2 position;
    EgWindowVector2 relativePosition;
} EgWindowMouseInfo;

typedef struct {
    unsigned int gamepadId;
    unsigned char axisId;
    short value;
} EgWindowGamepadAxisMotionEvent;

typedef enum {
    EgWindowGamepadButtonEventFlags_UP,
    EgWindowGamepadButtonEventFlags_DOWN
} EgWindowGamepadButtonEventFlags;

typedef struct {
    unsigned int gamepadId;
    unsigned char buttonIndex;
    EgWindowGamepadButtonEventFlags flags;
} EgWindowGamepadButtonEvent;

typedef enum {
    EgWindowGamepadEventKind_ADDED,
    EgWindowGamepadEventKind_REMOVED
} EgWindowGamepadEventKind;

typedef struct {
    EgWindowGamepadEventKind kind;
    unsigned int gamepadId;
} EgWindowGamepadEvent;

typedef struct {
    int width;
    int height;
    float refreshRate;
} EgWindowDisplayMode;

extern "C" {

    EG_EXPORT EgWindow egWindowCreateVulkan(const char* name);
    EG_EXPORT void egWindowDestroy(EgWindow window);

    EG_EXPORT void* egWindowGetWin32Handle(EgWindow window);
    EG_EXPORT EgWindowDisplayMode egWindowGetDesktopDisplayMode(EgWindow window);
    EG_EXPORT EgWindowDisplayMode egWindowGetCurrentDisplayMode(EgWindow window);
    EG_EXPORT void egWindowSetCurrentDisplayMode(EgWindow window, EgWindowDisplayMode displayMode);
    EG_EXPORT void egWindowGetDisplayModes(EgWindow window, void(*callbackDisplayMode)(EgWindowDisplayMode));

    EG_EXPORT void egWindowShow(EgWindow window);
    EG_EXPORT void egWindowHide(EgWindow window);
    EG_EXPORT void egWindowMinimize(EgWindow window);
    EG_EXPORT EgWindowBool egWindowIsFullscreen(EgWindow window);
    EG_EXPORT void egWindowSetFullscreen(EgWindow window, EgWindowBool value);
    EG_EXPORT EgWindowBool egWindowIsCursorVisible(EgWindow window);
    EG_EXPORT void egWindowSetCursorVisible(EgWindow window, EgWindowBool value);
    EG_EXPORT EgWindowBool egWindowIsBorderless(EgWindow window);
    EG_EXPORT void egWindowSetBorderless(EgWindow window, EgWindowBool value);
    EG_EXPORT EgWindowBool egWindowIsHidden(EgWindow window);
    EG_EXPORT EgWindowBool egWindowIsMinimized(EgWindow window);
    EG_EXPORT EgWindowVector2 egWindowGetSize(EgWindow window);
    EG_EXPORT void egWindowSetSize(EgWindow window, EgWindowVector2 value);
    EG_EXPORT EgWindowVector2 egWindowGetPosition(EgWindow window);
    EG_EXPORT void egWindowSetPosition(EgWindow window, EgWindowVector2 value);
    EG_EXPORT void egWindowPumpEvents(
        EgWindow window, 
        EgWindowBool hasImGuiInput, 
        void(*callbackKeyEvent)(EgWindowKeyEvent), 
        void(*callbackMouseInfo)(EgWindowMouseInfo), 
        void(*callbackMouseButtonEvent)(EgWindowMouseButtonEvent), 
        void(*callbackMouseWheelEvent)(EgWindowMouseWheelEvent),
        void(*callbackGamepadAxisMotionEvent)(EgWindowGamepadAxisMotionEvent),
        void(*callbackGamepadButtonEvent)(EgWindowGamepadButtonEvent),
        void(*callbackGamepadEvent)(EgWindowGamepadEvent),
        void(*callbackQuit)(void));

}