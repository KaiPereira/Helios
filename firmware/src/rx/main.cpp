#include "RadioConfig.h"

volatile bool receivedFlag = false;

void setFlag(void) {
	receivedFlag = true;
}

void setup() {
	Serial.begin(115200);

	while (!Serial && millis() < 5000); // Serial takes a minute to enumerate

	radio.tcxoVoltage = 0; // Using an external crystal so set to 0V

	Serial.print(F("[SX1262] Starting Up..."));

	config.frequency = 915; // 915 for America/US
	
	int state = radio.begin(config);

	if (state == RADIOLIB_ERR_NONE) {
		Serial.println(F("Success!"));
	} else {
		Serial.print(F("Failed!"));
		Serial.println(state);
	}

	radio.setDio2AsRfSwitch(true); // Sets the RF switch to receive
	radio.setPacketReceivedAction(setFlag);

	Serial.print(F("[SX1262] Listening..."));
	state = radio.startReceive();

	if (state == RADIOLIB_ERR_NONE) {
		Serial.println(F("Success!"));
	} else {
		Serial.print(F("Failed!"));
		Serial.println(state);
	}
}

void loop() {
	if (receivedFlag) {
		receivedFlag = false;

		String str;
		int state = radio.readData(str); // Reads data into the str

		if (state == RADIOLIB_ERR_NONE) {
			Serial.print(F("[SX1262] Receiving: "));
			Serial.println(str);

			Serial.print(F("  RSSI: "));
			Serial.print(radio.getRSSI());
			Serial.println(F(" dBm"));

			Serial.print(F("  SNR:  "));
			Serial.print(radio.getSNR());
			Serial.println(F(" dB"));
		} else if (state == RADIOLIB_ERR_CRC_MISMATCH) {
			Serial.println(F("[SX1262] Packet Corrupted"));
		} else {
			Serial.print(F("[SX1262] Failed: "));
			Serial.println(state);
		}

		radio.startReceive();
	}
}
