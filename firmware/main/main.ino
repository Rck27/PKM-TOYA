#define BOARDTYPE 1 // 1 for number, 2 for alphabet, 3 for shape puzzle


#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 3

#define CLK_PIN   39
#define DATA_PIN  40
#define CS_PIN    41

//MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const byte NUM_LEDS = 16;
const byte LED_PIN = 6;
int position, winCount;
unsigned long lastMillis, currentMillis;
char randomAlphabet, pressedKey;
int mode, score;
char t[100];

Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
};


int state[ROWS*COLS] = {0}; // Initialize all to 0

///ESP32 S2
//byte colPins[COLS] = {6, 4, 2, 1}; //connect to the column pinouts of the kpd
//byte rowPins[ROWS] = {14, 13, 10, 8}; //connect to the row pinouts of the kpd
//#define MODE_BUTTON_PIN 5
//#define RESET_BUTTON_PIN 7
//#define START_PAUSE_BUTTON_PIN 9


MD_MAX72XX::fontType_t myFont[] PROGMEM = 
{
  'F', 2, 0, 0, 0, 255, 8,
  0,  // 1 - 'Empty Cell'
  5, 62, 91, 79, 91, 62,  // 2 - 'Sad Smiley'
  5, 62, 107, 79, 107, 62,  // 3 - 'Happy Smiley'
  5, 28, 62, 124, 62, 28,   // 4 - 'Heart'
  5, 24, 60, 126, 60, 24,   // 5 - 'Diamond'
  5, 28, 87, 125, 87, 28,   // 6 - 'Clubs'
  5, 28, 94, 127, 94, 28,   // 7 - 'Spades'
  4, 0, 24, 60, 24,   // 8 - 'Bullet Point'
  5, 255, 231, 195, 231, 255,   // 9 - 'Rev Bullet Point'
  4, 0, 24, 36, 24,   // 10 - 'Hollow Bullet Point'
  5, 255, 231, 219, 231, 255,   // 11 - 'Rev Hollow BP'
  5, 48, 72, 58, 6, 14,   // 12 - 'Male'
  5, 38, 41, 121, 41, 38,   // 13 - 'Female'
  5, 64, 127, 5, 5, 7,  // 14 - 'Music Note 1'
  5, 64, 127, 5, 37, 63,  // 15 - 'Music Note 2'
  5, 90, 60, 231, 60, 90,   // 16 - 'Snowflake'
  5, 127, 62, 28, 28, 8,  // 17 - 'Right Pointer'
  5, 8, 28, 28, 62, 127,  // 18 - 'Left Pointer'
  5, 20, 34, 127, 34, 20,   // 19 - 'UpDown Arrows'
  5, 255, 255, 255, 255, 255,   // 20 - 'Full Block'
  5, 240, 240, 240, 240, 240,   // 21 - 'Half Block Bottom'
  3, 255, 255, 255,   // 22 - 'Half Block LHS'
  5, 0, 0, 0, 255, 255,   // 23 - 'Half Block RHS'
  5, 15, 15, 15, 15, 15,  // 24 - 'Half Block Top'
  5, 8, 4, 126, 4, 8,   // 25 - 'Up Arrow'
  5, 16, 32, 126, 32, 16,   // 26 - 'Down Arrow'
  5, 8, 8, 42, 28, 8,   // 27 - 'Right Arrow'
  5, 8, 28, 42, 8, 8,   // 28 - 'Left Arrow'
  5, 170, 0, 85, 0, 170,  // 29 - '30% shading'
  5, 170, 85, 170, 85, 170,   // 30 - '50% shading'
  5, 48, 56, 62, 56, 48,  // 31 - 'Up Pointer'
  5, 6, 14, 62, 14, 6,  // 32 - 'Down Pointer'
  2, 0, 0,  // 33  - 'Space'
  1, 95,  // 34 - '!'
  3, 7, 0, 7,   // 35 - '""'
  5, 20, 127, 20, 127, 20,  // 36 - '#'
  5, 68, 74, 255, 74, 50,   // 37 - '$'
  5, 99, 19, 8, 100, 99,  // 38 - '%'
  5, 54, 73, 73, 54, 72,  // 39 - '&'
  1, 7,   // 40 - '''
  3, 62, 65, 65,  // 41 - '('
  3, 65, 65, 62,  // 42 - ')'
  5, 8, 42, 28, 42, 8,  // 43 - '*'
  5, 8, 8, 62, 8, 8,  // 44 - '+'
  3, 96, 224, 0,  // 45'
  4, 8, 8, 8, 8,  // 46 - '-'
  2, 96, 96,  // 47 - '.'
  5, 96, 16, 8, 4, 3,   // 48 - '/'
  5, 62, 127, 73, 69, 62,   // 49 - '0'
  4, 4, 2, 127, 127,  // 50 - '1'
  5, 113, 121, 73, 79, 70,  // 51 - '2'
  5, 65, 73, 73, 127, 54,   // 52 - '3'
  5, 15, 15, 8, 120, 127,   // 53 - '4'
  5, 79, 79, 73, 121, 49,   // 54 - '5'
  5, 62, 127, 73, 73, 48,   // 55 - '6'
  5, 3, 3, 113, 121, 7,   // 56 - '7'
  5, 54, 127, 73, 73, 54,   // 57 - '8'
  5, 6, 73, 73, 127, 62,  // 58 - '9'
  2, 108, 108,  // 59 - ':'
  2, 108, 236,  // 60 - ';'
  3, 8, 20, 34,   // 61 - '<'
  4, 20, 20, 20, 20,  // 62 - '='
  3, 34, 20, 8,   // 63 - '>'
  5, 1, 89, 9, 9, 6,  // 64 - '?'
  5, 62, 65, 93, 89, 78,  // 65 - '@'
  5, 126, 127, 9, 9, 126,   // 66 - 'A'
  5, 127, 127, 73, 73, 54,  // 67 - 'B'
  5, 62, 127, 65, 65, 65,   // 68 - 'C'
  5, 127, 127, 65, 65, 62,  // 69 - 'D'
  5, 127, 127, 73, 73, 65,  // 70 - 'E'
  5, 127, 127, 9, 9, 1,   // 71 - 'F'
  5, 62, 127, 65, 73, 121,  // 72 - 'G'
  5, 127, 127, 8, 8, 127,   // 73 - 'H'
  4, 65, 127, 127, 65,  // 74 - 'I'
  5, 48, 65, 65, 127, 63,   // 75 - 'J'
  5, 127, 127, 20, 34, 65,  // 76 - 'K'
  5, 127, 127, 64, 64, 64,  // 77 - 'L'
  6, 127, 126, 4, 28, 6, 127,   // 78 - 'M'
  5, 127, 127, 4, 8, 127,   // 79 - 'N'
  5, 62, 127, 65, 65, 62,   // 80 - 'O'
  5, 127, 127, 9, 9, 6,   // 81 - 'P'
  5, 62, 127, 65, 97, 126,  // 82 - 'Q'
  5, 127, 127, 25, 41, 70,  // 83 - 'R'
  5, 70, 79, 73, 121, 49,   // 84 - 'S'
  6, 1, 1, 127, 127, 1, 1,  // 85 - 'T'
  5, 63, 127, 64, 64, 63,   // 86 - 'U'
  5, 31, 63, 64, 32, 31,  // 87 - 'V'
  6, 63, 127, 64, 48, 64, 63,   // 88 - 'W'
  5, 99, 119, 8, 20, 99,  // 89 - 'X'
  6, 3, 7, 124, 120, 4, 3,  // 90 - 'Y'
  5, 97, 113, 89, 77, 71,   // 91 - 'Z'
  3, 127, 65, 65,   // 92 - '['
  5, 3, 4, 8, 16, 96,   // 93 - '\'
  3, 65, 65, 127,   // 94 - ']'
  5, 4, 2, 1, 2, 4,   // 95 - '^'
  4, 128, 128, 128, 128,  // 96 - '_'
  3, 1, 2, 4,   // 97 - '`'
  4, 56, 68, 68, 124,   // 98 - 'a'
  4, 127, 68, 68, 56,   // 99 - 'b'
  4, 56, 68, 68, 68,  // 100 - 'c'
  4, 56, 68, 68, 127,   // 101 - 'd'
  4, 56, 84, 84, 88,  // 102 - 'e'
  4, 4, 126, 5, 1,  // 103 - 'f'
  4, 24, 164, 164, 124,   // 104 - 'g'
  4, 127, 4, 4, 120,  // 105 - 'h'
  1, 125,   // 106 - 'i'
  3, 132, 133, 124,   // 107 - 'j'
  4, 127, 16, 40, 68,   // 108 - 'k'
  1, 127,   // 109 - 'l'
  5, 124, 4, 120, 4, 120,   // 110 - 'm'
  4, 124, 4, 4, 120,  // 111 - 'n'
  4, 56, 68, 68, 56,  // 112 - 'o'
  4, 252, 36, 36, 24,   // 113 - 'p'
  4, 24, 36, 36, 252,   // 114 - 'q'
  4, 124, 4, 4, 8,  // 115 - 'r'
  4, 88, 84, 84, 52,  // 116 - 's'
  3, 4, 127, 4,   // 117 - 't'
  4, 60, 64, 64, 124,   // 118 - 'u'
  4, 28, 32, 64, 124,   // 119 - 'v'
  5, 60, 64, 48, 64, 60,  // 120 - 'w'
  4, 108, 16, 16, 108,  // 121 - 'x'
  4, 28, 160, 160, 124,   // 122 - 'y'
  4, 100, 84, 84, 76,   // 123 - 'z'
  4, 8, 54, 65, 65,   // 124 - '{'
  1, 127,   // 125 - '|'
  4, 65, 65, 54, 8,   // 126 - '}'
  4, 2, 1, 2, 1,  // 127 - '~'
  5, 127, 65, 65, 65, 127,  // 128 - 'Hollow Block'
  5, 62, 85, 85, 85, 65,  // 129 - 'Euro symbol'
  5, 56, 68, 68, 56, 68,  // 130 - 'Alpha'
  5, 124, 42, 42, 62, 20,   // 131 - 'Beta'
  5, 126, 2, 2, 6, 6,   // 132 - 'Gamma'
  5, 2, 126, 2, 126, 2,   // 133 - 'Pi'
  5, 99, 85, 73, 65, 99,  // 134 - 'Sigma'
  5, 56, 68, 68, 60, 4,   // 135 - 'Theta'
  5, 64, 126, 32, 30, 32,   // 136 - 'mu'
  5, 6, 2, 126, 2, 2,   // 137 - 'Tau'
  8, 99, 19, 8, 100, 99, 0, 96, 96,   // 138 - 'Percent 00'
  5, 42, 42, 42, 42, 42,  // 139 - '3 Bar Equals'
  3, 81, 74, 68,  // 140 - '>='
  3, 68, 74, 81,  // 141 - '<='
  5, 0, 0, 255, 1, 3,   // 142 - 'Top of Integral'
  3, 224, 128, 255,   // 143 - 'Bot of Integral'
  5, 54, 18, 54, 36, 54,  // 144 - 'Wavy ='
  3, 2, 5, 2,   // 145 - 'Degree'
  2, 24, 24,  // 146 - 'Math Product'
  2, 16, 16,  // 147 - 'Short Dash'
  5, 48, 64, 255, 1, 1,   // 148 - 'Square Root'
  4, 31, 1, 1, 30,  // 149 - 'Superscript n'
  0,  // 150
  0,  // 151  
  0,  // 152  
  0,  // 153
  9, 1, 1, 127, 1, 127, 2, 12, 2, 127,  // 154 - 'Trademark'
  0,  // 155
  0,  // 156
  0,  // 157
  0,  // 158
  0,  // 159
  0,  // 160
  1, 0,   // 161 - ' Non-breaking space'
  1, 125,   // 162 - '¡ Inverted Exclamation Mark'
  4, 24, 36, 126, 36,   // 163 - '¢ Cent sign'
  4, 68, 126, 69, 65,   // 164 - '£ Pound sign'
  5, 34, 28, 20, 28, 34,  // 165 - '¤ Currency sign'
  5, 1, 42, 124, 42, 1,   // 166 - '¥ Yen sign'
  1, 119,   // 167 - '¦ Broken bar'
  4, 78, 85, 85, 57,  // 168 - '§ Section sign'
  3, 2, 0, 2,   // 169 - '¨ Diaeresis (Umlaut)'
  7, 126, 129, 189, 165, 165, 129, 126,   // 170 - '© Copyright sign'
  3, 38, 41, 47,  // 171 - 'ª Feminine Ordinal Indicator'
  5, 8, 20, 42, 20, 34,   // 172 - '« Left-pointing double angle quotation mark'
  4, 8, 8, 8, 24,   // 173 - '¬ Not sign'
  3, 8, 8, 8,   // 174 - ' Soft hyphen'
  7, 126, 129, 189, 149, 169, 129, 126,   // 175 - '® Registered sign'
  5, 1, 1, 1, 1, 1,   // 176 - '¯ macron'
  3, 2, 5, 2,   // 177 - '° Degree symbol'
  3, 36, 46, 36,  // 178 - '± Plus-minus sign'
  3, 25, 21, 18,  // 179 - '² Superscript two'
  3, 21, 21, 10,  // 180 - '³ Superscript three'
  2, 2, 1,  // 181 - '´ Acute accent'
  4, 248, 32, 64, 120,  // 182 - 'µ Micro sign'
  5, 6, 9, 127, 1, 127,   // 183 - 'Pilcrow sign'
  2, 24, 24,  // 184 - '· Middle dot'
  4, 0, 128, 160, 192,  // 185 - '¸ Cedilla'
  3, 18, 31, 16,  // 186 - '¹ Superscript one'
  3, 38, 41, 38,  // 187 - 'º Masculine ordinal indicator'
  5, 34, 20, 42, 20, 8,   // 188 - '» Right-pointing double angle quotation mark'
  8, 64, 47, 16, 8, 4, 30, 17, 124,   // 189 - '¼ Vulgar fraction one quarter'
  8, 64, 47, 16, 8, 4, 98, 85, 76,  // 190 - '½ Vulgar fraction one half'
  9, 21, 85, 63, 16, 8, 4, 30, 17, 124,   // 191 - '¾ Vulgar fraction three quarters'
  5, 48, 72, 72, 77, 64,  // 192 - '¿ Inverted Question Mark'
  5, 120, 21, 22, 20, 120,  // 193 - 'À Latin Capital Letter A with grave'
  5, 120, 20, 22, 21, 120,  // 194 - 'Á Latin Capital letter A with acute'
  5, 122, 21, 20, 21, 122,  // 195 - 'Â Latin Capital letter A with circumflex'
  5, 120, 22, 21, 22, 121,  // 196 - 'Ã Latin Capital letter A with tilde'
  5, 120, 21, 20, 21, 120,  // 197 - 'Ä Latin Capital letter A with diaeresis'
  5, 120, 20, 21, 20, 120,  // 198 - 'Å Latin Capital letter A with ring above'
  7, 126, 9, 9, 127, 73, 73, 65,  // 199 - 'Æ Latin Capital letter Æ'
  5, 158, 161, 97, 33, 33,  // 200 - 'Ç Latin Capital letter C with cedilla'
  5, 124, 84, 85, 70, 68,   // 201 - 'È Latin Capital letter E with grave'
  5, 124, 84, 86, 69, 68,   // 202 - 'É Latin Capital letter E with acute'
  5, 126, 85, 84, 69, 70,   // 203 - 'Ê Latin Capital letter E with circumflex'
  5, 124, 85, 84, 69, 68,   // 204 - 'Ë Latin Capital letter E with diaeresis'
  3, 69, 126, 68,   // 205 - 'Ì Latin Capital letter I with grave'
  3, 68, 126, 69,   // 206 - 'Í Latin Capital letter I with acute'
  3, 70, 125, 70,   // 207 - 'Î Latin Capital letter I with circumflex'
  3, 69, 124, 69,   // 208 - 'Ï Latin Capital letter I with diaeresis'
  5, 8, 127, 73, 65, 62,  // 209 - 'Ð Latin Capital letter Eth'
  5, 124, 10, 17, 34, 125,  // 210 - 'Ñ Latin Capital letter N with tilde'
  5, 56, 68, 69, 70, 56,  // 211 - 'Ò Latin Capital letter O with grave'
  5, 56, 68, 70, 69, 56,  // 212 - 'Ó Latin Capital letter O with acute'
  5, 58, 69, 68, 69, 58,  // 213 - 'Ô Latin Capital letter O with circumflex'
  5, 56, 70, 69, 70, 57,  // 214 - 'Õ Latin Capital letter O with tilde'
  5, 56, 69, 68, 69, 56,  // 215 - 'Ö Latin Capital letter O with diaeresis'
  5, 34, 20, 8, 20, 34,   // 216 - '× Multiplication sign'
  5, 124, 98, 90, 70, 62,   // 217 - 'Ø Latin Capital letter O with stroke'
  5, 60, 64, 65, 66, 60,  // 218 - 'Ù Latin Capital letter U with grave'
  5, 60, 64, 66, 65, 60,  // 219 - 'Ú Latin Capital letter U with acute'
  5, 60, 66, 65, 66, 60,  // 220 - 'Û Latin Capital Letter U with circumflex'
  5, 60, 65, 64, 65, 60,  // 221 - 'Ü Latin Capital Letter U with diaeresis'
  5, 2, 4, 122, 5, 2,   // 222 - 'Ý Latin Capital Letter Y with acute'
  4, 63, 18, 18, 12,  // 223 - 'Þ Latin Capital Letter Thorn'
  5, 126, 73, 73, 78, 48,   // 224 - 'ß Latin Small Letter sharp S'
  4, 56, 69, 70, 124,   // 225 - 'à Latin Small Letter A with grave'
  4, 56, 68, 70, 125,   // 226 - 'á Latin Small Letter A with acute'
  4, 56, 70, 69, 126,   // 227 - 'â Latin Small Letter A with circumflex'
  4, 58, 69, 70, 125,   // 228 - 'ã Latin Small Letter A with tilde'
  4, 56, 69, 68, 125,   // 229 - 'ä Latin Small Letter A with diaeresis'
  4, 48, 74, 77, 122,   // 230 - 'å Latin Small Letter A with ring above'
  7, 32, 84, 84, 56, 84, 84, 88,  // 231 - 'æ Latin Small Letter Æ'
  4, 156, 162, 98, 34,  // 232 - 'ç Latin Small Letter C with cedilla'
  4, 56, 85, 86, 88,  // 233 - 'è Latin Small Letter E with grave'
  4, 56, 84, 86, 89,  // 234 - 'é Latin Small Letter E with acute'
  4, 56, 86, 85, 90,  // 235 - 'ê Latin Small Letter E with circumflex'
  4, 56, 85, 84, 89,  // 236 - 'ë Latin Small Letter E with diaeresis'
  2, 1, 122,  // 237 - 'ì Latin Small Letter I with grave'
  2, 122, 1,  // 238 - 'í Latin Small Letter I with acute'
  3, 2, 121, 2,   // 239 - 'î Latin Small Letter I with circumflex'
  3, 2, 120, 2,   // 240 - 'ï Latin Small Letter I with diaeresis'
  4, 48, 75, 75, 60,  // 241 - 'ð Latin Small Letter Eth'
  4, 122, 9, 10, 113,   // 242 - 'ñ Latin Small Letter N with tilde'
  4, 48, 73, 74, 48,  // 243 - 'ò Latin Small Letter O with grave'
  4, 48, 72, 74, 49,  // 244 - 'ó Latin Small Letter O with acute'
  4, 48, 74, 73, 50,  // 245 - 'ô Latin Small Letter O with circumflex'
  4, 50, 73, 74, 49,  // 246 - 'õ Latin Small Letter O with tilde'
  4, 57, 68, 68, 57,  // 247 - 'ö Latin Small Letter O with diaeresis'
  5, 8, 8, 42, 8, 8,  // 248 - '÷ Division sign'
  4, 56, 84, 76, 56,  // 249 - 'ø Latin Small Letter O with stroke'
  4, 56, 65, 66, 120,   // 250 - 'ù Latin Small Letter U with grave'
  4, 56, 64, 66, 121,   // 251 - 'ú Latin Small Letter U with acute'
  4, 56, 66, 65, 122,   // 252 - 'û Latin Small Letter U with circumflex'
  4, 58, 64, 64, 122,   // 253 - 'ü Latin Small Letter U with diaeresis'
  4, 24, 160, 162, 121,   // 254 - 'ý Latin Small Letter Y with acute'
  4, 252, 40, 40, 16  // 255 - 'þ Latin Small Letter Thorn'
};
int currentGameMode = 0; // 0 = simpleGame, 1 = simonSaysGame
bool gamePaused = false;

#define MODE_BUTTON_PIN 1
#define RESET_BUTTON_PIN 2
#define START_PAUSE_BUTTON_PIN 42
byte colPins[COLS] = {17, 16, 15, 7};
byte rowPins[ROWS] = {46, 3, 8, 18};
// byte colPins[COLS] = {12, 14, 27, 26}; 
// byte rowPins[ROWS] = {25, 33, 32, 35}; 


Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Function to get the index of the key in the keys array
int getKeyIndex(char key){
  for(int r = 0; r < ROWS; r++){
    for(int c = 0; c < COLS; c++){
      if(keys[r][c] == key) {
        return r * COLS + c; // Calculate the index
      }
    }
  }
  return -1; // Return -1 if the key is not found
}

void setLED(int index, int r, int g, int b) {
    if (index >= 0 && index < NUM_LEDS) {
        // Define the new mapping for the snake pattern
        int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 , 10, 11, 15, 14, 13, 12};
        int mappedIndex = snakeIndices[index];
        pixel.setPixelColor(mappedIndex, pixel.Color(r, g, b));
        pixel.show();
    }
}

void simonSaysGame(char input) {
  static char sequence[5]; // Array to hold the sequence
  static int currentLevel = 1; // Current level (starts at 1)
  static int inputIndex = 0; // Track the current input position
  static bool showSequence = true; // Flag to control sequence display
  static bool gameStarted = false;

  if (!gameStarted) {
    // Initialize the game
    Serial.println("Simon Says: Watch the sequence and repeat it.");

    // Generate a unique random sequence
    for (int i = 0; i < 5; i++) {
      char newChar;
      bool isUnique;
      do {
        newChar = 'A' + random(16); // Generate a random character
        isUnique = true;

        // Check if the character is already in the sequence
        for (int j = 0; j < i; j++) {
          if (sequence[j] == newChar) {
            isUnique = false;
            break;
          }
        }
      } while (!isUnique);

      sequence[i] = newChar;
      Serial.printf("Generated character %c for position %d\n", newChar, i);
    }
    gameStarted = true;
    inputIndex = 0;
  }

  if (showSequence) {
    // Show the current level sequence to the player
    for (int i = 0; i < currentLevel; i++) {
      int index = getKeyIndex(sequence[i]);
      if (index != -1) {
        setLED(index, 0, 0, 255); // Light up the LED in blue for the sequence
        delay(500); // Pause for half a second
        setLED(index, 0, 0, 0); // Turn off the LED
        delay(250); // Short pause between sequence items
      }
    }
    showSequence = false; // Move to player input phase
    Serial.println("Your turn! Repeat the sequence.");
  } else {
    // Player is inputting the sequence
    if (input == sequence[inputIndex]) {
      // Correct input
      Serial.printf("Correct! Pressed: %c\n", input);
      setLED(getKeyIndex(input), 0, 255, 0); // Green LED for correct input
      delay(200);
      setLED(getKeyIndex(input), 0, 0, 0);
      inputIndex++;
      if (inputIndex == currentLevel) {
        // Completed the current level
        currentLevel++;
        inputIndex = 0;
        showSequence = true; // Show the sequence for the next level
        if (currentLevel > 5) {
          Serial.println("Congratulations! You completed the Simon Says game!");
          for (int i = 0; i < NUM_LEDS; i++) {
            setLED(i, 255, 255, 0); // Celebrate with yellow LED flash
            delay(100);
          }
          // Reset the game
          currentLevel = 1;
          gameStarted = false;
        } else {
          Serial.println("Good job! Get ready for the next level.");
          delay(1000);
        }
      }
    } else {
      // Incorrect input
      Serial.printf("Incorrect! Expected: %c but got: %c\n", sequence[inputIndex], input);
      for (int i = 0; i < NUM_LEDS; i++) {
        setLED(i, 255, 0, 0); // Flash red LEDs for error
      }
      delay(1000);
      // Reset the game
      currentLevel = 1;
      gameStarted = false;
      for (int i = 0; i < NUM_LEDS; i++) setLED(i, 0, 0, 0);
    }
  }
}


void simpleGame(char input) {
  static bool firstRound = true;
  static char targetChar;

  if (firstRound) {
    targetChar = 'A' + random(16);  // Generate a random target
    sprintf(t, "Masukkan huruf: %c", targetChar);
    Serial.println(t);
    setLED(getKeyIndex(targetChar), 255, 255, 255); // Highlight the target key in white
    firstRound = false;
  }

  if (input == targetChar) {
    // Correct guess
    for (int i = 0; i < NUM_LEDS; i++) {
      setLED(i, random(255), random(255), random(255)); // Random color flash
      delay(100);
    }
    score++; // Increment the score
    Serial.printf("BENAR! Score: %d\n", score);

    // Generate a new target
    targetChar = 'A' + random(16);
    sprintf(t, "Masukkan huruf: %c", targetChar);
    Serial.println(t);
    setLED(getKeyIndex(targetChar), 255, 255, 255); // Highlight the new target key in white
  } else {
    // Incorrect guess
    int inputIndex = getKeyIndex(input);
    if (inputIndex != -1) {
      setLED(inputIndex, 255, 0, 0); // Flash red on the incorrect key
      delay(100);
      setLED(inputIndex, 0, 0, 0); // Turn off the key after flash
    }
    Serial.printf("Salah! Target was: %c\n", targetChar);
  }

  // Clear all LEDs after feedback
  for (int i = 0; i < NUM_LEDS; i++) setLED(i, 0, 0, 0);

  // Highlight the target key again
  setLED(getKeyIndex(targetChar), 255, 255, 255);
}


// void keypadRoutine(){
//   if (kpd.getKeys()) {
//     bool allPressed = true;

//     // Check if all keys are pressed
//     for(int i = 0; i < 16; i++) {
//       if(kpd.key[i].kstate != PRESSED) {
//         allPressed = false;
//         break;
//       }
//     }

//     // Determine if we should use PRESSED or RELEASED state based on allPressed
//     bool usePressed = !allPressed;

//     // Handle key state changes
//     for(int i = 0; i < 16; i++) {
//       if (kpd.key[i].stateChanged) {
//         if ((usePressed && kpd.key[i].kstate == PRESSED) || (!usePressed && kpd.key[i].kstate == RELEASED)) {
//           position = getKeyIndex(kpd.key[i].kchar); // Get the index of the key
          
//           if(position != -1) {
//             state[position] = !state[position]; // Toggle the state

//             if(state[position]) {
//               setLED(position, 255, 255, 0); // Turn on the LED
//               Serial.printf("Button %c at index %d is ON\n", kpd.key[i].kchar, position);
//               // simpleGame(kpd.key[i].kchar); // Call the game logic
//               simonSaysGame(kpd.key[i].kchar);
//             } else {
//               setLED(position, 0, 0, 0); // Turn off the LED
//               Serial.printf("Button %c at index %d is OFF\n", kpd.key[i].kchar, position);
//             }
//           }
//         }
//       }
//     }
//   }
// }


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  randomSeed(analogRead(11));
  randomAlphabet = 'A' + random(16); // Set initial random alphabet
  pinMode(MODE_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);
  pinMode(START_PAUSE_BUTTON_PIN, INPUT_PULLUP);
  P.begin();
  P.setInvert(false);
  P.setFont(myFont);
  P.setCharSpacing(1);
  P.setIntensity(0);
  P.print("TES");
  
}




void resetGame() {
  // Reset game-specific variables
  if (currentGameMode == 0) {
    // Reset simpleGame
    // You can reset the score, targetChar, or other variables as needed
  } else if (currentGameMode == 1) {
    // Reset simonSaysGame
    // Reset sequence, current level, or other variables as needed
  }
  // Clear all LEDs
  for (int i = 0; i < NUM_LEDS; i++) setLED(i, 0, 0, 0);
}

// Updated keypadRoutine to use currentGameMode
void keypadRoutine() {
  if (kpd.getKeys()) {
    bool allPressed = true;

    // Check if all keys are pressed
    for (int i = 0; i < 16; i++) {
      if (kpd.key[i].kstate != PRESSED) {
        allPressed = false;
        break;
      }
    }

    // Determine if we should use PRESSED or RELEASED state based on allPressed
    bool usePressed = !allPressed;

    // Handle key state changes
    for (int i = 0; i < 16; i++) {
      if (kpd.key[i].stateChanged) {
        if ((usePressed && kpd.key[i].kstate == PRESSED) || (!usePressed && kpd.key[i].kstate == RELEASED)) {
          position = getKeyIndex(kpd.key[i].kchar); // Get the index of the key

          if (position != -1) {
            state[position] = !state[position]; // Toggle the state

            if (state[position]) {
              setLED(position, 255, 255, 0); // Turn on the LED
              Serial.printf("Button %c at index %d is ON\n", kpd.key[i].kchar, position);

              // Call the appropriate game logic based on the current mode
              if (currentGameMode == 0) {
                simpleGame(kpd.key[i].kchar); // Call the simple game logic
              } else if (currentGameMode == 1) {
                simonSaysGame(kpd.key[i].kchar); // Call the Simon Says game logic
              }
            } else {
              setLED(position, 0, 0, 0); // Turn off the LED
              Serial.printf("Button %c at index %d is OFF\n", kpd.key[i].kchar, position);
            }
          }
        }
      }
    }
  }
}
void checkControlButtons() {
  if (digitalRead(MODE_BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(MODE_BUTTON_PIN) == LOW) {
      // Switch game mode
      currentGameMode = (currentGameMode + 1) % 2;
      Serial.printf("Switched to game mode: %d\n", currentGameMode);
      delay(500); // Avoid rapid toggling
    }
  }

  if (digitalRead(RESET_BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(RESET_BUTTON_PIN) == LOW) {
      // Reset the current game
      Serial.println("Game reset.");
      resetGame();
      delay(500); // Avoid rapid toggling
    }
  }

  if (digitalRead(START_PAUSE_BUTTON_PIN) == LOW) {
    delay(50); // Debounce delay
    if (digitalRead(START_PAUSE_BUTTON_PIN) == LOW) {
      // Start or pause the game
      gamePaused = !gamePaused;
      if (gamePaused) {
        Serial.println("Game paused.");
      } else {
        Serial.println("Game resumed.");
      }
      delay(500); // Avoid rapid toggling
    }
  }
}
void loop() {
  checkControlButtons();
  if(!gamePaused) keypadRoutine();
}
