// Created by https://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t DialogInput_plain_12Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xAA,0xA2,0x80, // '!'
	0xAA,0xA0, // '"'
	0x14,0x24,0x7E,0x28,0x28,0xFC,0x48,0x50, // '#'
	0x21,0xCA,0xA8,0xE0,0xE2,0xAA,0x70,0x82,0x00, // '$'
	0x60,0x90,0x90,0x64,0x18,0x6C,0x12,0x12,0x0C, // '%'
	0x38,0x81,0x03,0x06,0x12,0xA7,0x64,0x74, // '&'
	0xA8, // '''
	0x64,0x48,0x88,0x88,0x44,0x60, // '('
	0xC4,0x42,0x22,0x22,0x44,0xC0, // ')'
	0x22,0xA7,0x1C,0xA8,0x80, // '*'
	0x10,0x10,0x10,0xFE,0x10,0x10,0x10, // '+'
	0x4A,0x00, // ','
	0xE0, // '-'
	0xA0, // '.'
	0x04,0x10,0x20,0x81,0x04,0x08,0x20,0x41,0x00, // '/'
	0x78,0x92,0x14,0x29,0x50,0xA1,0x24,0x78, // '0'
	0xE0,0x82,0x08,0x20,0x82,0x08,0xF8, // '1'
	0x79,0x08,0x10,0x20,0x82,0x08,0x20,0xFC, // '2'
	0x79,0x08,0x10,0x23,0x80,0x81,0x42,0x78, // '3'
	0x18,0x30,0xA3,0x44,0x91,0x3F,0x04,0x08, // '4'
	0xF9,0x02,0x07,0xC0,0xC0,0x81,0x46,0x78, // '5'
	0x38,0x8A,0x05,0xCC,0xD0,0xA1,0x26,0x78, // '6'
	0xFC,0x18,0x20,0x41,0x02,0x08,0x10,0x40, // '7'
	0x79,0x0A,0x14,0x27,0x90,0xA1,0x42,0x78, // '8'
	0x79,0x92,0x14,0x28,0xCE,0x81,0x44,0x70, // '9'
	0xA0,0xA0, // ':'
	0x48,0x04,0xA0, // ';'
	0x04,0x73,0x06,0x03,0x80,0x80, // '<'
	0xFC,0x03,0xF0, // '='
	0x80,0xE0,0x30,0x67,0x10,0x00, // '>'
	0x72,0x20,0x8C,0x61,0x00,0x10,0x40, // '?'
	0x38,0x9A,0x14,0xEA,0x54,0xA7,0x60,0x40,0x70, // '@'
	0x30,0x60,0xC2,0x44,0x89,0x1E,0x42,0x84, // 'A'
	0xF9,0x0A,0x14,0x2F,0x90,0xA1,0x42,0xF8, // 'B'
	0x38,0x8A,0x04,0x08,0x10,0x20,0x22,0x38, // 'C'
	0xF1,0x12,0x14,0x28,0x50,0xA1,0x44,0xF0, // 'D'
	0xFD,0x02,0x04,0x0F,0xD0,0x20,0x40,0xFC, // 'E'
	0xFD,0x02,0x04,0x0F,0xD0,0x20,0x40,0x80, // 'F'
	0x38,0x8A,0x04,0x08,0xD0,0xA1,0x22,0x38, // 'G'
	0x85,0x0A,0x14,0x2F,0xD0,0xA1,0x42,0x84, // 'H'
	0xF8,0x82,0x08,0x20,0x82,0x08,0xF8, // 'I'
	0x38,0x20,0x82,0x08,0x20,0xA2,0x70, // 'J'
	0x85,0x12,0x45,0x0E,0x12,0x26,0x44,0x84, // 'K'
	0x81,0x02,0x04,0x08,0x10,0x20,0x40,0xFC, // 'L'
	0x85,0x9B,0x35,0xAB,0x56,0xA1,0x42,0x84, // 'M'
	0xC5,0x8A,0x95,0x2B,0x52,0xA5,0x46,0x8C, // 'N'
	0x78,0x92,0x14,0x28,0x50,0xA1,0x24,0x78, // 'O'
	0xF9,0x0A,0x14,0x2F,0x90,0x20,0x40,0x80, // 'P'
	0x78,0x92,0x14,0x28,0x50,0xA1,0x26,0x78,0x10,0x20, // 'Q'
	0xF8,0x84,0x84,0x84,0xF8,0x88,0x84,0x84,0x82, // 'R'
	0x79,0x0A,0x06,0x07,0x80,0x81,0x42,0x78, // 'S'
	0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10, // 'T'
	0x85,0x0A,0x14,0x28,0x50,0xA1,0x42,0x78, // 'U'
	0x85,0x09,0x22,0x44,0x89,0x0C,0x18,0x30, // 'V'
	0x82,0x92,0x92,0xAA,0xAA,0xAA,0x6C,0x44,0x44, // 'W'
	0x84,0x91,0x21,0x83,0x06,0x12,0x24,0x84, // 'X'
	0x82,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10, // 'Y'
	0xFC,0x18,0x20,0x83,0x04,0x10,0x60,0xFC, // 'Z'
	0xD2,0x49,0x24,0x93,0x00, // '['
	0x80,0x81,0x01,0x02,0x02,0x04,0x04,0x08,0x08, // '\'
	0xC9,0x24,0x92,0x4B,0x00, // ']'
	0x30,0x92,0x10, // '^'
	0xFE, // '_'
	0x42, // '`'
	0x72,0x20,0x9E,0x8A,0x27,0x80, // 'a'
	0x82,0x08,0x3C,0x8A,0x28,0xA2,0x8B,0xC0, // 'b'
	0x73,0x28,0x20,0x83,0x07,0x80, // 'c'
	0x08,0x20,0x9E,0x8A,0x28,0xA2,0x89,0xE0, // 'd'
	0x73,0x28,0xBE,0x82,0x27,0x00, // 'e'
	0x18,0x82,0x3E,0x20,0x82,0x08,0x20,0x80, // 'f'
	0x7A,0x28,0xA2,0x8A,0x27,0x82,0x48,0xC0, // 'g'
	0x82,0x08,0x2C,0xCA,0x28,0xA2,0x8A,0x20, // 'h'
	0x20,0x00,0x38,0x20,0x82,0x08,0x23,0xE0, // 'i'
	0x20,0x0E,0x22,0x22,0x22,0x22,0xC0, // 'j'
	0x82,0x08,0x22,0x92,0x8C,0x28,0x92,0x20, // 'k'
	0xE0,0x82,0x08,0x20,0x82,0x08,0x20,0x60, // 'l'
	0xFA,0xAA,0xAA,0xAA,0xAA,0x80, // 'm'
	0xB3,0x28,0xA2,0x8A,0x28,0x80, // 'n'
	0x72,0x28,0xA2,0x8A,0x27,0x00, // 'o'
	0xF2,0x28,0xA2,0x8A,0x2F,0x20,0x82,0x00, // 'p'
	0x7A,0x28,0xA2,0x8A,0x27,0x82,0x08,0x20, // 'q'
	0xF3,0x28,0x20,0x82,0x08,0x00, // 'r'
	0x72,0x28,0x1C,0x0A,0x27,0x00, // 's'
	0x20,0x8F,0x88,0x20,0x82,0x08,0x38, // 't'
	0x8A,0x28,0xA2,0x8A,0x27,0x80, // 'u'
	0x8A,0x25,0x14,0x50,0x82,0x00, // 'v'
	0x82,0x82,0x54,0x54,0x6C,0x28,0x28, // 'w'
	0x89,0x45,0x08,0x51,0x48,0x80, // 'x'
	0x8A,0x25,0x14,0x51,0x82,0x08,0x43,0x00, // 'y'
	0xF8,0x21,0x08,0x42,0x0F,0x80, // 'z'
	0x38,0x82,0x08,0x23,0x02,0x08,0x20,0x83,0x80, // '{'
	0xAA,0xAA,0xAA, // '|'
	0xE0,0x82,0x08,0x20,0x62,0x08,0x20,0x8E,0x00 // '}'
};
const GFXglyph DialogInput_plain_12Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   2,   1,   8,    0,   -1 }, // ' '
	  {     1,   2,   9,   8,    3,   -9 }, // '!'
	  {     4,   4,   3,   8,    2,   -9 }, // '"'
	  {     6,   8,   8,   8,    0,   -8 }, // '#'
	  {    14,   6,  11,   8,    1,   -9 }, // '$'
	  {    23,   8,   9,   8,    0,   -9 }, // '%'
	  {    32,   7,   9,   8,    1,   -9 }, // '&'
	  {    40,   2,   3,   8,    3,   -9 }, // '''
	  {    41,   4,  11,   8,    3,  -10 }, // '('
	  {    47,   4,  11,   8,    2,  -10 }, // ')'
	  {    53,   6,   6,   8,    1,   -9 }, // '*'
	  {    58,   8,   7,   8,    0,   -7 }, // '+'
	  {    65,   3,   3,   8,    2,   -2 }, // ','
	  {    67,   4,   1,   8,    2,   -4 }, // '-'
	  {    68,   2,   2,   8,    3,   -2 }, // '.'
	  {    69,   7,  10,   8,    1,   -9 }, // '/'
	  {    78,   7,   9,   8,    1,   -9 }, // '0'
	  {    86,   6,   9,   8,    1,   -9 }, // '1'
	  {    93,   7,   9,   8,    1,   -9 }, // '2'
	  {   101,   7,   9,   8,    1,   -9 }, // '3'
	  {   109,   7,   9,   8,    1,   -9 }, // '4'
	  {   117,   7,   9,   8,    1,   -9 }, // '5'
	  {   125,   7,   9,   8,    1,   -9 }, // '6'
	  {   133,   7,   9,   8,    1,   -9 }, // '7'
	  {   141,   7,   9,   8,    1,   -9 }, // '8'
	  {   149,   7,   9,   8,    1,   -9 }, // '9'
	  {   157,   2,   6,   8,    3,   -6 }, // ':'
	  {   159,   3,   7,   8,    2,   -6 }, // ';'
	  {   162,   7,   6,   8,    1,   -7 }, // '<'
	  {   168,   7,   3,   8,    1,   -5 }, // '='
	  {   171,   7,   6,   8,    1,   -7 }, // '>'
	  {   177,   6,   9,   8,    2,   -9 }, // '?'
	  {   184,   7,  10,   8,    1,   -8 }, // '@'
	  {   193,   7,   9,   8,    1,   -9 }, // 'A'
	  {   201,   7,   9,   8,    1,   -9 }, // 'B'
	  {   209,   7,   9,   8,    1,   -9 }, // 'C'
	  {   217,   7,   9,   8,    1,   -9 }, // 'D'
	  {   225,   7,   9,   8,    1,   -9 }, // 'E'
	  {   233,   7,   9,   8,    1,   -9 }, // 'F'
	  {   241,   7,   9,   8,    1,   -9 }, // 'G'
	  {   249,   7,   9,   8,    1,   -9 }, // 'H'
	  {   257,   6,   9,   8,    1,   -9 }, // 'I'
	  {   264,   6,   9,   8,    1,   -9 }, // 'J'
	  {   271,   7,   9,   8,    1,   -9 }, // 'K'
	  {   279,   7,   9,   8,    1,   -9 }, // 'L'
	  {   287,   7,   9,   8,    1,   -9 }, // 'M'
	  {   295,   7,   9,   8,    1,   -9 }, // 'N'
	  {   303,   7,   9,   8,    1,   -9 }, // 'O'
	  {   311,   7,   9,   8,    1,   -9 }, // 'P'
	  {   319,   7,  11,   8,    1,   -9 }, // 'Q'
	  {   329,   8,   9,   8,    1,   -9 }, // 'R'
	  {   338,   7,   9,   8,    1,   -9 }, // 'S'
	  {   346,   8,   9,   8,    0,   -9 }, // 'T'
	  {   355,   7,   9,   8,    1,   -9 }, // 'U'
	  {   363,   7,   9,   8,    1,   -9 }, // 'V'
	  {   371,   8,   9,   8,    0,   -9 }, // 'W'
	  {   380,   7,   9,   8,    1,   -9 }, // 'X'
	  {   388,   8,   9,   8,    0,   -9 }, // 'Y'
	  {   397,   7,   9,   8,    1,   -9 }, // 'Z'
	  {   405,   3,  11,   8,    3,  -10 }, // '['
	  {   410,   7,  10,   8,    1,   -9 }, // '\'
	  {   419,   3,  11,   8,    2,  -10 }, // ']'
	  {   424,   7,   3,   8,    0,   -9 }, // '^'
	  {   427,   8,   1,   8,    0,    2 }, // '_'
	  {   428,   4,   2,   8,    2,  -10 }, // '`'
	  {   429,   6,   7,   8,    1,   -7 }, // 'a'
	  {   435,   6,  10,   8,    1,  -10 }, // 'b'
	  {   443,   6,   7,   8,    1,   -7 }, // 'c'
	  {   449,   6,  10,   8,    1,  -10 }, // 'd'
	  {   457,   6,   7,   8,    1,   -7 }, // 'e'
	  {   463,   6,  10,   8,    1,  -10 }, // 'f'
	  {   471,   6,  10,   8,    1,   -7 }, // 'g'
	  {   479,   6,  10,   8,    1,  -10 }, // 'h'
	  {   487,   6,  10,   8,    1,  -10 }, // 'i'
	  {   495,   4,  13,   8,    2,  -10 }, // 'j'
	  {   502,   6,  10,   8,    1,  -10 }, // 'k'
	  {   510,   6,  10,   8,    1,  -10 }, // 'l'
	  {   518,   6,   7,   8,    1,   -7 }, // 'm'
	  {   524,   6,   7,   8,    1,   -7 }, // 'n'
	  {   530,   6,   7,   8,    1,   -7 }, // 'o'
	  {   536,   6,  10,   8,    1,   -7 }, // 'p'
	  {   544,   6,  10,   8,    1,   -7 }, // 'q'
	  {   552,   6,   7,   8,    2,   -7 }, // 'r'
	  {   558,   6,   7,   8,    1,   -7 }, // 's'
	  {   564,   6,   9,   8,    1,   -9 }, // 't'
	  {   571,   6,   7,   8,    1,   -7 }, // 'u'
	  {   577,   6,   7,   8,    1,   -7 }, // 'v'
	  {   583,   8,   7,   8,    0,   -7 }, // 'w'
	  {   590,   6,   7,   8,    1,   -7 }, // 'x'
	  {   596,   6,  10,   8,    1,   -7 }, // 'y'
	  {   604,   6,   7,   8,    1,   -7 }, // 'z'
	  {   610,   6,  11,   8,    1,  -10 }, // '{'
	  {   619,   2,  12,   8,    3,  -10 }, // '|'
	  {   622,   6,  11,   8,    1,  -10 } // '}'
};
const GFXfont DialogInput_plain_12 PROGMEM = {
(uint8_t  *)DialogInput_plain_12Bitmaps,(GFXglyph *)DialogInput_plain_12Glyphs,0x20, 0x7E, 15};