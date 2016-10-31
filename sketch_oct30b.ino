#include <Servo.h>

const int sPin1 = 9; // servo A digital pin 9
const int bPin1 = 2; // leftmost button on edge

const int sPin2 = 10; // servo B; digital pin 11
const int bPin2 = 3; // middle button

const int sPin3 = 8; // turnigy servo; digital pin 13
const int bPin3 = 4; // right button away from edge

Servo servo1;
Servo servo2;
Servo servo3;

int button1;
int button2;
int button3;

int pos1 = 1; //position of servo
int pos2 = 1; //position of servo
int pos3 = 1; //position of servo

boolean up1 = true;
boolean up2 = true;
boolean up3 = true;


int delayNum1 = 15;
int delayNum2 = 15;
int delayNum3 = 15;

void addSetUp(int sPin, int bPin, Servo servo) {
  servo.attach(sPin);
  //set up button
  pinMode(sPin, OUTPUT);
  pinMode(bPin, INPUT);
}

int sweeping(int bPin, int button, Servo servo, int delayNum, boolean *up_t, int *pos_t) {
  //read buttons
  button = digitalRead(bPin);

  boolean up = *up_t;
  int pos = *pos_t;

  if (button == HIGH)
  {
    if (pos > 178)
    {
      up = false;
      Serial.println("T");
    }

    if (pos <= 1) {
      up = true;
      Serial.println("F");
    }

    if (up) {
      servo.write(pos++);
      Serial.println(pos);
    }
    else {
      Serial.println("flag");
      servo.write(pos--);
    }
    delay(delayNum);
  }

  *up_t = up;
  *pos_t = pos;
}

void setup()
{
  addSetUp(sPin1, bPin1, servo1);
  addSetUp(sPin2, bPin2, servo2);
  addSetUp(sPin3, bPin3, servo3);

  Serial.begin(9600);
}

void loop()
{
  sweeping(bPin1, button1, servo1, delayNum1, &up1, &pos1);
  sweeping(bPin2, button2, servo2, delayNum2, &up2, &pos2);
  sweeping(bPin3, button3, servo3, delayNum3, &up3, &pos3);
}
