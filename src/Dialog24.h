// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Dialog_plain_24Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xDB,0x6D,0xB6,0xDB,0x60,0x06,0xD8, // '!'
	0xCD,0x9B,0x36,0x6C,0xD9,0xB3,0x00, // '"'
	0x03,0x08,0x01,0x8C,0x00,0xC6,0x00,0x63,0x00,0x21,0x83,0xFF,0xF9,0xFF,0xFC,0x0C,0x60,0x04,0x30,0x06,0x10,0x03,0x18,0x1F,0xFF,0xCF,0xFF,0xE0,0xC2,0x00,0x63,0x00,0x31,0x80,0x18,0xC0,0x08,0x60,0x00, // '#'
	0x04,0x00,0x40,0x04,0x01,0xF8,0x7F,0xCE,0x44,0xC4,0x0C,0x40,0xE4,0x07,0xC0,0x3F,0x80,0x7C,0x04,0xE0,0x46,0x04,0x68,0x4E,0xFF,0xC3,0xF0,0x04,0x00,0x40,0x04,0x00,0x40, // '$'
	0x3C,0x03,0x03,0x30,0x38,0x30,0xC1,0x81,0x86,0x18,0x0C,0x31,0xC0,0x61,0x8C,0x03,0x0C,0xE0,0x18,0x66,0x00,0x66,0x63,0xC1,0xE3,0x33,0x00,0x33,0x0C,0x03,0x98,0x60,0x18,0xC3,0x01,0xC6,0x18,0x0C,0x30,0xC0,0xC1,0x86,0x0E,0x06,0x60,0x60,0x1E,0x00, // '%'
	0x0F,0xC0,0x0F,0xF0,0x0E,0x08,0x06,0x00,0x03,0x00,0x01,0x80,0x00,0xE0,0x00,0x38,0x00,0x3E,0x00,0x3B,0x83,0x38,0xE1,0x98,0x39,0x8C,0x0E,0xC6,0x03,0xC3,0x80,0xE0,0xE1,0xF8,0x3F,0xCE,0x07,0xC3,0x80, // '&'
	0xDB,0x6D,0xB0, // '''
	0x18,0xC3,0x18,0x61,0x8C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x18,0x61,0x83,0x0C,0x18, // '('
	0xC1,0x86,0x0C,0x30,0xC1,0x06,0x18,0x61,0x86,0x18,0x61,0x8C,0x30,0xC6,0x18,0xC0, // ')'
	0x04,0x00,0x40,0xC4,0x67,0x5C,0x1F,0x01,0xF0,0x75,0xCC,0x46,0x04,0x00,0x40, // '*'
	0x01,0x80,0x00,0xC0,0x00,0x60,0x00,0x30,0x00,0x18,0x00,0x0C,0x00,0x06,0x01,0xFF,0xFE,0xFF,0xFF,0x00,0xC0,0x00,0x60,0x00,0x30,0x00,0x18,0x00,0x0C,0x00,0x06,0x00,0x03,0x00, // '+'
	0x66,0x66,0xCC, // ','
	0xFD,0xF8, // '-'
	0xDB,0x00, // '.'
	0x03,0x03,0x81,0x80,0xC0,0x60,0x60,0x30,0x18,0x1C,0x0C,0x06,0x07,0x03,0x01,0x80,0xC0,0xC0,0x60,0x30,0x38,0x18,0x00, // '/'
	0x0F,0x01,0xFE,0x1C,0x38,0xC0,0xC6,0x06,0x60,0x1B,0x00,0xD8,0x06,0xC0,0x36,0x01,0xB0,0x0D,0x80,0x6C,0x03,0x30,0x31,0x81,0x8E,0x1C,0x3F,0xC0,0x78,0x00, // '0'
	0x3C,0x1F,0x83,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x03,0x00,0x60,0xFF,0xDF,0xF8, // '1'
	0x3F,0x0F,0xF8,0xC1,0xC0,0x0E,0x00,0x60,0x06,0x00,0x60,0x0C,0x01,0xC0,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xFF,0xEF,0xFE, // '2'
	0x3F,0x03,0xFE,0x10,0x70,0x00,0xC0,0x06,0x00,0x30,0x01,0x80,0x18,0x1F,0x80,0xFE,0x00,0x38,0x00,0x60,0x03,0x00,0x18,0x00,0xD0,0x1C,0xFF,0xC1,0xF8,0x00, // '3'
	0x01,0xC0,0x0F,0x00,0x2C,0x01,0xB0,0x0C,0xC0,0x33,0x01,0x8C,0x0E,0x30,0x30,0xC1,0x83,0x06,0x0C,0x30,0x30,0xFF,0xFB,0xFF,0xE0,0x0C,0x00,0x30,0x00,0xC0,0x03,0x00, // '4'
	0x7F,0xC7,0xFC,0x60,0x06,0x00,0x60,0x06,0x00,0x7F,0x07,0xF8,0x41,0xC0,0x0E,0x00,0x60,0x06,0x00,0x60,0x06,0x00,0xE8,0x1C,0xFF,0x87,0xE0, // '5'
	0x07,0xC0,0xFF,0x0E,0x08,0xE0,0x06,0x00,0x60,0x03,0x3E,0x1B,0xF8,0xF8,0xE7,0x83,0xB8,0x0D,0xC0,0x6E,0x03,0x30,0x19,0xC1,0xCF,0x1C,0x3F,0xC0,0x7C,0x00, // '6'
	0xFF,0xEF,0xFE,0x00,0xC0,0x0C,0x01,0xC0,0x18,0x01,0x80,0x30,0x03,0x00,0x70,0x06,0x00,0x60,0x0C,0x00,0xC0,0x1C,0x01,0x80,0x18,0x03,0x00, // '7'
	0x1F,0x83,0xFF,0x1C,0x39,0x80,0x6C,0x03,0x60,0x1B,0x00,0xCC,0x1C,0x3F,0xC1,0xFE,0x1C,0x39,0x80,0x6C,0x03,0x60,0x1B,0x00,0xCE,0x1C,0x7F,0xE0,0xFC,0x00, // '8'
	0x1F,0x01,0xFE,0x1C,0x79,0xC1,0xCC,0x06,0x60,0x3B,0x01,0xD8,0x0E,0xE0,0xF3,0x8F,0x8F,0xEC,0x3E,0x60,0x03,0x00,0x30,0x03,0x88,0x38,0x7F,0x81,0xF0,0x00, // '9'
	0xDB,0x00,0x00,0x1B,0x60, // ':'
	0x66,0x60,0x00,0x00,0x06,0x66,0x6C,0xC0, // ';'
	0x00,0x02,0x00,0x1E,0x00,0xFC,0x07,0xE0,0x1F,0x80,0xFC,0x00,0xE0,0x00,0xFC,0x00,0x1F,0x80,0x07,0xE0,0x00,0xFC,0x00,0x1E,0x00,0x02, // '<'
	0xFF,0xFE,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0xFF,0xFE, // '='
	0x80,0x00,0xF0,0x00,0x7E,0x00,0x0F,0xC0,0x03,0xF0,0x00,0x7E,0x00,0x0E,0x00,0x7E,0x03,0xF0,0x0F,0xC0,0x7E,0x00,0xF0,0x00,0x80,0x00, // '>'
	0x3E,0x1F,0xCC,0x3A,0x06,0x01,0x80,0x60,0x30,0x1C,0x0E,0x07,0x01,0x80,0x60,0x18,0x00,0x00,0x00,0x60,0x18,0x06,0x00, // '?'
	0x00,0xFC,0x00,0x1F,0xFC,0x00,0xF0,0x3C,0x07,0x00,0x38,0x38,0x00,0x71,0xC3,0xCC,0xC6,0x3F,0xF3,0xB8,0xE3,0xC6,0xC7,0x07,0x1B,0x18,0x0C,0x6C,0x60,0x31,0xB1,0x80,0xC6,0xC6,0x07,0x33,0x8C,0x3D,0xC6,0x3F,0xFE,0x1C,0x3C,0xE0,0x38,0x00,0x00,0x70,0x02,0x00,0xF0,0x38,0x01,0xFF,0xC0,0x01,0xFC,0x00, // '@'
	0x03,0xC0,0x01,0xE0,0x00,0xF0,0x00,0xFC,0x00,0x66,0x00,0x33,0x00,0x30,0xC0,0x18,0x60,0x0C,0x30,0x0C,0x0C,0x06,0x06,0x07,0x03,0x83,0xFF,0xC1,0xFF,0xE1,0x80,0x18,0xC0,0x0C,0x60,0x06,0x60,0x01,0x80, // 'A'
	0xFF,0x07,0xFE,0x30,0x39,0x80,0xCC,0x06,0x60,0x33,0x01,0x98,0x18,0xFF,0x87,0xFE,0x30,0x19,0x80,0x6C,0x03,0x60,0x1B,0x00,0xD8,0x0C,0xFF,0xE7,0xFC,0x00, // 'B'
	0x07,0xE0,0x3F,0xF0,0xF0,0x73,0x80,0x26,0x00,0x1C,0x00,0x30,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00,0x0E,0x00,0x0C,0x00,0x1C,0x01,0x1E,0x0E,0x1F,0xF8,0x0F,0xC0, // 'C'
	0xFF,0x80,0xFF,0xF0,0xC0,0x78,0xC0,0x1C,0xC0,0x0C,0xC0,0x0E,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x06,0xC0,0x0E,0xC0,0x0C,0xC0,0x1C,0xC0,0x78,0xFF,0xF0,0xFF,0x80, // 'D'
	0xFF,0xEF,0xFE,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xFF,0xCF,0xFC,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xFF,0xEF,0xFE, // 'E'
	0xFF,0xDF,0xFB,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xFF,0x9F,0xF3,0x00,0x60,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x18,0x00, // 'F'
	0x07,0xE0,0x1F,0xF8,0x38,0x1C,0x70,0x04,0x60,0x00,0xE0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x7E,0xC0,0x7E,0xC0,0x06,0xC0,0x06,0xE0,0x06,0x60,0x06,0x70,0x06,0x3C,0x0E,0x1F,0xFC,0x07,0xF0, // 'G'
	0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xFF,0xFB,0xFF,0xEC,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x60, // 'H'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xD8, // 'I'
	0x0C,0x18,0x30,0x60,0xC1,0x83,0x06,0x0C,0x18,0x30,0x60,0xC1,0x83,0x06,0x0C,0x18,0x30,0x61,0x9F,0x3C,0x00, // 'J'
	0xC0,0x71,0x81,0xC3,0x07,0x06,0x1C,0x0C,0x70,0x19,0xC0,0x37,0x00,0x7C,0x00,0xF0,0x01,0xB0,0x03,0x38,0x06,0x38,0x0C,0x38,0x18,0x38,0x30,0x38,0x60,0x38,0xC0,0x39,0x80,0x38, // 'K'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xFF,0xEF,0xFE, // 'L'
	0xE0,0x07,0x78,0x07,0xBC,0x03,0xDF,0x03,0xED,0x81,0xB6,0xC0,0xDB,0x30,0xCD,0x98,0x66,0xCC,0x33,0x63,0x31,0xB1,0x98,0xD8,0xFC,0x6C,0x3C,0x36,0x1E,0x1B,0x06,0x0D,0x80,0x06,0xC0,0x03,0x60,0x01,0x80, // 'M'
	0xE0,0x1B,0xC0,0x6F,0x01,0xBE,0x06,0xD8,0x1B,0x30,0x6C,0xC1,0xB1,0x86,0xC6,0x1B,0x0C,0x6C,0x31,0xB0,0x66,0xC1,0x9B,0x03,0x6C,0x0D,0xB0,0x1E,0xC0,0x7B,0x00,0xE0, // 'N'
	0x07,0xE0,0x0F,0xFC,0x0F,0x07,0x0E,0x01,0xC6,0x00,0x67,0x00,0x3B,0x00,0x0D,0x80,0x06,0xC0,0x03,0x60,0x01,0xB0,0x00,0xD8,0x00,0x6E,0x00,0x73,0x00,0x31,0xC0,0x38,0x70,0x38,0x1F,0xF8,0x03,0xF0,0x00, // 'O'
	0xFF,0x0F,0xFC,0xC0,0xCC,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x0C,0xFF,0xCF,0xF0,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0x00, // 'P'
	0x07,0xE0,0x0F,0xFC,0x0F,0x07,0x0E,0x01,0xC6,0x00,0x67,0x00,0x3B,0x00,0x0D,0x80,0x06,0xC0,0x03,0x60,0x01,0xB0,0x00,0xD8,0x00,0x6E,0x00,0x73,0x00,0x31,0xC0,0x38,0x70,0x38,0x1F,0xF8,0x03,0xF8,0x00,0x0E,0x00,0x03,0x00,0x00,0xC0, // 'Q'
	0xFF,0x03,0xFF,0x0C,0x0C,0x30,0x18,0xC0,0x63,0x01,0x8C,0x06,0x30,0x30,0xFF,0xC3,0xFE,0x0C,0x1C,0x30,0x30,0xC0,0x63,0x01,0x8C,0x07,0x30,0x0C,0xC0,0x33,0x00,0x60, // 'R'
	0x1F,0x83,0xFF,0x1C,0x19,0x80,0x0C,0x00,0x60,0x03,0x00,0x0E,0x00,0x7F,0x00,0xFE,0x00,0x78,0x00,0xE0,0x03,0x00,0x18,0x00,0xD8,0x1C,0xFF,0xE1,0xFC,0x00, // 'S'
	0xFF,0xFD,0xFF,0xF8,0x0C,0x00,0x18,0x00,0x30,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00,0x0C,0x00,0x18,0x00,0x30,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00, // 'T'
	0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x6C,0x01,0xB0,0x06,0xC0,0x1B,0x00,0x66,0x03,0x1C,0x1C,0x3F,0xE0,0x3E,0x00, // 'U'
	0xC0,0x03,0x30,0x03,0x18,0x01,0x8C,0x00,0xC3,0x00,0xC1,0x80,0x60,0xE0,0x70,0x30,0x30,0x18,0x18,0x06,0x18,0x03,0x0C,0x01,0x86,0x00,0x66,0x00,0x33,0x00,0x1F,0x80,0x07,0x80,0x03,0xC0,0x01,0xE0,0x00, // 'V'
	0xC0,0x78,0x0D,0x80,0xF0,0x19,0x81,0xE0,0x63,0x03,0xC0,0xC6,0x0E,0xC1,0x8C,0x19,0x83,0x0C,0x33,0x0C,0x18,0x66,0x18,0x31,0xCE,0x30,0x63,0x0C,0x60,0x66,0x19,0x80,0xCC,0x33,0x01,0x98,0x66,0x03,0x60,0x6C,0x03,0xC0,0xF0,0x07,0x81,0xE0,0x0F,0x03,0xC0,0x1C,0x03,0x80, // 'W'
	0x70,0x0E,0x30,0x0C,0x18,0x18,0x1C,0x38,0x0C,0x70,0x06,0x60,0x07,0xC0,0x03,0xC0,0x03,0x80,0x03,0xC0,0x07,0xC0,0x06,0xE0,0x0C,0x60,0x1C,0x30,0x38,0x38,0x30,0x18,0x60,0x0C,0xE0,0x0E, // 'X'
	0xE0,0x1C,0xC0,0x30,0xC0,0xC1,0xC3,0x81,0x86,0x03,0x9C,0x03,0xF0,0x03,0xC0,0x07,0x80,0x06,0x00,0x0C,0x00,0x18,0x00,0x30,0x00,0x60,0x00,0xC0,0x01,0x80,0x03,0x00,0x06,0x00, // 'Y'
	0xFF,0xFD,0xFF,0xF8,0x00,0x60,0x01,0xC0,0x07,0x00,0x0C,0x00,0x30,0x00,0xC0,0x03,0x80,0x0E,0x00,0x18,0x00,0x60,0x01,0x80,0x07,0x00,0x1C,0x00,0x30,0x00,0xFF,0xFD,0xFF,0xF8, // 'Z'
	0xFB,0xEC,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x30,0xC3,0x0C,0x3E,0xF8, // '['
	0xC0,0x70,0x18,0x0C,0x06,0x01,0x80,0xC0,0x60,0x18,0x0C,0x06,0x03,0x00,0xC0,0x60,0x30,0x0C,0x06,0x03,0x01,0xC0,0x60, // '\'
	0xFB,0xE1,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0xBE,0xF8, // ']'
	0x03,0x80,0x07,0xC0,0x0E,0xE0,0x1C,0x70,0x38,0x38,0x70,0x1C,0xE0,0x0E, // '^'
	0xFF,0xF7,0xFF,0x80, // '_'
	0xE0,0x60,0x60,0x60, // '`'
	0x3F,0x07,0xFC,0x40,0xC0,0x06,0x00,0x61,0xFE,0x7F,0xEE,0x06,0xC0,0x6C,0x0E,0xE1,0xE7,0xFE,0x3E,0x60, // 'a'
	0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x67,0xC3,0xFF,0x1E,0x1C,0xE0,0x66,0x01,0xB0,0x0D,0x80,0x6C,0x03,0x60,0x1B,0x81,0x9E,0x1C,0xFF,0xC6,0x7C,0x00, // 'b'
	0x0F,0x87,0xF9,0xC1,0x30,0x0C,0x01,0x80,0x30,0x06,0x00,0xC0,0x0C,0x01,0xC1,0x1F,0xE1,0xF8, // 'c'
	0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0x03,0x0F,0x98,0xFF,0xCE,0x1E,0x60,0x76,0x01,0xB0,0x0D,0x80,0x6C,0x03,0x60,0x19,0x81,0xCE,0x1E,0x3F,0xF0,0xF9,0x80, // 'd'
	0x0F,0x81,0xFE,0x1C,0x38,0xC0,0x6C,0x03,0x7F,0xFB,0xFF,0xD8,0x00,0xC0,0x03,0x00,0x1C,0x08,0x7F,0xC0,0xFC,0x00, // 'e'
	0x0F,0x0F,0x8C,0x06,0x03,0x07,0xFB,0xFC,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x00, // 'f'
	0x1F,0x31,0xFF,0x9C,0x3D,0xC0,0xEC,0x03,0x60,0x1B,0x00,0xD8,0x06,0xC0,0x33,0x03,0x9C,0x3C,0x7F,0xE1,0xF3,0x00,0x18,0x01,0xC4,0x1C,0x3F,0xC0,0xFC,0x00, // 'g'
	0xC0,0x0C,0x00,0xC0,0x0C,0x00,0xC0,0x0C,0xF8,0xFF,0xCF,0x0E,0xE0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06, // 'h'
	0xDB,0x01,0xB6,0xDB,0x6D,0xB6,0xD8, // 'i'
	0x18,0x61,0x80,0x00,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x18,0x61,0x86,0x1B,0xCE,0x00, // 'j'
	0xC0,0x06,0x00,0x30,0x01,0x80,0x0C,0x00,0x60,0xE3,0x0E,0x18,0xE0,0xCE,0x06,0xE0,0x3E,0x01,0xF0,0x0D,0xC0,0x67,0x03,0x1C,0x18,0x70,0xC1,0xC6,0x07,0x00, // 'k'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xD8, // 'l'
	0xCF,0x87,0xC7,0xFE,0xFF,0x3C,0x3E,0x1D,0xC0,0xE0,0x6C,0x06,0x03,0x60,0x30,0x1B,0x01,0x80,0xD8,0x0C,0x06,0xC0,0x60,0x36,0x03,0x01,0xB0,0x18,0x0D,0x80,0xC0,0x6C,0x06,0x03,0x00, // 'm'
	0xCF,0x8F,0xFC,0xF0,0xEE,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x60, // 'n'
	0x1F,0x81,0xFE,0x1C,0x39,0xC0,0xCC,0x03,0x60,0x1B,0x00,0xD8,0x06,0xC0,0x37,0x03,0x1C,0x38,0x7F,0x81,0xF8,0x00, // 'o'
	0xCF,0x87,0xFE,0x3C,0x39,0xC0,0xCC,0x03,0x60,0x1B,0x00,0xD8,0x06,0xC0,0x37,0x03,0x3C,0x39,0xFF,0x8C,0xF8,0x60,0x03,0x00,0x18,0x00,0xC0,0x06,0x00,0x00, // 'p'
	0x1F,0x31,0xFF,0x9C,0x3C,0xC0,0xEC,0x03,0x60,0x1B,0x00,0xD8,0x06,0xC0,0x33,0x03,0x9C,0x3C,0x7F,0xE1,0xF3,0x00,0x18,0x00,0xC0,0x06,0x00,0x30,0x01,0x80, // 'q'
	0xCF,0x7F,0xBC,0x1C,0x0C,0x06,0x03,0x01,0x80,0xC0,0x60,0x30,0x18,0x0C,0x00, // 'r'
	0x3F,0x0F,0xF3,0x82,0x60,0x0C,0x01,0xF8,0x0F,0xC0,0x3E,0x00,0xC0,0x1A,0x07,0x7F,0xC7,0xF0, // 's'
	0x30,0x18,0x0C,0x06,0x0F,0xF7,0xF8,0xC0,0x60,0x30,0x18,0x0C,0x06,0x03,0x01,0x80,0xC0,0x7E,0x1F,0x00, // 't'
	0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x06,0xC0,0x6C,0x0E,0xE1,0xE7,0xFE,0x3E,0x60, // 'u'
	0xC0,0x19,0x80,0xC6,0x03,0x18,0x1C,0x30,0x60,0xC1,0x81,0x8E,0x06,0x30,0x18,0xC0,0x36,0x00,0xD8,0x03,0xE0,0x07,0x00, // 'v'
	0xC1,0xE0,0xD8,0x3C,0x19,0x87,0x86,0x30,0xF0,0xC6,0x33,0x18,0xE6,0x67,0x0C,0xCC,0xC1,0x99,0x98,0x36,0x1B,0x03,0xC3,0xC0,0x78,0x78,0x0F,0x0F,0x01,0xC0,0xE0, // 'w'
	0xE0,0x39,0xC1,0xC3,0x8E,0x06,0x30,0x0D,0x80,0x3E,0x00,0x70,0x03,0xE0,0x1D,0xC0,0x63,0x03,0x06,0x1C,0x1C,0xE0,0x38, // 'x'
	0xC0,0x19,0x80,0xC6,0x03,0x1C,0x1C,0x30,0x60,0xC3,0x81,0x8C,0x06,0x30,0x0D,0x80,0x36,0x00,0xF8,0x01,0xC0,0x07,0x00,0x18,0x00,0x60,0x03,0x00,0x7C,0x01,0xE0,0x00, // 'y'
	0xFF,0xEF,0xFE,0x00,0xC0,0x1C,0x03,0x80,0x70,0x0E,0x01,0xC0,0x38,0x07,0x00,0x60,0x0F,0xFE,0xFF,0xE0, // 'z'
	0x07,0x83,0xE0,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0C,0x07,0x0F,0x83,0xE0,0x1C,0x03,0x00,0xC0,0x30,0x0C,0x03,0x00,0xC0,0x30,0x0F,0x81,0xE0, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6D,0xB6, // '|'
	0xF0,0x3E,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x07,0x00,0xF8,0x3E,0x1C,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0xF8,0x3C,0x00 // '}'
};
const GFXglyph Dialog_plain_24Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   9,    0,    0 }, // ' '
	  {     1,   3,  18,  11,    4,  -18 }, // '!'
	  {     8,   7,   7,  12,    2,  -18 }, // '"'
	  {    15,  17,  18,  21,    2,  -18 }, // '#'
	  {    54,  12,  22,  16,    2,  -18 }, // '$'
	  {    87,  21,  18,  24,    1,  -18 }, // '%'
	  {   135,  17,  18,  20,    1,  -18 }, // '&'
	  {   174,   3,   7,   8,    2,  -18 }, // '''
	  {   177,   6,  21,  10,    2,  -18 }, // '('
	  {   193,   6,  21,  10,    2,  -18 }, // ')'
	  {   209,  12,  10,  13,    0,  -18 }, // '*'
	  {   224,  17,  16,  21,    3,  -16 }, // '+'
	  {   258,   4,   6,   9,    2,   -3 }, // ','
	  {   261,   7,   2,  10,    1,   -8 }, // '-'
	  {   263,   3,   3,   9,    3,   -3 }, // '.'
	  {   265,   9,  20,   9,    0,  -18 }, // '/'
	  {   288,  13,  18,  16,    2,  -18 }, // '0'
	  {   318,  11,  18,  16,    3,  -18 }, // '1'
	  {   343,  12,  18,  16,    2,  -18 }, // '2'
	  {   370,  13,  18,  16,    2,  -18 }, // '3'
	  {   400,  14,  18,  16,    1,  -18 }, // '4'
	  {   432,  12,  18,  16,    2,  -18 }, // '5'
	  {   459,  13,  18,  16,    2,  -18 }, // '6'
	  {   489,  12,  18,  16,    2,  -18 }, // '7'
	  {   516,  13,  18,  16,    2,  -18 }, // '8'
	  {   546,  13,  18,  16,    2,  -18 }, // '9'
	  {   576,   3,  12,   9,    3,  -12 }, // ':'
	  {   581,   4,  15,   9,    2,  -12 }, // ';'
	  {   589,  16,  13,  21,    3,  -14 }, // '<'
	  {   615,  16,   7,  21,    3,  -11 }, // '='
	  {   629,  16,  13,  21,    3,  -14 }, // '>'
	  {   655,  10,  18,  14,    2,  -18 }, // '?'
	  {   678,  22,  21,  25,    2,  -17 }, // '@'
	  {   736,  17,  18,  17,    0,  -18 }, // 'A'
	  {   775,  13,  18,  17,    2,  -18 }, // 'B'
	  {   805,  15,  18,  18,    1,  -18 }, // 'C'
	  {   839,  16,  18,  19,    2,  -18 }, // 'D'
	  {   875,  12,  18,  16,    2,  -18 }, // 'E'
	  {   902,  11,  18,  15,    2,  -18 }, // 'F'
	  {   927,  16,  18,  20,    1,  -18 }, // 'G'
	  {   963,  14,  18,  19,    2,  -18 }, // 'H'
	  {   995,   3,  18,   8,    2,  -18 }, // 'I'
	  {  1002,   7,  23,   8,   -2,  -18 }, // 'J'
	  {  1023,  15,  18,  17,    2,  -18 }, // 'K'
	  {  1057,  12,  18,  14,    2,  -18 }, // 'L'
	  {  1084,  17,  18,  22,    2,  -18 }, // 'M'
	  {  1123,  14,  18,  19,    2,  -18 }, // 'N'
	  {  1155,  17,  18,  20,    1,  -18 }, // 'O'
	  {  1194,  12,  18,  15,    2,  -18 }, // 'P'
	  {  1221,  17,  21,  20,    1,  -18 }, // 'Q'
	  {  1266,  14,  18,  18,    2,  -18 }, // 'R'
	  {  1298,  13,  18,  16,    2,  -18 }, // 'S'
	  {  1328,  15,  18,  16,    0,  -18 }, // 'T'
	  {  1362,  14,  18,  19,    2,  -18 }, // 'U'
	  {  1394,  17,  18,  17,    0,  -18 }, // 'V'
	  {  1433,  23,  18,  25,    1,  -18 }, // 'W'
	  {  1485,  16,  18,  18,    1,  -18 }, // 'X'
	  {  1521,  15,  18,  16,    0,  -18 }, // 'Y'
	  {  1555,  15,  18,  17,    1,  -18 }, // 'Z'
	  {  1589,   6,  21,  10,    2,  -18 }, // '['
	  {  1605,   9,  20,   9,    0,  -18 }, // '\'
	  {  1628,   6,  21,  10,    2,  -18 }, // ']'
	  {  1644,  16,   7,  21,    3,  -18 }, // '^'
	  {  1658,  13,   2,  13,    0,    4 }, // '_'
	  {  1662,   7,   4,  13,    2,  -19 }, // '`'
	  {  1666,  12,  13,  15,    1,  -13 }, // 'a'
	  {  1686,  13,  18,  16,    2,  -18 }, // 'b'
	  {  1716,  11,  13,  14,    1,  -13 }, // 'c'
	  {  1734,  13,  18,  16,    1,  -18 }, // 'd'
	  {  1764,  13,  13,  15,    1,  -13 }, // 'e'
	  {  1786,   9,  18,   9,    1,  -18 }, // 'f'
	  {  1807,  13,  18,  16,    1,  -13 }, // 'g'
	  {  1837,  12,  18,  16,    2,  -18 }, // 'h'
	  {  1864,   3,  18,   8,    2,  -18 }, // 'i'
	  {  1871,   6,  23,   8,   -1,  -18 }, // 'j'
	  {  1889,  13,  18,  15,    2,  -18 }, // 'k'
	  {  1919,   3,  18,   7,    2,  -18 }, // 'l'
	  {  1926,  21,  13,  25,    2,  -13 }, // 'm'
	  {  1961,  12,  13,  16,    2,  -13 }, // 'n'
	  {  1981,  13,  13,  15,    1,  -13 }, // 'o'
	  {  2003,  13,  18,  16,    2,  -13 }, // 'p'
	  {  2033,  13,  18,  16,    1,  -13 }, // 'q'
	  {  2063,   9,  13,  11,    2,  -13 }, // 'r'
	  {  2078,  11,  13,  13,    1,  -13 }, // 's'
	  {  2096,   9,  17,  10,    0,  -17 }, // 't'
	  {  2116,  12,  13,  16,    2,  -13 }, // 'u'
	  {  2136,  14,  13,  16,    1,  -13 }, // 'v'
	  {  2159,  19,  13,  21,    1,  -13 }, // 'w'
	  {  2190,  14,  13,  16,    1,  -13 }, // 'x'
	  {  2213,  14,  18,  16,    1,  -13 }, // 'y'
	  {  2245,  12,  13,  14,    1,  -13 }, // 'z'
	  {  2265,  10,  22,  16,    3,  -18 }, // '{'
	  {  2293,   3,  24,   9,    3,  -18 }, // '|'
	  {  2302,  10,  22,  16,    3,  -18 } // '}'
};
const GFXfont Dialog_plain_24 PROGMEM = {
(uint8_t  *)Dialog_plain_24Bitmaps,(GFXglyph *)Dialog_plain_24Glyphs,0x20, 0x7E, 29};