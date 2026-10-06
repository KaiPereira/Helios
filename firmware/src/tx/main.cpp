#include "RadioConfig.h"
#include <BH1750.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_BME280 bme280;
BH1750 bh1750;

bool bme280_state;
bool bh1750_state;

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

	config.frequency = 915; // 915 for America/US
	
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

	if (bme280_state) {
		message += "T=" + String(bme280.readTemperature(), 1) + "C ";
		message += "H=" + String(bme280.readHumidity(), 1) + "% ";
		message += "P=" + String(bme280.readPressure() / 100.0F, 1) + "hPa ";
	}

	if (bh1750_state) {
		message += "L=" + String(bh1750.readLightLevel(), 1) + "lx";
	}

	message.trim();

	if (message.length() == 0) {
		message = "No sensor data";
	}

	Serial.print(F("Sensor Data: "));
	Serial.println(message);

	int radio_state = radio.transmit(message);

	Serial.print(F("[SX1262] TX: "));
	Serial.println(radio_state == RADIOLIB_ERR_NONE ? F("Success!") : F("Failed"));
	
	delay(5000);
}
