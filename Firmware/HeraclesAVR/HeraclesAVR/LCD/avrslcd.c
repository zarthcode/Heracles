/*
 * avrslcd.c
 *
 * Created: 7/28/2012 7:22:47 PM
 *  Author: Anthony Clay, ZarthCode LLC
 */
#include "avrslcd.h"
#include "global.h"

#include <avr/io.h>
#include <util/delay.h>

/// STDIO interface
static int lcd_putchar(char c, FILE *stream);

static FILE lcdstdout = FDEV_SETUP_STREAM(lcd_putchar, NULL, _FDEV_SETUP_WRITE);

void avrslcd_init(uint8_t set_function, uint8_t entry_mode, uint8_t on)
{

	// Ensure ENABLE is low
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_ENABLE));
	
	// Wait 20ms for startup
	_delay_ms(20);
	
	// Function set
	avrslcd_FunctionSet(1, 1, 0);
	
	// Display On
	avrslcd_Display(1, 0, 0);
	
	// Entry Mode
	avrslcd_SetEntryMode(1, 0);
	
	avrslcd_Clear();
	
	stdout = &lcdstdout;
	
}

void avrslcd_load_byte(uint8_t data)
{
	// Ensure ENABLE is low
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_ENABLE));
	
	// CLK low
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_CLK));	
	
	// Load data
	for(int bit=0; bit<8; bit++)
	{
		// Place data bit
		bit_write(data & 0x80, AVRSLCD_PORT, BIT(AVRSLCD_DATA));
		data = data << 1;		
		
		// Pulse clock
		bit_set(AVRSLCD_PORT, BIT(AVRSLCD_CLK));
		bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_CLK));
	}
	
	// Latch the data onto the register.
	bit_set(AVRSLCD_PORT, BIT(AVRSLCD_LATCH));
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_LATCH));

}


void avrslcd_send_cmd(void)
{
	
	// Set RS pin low
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_RS));
	
	// Set ENABLE high
	bit_set(AVRSLCD_PORT, BIT(AVRSLCD_ENABLE));
	
	// Wait 450nS
	_delay_us(1);
	
	// Lower ENABLE
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_ENABLE));
	
	
}


void avrslcd_send_char(void)
{
	
	// Ensure RS pin is high
	bit_set(AVRSLCD_PORT, BIT(AVRSLCD_RS));	
	
	// Set ENABLE high
	bit_set(AVRSLCD_PORT, BIT(AVRSLCD_ENABLE));
	
	// Wait 450nS
	_delay_us(1);
	
	// Lower ENABLE
	bit_clear(AVRSLCD_PORT, BIT(AVRSLCD_ENABLE));
	
}



void avrslcd_FunctionSet( uint8_t DL, uint8_t N, uint8_t F)
{
	// Initial command
	uint8_t data = _AVRSLCD_CMD_FUNCTION_SET;
	
	// font bit
	bit_write(F, data, BIT(2));
	
	// Number of lines
	bit_write(N, data, BIT(3));
	
	// data length
	bit_write(DL, data, BIT(4));
	
	// Load data
	avrslcd_load_byte(data);
	
	// Send cmd
	avrslcd_send_cmd();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
}

void avrslcd_Clear()
{
	
	avrslcd_load_byte(_AVRSLCD_CMD_CLEAR);
	
	avrslcd_send_cmd();
	
	// 1.52mS wait req'd.
	_delay_ms(2);
	
}

void avrslcd_ReturnHome()
{
	
	avrslcd_load_byte(_AVRSLCD_CMD_HOME);
	
	avrslcd_send_cmd();
	
	// 1.52mS wait req'd.
	_delay_ms(2);
	
}

void avrslcd_SetEntryMode( uint8_t bIncrement, uint8_t bShift )
{
	
	// Initial command
	uint8_t data = _AVRSLCD_CMD_SET_ENTRY_MODE;
	
	// Increment/Decrement
	bit_write(bIncrement, data, BIT(1));
	
	// Display Shift
	bit_write(bShift, data, BIT(0));
	
	// Load data
	avrslcd_load_byte(data);
	
	// Send cmd
	avrslcd_send_cmd();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
}

void avrslcd_Display(uint8_t bDisplayOn, uint8_t bCursorOn, uint8_t bBlink)
{

	// Initial command
	uint8_t data = _AVRSLCD_CMD_DISPLAY_ON;

	// display on
	bit_write(bDisplayOn, data, BIT(2));
	
	// cursor on
	bit_write(bCursorOn, data, BIT(1));
	
	// blink on
	bit_write(bBlink, data, BIT(0));
	
	// Load data
	avrslcd_load_byte(data);
	
	// Send cmd
	avrslcd_send_cmd();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
	
}

void avrslcd_CursorDisplayShift( uint8_t bDisplayShift, uint8_t bShiftRight )
{
	
	// Initial command
	uint8_t data = _AVRSLCD_CMD_DISPLAY_SHIFT;

	// display shift
	bit_write(bDisplayShift, data, BIT(3));
	
	// cursor on
	bit_write(bShiftRight, data, BIT(2));
	
	// Load data
	avrslcd_load_byte(data);
	
	// Send cmd
	avrslcd_send_cmd();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
	
}

void avrslcd_SetCGRAMAddress( uint8_t address )
{
	// Initial command
	uint8_t data = address;

	// Clear DB7
	bit_clear(data, BIT(7));
	
	// Set DB6
	bit_set(data, BIT(6));
	
	// Load data
	avrslcd_load_byte(data);
	
	// Send cmd
	avrslcd_send_cmd();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
}

void avrslcd_SetDDRAMAddress( uint8_t address )
{
	
	// Initial command
	uint8_t data = address;

	// Set DB7
	bit_set(data, BIT(7));
	
	// Load data
	avrslcd_load_byte(data);
	
	// Send cmd
	avrslcd_send_cmd();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
	
}


void avrslcd_MoveCursor(uint8_t row, uint8_t column)
{
	uint8_t address = 0;
	switch (row)
	{
	case 1:
		address = _AVRSLCD_LINE_1;
		break;
	case 2:
		address = _AVRSLCD_LINE_2;
		break;
	}
	
	address += column;
	
	avrslcd_SetDDRAMAddress(address);
	
}

void avrslcd_IncrementCursor(uint8_t spaces)
{
	
	while (spaces--)
	{
		avrslcd_CursorDisplayShift(0,1);
	}
	
}	

void avrslcd_DecrementCursor(uint8_t spaces)
{
	while (spaces--)
	{
		avrslcd_CursorDisplayShift(0,0);
	}
}

void avrslcd_putc(const char c)
{
	
	// Load data
	avrslcd_load_byte(c);
	
	// Send data
	avrslcd_send_char();
	
	// 37uS wait req'd.
	_delay_us(40);
	
	// Finished.
}


void avrslcd_puts(const char *s)
{
	const char *c = s;
	
	// Print until a null terminator is encountered.
	while(*c != '\0')
	{
		avrslcd_putc(*c);
		c++;	// No it's not!
	}
	
}



static int lcd_putchar( char c, FILE *stream )
{
	// Special character handling
	
	
	// Send character
	avrslcd_putc(c);
	return 0;
}
