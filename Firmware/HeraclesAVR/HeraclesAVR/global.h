/*
 * global.h
 *
 * Created: 7/21/2012 5:07:10 PM
 *  Author: Anthony Clay. ZarthCode LLC
 */ 


#pragma once

#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x)	(0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))

#define F_CPU 16000000UL

