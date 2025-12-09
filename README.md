# Helios - Solar Powered LoRa Weather Station

<img width="1916" height="1256" alt="image" src="https://github.com/user-attachments/assets/9f952b21-a011-42dc-87c3-58435392f2f4" />

Helios is a small, solar powered LoRa weather station, in Pi Zero 2W form factor! It's designed for extremely low power consumption, small price, expandability and hobby purposes! It has a couple onboard sensors for temperature, humidity, pressure and light, but it's mostly designed to be your own little customizable node!

## Custom Features
- 150MHz to 960MHz LoRa SMA antenna
- Solar powered battery charging up to 18V 
- 300mA peak power consumption
- Pi Zero 2W form factor
- USB-C programming and power
- 20 programmable GPIO's + Soil Sensor
- Temperature, humidity, pressure and ambient light sensors

## PCB Design

Helios is designed to be a low-cost PCB and is a 4 layer PCB, with a SIGNAL/GND/PWR/SIGNAL stackup! 

<img width="2560" height="1403" alt="image" src="https://github.com/user-attachments/assets/73ecfd4b-a6da-4292-a8ed-3df7514fc9db" />

It's built off the STM32L072 MCU, using the SX1262 LoRa transceiver with the 0900FM filter and the PE4259 RF switch! It's a classic SMA antenna that broadcasts temperature, humidity, pressure and ambient light from the BME280 and BH1750! 

The board can be powered off of USB-C, or solar powered battery charging with the SPV1050 alongside very minimal power usage!

<img width="2560" height="1403" alt="image" src="https://github.com/user-attachments/assets/b938e326-a254-41c2-b954-ac0939eb8c35" />
<img width="2560" height="1406" alt="image" src="https://github.com/user-attachments/assets/f23da988-3b1c-4ee0-b8fb-17cf2ece0fbd" />
<img width="2560" height="1402" alt="image" src="https://github.com/user-attachments/assets/73bb9cfa-c803-49cb-8532-408490759493" />
<img width="2560" height="1405" alt="image" src="https://github.com/user-attachments/assets/9dd90fdd-9d13-44dd-9336-654e07615e78" />
