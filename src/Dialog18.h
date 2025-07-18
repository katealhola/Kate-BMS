// Created by https://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t DialogInput_plain_18Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xDB,0x6D,0xB6,0xC0,0x6C, // '!'
	0xCD,0x9B,0x36,0x6C,0xC0, // '"'
	0x04,0xC0,0xC8,0x0C,0x80,0x98,0x7F,0xE7,0xFE,0x19,0x01,0x30,0xFF,0xCF,0xFC,0x32,0x02,0x20,0x26,0x06,0x60, // '#'
	0x08,0x02,0x03,0xE1,0xFC,0xC9,0x32,0x0C,0x81,0xE0,0x0F,0x02,0x60,0x9A,0x26,0xFF,0x1F,0x80,0x80,0x20,0x08,0x00, // '$'
	0x78,0x0C,0xC0,0xCC,0x0C,0xC0,0xCC,0x07,0x9C,0x0E,0x07,0x3C,0x06,0x60,0x66,0x06,0x60,0x66,0x03,0xC0, // '%'
	0x1F,0x07,0xE0,0xC0,0x18,0x01,0x80,0x78,0x1B,0x36,0x76,0xC7,0xD8,0x73,0x8C,0x3E,0xC3,0xDC, // '&'
	0xDB,0x6C, // '''
	0x31,0x18,0xC4,0x63,0x18,0xC6,0x30,0x86,0x30,0x86, // '('
	0xC2,0x18,0xC2,0x18,0xC6,0x31,0x8C,0x46,0x31,0x18, // ')'
	0x10,0x92,0x54,0x38,0x38,0x54,0x92,0x10, // '*'
	0x0C,0x01,0x80,0x30,0x06,0x0F,0xFD,0xFF,0x83,0x00,0x60,0x0C,0x01,0x80, // '+'
	0x66,0x6C,0x80, // ','
	0xFB,0xE0, // '-'
	0xDB,0x00, // '.'
	0x01,0x80,0xC0,0x30,0x18,0x06,0x03,0x00,0xC0,0x70,0x18,0x06,0x03,0x00,0xC0,0x60,0x18,0x0C,0x00, // '/'
	0x3E,0x1F,0xC6,0x33,0x06,0xC1,0xB3,0x6C,0xDB,0x06,0xC1,0xB0,0x66,0x31,0xFC,0x3E,0x00, // '0'
	0x38,0x7C,0x36,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x1F,0xEF,0xF0, // '1'
	0x7E,0x3F,0xC8,0x38,0x06,0x01,0x80,0xE0,0x30,0x38,0x1C,0x0E,0x06,0x03,0xFE,0xFF,0x80, // '2'
	0x7E,0x3F,0xC8,0x38,0x06,0x03,0x8F,0xC3,0xF0,0x0E,0x01,0x80,0x68,0x3B,0xFC,0x7E,0x00, // '3'
	0x06,0x03,0x80,0xE0,0x58,0x36,0x09,0x86,0x63,0x18,0xFF,0xBF,0xE0,0x60,0x18,0x06,0x00, // '4'
	0x7F,0x1F,0xC6,0x01,0x80,0x7E,0x1F,0xC4,0x38,0x06,0x01,0x80,0x68,0x3B,0xFC,0x7E,0x00, // '5'
	0x1E,0x1F,0xC7,0x13,0x80,0xC0,0x37,0x8F,0xF3,0x8E,0xC1,0xB0,0x66,0x39,0xFC,0x3E,0x00, // '6'
	0xFF,0xBF,0xE0,0x30,0x0C,0x07,0x01,0x80,0x60,0x30,0x0C,0x07,0x01,0x80,0x60,0x30,0x00, // '7'
	0x3E,0x1F,0xCC,0x1B,0x06,0xC1,0x9F,0xC7,0xF3,0x8E,0xC1,0xB0,0x6E,0x39,0xFC,0x3E,0x00, // '8'
	0x3E,0x1F,0xCE,0x33,0x06,0xC1,0xB8,0xE7,0xF8,0xF6,0x01,0x80,0xE4,0x71,0xF8,0x3C,0x00, // '9'
	0xDB,0x00,0x36,0xC0, // ':'
	0x66,0x60,0x00,0x66,0x6C,0x80, // ';'
	0x00,0x81,0xE1,0xE1,0xC0,0xC0,0x1C,0x01,0xE0,0x1E,0x00,0x80, // '<'
	0xFF,0xBF,0xE0,0x00,0x00,0xFF,0xBF,0xE0, // '='
	0x80,0x3C,0x03,0xC0,0x1C,0x01,0x81,0xC3,0xC3,0xC0,0x80,0x00, // '>'
	0x7C,0xFE,0x86,0x06,0x0E,0x1C,0x38,0x30,0x30,0x30,0x00,0x30,0x30, // '?'
	0x1E,0x0C,0xC6,0x19,0x9E,0xCD,0xB3,0x6C,0xDB,0x36,0xCD,0xB3,0x6C,0x79,0x80,0x60,0x0C,0x01,0xE0, // '@'
	0x1C,0x07,0x01,0xC0,0x70,0x36,0x0D,0x83,0x60,0xD8,0x7F,0x1F,0xC6,0x33,0x06,0xC1,0x80, // 'A'
	0xFE,0x3F,0xCC,0x1B,0x06,0xC1,0xBF,0xCF,0xF3,0x0E,0xC1,0xB0,0x6C,0x3B,0xFC,0xFE,0x00, // 'B'
	0x1F,0x0F,0xE7,0x0B,0x80,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x38,0x07,0x08,0xFE,0x1F,0x00, // 'C'
	0xFC,0x3F,0x8C,0x73,0x0E,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0xEC,0x73,0xF8,0xFC,0x00, // 'D'
	0xFF,0xBF,0xEC,0x03,0x00,0xC0,0x3F,0xEF,0xFB,0x00,0xC0,0x30,0x0C,0x03,0xFE,0xFF,0x80, // 'E'
	0xFF,0xBF,0xEC,0x03,0x00,0xC0,0x3F,0xCF,0xF3,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x00, // 'F'
	0x1F,0x0F,0xE7,0x0B,0x80,0xC0,0x31,0xEC,0x7B,0x06,0xC1,0xB8,0x66,0x18,0xFE,0x1E,0x00, // 'G'
	0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xBF,0xEF,0xFB,0x06,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0x80, // 'H'
	0xFF,0x7F,0x86,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x1F,0xEF,0xF0, // 'I'
	0x3E,0x3E,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x86,0xFC,0x7C, // 'J'
	0xC1,0x98,0x63,0x18,0x66,0x0D,0x81,0xF0,0x3E,0x06,0x60,0xCE,0x18,0xC3,0x0C,0x61,0xCC,0x18, // 'K'
	0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x03,0xFE,0xFF,0x80, // 'L'
	0xE3,0xB8,0xEE,0x3B,0xDE,0xD5,0xB5,0x6D,0xDB,0x26,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0x80, // 'M'
	0xE1,0xB8,0x6F,0x1B,0x46,0xD1,0xB6,0x6C,0x9B,0x36,0xC5,0xB1,0x6C,0x7B,0x0E,0xC3,0x80, // 'N'
	0x3E,0x1F,0xC6,0x33,0x06,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x66,0x31,0xFC,0x3E,0x00, // 'O'
	0xFE,0x3F,0xCC,0x3B,0x06,0xC1,0xB0,0xEF,0xF3,0xF8,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x00, // 'P'
	0x3E,0x1F,0xC6,0x33,0x06,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x66,0x31,0xFC,0x3E,0x01,0xC0,0x30, // 'Q'
	0xFE,0x1F,0xE3,0x0E,0x60,0xCC,0x19,0x87,0x3F,0xC7,0xF0,0xC3,0x18,0x73,0x06,0x60,0xCC,0x0C, // 'R'
	0x3E,0x1F,0xCE,0x13,0x00,0xC0,0x1F,0x03,0xF0,0x0E,0x01,0x80,0x68,0x3B,0xFC,0x7E,0x00, // 'S'
	0xFF,0xDF,0xF8,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0, // 'T'
	0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x6E,0x39,0xFC,0x3E,0x00, // 'U'
	0xC1,0xB0,0x66,0x31,0x8C,0x63,0x1D,0xC3,0x60,0xD8,0x36,0x07,0x01,0xC0,0x70,0x1C,0x00, // 'V'
	0xC0,0x6C,0x06,0xC0,0x66,0x0C,0x6E,0xC6,0xEC,0x6A,0xC6,0xAC,0x6A,0xC7,0xBC,0x31,0x83,0x18,0x31,0x80, // 'W'
	0xE3,0x98,0xC7,0x60,0xD8,0x1C,0x07,0x01,0xC0,0x70,0x3E,0x0D,0x87,0x71,0x8C,0xE3,0x80, // 'X'
	0xE1,0xCC,0x31,0xCE,0x19,0x81,0xE0,0x3C,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0, // 'Y'
	0xFF,0xBF,0xE0,0x30,0x1C,0x06,0x03,0x01,0xC0,0x60,0x38,0x1C,0x06,0x03,0xFE,0xFF,0x80, // 'Z'
	0xF7,0xB1,0x8C,0x63,0x18,0xC6,0x31,0x8C,0x63,0xDE, // '['
	0xC0,0x18,0x06,0x00,0xC0,0x30,0x06,0x01,0x80,0x70,0x0C,0x03,0x00,0x60,0x18,0x03,0x00,0xC0,0x18, // '\'
	0xF7,0x8C,0x63,0x18,0xC6,0x31,0x8C,0x63,0x1B,0xDE, // ']'
	0x0C,0x03,0xC0,0xCC,0x30,0xCC,0x0C, // '^'
	0xFF,0xEF,0xFE, // '_'
	0xC3,0x0C, // '`'
	0x3E,0x1F,0xC4,0x38,0x06,0x3F,0xBF,0xEC,0x1B,0x0E,0xFF,0x9F,0x60, // 'a'
	0xC0,0x30,0x0C,0x03,0x00,0xDE,0x3F,0xCE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0xFF,0x37,0x80, // 'b'
	0x1E,0x3F,0x98,0x58,0x0C,0x06,0x03,0x00,0xC2,0x7F,0x0F,0x00, // 'c'
	0x01,0x80,0x60,0x18,0x06,0x3D,0x9F,0xEE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0x7F,0x8F,0x60, // 'd'
	0x3E,0x1F,0xC6,0x3B,0x06,0xFF,0xBF,0xEC,0x01,0x82,0x7F,0x87,0xC0, // 'e'
	0x0F,0x0F,0x86,0x03,0x0F,0xF7,0xF8,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0, // 'f'
	0x3D,0x9F,0xEE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0x7F,0x8F,0x60,0x19,0x0E,0x7F,0x0F,0x80, // 'g'
	0xC0,0x30,0x0C,0x03,0x00,0xCE,0x3F,0xCE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x60, // 'h'
	0x18,0x0C,0x00,0x00,0x0F,0x87,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x0F,0xF7,0xF8, // 'i'
	0x0C,0x18,0x00,0x07,0xCF,0x83,0x06,0x0C,0x18,0x30,0x60,0xC1,0x83,0x06,0xF9,0xE0, // 'j'
	0xC0,0x30,0x0C,0x03,0x00,0xC3,0xB1,0xCC,0xE3,0x70,0xF8,0x3F,0x0C,0xC3,0x18,0xC7,0x30,0xE0, // 'k'
	0xF8,0x7C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x00,0xF0,0x78, // 'l'
	0xDB,0x9F,0xFB,0x33,0x66,0x6C,0xCD,0x99,0xB3,0x36,0x66,0xCC,0xD9,0x98, // 'm'
	0xCE,0x3F,0xCE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x60, // 'n'
	0x3E,0x1F,0xCE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0x7F,0x0F,0x80, // 'o'
	0xDE,0x3F,0xCE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0xFF,0x37,0x8C,0x03,0x00,0xC0,0x30,0x00, // 'p'
	0x3D,0x9F,0xEE,0x3B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0x7F,0x8F,0x60,0x18,0x06,0x01,0x80,0x60, // 'q'
	0xDC,0xDE,0xE2,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0, // 'r'
	0x3F,0x3F,0xEC,0x0B,0xE0,0x7F,0x01,0xE0,0x1A,0x06,0xFF,0x9F,0x80, // 's'
	0x18,0x06,0x01,0x83,0xFE,0xFF,0x86,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x7E,0x0F,0x80, // 't'
	0xC1,0xB0,0x6C,0x1B,0x06,0xC1,0xB0,0x6C,0x1B,0x8E,0x7F,0x8E,0x60, // 'u'
	0xC1,0x98,0xC6,0x31,0x8C,0x36,0x0D,0x83,0x60,0x70,0x1C,0x07,0x00, // 'v'
	0xC0,0x6C,0x06,0x60,0xC6,0x4C,0x6E,0xC6,0xAC,0x3B,0x83,0xB8,0x31,0x83,0x18, // 'w'
	0xE3,0x9D,0xC3,0x60,0x70,0x1C,0x07,0x03,0xE0,0xD8,0x63,0x38,0xE0, // 'x'
	0xC1,0x98,0xC6,0x31,0xCC,0x36,0x0D,0x81,0xE0,0x70,0x0C,0x07,0x01,0x80,0x60,0x78,0x1C,0x00, // 'y'
	0xFF,0xBF,0xE0,0x70,0x38,0x1C,0x06,0x03,0x01,0xC0,0xFF,0xBF,0xE0, // 'z'
	0x0F,0x0F,0x86,0x03,0x01,0x80,0xC0,0x61,0xE0,0xF0,0x1C,0x06,0x03,0x01,0x80,0xC0,0x60,0x3E,0x0F,0x00, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xD8, // '|'
	0xF0,0x7C,0x06,0x03,0x01,0x80,0xC0,0x60,0x1E,0x0F,0x0E,0x06,0x03,0x01,0x80,0xC0,0x61,0xF0,0xF0,0x00 // '}'
};
const GFXglyph DialogInput_plain_18Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   2,   1,  12,    0,   -1 }, // ' '
	  {     1,   3,  13,  12,    5,  -13 }, // '!'
	  {     6,   7,   5,  12,    3,  -13 }, // '"'
	  {    11,  12,  14,  12,    0,  -14 }, // '#'
	  {    32,  10,  17,  12,    1,  -14 }, // '$'
	  {    54,  12,  13,  12,    0,  -13 }, // '%'
	  {    74,  11,  13,  12,    1,  -13 }, // '&'
	  {    92,   3,   5,  12,    5,  -13 }, // '''
	  {    94,   5,  16,  12,    4,  -14 }, // '('
	  {   104,   5,  16,  12,    3,  -14 }, // ')'
	  {   114,   8,   8,  12,    2,  -13 }, // '*'
	  {   122,  11,  10,  12,    1,  -11 }, // '+'
	  {   136,   4,   5,  12,    3,   -3 }, // ','
	  {   139,   6,   2,  12,    3,   -6 }, // '-'
	  {   141,   3,   3,  12,    4,   -3 }, // '.'
	  {   143,  10,  15,  12,    1,  -13 }, // '/'
	  {   162,  10,  13,  12,    1,  -13 }, // '0'
	  {   179,   9,  13,  12,    2,  -13 }, // '1'
	  {   194,  10,  13,  12,    1,  -13 }, // '2'
	  {   211,  10,  13,  12,    1,  -13 }, // '3'
	  {   228,  10,  13,  12,    1,  -13 }, // '4'
	  {   245,  10,  13,  12,    1,  -13 }, // '5'
	  {   262,  10,  13,  12,    1,  -13 }, // '6'
	  {   279,  10,  13,  12,    1,  -13 }, // '7'
	  {   296,  10,  13,  12,    1,  -13 }, // '8'
	  {   313,  10,  13,  12,    1,  -13 }, // '9'
	  {   330,   3,   9,  12,    4,   -9 }, // ':'
	  {   334,   4,  11,  12,    3,   -9 }, // ';'
	  {   340,  10,   9,  12,    1,  -10 }, // '<'
	  {   352,  10,   6,  12,    1,   -9 }, // '='
	  {   360,  10,   9,  12,    1,  -10 }, // '>'
	  {   372,   8,  13,  12,    2,  -13 }, // '?'
	  {   385,  10,  15,  12,    1,  -12 }, // '@'
	  {   404,  10,  13,  12,    1,  -13 }, // 'A'
	  {   421,  10,  13,  12,    1,  -13 }, // 'B'
	  {   438,  10,  13,  12,    1,  -13 }, // 'C'
	  {   455,  10,  13,  12,    1,  -13 }, // 'D'
	  {   472,  10,  13,  12,    1,  -13 }, // 'E'
	  {   489,  10,  13,  12,    1,  -13 }, // 'F'
	  {   506,  10,  13,  12,    1,  -13 }, // 'G'
	  {   523,  10,  13,  12,    1,  -13 }, // 'H'
	  {   540,   9,  13,  12,    2,  -13 }, // 'I'
	  {   555,   8,  13,  12,    1,  -13 }, // 'J'
	  {   568,  11,  13,  12,    1,  -13 }, // 'K'
	  {   586,  10,  13,  12,    1,  -13 }, // 'L'
	  {   603,  10,  13,  12,    1,  -13 }, // 'M'
	  {   620,  10,  13,  12,    1,  -13 }, // 'N'
	  {   637,  10,  13,  12,    1,  -13 }, // 'O'
	  {   654,  10,  13,  12,    1,  -13 }, // 'P'
	  {   671,  10,  15,  12,    1,  -13 }, // 'Q'
	  {   690,  11,  13,  12,    1,  -13 }, // 'R'
	  {   708,  10,  13,  12,    1,  -13 }, // 'S'
	  {   725,  11,  13,  12,    1,  -13 }, // 'T'
	  {   743,  10,  13,  12,    1,  -13 }, // 'U'
	  {   760,  10,  13,  12,    1,  -13 }, // 'V'
	  {   777,  12,  13,  12,    0,  -13 }, // 'W'
	  {   797,  10,  13,  12,    1,  -13 }, // 'X'
	  {   814,  11,  13,  12,    1,  -13 }, // 'Y'
	  {   832,  10,  13,  12,    1,  -13 }, // 'Z'
	  {   849,   5,  16,  12,    4,  -14 }, // '['
	  {   859,  10,  15,  12,    1,  -13 }, // '\'
	  {   878,   5,  16,  12,    3,  -14 }, // ']'
	  {   888,  11,   5,  12,    1,  -13 }, // '^'
	  {   895,  12,   2,  12,    0,    2 }, // '_'
	  {   898,   5,   3,  12,    2,  -14 }, // '`'
	  {   900,  10,  10,  12,    1,  -10 }, // 'a'
	  {   913,  10,  14,  12,    1,  -14 }, // 'b'
	  {   931,   9,  10,  12,    1,  -10 }, // 'c'
	  {   943,  10,  14,  12,    1,  -14 }, // 'd'
	  {   961,  10,  10,  12,    1,  -10 }, // 'e'
	  {   974,   9,  14,  12,    1,  -14 }, // 'f'
	  {   990,  10,  14,  12,    1,  -10 }, // 'g'
	  {  1008,  10,  14,  12,    1,  -14 }, // 'h'
	  {  1026,   9,  14,  12,    2,  -14 }, // 'i'
	  {  1042,   7,  18,  12,    1,  -14 }, // 'j'
	  {  1058,  10,  14,  12,    1,  -14 }, // 'k'
	  {  1076,   9,  14,  12,    1,  -14 }, // 'l'
	  {  1092,  11,  10,  12,    1,  -10 }, // 'm'
	  {  1106,  10,  10,  12,    1,  -10 }, // 'n'
	  {  1119,  10,  10,  12,    1,  -10 }, // 'o'
	  {  1132,  10,  14,  12,    1,  -10 }, // 'p'
	  {  1150,  10,  14,  12,    1,  -10 }, // 'q'
	  {  1168,   8,  10,  12,    3,  -10 }, // 'r'
	  {  1178,  10,  10,  12,    1,  -10 }, // 's'
	  {  1191,  10,  13,  12,    1,  -13 }, // 't'
	  {  1208,  10,  10,  12,    1,  -10 }, // 'u'
	  {  1221,  10,  10,  12,    1,  -10 }, // 'v'
	  {  1234,  12,  10,  12,    0,  -10 }, // 'w'
	  {  1249,  10,  10,  12,    1,  -10 }, // 'x'
	  {  1262,  10,  14,  12,    1,  -10 }, // 'y'
	  {  1280,  10,  10,  12,    1,  -10 }, // 'z'
	  {  1293,   9,  17,  12,    2,  -14 }, // '{'
	  {  1313,   3,  18,  12,    5,  -14 }, // '|'
	  {  1320,   9,  17,  12,    2,  -14 } // '}'
};
const GFXfont DialogInput_plain_18 PROGMEM = {
(uint8_t  *)DialogInput_plain_18Bitmaps,(GFXglyph *)DialogInput_plain_18Glyphs,0x20, 0x7E, 22};