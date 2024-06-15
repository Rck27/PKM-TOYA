#include <Keypad.h>
#include <Adafruit_NeoPixel.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
// #include "myFont.h"
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   33  // or SCK
#define DATA_PIN  35  // or MOSI
#define CS_PIN    32  // or SS

// SPI hardware interface
MD_Parola mx = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);



const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const byte NUM_LEDS = 16;
const byte LED_PIN = 15;
int position, winCount;
unsigned long lastMillis, currentMillis;
char randomAlphabet;
int mode = 0;
char t[100];

Adafruit_NeoPixel pixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

char keys[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},
  {'E', 'F', 'G', 'H'},
  {'I', 'J', 'K', 'L'},
  {'M', 'N', 'O', 'P'},
};


MD_MAX72XX::fontType_t myFont[] PROGMEM = 
{
	'F', 2, 0, 0, 0, 255, 8,
	0, 	// 1 - 'Empty Cell'
	5, 62, 91, 79, 91, 62, 	// 2 - 'Sad Smiley'
	5, 62, 107, 79, 107, 62, 	// 3 - 'Happy Smiley'
	5, 28, 62, 124, 62, 28, 	// 4 - 'Heart'
	5, 24, 60, 126, 60, 24, 	// 5 - 'Diamond'
	5, 28, 87, 125, 87, 28, 	// 6 - 'Clubs'
	5, 28, 94, 127, 94, 28, 	// 7 - 'Spades'
	4, 0, 24, 60, 24, 	// 8 - 'Bullet Point'
	5, 255, 231, 195, 231, 255, 	// 9 - 'Rev Bullet Point'
	4, 0, 24, 36, 24, 	// 10 - 'Hollow Bullet Point'
	5, 255, 231, 219, 231, 255, 	// 11 - 'Rev Hollow BP'
	5, 48, 72, 58, 6, 14, 	// 12 - 'Male'
	5, 38, 41, 121, 41, 38, 	// 13 - 'Female'
	5, 64, 127, 5, 5, 7, 	// 14 - 'Music Note 1'
	5, 64, 127, 5, 37, 63, 	// 15 - 'Music Note 2'
	5, 90, 60, 231, 60, 90, 	// 16 - 'Snowflake'
	5, 127, 62, 28, 28, 8, 	// 17 - 'Right Pointer'
	5, 8, 28, 28, 62, 127, 	// 18 - 'Left Pointer'
	5, 20, 34, 127, 34, 20, 	// 19 - 'UpDown Arrows'
	5, 255, 255, 255, 255, 255, 	// 20 - 'Full Block'
	5, 240, 240, 240, 240, 240, 	// 21 - 'Half Block Bottom'
	3, 255, 255, 255, 	// 22 - 'Half Block LHS'
	5, 0, 0, 0, 255, 255, 	// 23 - 'Half Block RHS'
	5, 15, 15, 15, 15, 15, 	// 24 - 'Half Block Top'
	5, 8, 4, 126, 4, 8, 	// 25 - 'Up Arrow'
	5, 16, 32, 126, 32, 16, 	// 26 - 'Down Arrow'
	5, 8, 8, 42, 28, 8, 	// 27 - 'Right Arrow'
	5, 8, 28, 42, 8, 8, 	// 28 - 'Left Arrow'
	5, 170, 0, 85, 0, 170, 	// 29 - '30% shading'
	5, 170, 85, 170, 85, 170, 	// 30 - '50% shading'
	5, 48, 56, 62, 56, 48, 	// 31 - 'Up Pointer'
	5, 6, 14, 62, 14, 6, 	// 32 - 'Down Pointer'
	2, 0, 0, 	// 33  - 'Space'
	1, 95, 	// 34 - '!'
	3, 7, 0, 7, 	// 35 - '""'
	5, 20, 127, 20, 127, 20, 	// 36 - '#'
	5, 68, 74, 255, 74, 50, 	// 37 - '$'
	5, 99, 19, 8, 100, 99, 	// 38 - '%'
	5, 54, 73, 73, 54, 72, 	// 39 - '&'
	1, 7, 	// 40 - '''
	3, 62, 65, 65, 	// 41 - '('
	3, 65, 65, 62, 	// 42 - ')'
	5, 8, 42, 28, 42, 8, 	// 43 - '*'
	5, 8, 8, 62, 8, 8, 	// 44 - '+'
	3, 96, 224, 0, 	// 45'
	4, 8, 8, 8, 8, 	// 46 - '-'
	2, 96, 96, 	// 47 - '.'
	5, 96, 16, 8, 4, 3, 	// 48 - '/'
	5, 62, 127, 73, 69, 62, 	// 49 - '0'
	4, 4, 2, 127, 127, 	// 50 - '1'
	5, 113, 121, 73, 79, 70, 	// 51 - '2'
	5, 65, 73, 73, 127, 54, 	// 52 - '3'
	5, 15, 15, 8, 120, 127, 	// 53 - '4'
	5, 79, 79, 73, 121, 49, 	// 54 - '5'
	5, 62, 127, 73, 73, 48, 	// 55 - '6'
	5, 3, 3, 113, 121, 7, 	// 56 - '7'
	5, 54, 127, 73, 73, 54, 	// 57 - '8'
	5, 6, 73, 73, 127, 62, 	// 58 - '9'
	2, 108, 108, 	// 59 - ':'
	2, 108, 236, 	// 60 - ';'
	3, 8, 20, 34, 	// 61 - '<'
	4, 20, 20, 20, 20, 	// 62 - '='
	3, 34, 20, 8, 	// 63 - '>'
	5, 1, 89, 9, 9, 6, 	// 64 - '?'
	5, 62, 65, 93, 89, 78, 	// 65 - '@'
	5, 126, 127, 9, 9, 126, 	// 66 - 'A'
	5, 127, 127, 73, 73, 54, 	// 67 - 'B'
	5, 62, 127, 65, 65, 65, 	// 68 - 'C'
	5, 127, 127, 65, 65, 62, 	// 69 - 'D'
	5, 127, 127, 73, 73, 65, 	// 70 - 'E'
	5, 127, 127, 9, 9, 1, 	// 71 - 'F'
	5, 62, 127, 65, 73, 121, 	// 72 - 'G'
	5, 127, 127, 8, 8, 127, 	// 73 - 'H'
	4, 65, 127, 127, 65, 	// 74 - 'I'
	5, 48, 65, 65, 127, 63, 	// 75 - 'J'
	5, 127, 127, 20, 34, 65, 	// 76 - 'K'
	5, 127, 127, 64, 64, 64, 	// 77 - 'L'
	6, 127, 126, 4, 28, 6, 127, 	// 78 - 'M'
	5, 127, 127, 4, 8, 127, 	// 79 - 'N'
	5, 62, 127, 65, 65, 62, 	// 80 - 'O'
	5, 127, 127, 9, 9, 6, 	// 81 - 'P'
	5, 62, 127, 65, 97, 126, 	// 82 - 'Q'
	5, 127, 127, 25, 41, 70, 	// 83 - 'R'
	5, 70, 79, 73, 121, 49, 	// 84 - 'S'
	6, 1, 1, 127, 127, 1, 1, 	// 85 - 'T'
	5, 63, 127, 64, 64, 63, 	// 86 - 'U'
	5, 31, 63, 64, 32, 31, 	// 87 - 'V'
	6, 63, 127, 64, 48, 64, 63, 	// 88 - 'W'
	5, 99, 119, 8, 20, 99, 	// 89 - 'X'
	6, 3, 7, 124, 120, 4, 3, 	// 90 - 'Y'
	5, 97, 113, 89, 77, 71, 	// 91 - 'Z'
	3, 127, 65, 65, 	// 92 - '['
	5, 3, 4, 8, 16, 96, 	// 93 - '\'
	3, 65, 65, 127, 	// 94 - ']'
	5, 4, 2, 1, 2, 4, 	// 95 - '^'
	4, 128, 128, 128, 128, 	// 96 - '_'
	3, 1, 2, 4, 	// 97 - '`'
	4, 56, 68, 68, 124, 	// 98 - 'a'
	4, 127, 68, 68, 56, 	// 99 - 'b'
	4, 56, 68, 68, 68, 	// 100 - 'c'
	4, 56, 68, 68, 127, 	// 101 - 'd'
	4, 56, 84, 84, 88, 	// 102 - 'e'
	4, 4, 126, 5, 1, 	// 103 - 'f'
	4, 24, 164, 164, 124, 	// 104 - 'g'
	4, 127, 4, 4, 120, 	// 105 - 'h'
	1, 125, 	// 106 - 'i'
	3, 132, 133, 124, 	// 107 - 'j'
	4, 127, 16, 40, 68, 	// 108 - 'k'
	1, 127, 	// 109 - 'l'
	5, 124, 4, 120, 4, 120, 	// 110 - 'm'
	4, 124, 4, 4, 120, 	// 111 - 'n'
	4, 56, 68, 68, 56, 	// 112 - 'o'
	4, 252, 36, 36, 24, 	// 113 - 'p'
	4, 24, 36, 36, 252, 	// 114 - 'q'
	4, 124, 4, 4, 8, 	// 115 - 'r'
	4, 88, 84, 84, 52, 	// 116 - 's'
	3, 4, 127, 4, 	// 117 - 't'
	4, 60, 64, 64, 124, 	// 118 - 'u'
	4, 28, 32, 64, 124, 	// 119 - 'v'
	5, 60, 64, 48, 64, 60, 	// 120 - 'w'
	4, 108, 16, 16, 108, 	// 121 - 'x'
	4, 28, 160, 160, 124, 	// 122 - 'y'
	4, 100, 84, 84, 76, 	// 123 - 'z'
	4, 8, 54, 65, 65, 	// 124 - '{'
	1, 127, 	// 125 - '|'
	4, 65, 65, 54, 8, 	// 126 - '}'
	4, 2, 1, 2, 1, 	// 127 - '~'
	5, 127, 65, 65, 65, 127, 	// 128 - 'Hollow Block'
	5, 62, 85, 85, 85, 65, 	// 129 - 'Euro symbol'
	5, 56, 68, 68, 56, 68, 	// 130 - 'Alpha'
	5, 124, 42, 42, 62, 20, 	// 131 - 'Beta'
	5, 126, 2, 2, 6, 6, 	// 132 - 'Gamma'
	5, 2, 126, 2, 126, 2, 	// 133 - 'Pi'
	5, 99, 85, 73, 65, 99, 	// 134 - 'Sigma'
	5, 56, 68, 68, 60, 4, 	// 135 - 'Theta'
	5, 64, 126, 32, 30, 32, 	// 136 - 'mu'
	5, 6, 2, 126, 2, 2, 	// 137 - 'Tau'
	8, 99, 19, 8, 100, 99, 0, 96, 96, 	// 138 - 'Percent 00'
	5, 42, 42, 42, 42, 42, 	// 139 - '3 Bar Equals'
	3, 81, 74, 68, 	// 140 - '>='
	3, 68, 74, 81, 	// 141 - '<='
	5, 0, 0, 255, 1, 3, 	// 142 - 'Top of Integral'
	3, 224, 128, 255, 	// 143 - 'Bot of Integral'
	5, 54, 18, 54, 36, 54, 	// 144 - 'Wavy ='
	3, 2, 5, 2, 	// 145 - 'Degree'
	2, 24, 24, 	// 146 - 'Math Product'
	2, 16, 16, 	// 147 - 'Short Dash'
	5, 48, 64, 255, 1, 1, 	// 148 - 'Square Root'
	4, 31, 1, 1, 30, 	// 149 - 'Superscript n'
	0, 	// 150
	0, 	// 151  
	0, 	// 152  
	0, 	// 153
	9, 1, 1, 127, 1, 127, 2, 12, 2, 127, 	// 154 - 'Trademark'
	0, 	// 155
	0, 	// 156
	0, 	// 157
	0, 	// 158
	0, 	// 159
	0, 	// 160
	1, 0, 	// 161 - ' Non-breaking space'
	1, 125, 	// 162 - '¡ Inverted Exclamation Mark'
	4, 24, 36, 126, 36, 	// 163 - '¢ Cent sign'
	4, 68, 126, 69, 65, 	// 164 - '£ Pound sign'
	5, 34, 28, 20, 28, 34, 	// 165 - '¤ Currency sign'
	5, 1, 42, 124, 42, 1, 	// 166 - '¥ Yen sign'
	1, 119, 	// 167 - '¦ Broken bar'
	4, 78, 85, 85, 57, 	// 168 - '§ Section sign'
	3, 2, 0, 2, 	// 169 - '¨ Diaeresis (Umlaut)'
	7, 126, 129, 189, 165, 165, 129, 126, 	// 170 - '© Copyright sign'
	3, 38, 41, 47, 	// 171 - 'ª Feminine Ordinal Indicator'
	5, 8, 20, 42, 20, 34, 	// 172 - '« Left-pointing double angle quotation mark'
	4, 8, 8, 8, 24, 	// 173 - '¬ Not sign'
	3, 8, 8, 8, 	// 174 - ' Soft hyphen'
	7, 126, 129, 189, 149, 169, 129, 126, 	// 175 - '® Registered sign'
	5, 1, 1, 1, 1, 1, 	// 176 - '¯ macron'
	3, 2, 5, 2, 	// 177 - '° Degree symbol'
	3, 36, 46, 36, 	// 178 - '± Plus-minus sign'
	3, 25, 21, 18, 	// 179 - '² Superscript two'
	3, 21, 21, 10, 	// 180 - '³ Superscript three'
	2, 2, 1, 	// 181 - '´ Acute accent'
	4, 248, 32, 64, 120, 	// 182 - 'µ Micro sign'
	5, 6, 9, 127, 1, 127, 	// 183 - 'Pilcrow sign'
	2, 24, 24, 	// 184 - '· Middle dot'
	4, 0, 128, 160, 192, 	// 185 - '¸ Cedilla'
	3, 18, 31, 16, 	// 186 - '¹ Superscript one'
	3, 38, 41, 38, 	// 187 - 'º Masculine ordinal indicator'
	5, 34, 20, 42, 20, 8, 	// 188 - '» Right-pointing double angle quotation mark'
	8, 64, 47, 16, 8, 4, 30, 17, 124, 	// 189 - '¼ Vulgar fraction one quarter'
	8, 64, 47, 16, 8, 4, 98, 85, 76, 	// 190 - '½ Vulgar fraction one half'
	9, 21, 85, 63, 16, 8, 4, 30, 17, 124, 	// 191 - '¾ Vulgar fraction three quarters'
	5, 48, 72, 72, 77, 64, 	// 192 - '¿ Inverted Question Mark'
	5, 120, 21, 22, 20, 120, 	// 193 - 'À Latin Capital Letter A with grave'
	5, 120, 20, 22, 21, 120, 	// 194 - 'Á Latin Capital letter A with acute'
	5, 122, 21, 20, 21, 122, 	// 195 - 'Â Latin Capital letter A with circumflex'
	5, 120, 22, 21, 22, 121, 	// 196 - 'Ã Latin Capital letter A with tilde'
	5, 120, 21, 20, 21, 120, 	// 197 - 'Ä Latin Capital letter A with diaeresis'
	5, 120, 20, 21, 20, 120, 	// 198 - 'Å Latin Capital letter A with ring above'
	7, 126, 9, 9, 127, 73, 73, 65, 	// 199 - 'Æ Latin Capital letter Æ'
	5, 158, 161, 97, 33, 33, 	// 200 - 'Ç Latin Capital letter C with cedilla'
	5, 124, 84, 85, 70, 68, 	// 201 - 'È Latin Capital letter E with grave'
	5, 124, 84, 86, 69, 68, 	// 202 - 'É Latin Capital letter E with acute'
	5, 126, 85, 84, 69, 70, 	// 203 - 'Ê Latin Capital letter E with circumflex'
	5, 124, 85, 84, 69, 68, 	// 204 - 'Ë Latin Capital letter E with diaeresis'
	3, 69, 126, 68, 	// 205 - 'Ì Latin Capital letter I with grave'
	3, 68, 126, 69, 	// 206 - 'Í Latin Capital letter I with acute'
	3, 70, 125, 70, 	// 207 - 'Î Latin Capital letter I with circumflex'
	3, 69, 124, 69, 	// 208 - 'Ï Latin Capital letter I with diaeresis'
	5, 8, 127, 73, 65, 62, 	// 209 - 'Ð Latin Capital letter Eth'
	5, 124, 10, 17, 34, 125, 	// 210 - 'Ñ Latin Capital letter N with tilde'
	5, 56, 68, 69, 70, 56, 	// 211 - 'Ò Latin Capital letter O with grave'
	5, 56, 68, 70, 69, 56, 	// 212 - 'Ó Latin Capital letter O with acute'
	5, 58, 69, 68, 69, 58, 	// 213 - 'Ô Latin Capital letter O with circumflex'
	5, 56, 70, 69, 70, 57, 	// 214 - 'Õ Latin Capital letter O with tilde'
	5, 56, 69, 68, 69, 56, 	// 215 - 'Ö Latin Capital letter O with diaeresis'
	5, 34, 20, 8, 20, 34, 	// 216 - '× Multiplication sign'
	5, 124, 98, 90, 70, 62, 	// 217 - 'Ø Latin Capital letter O with stroke'
	5, 60, 64, 65, 66, 60, 	// 218 - 'Ù Latin Capital letter U with grave'
	5, 60, 64, 66, 65, 60, 	// 219 - 'Ú Latin Capital letter U with acute'
	5, 60, 66, 65, 66, 60, 	// 220 - 'Û Latin Capital Letter U with circumflex'
	5, 60, 65, 64, 65, 60, 	// 221 - 'Ü Latin Capital Letter U with diaeresis'
	5, 2, 4, 122, 5, 2, 	// 222 - 'Ý Latin Capital Letter Y with acute'
	4, 63, 18, 18, 12, 	// 223 - 'Þ Latin Capital Letter Thorn'
	5, 126, 73, 73, 78, 48, 	// 224 - 'ß Latin Small Letter sharp S'
	4, 56, 69, 70, 124, 	// 225 - 'à Latin Small Letter A with grave'
	4, 56, 68, 70, 125, 	// 226 - 'á Latin Small Letter A with acute'
	4, 56, 70, 69, 126, 	// 227 - 'â Latin Small Letter A with circumflex'
	4, 58, 69, 70, 125, 	// 228 - 'ã Latin Small Letter A with tilde'
	4, 56, 69, 68, 125, 	// 229 - 'ä Latin Small Letter A with diaeresis'
	4, 48, 74, 77, 122, 	// 230 - 'å Latin Small Letter A with ring above'
	7, 32, 84, 84, 56, 84, 84, 88, 	// 231 - 'æ Latin Small Letter Æ'
	4, 156, 162, 98, 34, 	// 232 - 'ç Latin Small Letter C with cedilla'
	4, 56, 85, 86, 88, 	// 233 - 'è Latin Small Letter E with grave'
	4, 56, 84, 86, 89, 	// 234 - 'é Latin Small Letter E with acute'
	4, 56, 86, 85, 90, 	// 235 - 'ê Latin Small Letter E with circumflex'
	4, 56, 85, 84, 89, 	// 236 - 'ë Latin Small Letter E with diaeresis'
	2, 1, 122, 	// 237 - 'ì Latin Small Letter I with grave'
	2, 122, 1, 	// 238 - 'í Latin Small Letter I with acute'
	3, 2, 121, 2, 	// 239 - 'î Latin Small Letter I with circumflex'
	3, 2, 120, 2, 	// 240 - 'ï Latin Small Letter I with diaeresis'
	4, 48, 75, 75, 60, 	// 241 - 'ð Latin Small Letter Eth'
	4, 122, 9, 10, 113, 	// 242 - 'ñ Latin Small Letter N with tilde'
	4, 48, 73, 74, 48, 	// 243 - 'ò Latin Small Letter O with grave'
	4, 48, 72, 74, 49, 	// 244 - 'ó Latin Small Letter O with acute'
	4, 48, 74, 73, 50, 	// 245 - 'ô Latin Small Letter O with circumflex'
	4, 50, 73, 74, 49, 	// 246 - 'õ Latin Small Letter O with tilde'
	4, 57, 68, 68, 57, 	// 247 - 'ö Latin Small Letter O with diaeresis'
	5, 8, 8, 42, 8, 8, 	// 248 - '÷ Division sign'
	4, 56, 84, 76, 56, 	// 249 - 'ø Latin Small Letter O with stroke'
	4, 56, 65, 66, 120, 	// 250 - 'ù Latin Small Letter U with grave'
	4, 56, 64, 66, 121, 	// 251 - 'ú Latin Small Letter U with acute'
	4, 56, 66, 65, 122, 	// 252 - 'û Latin Small Letter U with circumflex'
	4, 58, 64, 64, 122, 	// 253 - 'ü Latin Small Letter U with diaeresis'
	4, 24, 160, 162, 121, 	// 254 - 'ý Latin Small Letter Y with acute'
	4, 252, 40, 40, 16 	// 255 - 'þ Latin Small Letter Thorn'
};



int state[ROWS*COLS] = {0}; // Initialize all to 0

byte colPins[COLS] = {19, 21, 22, 23}; //connect to the column pinouts of the kpd
byte rowPins[ROWS] = {2, 4, 5,  18}; //connect to the row pinouts of the kpd

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

// Function to turn on/off the LED at the given index
// void setLED(int index, int r, int g, int b){
//   if(index >= 0 && index < NUM_LEDS){
//     pixel.setPixelColor(index, pixel.Color(r, g, b));
//     pixel.show();
//   }
// }



void setLED(int index, int r, int g, int b) {
    if (index >= 0 && index < NUM_LEDS) {
        // Define the new mapping for the snake pattern
        int snakeIndices[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9 , 10, 11, 15, 14, 13, 12};
        int mappedIndex = snakeIndices[index];
        pixel.setPixelColor(mappedIndex, pixel.Color(r, g, b));
        pixel.show();
    }
}


void simpleGame(char input) {
  static bool firstRound = true;
  static bool correctGuess = false;
  if (firstRound || correctGuess) {
    sprintf(t, "Masukkan huruf : %c \n", randomAlphabet);
    Serial.println(t);
    mx.print(t);
    firstRound = false;
  }

  if (input == randomAlphabet) {
    randomAlphabet = 'A' + random(16);
    for (int i = 0; i <= 15; i++){ 
        setLED(i, random(255), random(255), random(255));
        delay(150);
        }
    correctGuess = true;
    mx.print("BENAR");
  } else {
    for (int i = 16; i >= 0; i--) {setLED(i, 255, 0, 0); delay(100);};
    correctGuess = false;
    // mx.
  }
  for (int i = 0; i <= 15; i++) setLED(i, 0, 0, 0);

  // Handle individual LED behavior here based on correctGuess
  // (turn on corresponding LED briefly if correct, otherwise handle wrong guess)
}


void keypadRoutine(){
  if (kpd.getKeys()) {
    for (int i=0; i<16; i++) {
      if (kpd.key[i].stateChanged) {
        switch (kpd.key[i].kstate) {
          case PRESSED:
            position = getKeyIndex(kpd.key[i].kchar); // Get the index of the pressed key
            if(position != -1 && state[position] == 0){
              state[position] = 1; // Set the state to 1
              setLED(position, 255, 255, 0); // Turn the LED on
                switch(mode){
                    case 0:simpleGame(kpd.key[i].kchar); break;
                }
            //   simpleGame(kpd.key[i].kchar);
              Serial.printf("button %c at index %d is pressed, state is now ON\n", kpd.key[i].kchar, position);
            }
            break;
          case RELEASED:
            position = getKeyIndex(kpd.key[i].kchar); // Get the index of the released key
            if(position != -1 && state[position] == 1){
              state[position] = 0; // Set the state to 0
              setLED(position, 0, 0, 0); // Turn the LED off
              Serial.printf("button %c at index %d is released, state is now OFF\n", kpd.key[i].kchar, position);
            }
            break;
        }
      }
    }
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pixel.begin();
  pixel.clear();  pixel.show();
  randomSeed(analogRead(11));
  randomAlphabet = 'A' + random(16); // Set initial random alphabet

	mx.begin();
	mx.setTextAlignment(PA_CENTER);
	mx.setFont(myFont);
	mx.setCharSpacing(1);
}
void loop() {

  keypadRoutine();


}
