#include <Servo.h>
Servo servo;               // create servo object to control a servo

int  potPin       = 0;     // select the input pin for the potentiometer
int  ledPin       = 13;    // select the pin for the LED
int  swPin        = 2;     // select the input pin for the potentiometer
int  val          = 0;     // variable to store the value coming from the sensor
int  ledTimer     = 0;
int  autoServoMin = 0;     // minimum value to automatically oscillate between
int  autoServoMax = 50;    // maximum value to automatically oscillate between
bool ledOn        = true;  // default LED to on
bool swState      = false;
bool autoServoInc = true;

void setup() {
  pinMode(ledPin, OUTPUT); // declare the ledPin as an OUTPUT
  pinMode(swPin, INPUT);   // declare the swPin as an INPUT
  servo.attach(9);         // attach servo to port 9
}

void loop() {
  swState = digitalRead(swPin);

  if (swState == LOW) {
    digitalWrite(ledPin, LOW);

    if (val < autoServoMin)
      val = autoServoMin;
    else if (val > autoServoMax)
      val = autoServoMax;

    servo.write(val);
    delay(5);

    if (autoServoInc)
      val++;
    else
      val--;
  }
  else {
    val = analogRead(potPin) / 5.683333333;
    servo.write(val);

    if (ledOn)
      digitalWrite(ledPin, HIGH);
    else
      digitalWrite(ledPin, LOW);

  }

  ledTimer++;
  if (ledTimer > val * 2) {
    ledTimer = 0;
    ledOn = !ledOn;
  }
}



