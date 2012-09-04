/*
 * avrslcd.h
 *
 * Created: 7/28/2012 2:27:20 PM
 *  Author: Anthony Clay, ZarthCode LLC
 */ 

#pragma once

#include <stdint.h>
#include <stdio.h>

/* default pin settings */
#ifndef AVRSLCD_CUSTOM

// 74**595 Input Pins
#define AVRSLCD_PORT		PORTD
#define AVRSLCD_DATA		2
#define AVRSLCD_CLK			3
#define AVRSLCD_LATCH		4
#define AVRSLCD_RS			5
#define AVRSLCD_ENABLE		6

// 74**595 endianness



// Display Properties
#define AVRSLCD_LINES		2
#define AVRSLCD_COLS		16

#endif

/* LCD commands */
#define _AVRSLCD_CMD_CLEAR			0x01	// clear display, home
#define _AVRSLCD_CMD_HOME			0x02	// return home
#define _AVRSLCD_CMD_SET_ENTRY_MODE	0x04	// set entry mode
#define _AVRSLCD_CMD_DISPLAY_ON		0x08	// display/cursor/blink
#define _AVRSLCD_CMD_DISPLAY_SHIFT   0x10    // cursor/display shift
#define _AVRSLCD_CMD_FUNCTION_SET    0x20    // Function Set

/* Line addresses */
#define _AVRSLCD_LINE_1              0x00 /* bit 7 is always set: 0x80 = 0x00 */
#define _AVRSLCD_LINE_2              0x40 /* 2nd line at position 40 */
// Implement lines 3 and 4


/* Internal functions */

void avrslcd_init(uint8_t, uint8_t, uint8_t);

void avrslcd_load_byte(uint8_t data);

void avrslcd_send_cmd(void);
void avrslcd_send_char(void);


void avrslcd_MoveCursor(uint8_t row, uint8_t column);
void avrslcd_IncrementCursor(uint8_t spaces);
void avrslcd_DecrementCursor(uint8_t spaces);

/// Write single character to DDRAM
void avrslcd_putc(const char c);

/// Write a string
void avrslcd_puts(const char *s);



/* LCD Instructions */

// Clears entire display and sets DDRAM to address 0 in counter
void avrslcd_Clear();				

void avrslcd_ReturnHome();			// Sets DDRAM address to 0; Returns shift to orig position, DDRAM contents left unchanged.

/// Sets cursor move dir and specifies display shift.
void avrslcd_SetEntryMode(	uint8_t bIncrement, /* 1 = increment, 0 = decrement */
							uint8_t bShift /* Enable display shift during write */
							);
/// Sets entire display on/off, cursor on/off, blinking of cursor position char.
void avrslcd_Display(uint8_t bDisplayOn, uint8_t bCursorOn, uint8_t bBlink);	

/// Moves cursor and shifts display without changing DDRAM contents.
void avrslcd_CursorDisplayShift(uint8_t bDisplayShift,	// 1: Shift Display 0: Cursor Move
								uint8_t bShiftRight		// 1: Right 0: Left
								);

/// Sets interface data length, number of lines, and character font
void avrslcd_FunctionSet(uint8_t DL,	/* Datalength 0 = 4bit, 1 = 8bit */
						uint8_t N,		/* Number of lines 0 = 1 line, 1 = 2 lines */
						uint8_t F		/* Font 0 5x8 dots, 1 = 5x10 dots */
						);

///  Set 6-bit CGRAM address counter
void avrslcd_SetCGRAMAddress(uint8_t address);

/// Set 7-bit DDRAM address counter
void avrslcd_SetDDRAMAddress(uint8_t address);

/// Not implemented
uint8_t avrslcd_CheckReadBusy();

void avrslcd_WriteData(uint8_t data);					// Writes data into DDRAM or CGRAM.

void avrslcd_ReadData();					// Reads data from DDRAM or CGRAM.