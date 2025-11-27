---
title: Helios
author: Kai Pereira
description: Solar powered, LoRa weather station transceiver and receiver!
created_at: 2025-10-26
---
## Day 1 - Starting Helios :D

I've decided to work on speedrunning a little project to learn more about radio's and to improve my STM32 skills, because I absolutely love their SoC's!!

The project is going to be a little solar transceiver and receiver, the transceiver will use a battery with solar panels, and be able to check the weather and soil, and the receiver will be a little antenna on my homeserver and I'll put that on my website!!

So the first thing I did is flesh out some of the details. I have a very good vision of the project in my head, so I didn't write too much down, but I got some of the components down:

![[Pasted image 20251126061624.png]]

Next, I'm going to start on the MCU! I'm using the STM32L072 because it's really low power and I don't need too many peripherals! So I wired the really simple stuff:

![[Pasted image 20251126061833.png]]

Next, I need to add a ferrite bead on VDDA to filter the high frequency noise so it doesn't affect the analog aspects of my MCU!

I decided to use the GZ1608D601TF ferrite bead, because it has filtering at 600 ohms, and my MCU isn't drawing much current so I don't need anything crazy, and it'll have low drop:

![[Pasted image 20251126062939.png]]

I also added some decoupling after the ferrite bead, a bulk to smooth the voltage drop, and a smaller one for the MCU:

![[Pasted image 20251126064133.png]]

And then there's 4 VDD pins (one VDD_USB), and I already did VDDA, so I do one bulk cap for the group, and then one 100nF per VDD pin:

![[Pasted image 20251126065419.png]]

Next, I need to add my boot and reset button. The reset button has a 100nF cap so that the module doesn't accidentally reset from a voltage spike!

![[Pasted image 20251126163436.png]]

Next, I need to work on my power systems! I'm going to add USB-C so that I can actually program this thing:

![[Pasted image 20251126163624.png]]

You can see I use a ferrite bead on shield so that it doesn't act as a weak antenna, and I also added ESD protection!