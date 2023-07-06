# Car Warriors

## INTRODUCTION
 
_Construction of an autonomous, engineered car for the WRO 2023 competition._

**Team:** Car Warriors
**Car name:** Xiwawa 2.0
**Participants:** Carlos González
              Alexis Acuna


This GitHub repository contains some explanation of the construction and operation of the CarWarriors team project that participates in the future engineers WRO Competition in the 2023 season.

Our team comes from the city of Aguaduce, it's members are two IPTIA students and a tutor graduated from the same institute. For the creation of the car we used a metal chassis manufactured by the sunfounder company as the base and modified it entirely for it's usage. Concerning to our robot it's necessary to mention that we use the Rasberry Pi computer with which we have to carry out the heavy job of processing most of the important data, in addition to, we've to mention the Arduino microcontroller with which we carry out the rest of the work.

Now we will talk about the components conections to our microcontroller and microcomputer.

**Arduino:**
We will talk about the connection of the ultrasonic modules connected to our Arduino development board that serve to guide the car without colliding with obstacles or side fences.

Also, we connected the servo of the gearbox for the synchronization of the ultrasonic modules to avoid hitting the obstacles and side fences.

There is two buttons to control the main direction of functioning of the car based on clockwise or anticlockwise rotation.

In this case we also have a controller or L298N mod to control the speed of the car either backwards or forwards.

**Rasberry:**
We have a Raspberry Pi 3 (model b) that is in charge of color processing. We synchronized our RPi module to our Arduino development board by using Serial communication and connecting it with a USB cable
