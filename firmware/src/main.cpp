#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>

ConfigLoRa_t config;

int SX_SCLK = PB13;
int SX_MISO = PB14;
int SX_MOSI = PB15;
int SX_NSS = PB12;
int SX_BUSY = PA2;
int SX_RESET = PA1;
int SX_DIO_1 = PA0;

SPIClass SPI_LORA(SX_MOSI, SX_MISO, SX_SCLK);
SX1262 radio = new Module(SX_NSS, SX_DIO_1, SX_RESET, SX_BUSY, SPI_LORA);

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
}

void loop() {

}
