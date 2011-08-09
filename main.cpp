/*
 * main.c
 *
 *  Created on: Aug 8, 2011
 *      Author: XtremD
 */
//includes
#include <stdlib.h>
extern "C" {
#include "aes/aes.h"
}
//#include "aes/aes.h"
#include "Arduino Cores/WProgram.h"


extern "C" void __cxa_pure_virtual()
{
  cli();
  for (;;);
}

int main(void) {
//Main

	/* Must call init for arduino to work properly */
	  init();
	  Serial.begin(9600);
	  Serial.println("Hello World!");
	  uint8_t key[16] = { 0x2b, 0x7e, 0x15, 0x16,
	  		                    0x28, 0xae, 0xd2, 0xa6,
	  		                    0xab, 0xf7, 0x15, 0x88,
	  		                    0x09, 0xcf, 0x4f, 0x3c };
	  		uint8_t data[16] = { 0x32, 0x43, 0xf6, 0xa8,
	  		                     0x88, 0x5a, 0x30, 0x8d,
	  		                     0x31, 0x31, 0x98, 0xa2,
	  		                     0xe0, 0x37, 0x07, 0x34 };
	  		aes128_ctx_t ctx;
	  		aes128_init(key, &ctx);
	  		//cli_putstr_P(PSTR("\r\n\r\n cipher test (FIPS 197):\r\n key:        "));
	  		//cli_hexdump(key, 16);
	  		//cli_putstr_P(PSTR("\r\n plaintext:  "));
	  		//cli_hexdump(data, 16);
	  		for (int i = 0; i < 16; i++) { //PlainText
	  			Serial.print(data[i], HEX);
	  		}
	  		Serial.println();
	  		aes128_enc(data, &ctx);
	  		//cli_putstr_P(PSTR("\r\n ciphertext: "));
	  		//cli_hexdump(data, 16);
	  		for (int i = 0; i < 16; i++) { //Ciphertext
	  			  			Serial.print(data[i], HEX);
	  		}
	  		Serial.println();
	  		aes128_dec(data, &ctx);
	  		//cli_putstr_P(PSTR("\r\n plaintext:  "));
	  		//cli_hexdump(data, 16);
	  		for (int i = 0; i < 16; i++) { //Decoded ciphertext
	  			  			Serial.print(data[i],HEX);
	  		}
	  		Serial.println();
	  		Serial.print("Done Encrypting!");
	  for (;;) {
		  	  delay(100);//Just do nothing!
	    /****************************/
	    /*** write main loop here ***/
	    /****************************/

	  } // end for


return 0;
}
