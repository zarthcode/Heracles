/*
 * jtag.c
 *
 * Created: 7/31/2012 10:46:38 PM
 *  Author: Anthony
 */ 

#include "jtag.h"


// Static global that contains the target device's TAP state.
static JTAGState currentState = RunTestIdle;
static uint8_t unknownState = 1;


