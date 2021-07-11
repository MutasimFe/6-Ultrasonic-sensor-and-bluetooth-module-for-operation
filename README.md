# 6 - Adding Ultrasonic sensor and Bluetooth module for operation


![Screenshot_3](https://user-images.githubusercontent.com/85455361/124705407-4b38b880-defe-11eb-9f68-1afa998dbb38.jpg)

# The Main Idea:

Adding ultrasonic sensor and Bluetooth module for the robotic arm task (previous task). 

The ultrasonic for sensing objects if there is in front of the robot or not.
And the Bluetooth for communicate with the tablet wirelessly

### Work done with my mate:

@https://github.com/abdukhaledi

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

## MG995 Servo Motor:

![MG995-Servo-Pinout](https://user-images.githubusercontent.com/85455361/125038290-ecaa4080-e09d-11eb-9b9f-f8967cbb6d89.png)

### As shown the servomotor has 3 pins:

1. Vcc (Red) ; power pin which must connect to the voltage source.
2. Ground (Brown); ground pin.
3. Singla (Orange); which is responsible for controling the degree of the brush and it must be connected to a PWM pin.


# Connection:

![aaa](https://user-images.githubusercontent.com/85455361/124711475-cbfbb280-df06-11eb-9788-6bbc21646dea.jpg)

# Video:

https://user-images.githubusercontent.com/85455361/125161363-86e7b280-e18a-11eb-8f8a-1803c21f95dd.mp4

### Notes

* The video is for explain the idea so i made small changes in code. The main code is as in the code file.

### Notes:

* The degrees are based on imagination so they can be easily adjusted based on simple math after designing the arms by the mechanical engineer. 

# Code:

I present only the important new codes instead of all code. Also, I left comments to explain the code.

The full code is in code file.

* Libraries:

``` c++
  #include<Servo.h>
  #include <SoftwareSerial.h>  
```

* Defning:

``` c++  
  char Stats;
  int  turnON = 1;
  int  turnOFF = 0;
  int  attention = 10;
  int  x = 0;

  int range = 300;    //the range of ultrasonic sensor 300cm
  float distance = 0; //for distance

  int  key1 = 0;
  int  key2 = 0;

  Servo servo1; //first hard ( Shoulder )
  Servo servo2; //first hand ( Shoulder )
  Servo servo3; //first hand ( Arm )

  Servo servo4; //second hand ( Shoulder )
  Servo servo5; //second hand ( Shoulder )
  Servo servo6; //second hand ( Arm )
```

Also, I defined the angle of each mode at the beginning of the code so we can change it easily if I want. For of two modes exmaple:
``` c++
  int angle11 = 0; //initial pos ( out of range )
  int angle12 = 0;
  int angle13 = 20;

  int angle14 = 180;
  int angle15 = 180;
  int angle16 = 160;

  int angle21 = 120; // waving
  int angle22 = 40;
  int angle23 = 0;

  int angle24 = 40;
  int angle25 = 140;
  int angle26 = 180;
``` 

* This part for operate the ultrasonic sensor:

``` c++
  long readUltrasonicDistance(int trigPin, int echoPin) // this is for operate the ultra sonic sensor
  {
    pinMode(trigPin, OUTPUT);  // Clear the trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);

    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
  }
```

* Setup:

``` c++
    Bluetooth.begin(9600); //for bluetooth

  Serial.begin(9600);    //start the communication with 9600 bound rate

  servo1.write(angle11);
  servo2.write(angle12);
  servo3.write(angle13);

  servo4.write(angle14); //starts from 180 ends in 90 degree since these servo motors are in opposide place ( merroring
  servo5.write(angle15);
  servo6.write(angle16);

  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);

  servo4.attach(9);
  servo5.attach(10);
  servo6.attach(11);
```

* The main body (points):
  
For calculating the distance and store it in a variable:
``` c++
    distance = 0.01723 * readUltrasonicDistance(8, 7); // distance of object
```

If the object is outside ultrasonic range:
``` c++
     if (distance > range)  //out of Ultrasonic sensor range
  {
    servo1.write(angle11);
    servo2.write(angle12);
    servo3.write(angle13);

    servo4.write(angle14);
    servo5.write(angle15);
    servo6.write(angle16);

    while (key1 == 0 && key2 == 0) // these are the keys of sending the bluetooth singnal only once
    {
      Bluetooth.write(turnOFF); // the bluetooth is sening 'turnOFF'
      delay(500);
      key1 = 1;
      key2 = 1;
    }

    x = 0; // for initializing the value of x that is used as a key for the next if conditions 

  }
```
This loop is responsible of the detection time 
``` c++
  if ( distance < range && distance > range - 300 && x <= 3 ) // this loop is for controlling the time before enter the programm
  {
    x++;
    delay(700); // not exactly 3 seconds but around 3 seconds
  }
``` 
This loop is for sending only one signal to the tablet tells in which mode we are:
``` c++
        while (key1 == 0 && key2 == 0) // these are the keys of sending the bluetooth singnal only once
    {
      Bluetooth.write(turnOFF); // the bluetooth is sening 'turnOFF'
      delay(500);
      key1 = 1;
      key2 = 1;
    }
```

If the object is in attention mode ultrasonic range:
``` c++
    if ( distance < range && distance > range - 100 && x >= 3 ) // waving for attract people in 2-3 meters away  //x=3 means 3 seconds
  {
    servo1.write(angle21);
    servo2.write(angle22);
    servo3.write(angle23);

    servo4.write(angle24);
    servo5.write(angle25);
    servo6.write(angle26);

    while (key1 == 1) //this loop is for sending only one signal that tells the screen to turn on the smile mode.
    {
      Bluetooth.write(attention); // the bluetooth is sending 'attention' for starting the smile screen
      delay(500);
      key1 = 0; //make it zero for the other modes
    }

    servo3.write(40); // these for waving
    servo6.write(140);
    delay(2000);

    servo3.write(0);
    servo6.write(180);
    delay(2000);
  }
```
If the object is in evaluation range
``` c++
     if ( distance < range - 100 && distance > range - 300 && x >= 3 ) //welcoming and start evaluate   //x=3 means 3 seconds
  {
    servo1.write(angle31);
    servo2.write(angle32);
    servo3.write(angle33);

    servo4.write(angle34);
    servo5.write(angle35);
    servo6.write(angle36);
    delay(1000);

    while (key2 == 1)//this loop is for sending only one signal that tells the screen to turn on the evaluation mode.
    {
      Bluetooth.write(turnON);  //the bluetooth is sending 'turnON' for starting the evaluation process for the coustomer
      key2 = 0; //make it zero for the other modes
      delay(500);
    }

    if (Bluetooth.available()) // after evaluate
    {

      Stats = Bluetooth.read(); // for reading the incoming signal and store from outside

      if (Stats == 'H') // Happy " على راسي "
      {
        servo1.write(angle41);
        servo2.write(angle42);
        servo3.write(angle43);

        servo4.write(angle44);
        servo5.write(angle45);
        servo6.write(angle46);
        delay(3000);

        servo3.write(70);
        servo6.write(110);
        delay(2000);

        servo3.write(90);
        servo6.write(90);
        delay(2000);

        servo3.write(70);
        servo6.write(110);
        delay(2000);

        servo3.write(90);
        servo6.write(90);
        delay(2000);
      }

      else if (Stats == 'S') // Sad
      {
        servo1.write(angle51);
        servo2.write(angle52);
        servo3.write(angle53);

        servo4.write(angle54);
        servo5.write(angle55);
        servo6.write(angle56);
        delay(5000); //for taken the enough time before the next move

      }

      else if (Stats == 'B') //Bye
      {
        servo1.write(angle61);
        servo2.write(angle62);
        servo3.write(angle63);

        servo4.write(angle64);
        servo5.write(angle65);
        servo6.write(angle66);
        delay(3000);

        servo3.write(40); //One hand  is waving
        delay(2000);

        servo3.write(0);
        delay(2000);

        servo3.write(40);
        delay(2000);

        servo3.write(0);
        delay(2000);
      }
    }
  }
```

### Note:

* Since there is no bluetooth module in tinkercad so the code did not test, so it may occur small errors can be adjusted easily. 

# Important notes:

* There is no bluetooth module in tinkercad.


