// 6 servo motors of a robotic arm + Ultrasonic sensor and Bluetooth module

#include<Servo.h>

#include <SoftwareSerial.h>

SoftwareSerial Bluetooth(0, 1); //Rx then Tx and Rx to Tx and Tx to Rx

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

int echoPin = 7;
int trigPin = 8;

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


int angle31 = 70; // Welcoming
int angle32 = 20;
int angle33 = 30;

int angle34 = 110;
int angle35 = 160;
int angle36 = 150;

int angle41 = 160; //Happy " على راسي"
int angle42 = 20;
int angle43 = 90;

int angle44 = 20;
int angle45 = 160;
int angle46 = 90;

int angle51 = 0; //Sad
int angle52 = 0;
int angle53 = 0;

int angle54 = 180;
int angle55 = 180;
int angle56 = 180;


int angle61 = 120; //Good Bye
int angle62 = 40;
int angle63 = 0;

int angle64 = 180;
int angle65 = 180;
int angle66 = 160;


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



void setup()
{
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
}

void loop()
{

  distance = 0.01723 * readUltrasonicDistance(8, 7); // distance of object

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


  if ( distance < range && distance > range - 300 && x <= 3 ) // this loop is for controlling the time before enter the programm
  {
    x++;
    delay(700); // not exactly 3 seconds but around 3 seconds
  }


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
      key1 = 0;
    }

    servo3.write(40); // these for waving
    servo6.write(140);
    delay(2000);

    servo3.write(0);
    servo6.write(180);
    delay(2000);
  }

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
      key2 = 0;
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
}
