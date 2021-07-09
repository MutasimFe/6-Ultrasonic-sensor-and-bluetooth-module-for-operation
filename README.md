# 6 - Adding Ultrasonic sensor and Bluetooth module for operation


![Screenshot_3](https://user-images.githubusercontent.com/85455361/124705407-4b38b880-defe-11eb-9f68-1afa998dbb38.jpg)

# The Main Idea:

Adding ultrasonic sensor and Bluetooth module for the robotic arm task (previous task). 

The ultrasonic for sensing objects if there is in front of the robot or not.
And the Bluetooth for communicate with the tablet wirelessly

# Components:

1. Arduino
2. Servo motors x6
3. Battery
4. Capacitors x2
5. Voltage regulator 
6. Ultra sonic sensor
7. HC 05 Bluetooth module

## Ultrasonic Sensor connection pins

![Introduction-to-HC-SR04](https://user-images.githubusercontent.com/85455361/124712954-9657c900-df08-11eb-968b-2246cb1c8ce9.jpg)

### As shown. for ultrasonic sensors there are 4 pins:

1. Vcc ; power pin which must connect to the voltage source.
2. Ground ; ground pin.
3. Trig ; which is responsible for sending ultrasonic waves.
4. Echo ; which is responsible for receiving the reflected waves.

## Bluetooth module connection pins

![hc051](https://user-images.githubusercontent.com/85455361/124713078-bdae9600-df08-11eb-8240-8f3872993614.jpg)

### As shown. forBluetooth module there are 6 pins but we are using only 4 pins which are:

1. Vcc ; power pin which must connect to the voltage source.
2. Ground ; ground pin.
3. Tx ; which which is responsible for sending data from Arduino to the outer world. ( must be connect to the Rx )
4. Rx ; which which is responsible for receiving data from outer world to the Arduino. ( must be connectct to the Tx ) 

# Connection:

![aaa](https://user-images.githubusercontent.com/85455361/124711475-cbfbb280-df06-11eb-9788-6bbc21646dea.jpg)


### Notes:

* The degrees are based on imagination so they can be easily adjusted based on simple math after designing the arms by the mechanical engineer. 

# Code:

I present only the important new codes instead of all code.

* Libraries 

* Defning:

* Setup:

* The main body (points):

### Note:

* Since there is no bluetooth module in tinkercad so the code did not test, so it may occur small errors can be adjusted easily. 

# Important notes:

* There is no bluetooth module in tinkercad that why i did not record a video.


# Suggested Ideas: 
###  
