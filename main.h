/*
 * main.h
 *
 *  Created on: Aug 11, 2011
 *      Author: XtremD
 */

#ifndef MAIN_H_
#define MAIN_H_

//#include <stdlib.h>
//#include <stdio.h>
extern "C" {
#include "aes/aes.h"
} //This is a C lib not a CPP lib!
//#include "aes/aes.h"
#include "WProgram.h" //
#include "NewSoftSerial.h"
#include "XBee.h"


extern "C" void __cxa_pure_virtual();

//******Configuration stuff******// (This should be in a header in the future.)
#define IS_THIS_A_DOOR 1 //This should be in a configuration file header.
#define DEBUG_MODE 0

void cleanPayload();

void cleanRXPacket();

void randoPayload();

void sendAtCommand();




#endif /* MAIN_H_ */
