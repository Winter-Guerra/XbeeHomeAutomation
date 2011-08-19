/*
 * main.h
 *
 *  Created on: Aug 11, 2011
 *      Author: XtremD
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
extern "C" {
#include "aes.h"
} //This is a C lib not a CPP lib!
#include "WProgram.h" // Arduino!
#include "xbee-arduino-read-only/XBee.h"

extern "C" void __cxa_pure_virtual();

//******Configuration stuff******// (This should be in a header in the future.)
#define IS_THIS_A_DOOR 1
#define DEBUG_MODE 1

void cleanPayload();

void cleanRXPacket();

void randoPayload();

void sendAtCommand();

bool handleTXAftermath();




#endif /* MAIN_H_ */
