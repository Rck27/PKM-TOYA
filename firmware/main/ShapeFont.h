// created with https://pjrp.github.io/MDParolaFontEditor
// modyifing the standard font contained in
// libraries/MD_MAX72XX/src/MD_MAX72xx_font.cpp
#include <MD_MAX72xx.h>

MD_MAX72XX::fontType_t _fontname[] PROGMEM = {
  'F', 1, 0, 255, 8,
  0,		// 0 - 'Empty Cell'
  0,		// 1
  0,		// 2
  0,		// 3
  0,		// 4
  0,		// 5
  0,		// 6
  0,		// 7
  0,		// 8
  0,		// 9
  0,		// 10
  0,		// 11
  0,		// 12
  0,		// 13
  0,		// 14
  0,		// 15
  0,		// 16
  0,		// 17
  0,		// 18
  0,		// 19
  0,		// 20
  0,		// 21
  0,		// 22
  0,		// 23
  0,		// 24
  0,		// 25
  0,		// 26
  0,		// 27
  0,		// 28
  0,		// 29
  0,		// 30
  0,		// 31
  0,		// 32
  0,		// 33
  0,		// 34
  0,		// 35
  0,		// 36
  0,		// 37
  0,		// 38
  0,		// 39
  0,		// 40
  0,		// 41
  5, 8, 42, 28, 42, 8,		// 42 - '*'
  0,		// 43
  0,		// 44
  0,		// 45
  0,		// 46
  0,		// 47
  0,		// 48
  0,		// 49
  0,		// 50
  0,		// 51
  0,		// 52
  0,		// 53
  0,		// 54
  0,		// 55
  0,		// 56
  0,		// 57
  0,		// 58
  0,		// 59
  0,		// 60
  0,		// 61
  0,		// 62
  0,		// 63
  0,		// 64
  7, 0, 126, 126, 126, 126, 126, 126,		// 65 - '0'
  7, 0, 60, 60, 60, 60, 60, 60,		// 66 - '1'
  7, 0, 60, 66, 66, 66, 66, 60,		// 67 - '2'
  8, 112, 76, 66, 66, 66, 66, 76, 112,		// 68 - '3'
  9, 32, 48, 56, 60, 62, 60, 56, 48, 32,		// 69 - '4'
  8, 0, 8, 20, 34, 33, 34, 20, 8,		// 70 - '5'
  8, 56, 62, 63, 63, 31, 15, 7, 3,		// 71 - '6'
  7, 8, 20, 34, 65, 34, 20, 8,		// 72 - '7'
  7, 0, 0, 254, 130, 130, 68, 56,		// 73 - '8'
  8, 30, 17, 17, 241, 129, 129, 129, 126,		// 74 - '9'
  8, 0, 254, 130, 132, 136, 144, 160, 192,		// 75 - 'X'
  8, 24, 36, 66, 129, 129, 66, 36, 24,		// 76 - '-'
  8, 24, 36, 66, 129, 129, 66, 36, 24,		// 77
  9, 8, 212, 180, 134, 115, 134, 180, 84, 8,		// 78 - 'Bintang'
  8, 0, 254, 130, 132, 136, 144, 160, 192,		// 79 - 'X'
  8, 24, 36, 66, 129, 129, 66, 36, 24,		// 80 - 'P'
  5, 62, 65, 65, 97, 126,		// 81 - 'Q'
  5, 127, 9, 25, 41, 70,		// 82 - 'R'
  5, 70, 73, 73, 73, 49,		// 83 - 'S'
  5, 1, 1, 127, 1, 1,		// 84 - 'T'
  5, 63, 64, 64, 64, 63,		// 85 - 'U'
  5, 31, 32, 64, 32, 31,		// 86 - 'V'
  5, 63, 64, 56, 64, 63,		// 87 - 'W'
  5, 99, 20, 8, 20, 99,		// 88 - 'X'
  5, 3, 4, 120, 4, 3,		// 89 - 'Y'
  5, 97, 81, 73, 69, 67,		// 90 - 'Z'
  0,		// 91
  0,		// 92
  0,		// 93
  5, 4, 9, 8, 9, 4,		// 94 - '^'
  0,		// 95
  0,		// 96
  0,		// 97
  0,		// 98
  0,		// 99
  0,		// 100
  0,		// 101
  0,		// 102
  0,		// 103
  0,		// 104
  0,		// 105
  0,		// 106
  0,		// 107
  0,		// 108
  0,		// 109
  0,		// 110
  0,		// 111
  0,		// 112
  0,		// 113
  0,		// 114
  0,		// 115
  0,		// 116
  0,		// 117
  0,		// 118
  0,		// 119
  0,		// 120
  0,		// 121
  0,		// 122
  0,		// 123
  0,		// 124
  0,		// 125
  0,		// 126
  0,		// 127
  0,		// 128
  0,		// 129
  0,		// 130
  0,		// 131
  0,		// 132
  0,		// 133
  0,		// 134
  0,		// 135
  0,		// 136
  0,		// 137
  0,		// 138
  0,		// 139
  0,		// 140
  0,		// 141
  0,		// 142
  0,		// 143
  0,		// 144
  0,		// 145
  0,		// 146
  0,		// 147
  0,		// 148
  0,		// 149
  0,		// 150
  0,		// 151
  0,		// 152
  0,		// 153
  0,		// 154
  0,		// 155
  0,		// 156
  0,		// 157
  0,		// 158
  0,		// 159
  0,		// 160
  0,		// 161
  0,		// 162
  0,		// 163
  0,		// 164
  0,		// 165
  0,		// 166
  0,		// 167
  0,		// 168
  0,		// 169
  0,		// 170
  0,		// 171
  0,		// 172
  0,		// 173
  0,		// 174
  0,		// 175
  0,		// 176
  0,		// 177
  0,		// 178
  0,		// 179
  0,		// 180
  0,		// 181
  0,		// 182
  0,		// 183
  0,		// 184
  0,		// 185
  0,		// 186
  0,		// 187
  0,		// 188
  0,		// 189
  0,		// 190
  0,		// 191
  0,		// 192
  0,		// 193
  0,		// 194
  0,		// 195
  0,		// 196
  0,		// 197
  0,		// 198
  0,		// 199
  0,		// 200
  0,		// 201
  0,		// 202
  0,		// 203
  0,		// 204
  0,		// 205
  0,		// 206
  0,		// 207
  0,		// 208
  0,		// 209
  0,		// 210
  0,		// 211
  0,		// 212
  0,		// 213
  0,		// 214
  0,		// 215
  0,		// 216
  0,		// 217
  0,		// 218
  0,		// 219
  0,		// 220
  0,		// 221
  0,		// 222
  0,		// 223
  0,		// 224
  0,		// 225
  0,		// 226
  0,		// 227
  0,		// 228
  0,		// 229
  0,		// 230
  0,		// 231
  0,		// 232
  0,		// 233
  0,		// 234
  0,		// 235
  0,		// 236
  0,		// 237
  0,		// 238
  0,		// 239
  0,		// 240
  0,		// 241
  0,		// 242
  0,		// 243
  0,		// 244
  0,		// 245
  0,		// 246
  0,		// 247
  0,		// 248
  0,		// 249
  0,		// 250
  0,		// 251
  0,		// 252
  0,		// 253
  0,		// 254
  0,		// 255
};
