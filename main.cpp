/*
 * main.c
 *
 *  Created on: Aug 8, 2011
 *      Author: XtremD
 */
//includes
#include "main.h" //include the headerfile!
extern "C" void __cxa_pure_virtual() {
	cli();
	for (;;)
		;
}

//****Universal varibles that both the door and key use****////
uint8_t xbeeRX = 2;
uint8_t xbeeTX = 3;
uint8_t xbeeRTS = 4; //Pull high to stop the XBee from sending more data to the Arduino through its output line. Must be enabled first.
uint8_t xbeeCTS = 5; //Is pulled high by the XBee when the XBee input UART line is 17 byte away from full.
uint8_t xbeeDTR = 6; //Pull high to force sleep mode.
uint8_t xbeeReset = 7; //Pull low to reset the XBee (Usually after a command session).

uint8_t payload[40]; //Payload buffer. Clean this promptly after using!!!!!
uint8_t recievedPayload[40]; //Buffer for the recieved data. Clean promptly after using!


//structuring the devices. A device object will have three things, a 64bit address,
//encryption key, signing key and device type

struct xbeeDevice_t {
	  uint32_t lowByte;
	  uint32_t highbyte;
	  uint8_t encKey[16];
	  uint8_t deviceType;
	} xbeeDevices[3];


	/*
//Key storage in two dimensions!
uint8_t keys[10] [16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab,
		0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c}; //Ten keys that are each 128bits long.
//For testing purposes we will auto define a master preshared key.

uint16_t addresses[10] = {0x1000,0x5000,0x5001}

uint8_t randomData[16] = { 0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31,
			0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34 };
*/
String thingsToSay[3] = { //This should be in Progmem
		"Hello world!", "I see you!", "Are you still there?" }; //little testing things.....

//XBee AT commands. USE PROGMEM TO SAVE SPACE!
uint8_t ATMY[] = { 'M', 'Y' };
uint8_t ATWR[] = { 'W', 'R' };

//*****Addresses based on the uploaded configuration file*****//
#if IS_THIS_A_DOOR //This Arduino is acting as the door. Configure the addresses!
uint16_t myself = 0x1000; //my address //This should probably be random and automatically uploaded to the Keys
uint16_t key1 = 0x5000, key2 = 0x5001; //This should probably be random and automatically uploaded to the Keys

#else //****We are acting as the Key!******//
uint16_t myself = 0x5000; //This should probably be random and automatically uploaded to the Keys
uint16_t door1 = 0x1000, door2 = 0x1001;//This should probably be random and automatically uploaded to the Keys
#endif

uint8_t myself8[] = { highByte(myself), lowByte(myself) }; //A array for autoconfiging the XBee address.

//*****Reusable Instances!!******//
//NewSoftSerial nss(xbeeRX, xbeeTX); //Instantiate a new NewSoftSerial instance for the XBee.
XBee xbee = XBee(); //Instantiate a new xbee instance
TxStatusResponse txStatus = TxStatusResponse();
AtCommandRequest atRequest = AtCommandRequest(ATMY);
AtCommandResponse atResponse = AtCommandResponse();



//******MAIN LOOP***************//

int main(void) {

	/* Must call init for arduino to work properly */
	init();
	//Enter COPIED CODE!
	Serial1.begin(9600);
	//xbee.setSerial(Serial1); //set the xbee to use Serialport 1
	//xbee.begin(9600); //start communication with the xbee

	randomSeed(analogRead(0)); //IN THE FUTURE USE THE TRUERANDOM LIBRARY!

	//***Start debugging serialprint***//
#if DEBUG_MODE
	Serial.begin(9600); //Start the debugging prompt.
	Serial.println("Hello World! Setting up the Xbee modems to their corresponding addresses.");//USE PROGMEM!!!!
	delay(5000); //Wait for the XBee to initialize.
	//**Setup address logs if we are in debugmode**//

	atRequest = AtCommandRequest(ATMY, myself8, sizeof(myself8));
	sendAtCommand();//Send the command

	atRequest = AtCommandRequest(ATWR);
	sendAtCommand();

		Serial.println("Hello World!");
		Serial.println("Starting handshake");
#endif

	//Something inits the handshake

	//the master inits the connection with a broadcast challenge to all (listed) XBee devices

	//The slave checks the sender address and responds with a random challenge using a preshared key (enc'ed and signed)

	//The door decs the packet and checks the sig using the key to make sure everything is allright

	//The door either hashes or XORs the dec'ed packet using its key before

	//Random data function belongs here!

/*
	aes128_ctx_t ctx;
	aes128_init(keys, &ctx);
	//cli_putstr_P(PSTR("\r\n\r\n cipher test (FIPS 197):\r\n key:        "));
	//cli_hexdump(key, 16);
	//cli_putstr_P(PSTR("\r\n plaintext:  "));
	//cli_hexdump(data, 16);
	for (int i = 0; i < 16; i++) { //PlainText
		Serial.print(randomData[i], HEX);
	}
	Serial.println();
	aes128_enc(randomData, &ctx);
	//cli_putstr_P(PSTR("\r\n ciphertext: "));
	//cli_hexdump(data, 16);
	for (int i = 0; i < 16; i++) { //Ciphertext
		Serial.print(randomData[i], HEX);
	}
	Serial.println();
	aes128_dec(randomData, &ctx);
	//cli_putstr_P(PSTR("\r\n plaintext:  "));
	//cli_hexdump(data, 16);
	for (int i = 0; i < 16; i++) { //Decoded ciphertext
		Serial.print(randomData[i], HEX);
	}
	Serial.println();
	*/
	Serial.print("Done Encrypting!");
	for (;;) {
		/****************************/
		/*** -----MAIN LOOP------ ***/
		/****************************/

		delay(100); //Just do nothing!

#if IS_THIS_A_DOOR
		randoPayload(); //building payload
		Serial.println("Building and sending packet!");
		Tx16Request tx = Tx16Request(key1, payload, sizeof(payload)); //Build the txPacket
		xbee.send(tx); //Fire ze missiles!
		handleTXAftermath();

		delay(1000);
#endif
	} // end for

	return 0;
}

void cleanPayload() {
	for (int i = 0; i < 40; i++) {
		//clean the packet!
		payload[i] = '\0';
	}
}

void cleanRXPacket() {
	for (int i = 0; i < 40; i++) {
		//clean the packet!
		recievedPayload[i] = '\0';
	}
}

void randoPayload() {
	cleanPayload(); //clean it!
	uint8_t selection = random(0, 3); //get our payload selection
	thingsToSay[selection].getBytes((unsigned char*)payload, (unsigned int) 40); //copy the string to the payload byte by byte
}

void sendAtCommand() {
#if DEBUG_MODE
	Serial.println("Sending command to the XBee"); //Debug
#endif
	xbee.send(atRequest); //Send the command packet.
	// wait up to 5 seconds for the status response
	if (xbee.readPacket(5000)) {
		// got a response!

		// should be an AT command response
		if (xbee.getResponse().getApiId() == AT_COMMAND_RESPONSE) {
			xbee.getResponse().getAtCommandResponse(atResponse);

			if (atResponse.isOk()) {
				Serial.print("Command [");
				Serial.print(atResponse.getCommand()[0]);
				Serial.print(atResponse.getCommand()[1]);
				Serial.println("] was successful!");

				if (atResponse.getValueLength() > 0) {
					Serial.print("Command value length is ");
					Serial.println(atResponse.getValueLength(), DEC);

					Serial.print("Command value: ");

					for (int i = 0; i < atResponse.getValueLength(); i++) {
						Serial.print(atResponse.getValue()[i], HEX);
						Serial.print(" ");
					}

					Serial.println("");
				}
			} else {
				Serial.print("Command return error code: ");
				Serial.println(atResponse.getStatus(), HEX);
			}
		} else {
			Serial.print("Expected AT response but got ");
			Serial.print(xbee.getResponse().getApiId(), HEX);
		}
	} else {
		// at command failed
		if (xbee.getResponse().isError()) {
			Serial.print("Error reading packet.  Error code: ");
			Serial.println(xbee.getResponse().getErrorCode());
		} else {
			Serial.print("No response from radio");
		}
	}
}

bool handleTXAftermath() {
	bool returnStatus = false;
	// after sending a TX request, we expect a status response
	// wait up to 1 seconds for the status response
	if (xbee.readPacket(1000)) {
		// got a response!
		// should be a znet tx status
		if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
			xbee.getResponse().getZBTxStatusResponse(txStatus);

			// get the delivery status, the fifth byte
			if (txStatus.getStatus() == SUCCESS) {
				// success.  time to celebrate
				Serial.println("Packet sent with ACK!");
				returnStatus = true;
			} else {
				// the remote XBee did not receive our packet. is it powered on?
				Serial.println("Packet transmission failed.....");
				returnStatus = false;
			}
		}
	} else {
		// local XBee did not provide a timely TX Status Response -- should not happen
		Serial.println("Wait, WTF? The Xbee did not respond!!!!");
		returnStatus = false;
	}
	cleanPayload();
	cleanRXPacket();
	return returnStatus;
}

