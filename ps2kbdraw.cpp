/*
  build from 
  
  PS2Keyboard.cpp - PS2Keyboard library
  Copyright (c) 2007 Free Software Foundation.  All right reserved.
  Written by Christian Weichel <info@32leaves.net>

  ** Mostly rewritten Paul Stoffregen <paul@pjrc.com>, June 2010
  ** Modified for use beginning with Arduino 13 by L. Abraham Smith, <n3bah@microcompdesign.com> * 
  ** Modified for easy interrup pin assignement on method begin(datapin,irq_pin). Cuningan <cuninganreset@gmail.com> **
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif
#include "ps2kbdraw.h"
#include "binary.h"
#include "debug.h"
typedef uint8_t boolean;
typedef uint8_t byte;

#define BUFFER_SIZE 45
static volatile uint8_t buffer[BUFFER_SIZE];
static volatile uint8_t head, tail;
static uint8_t ps2Keyboard_DataPin;
static int  ps2Keyboard_CharBuffer=0;
static volatile  uint8_t flag_release = 0; //  bool flag_release = false; 
static volatile  uint8_t flag_shift = 0;

// The ISR for the external interrupt
void ps2interrupt(void)
{
	static uint8_t bitcount=0;
	static uint8_t incoming=0;
	static uint32_t prev_ms=0;
	uint32_t now_ms;
	uint8_t n, val;

	val = digitalRead(ps2Keyboard_DataPin);
	now_ms = millis();
	if (now_ms - prev_ms > 250) {
		bitcount = 0;
		incoming = 0;
	}
	prev_ms = now_ms;
	n = bitcount - 1;
	if (n <= 7) {
		incoming |= (val << n);
	}
	bitcount++;
	if (bitcount == 11) {
		uint8_t i = head + 1;
		if (i >= BUFFER_SIZE) i = 0;
		if (i != tail) {
			buffer[i] = incoming;
			head = i;
		}
		bitcount = 0;
		incoming = 0;
	}
}

static inline uint8_t get_scan_code(void)
{
	uint8_t c, i;
	i = tail;
	if (i == head) return 0;
	i++;
	if (i >= BUFFER_SIZE) i = 0;
	c = buffer[i];
	tail = i;
	return c;
}



static int get_code(void) {
	static uint8_t state=0;
	int s;
	while (1) {
		s = get_scan_code();
		if (!s) return 0; 
//		return 	kbdmap[s];
		if (flag_release  ) { 
			flag_release =0 ;
			flag_shift =0 ; 
			return 0;
   		} else {    
 			if (s == 240 )  { 
				flag_release = 1;
				flag_shift =0 ; 	
				return 0;
   			} else { 
				if (s == 224 ) {   
					flag_shift = 1; 
					return 0;
				} else 	{
  
                                          if (s == 18) { 
                                         /* 
                                        Le code 18 apparait quelques fois quand on appuye 
                                        sur la touche 224/125 après avoir appué sur la touche 119.
                                        Comme la touche 18 n'est pas cablé, le code est simplement ignoré.
                                        */ 
                                         return 0;
                                        } else { 
					s=s+flag_shift*120;
					return 	s;
                                        }
				}
			}
			
		}
	}
}

bool PS2Keyboard::available() {
	if (ps2Keyboard_CharBuffer) return true;
	ps2Keyboard_CharBuffer = get_code();
	if (ps2Keyboard_CharBuffer) return true;
	return false;
}

int PS2Keyboard::read() {
int result;

	result = ps2Keyboard_CharBuffer;
	if (result) {
		ps2Keyboard_CharBuffer = 0;
	} else {
		result = get_code();
	}
	if (!result) return -1;
	return result;
}

PS2Keyboard::PS2Keyboard() {
  // nothing to do here, begin() does it all
}

void PS2Keyboard::begin(uint8_t dataPin, uint8_t irq_pin) {
  debugln("init PS2");
  uint8_t irq_num=0;

  ps2Keyboard_DataPin = dataPin;

  // initialize the pins

  pinMode(irq_pin, INPUT_PULLUP);
  pinMode(dataPin, INPUT_PULLUP);

  
  switch(irq_pin) {
    #ifdef CORE_INT0_PIN
    case CORE_INT0_PIN:
      irq_num = 0;
      break;
    #endif
    #ifdef CORE_INT1_PIN
    case CORE_INT1_PIN:
      irq_num = 1;
      break;
    #endif
    #ifdef CORE_INT2_PIN
    case CORE_INT2_PIN:
      irq_num = 2;
      break;
    #endif
    #ifdef CORE_INT3_PIN
    case CORE_INT3_PIN:
      irq_num = 3;
      break;
    #endif
    #ifdef CORE_INT4_PIN
    case CORE_INT4_PIN:
      irq_num = 4;
      break;
    #endif
    #ifdef CORE_INT5_PIN
    case CORE_INT5_PIN:
      irq_num = 5;
      break;
    #endif
    #ifdef CORE_INT6_PIN
    case CORE_INT6_PIN:
      irq_num = 6;
      break;
    #endif
    #ifdef CORE_INT7_PIN
    case CORE_INT7_PIN:
      irq_num = 7;
      break;
    #endif
    default:
      irq_num = 0;
      break;
  }
  head = 0;
  tail = 0;
  attachInterrupt(irq_num, ps2interrupt, FALLING);
}



