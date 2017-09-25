/*
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 * 
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 * 
 *    This permission notice shall be included in all copies or 
 *    substantial portions of the Software.
 * 
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef LedControl_h
#define LedControl_h

//#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/* here's the character table */
PROGMEM const unsigned char CH[] = {
    3, 8, B0000000, B0000000, B0000000, B0000000, B0000000, // space
    1, 8, B1011111, B0000000, B0000000, B0000000, B0000000, // !
    3, 8, B0000011, B0000000, B0000011, B0000000, B0000000, // "
    5, 8, B0010100, B0111110, B0010100, B0111110, B0010100, // #
    4, 8, B0100100, B1101010, B0101011, B0010010, B0000000, // $
    5, 8, B1100011, B0010011, B0001000, B1100100, B1100011, // %
    5, 8, B0110110, B1001001, B1010110, B0100000, B1010000, // &
    1, 8, B0000011, B0000000, B0000000, B0000000, B0000000, // '
    3, 8, B0011100, B0100010, B1000001, B0000000, B0000000, // (
    3, 8, B1000001, B0100010, B0011100, B0000000, B0000000, // )
    5, 8, B0101000, B0011000, B0001110, B0011000, B0101000, // * 
    5, 8, B0001000, B0001000, B0111110, B0001000, B0001000, // +
    2, 8, B10110000, B1110000, B0000000, B0000000, B0000000, // ,
    4, 8, B0001000, B0001000, B0001000, B0001000, B0000000, // -
    2, 8, B1100000, B1100000, B0000000, B0000000, B0000000, // .
    4, 8, B1100000, B0011000, B0000110, B0000001, B0000000, // /
    4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // 0
    3, 8, B1000010, B1111111, B1000000, B0000000, B0000000, // 1
    4, 8, B1100010, B1010001, B1001001, B1000110, B0000000, // 2
    4, 8, B0100010, B1000001, B1001001, B0110110, B0000000, // 3
    4, 8, B0011000, B0010100, B0010010, B1111111, B0000000, // 4
    4, 8, B0100111, B1000101, B1000101, B0111001, B0000000, // 5
    4, 8, B0111110, B1001001, B1001001, B0110000, B0000000, // 6
    4, 8, B1100001, B0010001, B0001001, B0000111, B0000000, // 7
    4, 8, B0110110, B1001001, B1001001, B0110110, B0000000, // 8
    4, 8, B0000110, B1001001, B1001001, B0111110, B0000000, // 9
    2, 8, B01010000, B0000000, B0000000, B0000000, B0000000, // :
    2, 8, B10000000, B01010000, B0000000, B0000000, B0000000, // ;
    3, 8, B0010000, B0101000, B1000100, B0000000, B0000000, // <
    3, 8, B0010100, B0010100, B0010100, B0000000, B0000000, // =
    3, 8, B1000100, B0101000, B0010000, B0000000, B0000000, // >
    4, 8, B0000010, B1011001, B0001001, B0000110, B0000000, // ?
    5, 8, B0111110, B1001001, B1010101, B1011101, B0001110, // @
    4, 8, B1111110, B0010001, B0010001, B1111110, B0000000, // A
    4, 8, B1111111, B1001001, B1001001, B0110110, B0000000, // B
    4, 8, B0111110, B1000001, B1000001, B0100010, B0000000, // C
    4, 8, B1111111, B1000001, B1000001, B0111110, B0000000, // D
    4, 8, B1111111, B1001001, B1001001, B1000001, B0000000, // E
    4, 8, B1111111, B0001001, B0001001, B0000001, B0000000, // F
    4, 8, B0111110, B1000001, B1001001, B1111010, B0000000, // G
    4, 8, B1111111, B0001000, B0001000, B1111111, B0000000, // H
    3, 8, B1000001, B1111111, B1000001, B0000000, B0000000, // I
    4, 8, B0110000, B1000000, B1000001, B0111111, B0000000, // J
    4, 8, B1111111, B0001000, B0010100, B1100011, B0000000, // K
    4, 8, B1111111, B1000000, B1000000, B1000000, B0000000, // L
    5, 8, B1111111, B0000010, B0001100, B0000010, B1111111, // M
    5, 8, B1111111, B0000100, B0001000, B0010000, B1111111, // N
    4, 8, B0111110, B1000001, B1000001, B0111110, B0000000, // O
    4, 8, B1111111, B0001001, B0001001, B0000110, B0000000, // P
    4, 8, B0111110, B1000001, B1000001, B10111110, B0000000, // Q
    4, 8, B1111111, B0001001, B0001001, B1110110, B0000000, // R
    4, 8, B1000110, B1001001, B1001001, B0110010, B0000000, // S
    5, 8, B0000001, B0000001, B1111111, B0000001, B0000001, // T
    4, 8, B0111111, B1000000, B1000000, B0111111, B0000000, // U
    5, 8, B0001111, B0110000, B1000000, B0110000, B0001111, // V
    5, 8, B0111111, B1000000, B0111000, B1000000, B0111111, // W
    5, 8, B1100011, B0010100, B0001000, B0010100, B1100011, // X
    5, 8, B0000111, B0001000, B1110000, B0001000, B0000111, // Y
    4, 8, B1100001, B1010001, B1001001, B1000111, B0000000, // Z
    2, 8, B1111111, B1000001, B0000000, B0000000, B0000000, // [
    4, 8, B0000001, B0000110, B0011000, B1100000, B0000000, // backslash
    2, 8, B1000001, B1111111, B0000000, B0000000, B0000000, // ]
    3, 8, B0000010, B0000001, B0000010, B0000000, B0000000, // hat
    4, 8, B1000000, B1000000, B1000000, B1000000, B0000000, // _
    2, 8, B0000001, B0000010, B0000000, B0000000, B0000000, // `
    4, 8, B0100000, B1010100, B1010100, B1111000, B0000000, // a
    4, 8, B1111111, B1000100, B1000100, B0111000, B0000000, // b
    4, 8, B0111000, B1000100, B1000100, B0000000, B0000000, // c // JFM MOD.
    4, 8, B0111000, B1000100, B1000100, B1111111, B0000000, // d
    4, 8, B0111000, B1010100, B1010100, B0011000, B0000000, // e
    3, 8, B0000100, B1111110, B0000101, B0000000, B0000000, // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B0000000, // g
    4, 8, B1111111, B0000100, B0000100, B1111000, B0000000, // h
    3, 8, B1000100, B1111101, B1000000, B0000000, B0000000, // i
    4, 8, B1000000, B10000000, B10000100, B1111101, B0000000, // j
    4, 8, B1111111, B0010000, B0101000, B1000100, B0000000, // k
    3, 8, B1000001, B1111111, B1000000, B0000000, B0000000, // l
    5, 8, B1111100, B0000100, B1111100, B0000100, B1111000, // m
    4, 8, B1111100, B0000100, B0000100, B1111000, B0000000, // n
    4, 8, B0111000, B1000100, B1000100, B0111000, B0000000, // o
    4, 8, B11111100, B0100100, B0100100, B0011000, B0000000, // p
    4, 8, B0011000, B0100100, B0100100, B11111100, B0000000, // q
    4, 8, B1111100, B0001000, B0000100, B0000100, B0000000, // r
    4, 8, B1001000, B1010100, B1010100, B0100100, B0000000, // s
    3, 8, B0000100, B0111111, B1000100, B0000000, B0000000, // t
    4, 8, B0111100, B1000000, B1000000, B1111100, B0000000, // u
    5, 8, B0011100, B0100000, B1000000, B0100000, B0011100, // v
    5, 8, B0111100, B1000000, B0111100, B1000000, B0111100, // w
    5, 8, B1000100, B0101000, B0010000, B0101000, B1000100, // x
    4, 8, B10011100, B10100000, B10100000, B1111100, B0000000, // y
    3, 8, B1100100, B1010100, B1001100, B0000000, B0000000, // z
    3, 8, B0001000, B0110110, B1000001, B0000000, B0000000, // {
    1, 8, B1111111, B0000000, B0000000, B0000000, B0000000, // |
    3, 8, B1000001, B0110110, B0001000, B0000000, B0000000, // }
    4, 8, B0001000, B0000100, B0001000, B0000100, B0000000, // ~
};

/*
 * Segments to be switched on for characters and digits on
 * 7-Segment Displays
 */
const static byte charTable [] PROGMEM  = {
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B10000000,B00000001,B10000000,B00000000,
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00000000,B00000000,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00010101,B00011101,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};

class LedControl {
    private :
        /* The array for shifting the data to the devices */
        byte spidata[16];
        /* Send out a single command to the device */
        void spiTransfer(int addr, byte opcode, byte data);

        /* We keep track of the led-status for all 8 devices in this array */
        byte status[64];
        /* Data is shifted out of this pin*/
        int SPI_MOSI;
        /* The clock is signaled on this pin */
        int SPI_CLK;
        /* This one is driven LOW for chip selectzion */
        int SPI_CS;
        /* The maximum number of devices we use */
        int maxDevices;

        bool invert;

    public:
        /* 
         * Create a new controler 
         * Params :
         * dataPin		pin on the Arduino where data gets shifted out
         * clockPin		pin for the clock
         * csPin		pin for selecting the device 
         * numDevices	maximum number of devices that can be controled
         */
        LedControl(int dataPin, int clkPin, int csPin, int numDevices=1, bool inv=false);

        /*
         * Gets the number of devices attached to this LedControl.
         * Returns :
         * int	the number of devices on this LedControl
         */
        int getDeviceCount();

        /* 
         * Set the shutdown (power saving) mode for the device
         * Params :
         * addr	The address of the display to control
         * status	If true the device goes into power-down mode. Set to false
         *		for normal operation.
         */
        void shutdown(int addr, bool status);

        /* 
         * Set the number of digits (or rows) to be displayed.
         * See datasheet for sideeffects of the scanlimit on the brightness
         * of the display.
         * Params :
         * addr	address of the display to control
         * limit	number of digits to be displayed (1..8)
         */
        void setScanLimit(int addr, int limit);

        /* 
         * Set the brightness of the display.
         * Params:
         * addr		the address of the display to control
         * intensity	the brightness of the display. (0..15)
         */
        void setIntensity(int addr, int intensity);

        /* 
         * Switch all Leds on the display off. 
         * Params:
         * addr	address of the display to control
         */
        void clearDisplay(int addr);

        /*
         * redraw the display; used after setting status array
         *
         */
        void refreshDisplay(int addr);

        /* 
         * Set the status of a single Led.
         * Params :
         * addr	address of the display 
         * row	the row of the Led (0..7)
         * col	the column of the Led (0..7)
         * state	If true the led is switched on, 
         *		if false it is switched off
         */
        void setLed(int addr, int row, int col, boolean state);

        /* 
         * Set all 8 Led's in a row to a new state
         * Params:
         * addr	address of the display
         * row	row which is to be set (0..7)
         * value	each bit set to 1 will light up the
         *		corresponding Led.
         */
        void setRow(int addr, int row, byte value);

        /* 
         * Set all 8 Led's in a column to a new state
         * Params:
         * addr	address of the display
         * col	column which is to be set (0..7)
         * value	each bit set to 1 will light up the
         *		corresponding Led.
         */
        void setColumn(int addr, int col, byte value);

        /* 
         * Display a hexadecimal digit on a 7-Segment Display
         * Params:
         * addr	address of the display
         * digit	the position of the digit on the display (0..7)
         * value	the value to be displayed. (0x00..0x0F)
         * dp	sets the decimal point.
         */
        void setDigit(int addr, int digit, byte value, boolean dp);

        /* 
         * Display a character on a 7-Segment display.
         * There are only a few characters that make sense here :
         *	'0','1','2','3','4','5','6','7','8','9','0',
         *  'A','b','c','d','E','F','H','L','P',
         *  '.','-','_',' ' 
         * Params:
         * addr	address of the display
         * digit	the position of the character on the display (0..7)
         * value	the character to be displayed. 
         * dp	sets the decimal point.
         */
        void setChar(int addr, int digit, char value, boolean dp);

        void shiftUppish(bool rotate);
        void shiftLeft(bool rotate);
        void shiftRight(bool rotate);
        void writeLeft(char c, int delaytime);
        byte *getStatus(void);
};

#endif	//LedControl.h
