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
