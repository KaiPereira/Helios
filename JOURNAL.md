---
title: Helios
author: Kai Pereira
description: Solar powered, LoRa weather station transceiver and receiver!
created_at: 2025-10-26
---
## Day 1 - Starting Helios :D - 5 Hours

I've decided to work on speedrunning a little project to learn more about radio's and to improve my STM32 skills, because I absolutely love their SoC's!!

The project is going to be a little solar transceiver and receiver, the transceiver will use a battery with solar panels, and be able to check the weather and soil, and the receiver will be a little antenna on my homeserver and I'll put that on my website!!

So the first thing I did is flesh out some of the details. I have a very good vision of the project in my head, so I didn't write too much down, but I got some of the components down:

![Pasted image 20251126061624.png](images/Pasted%20image%2020251126061624.png)

Next, I'm going to start on the MCU! I'm using the STM32L072 because it's really low power and I don't need too many peripherals! So I wired the really simple stuff:

![Pasted image 20251126061833.png](images/Pasted%20image%2020251126061833.png)

Next, I need to add a ferrite bead on VDDA to filter the high frequency noise so it doesn't affect the analog aspects of my MCU!

I decided to use the GZ1608D601TF ferrite bead, because it has filtering at 600 ohms, and my MCU isn't drawing much current so I don't need anything crazy, and it'll have low drop:

![Pasted image 20251126062939.png](images/Pasted%20image%2020251126062939.png)

I also added some decoupling after the ferrite bead, a bulk to smooth the voltage drop, and a smaller one for the MCU:

![Pasted image 20251126064133.png](images/Pasted%20image%2020251126064133.png)

And then there's 4 VDD pins (one VDD_USB), and I already did VDDA, so I do one bulk cap for the group, and then one 100nF per VDD pin:

![Pasted image 20251126065419.png](images/Pasted%20image%2020251126065419.png)

Next, I need to add my boot and reset button. The reset button has a 100nF cap so that the module doesn't accidentally reset from a voltage spike!

![Pasted image 20251126163436.png](images/Pasted%20image%2020251126163436.png)

Next, I need to work on my power systems! I'm going to add USB-C so that I can actually program this thing:

![Pasted image 20251126163624.png](images/Pasted%20image%2020251126163624.png)

You can see I use a ferrite bead on shield so that it doesn't act as a weak antenna, and I also added ESD protection!

And that kind of concluded my first day working on the project! 

## Day 2 - Main Systems - 6 Hours

Day 2 is all about getting the main systems in so that the board is actually programmable and works, but without any of the real features.

So the first thing I added was the connectors for the battery and solar panels! I decided to use a screw terminal for the solar panels so that like 90% of solar panels would work with this board! And then the battery will probably just be a JST connector or screw terminals, I need to do a bit more research on the most common thing to use:

![Pasted image 20251129142222.png](images/Pasted%20image%2020251129142222.png)

Next I need to add the actual energy harvester for the solar panels. This handles everything from the protection, to charging, etc, it's really cool! I decided to use the SPV1050 because it's really low power and not as complicated as some of the other modules.

This wiring took me FOREVER, but I got it pretty clean:

![Pasted image 20251129142350.png](images/Pasted%20image%2020251129142350.png)

It took me quite a long time for a couple reasons:
- The voltage divider was really confusing, I ended up just copying another design and tried to BOM optimize it the most possible!
- I wanted to keep the schematic really clean, so I was continuously modifying the symbol so that it looks really good!
- And then the actual wiring was pretty difficult because the application circuit wasn't complete!

I learned a lot about how the different parts like how the resistor divider actually works and also on storing energy with caps.

Next I needed to step down the LiPo 3.7V to 3V3, I decided not to add battery protection to keep low overhead complexity and most of them include protection these days too! I chose an LDO with a medium dropout, low current, and very low quiescant, because I want something good for battery applications but enough to keep it active!

![[Pasted image 20251129143007.png]]

Next, I tuned up my MCU schematic and double checked stuff, and realized I missed an external crystal I should probably have! I added the 32.768 KHz crystal so that I could keep track of the time in low-power mode so I could send signals accurately from my antenna!

![[Pasted image 20251129143206.png]]

And then I tuned out for the day, because the SPV1050 wiring took me absolutely forever!! I'm ready to start working on the actual antenna stuff now though, and I think I can lock in and get a bunch done at once!

## Day 3 - RF and Sensor Shenanigans

Now that I have all my core logic in, I have to add the actual LoRa antenna and transceiver.

There's a couple parts to this:
- The transceiver (SX1262) sends and receives the LoRa radio signals
- The RF switch (PE4259) switches these signals on and off with very little loss so you an just quickly send out a signal and whatnot
- The 0900FM is a filter that cleans up the LoRa signals before they get sent off

So with that in mind, I did all the wiring :D 

![[Pasted image 20251203184010.png]]

You'll notice a couple strange things here, the first is the crystal which is used to create a very precise clock to generate the 900 MHz frequencies, it has built in load caps so you don't need any.

You'll also notice an inductor on DCC_SW which gives a higher voltage to the power amplifier on the SX1262 which will let the PA push more current and achieve a higher output power!

Next you'll notice an inductor in parallel with RFO which is part of the RF filter for the power amplifier output. So PA is the power booster, and RFO is the actual signal, PA is boosting this signal and it's going through a matching network which is the capacitors and inductors to achieve a consistent 50ohm impedance.

After that, it goes through the RF filter, and then onto the actual RF switch. You'll notice the signal to control the RF switch (SX_DIO2), has a very small decoupling capacitor. This is a low-pass filter or debounce cap to prevent the switch from actually turning on and off, and it's a really sensitive signal so that's why it's so small. 

And then finally, you'll see what's called a Pi-L Matching Network which is a:
- Series capacitor to provide series reactance for tuning and prevents DC from going into the antenna
- Parallel capacitor which is part of tuning the impedance
- Series inductor to provide more series reactance to match the impedance
- Another parallel capacitor, for more tuning

This just fine tunes our signal even further, and that's our RF circuit! Pretty complicated right! But I hope to learn a lot more about how RF works once I spend more time working on RF boards! 

Next up, I want to add all the sensors onto my board.

I compiled a list of different sensors I could use like temperature, humidity, pressure, soil, etc, and decided on using just 3 components and then breaking out the rest:
- BME280: temperature, humidity, pressure
- Capacitative soil sensor
- BH1750: ambient light detector

And then you'll be able to add your own sensors to customize it using the broken out pins!

It's pretty easy to wire sensors, I did have to make/alter the symbols and go looking for some footprints, but it was relatively easy:

![[Pasted image 20251204061734.png]]

I decided to split the I2C for my BH1750 and the BME280 because I didn't want any extra programming overhead or to even possibly lose more energy on it.

And with that, I have all the fundamentals of the board in, and now I just have to clean up the mistakes, add the pin headers and footprints, and route the board! 


