#include "RadioConfig.h"

volatile bool packetReceived = false;

void onPacket(void) {
	packetReceived = true;
}

void setup() {
	Serial.begin(115200);

	while (!Serial && millis() < 5000); // Serial takes a minute to enumerate

	radio.tcxoVoltage = 0; // Using an external crystal so set to 0V

	Serial.print(F("[SX1262] Starting Up..."));

	config.frequency = NODE_CHANNEL;
	
	int state = radio.begin(config);

	if (state == RADIOLIB_ERR_NONE) {
		Serial.println(F("Success!"));
	} else {
		Serial.print(F("Failed!"));
		Serial.println(state);
	}

	radio.setDio2AsRfSwitch(true); // Sets the RF switch to receive
	radio.setPacketReceivedAction(onPacket);

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
	if (packetReceived) {
		packetReceived = false;

		String message;
		int state = radio.readData(message); // Reads data into the message

		if (state == RADIOLIB_ERR_NONE && message.startsWith("id=")) {
			message += " rs=" + String((int)radio.getRSSI());

			Serial.print(F("[Relay] Trying..."));
			Serial.println(message);

			radio.setFrequency(LINK_CHANNEL);

			int radio_state = radio.transmit(message);

			if (radio_state == RADIOLIB_ERR_NONE) {
				Serial.println(F("[Relay] Successfully Repeated!"));
			} else {
				Serial.print(F("[Relay] Failed"));
				Serial.println(radio_state);
			}
		} else {
			Serial.print(F("[SX1262] Failed: "));
			Serial.println(state);
		}

		radio.startReceive();
	}
}

