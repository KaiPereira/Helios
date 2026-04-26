# Helios - Solar Powered LoRa Weather Station

<img max-width="2560" max-height="1150" alt="image" src="https://github.com/user-attachments/assets/d7b09e14-7f52-4f15-a828-37077befd7e7" />

Helios is a small, solar powered LoRa weather station, in Pi Zero 2W form factor! It's designed for extremely low power consumption, small price, expandability and hobby purposes! It has a couple onboard sensors for temperature, humidity, pressure and light, but it's mostly designed to be your own little customizable node!

## Custom Features
- 150MHz to 960MHz LoRa SMA antenna, up to +22 dBm
- Solar powered battery charging up to 18V
- 300mA peak power consumption
- Pi Zero 2W form factor
- USB-C programming and power
- 20 programmable GPIO's for expandability
- Temperature, humidity, pressure and ambient light sensors

## PCB Design

Helios is designed to be a low-cost PCB and is a 4 layer PCB, with a SIGNAL/GND/PWR/SIGNAL stackup! 

<img max-width="2560" max-height="1150" alt="image" src="https://github.com/user-attachments/assets/558cc3f1-d812-403a-bca1-61831f168143" />

It's built off the STM32L072 MCU, using the SX1262 LoRa transceiver with the 0900FM filter and the PE4259 RF switch! It's a classic SMA antenna that broadcasts temperature, humidity, pressure and ambient light from the BME280 and BH1750! 

The board can be powered off of USB-C, or solar powered battery charging with the SPV1050 alongside very minimal power usage!

<img max-width="2560" max-height="1150" alt="image" src="https://github.com/user-attachments/assets/b938e326-a254-41c2-b954-ac0939eb8c35" />
<img max-width="2560" max-height="1150" alt="image" src="https://github.com/user-attachments/assets/f23da988-3b1c-4ee0-b8fb-17cf2ece0fbd" />
<img max-width="2560" max-height="1150" alt="image" src="https://github.com/user-attachments/assets/73bb9cfa-c803-49cb-8532-408490759493" />
<img max-width="2560" max-height="1150" alt="image" src="https://github.com/user-attachments/assets/9dd90fdd-9d13-44dd-9336-654e07615e78" />

## Manufacturing

The PCB is fairly simple to manufacture. You can get them from JLC, PCBWay or hand-solder it with a stencil and hotplate! If you want the board to be cheaper, just remove the sensors and other unnecessary things you don't need.

The gerbers (PCB.zip), BOM and CPL are located in the [production folder](/TRANSCEIVER_PCB/production/), and there's also a link to the solar panels and battery I used for the project! I got the boards manufactured by PCBWay, so there's a PCBWay specific BOM in that directory too!

I've created a very minimal case for this project if you want to keep it waterproof while having it active outside, and you can view all the files for that in the [CAD folder](https://github.com/KaiPereira/Helios/tree/master/CAD)! Here's an [Onshape link](https://cad.onshape.com/documents/da47fca73387cbfcd2fcd0da/w/e0853c342d07596ecafe782f/e/20c20d8fae7f9e025aea9deb?renderMode=0&uiState=69e2c1399592b2bbbb38fdc5) too!

## Firmware

The boards can run meshatastic or LoRaWAN! It's fairly complicated to setup, so I'll add the firmware to the repository once I've received the boards (soon :D)! 

## Contributions

Thanks so much to PCBWay and Hack Club for sponsoring this project! Another big thanks to the guys in the KiCad discord server for their help and reviews of the board :D
