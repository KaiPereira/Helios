#include "RadioConfig.h"
#include <BH1750.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Macro to make each device id easy to name
#ifndef NODE_ID
#error "NODE_ID not set, please set one using -D NODE_ID=<number> to your build flags"
#endif

Adafruit_BME280 bme280;
BH1750 bh1750;

bool bme280_state;
bool bh1750_state;

uint32_t messageCount = 0;

void setup() {
	Serial.begin(115200);

	while (!Serial && millis() < 5000); // Serial takes a minute to enumerate

	
	// Sensors
	Wire.setSDA(SENSOR_SDA);
	Wire.setSCL(SENSOR_SCL);
	Wire.begin();
	
	Serial.println(F("[BME280] Starting Up..."));

	bme280_state = bme280.begin(BME280_ADDR, &Wire);

	Serial.println(bme280_state ? "Success!" : "Failed!");


	Serial.println("[BH1750] Starting Up...");
	
	bh1750_state = bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, BH1750_ADDR, &Wire);

	Serial.println(bh1750_state ? "Success!" : "Failed!");

	
	// LoRa Radio
	radio.tcxoVoltage = 0; // Using an external crystal so set to 0V

	config.frequency = NODE_CHANNEL;
	
	Serial.print(F("[SX1262] Starting Up..."));

	int radio_state = radio.begin(config);

	if (radio_state == RADIOLIB_ERR_NONE) {
		Serial.println(F("Success!"));
	} else {
		Serial.print(F("Failed:"));
		Serial.println(radio_state);
	}
}

void loop() {
	String message;

	String msg = "id=" + String(NODE_ID) + " n=" + String(messageCount++);
 
	if (bme280_state) {
		msg += " T=" + String(bme280.readTemperature(), 1);
		msg += " H=" + String(bme280.readHumidity(), 1);
		msg += " P=" + String(bme280.readPressure() / 100.0F, 1);
	}
 
	if (bh1750_state) {
		msg += " L=" + String(bh1750.readLightLevel(), 1);
	}

	Serial.println(message);

	int radio_state = radio.transmit(message);

	Serial.print(F("[SX1262] TX: "));
	Serial.println(radio_state == RADIOLIB_ERR_NONE ? F("Success!") : F("Failed"));
	
	delay(5000);
}
