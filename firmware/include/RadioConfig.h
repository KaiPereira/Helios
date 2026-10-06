#include <Arduino.h>
#include <SPI.h>
#include <RadioLib.h>

ConfigLoRa_t config;

const int SX_SCLK = PB13;
const int SX_MISO = PB14;
const int SX_MOSI = PB15;
const int SX_NSS = PB12;
const int SX_BUSY = PA2;
const int SX_RESET = PA1;
const int SX_DIO_1 = PA0;

const int SENSOR_SDA = PA10;
const int SENSOR_SCL = PA9;
const uint8_t BME280_ADDR = 0x76;
const uint8_t BH1750_ADDR = 0x23;

SPIClass SPI_LORA(SX_MOSI, SX_MISO, SX_SCLK);
SX1262 radio = new Module(SX_NSS, SX_DIO_1, SX_RESET, SX_BUSY, SPI_LORA);
