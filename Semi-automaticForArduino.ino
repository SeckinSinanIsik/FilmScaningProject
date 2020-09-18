/* Stepper Motor for Film Carriers
   Arduino Nano
   MIT License
   Copyright (c) 2020 Seckin Sinan Isik
*/
// stepper control outputs
#define motStepPin     8
#define motDirPin      7
#define motMS1Pin      11
#define motMS2Pin      10
#define motMS3Pin      9
// button inputs
#define buttonRev      4
#define buttonRunRev   13
#define buttonRun      6
#define buttonFrw      5
#define buttonPicture  3
// speed control pot
#define speedPot        A7 //change from A6
int FrameLength=111;
const int ledPin =  12;
int motSpeed;

void setup() {
Serial.begin(9600);

  pinMode(buttonRun, INPUT);
  pinMode(buttonRunRev, INPUT);
  pinMode(buttonFrw, INPUT);
  pinMode(buttonRev, INPUT);
  pinMode(buttonPicture, INPUT);
  // configure initial motor settings
  digitalWrite(motStepPin, LOW);
  digitalWrite(motDirPin, HIGH);
  digitalWrite(motMS1Pin, LOW);
  digitalWrite(motMS2Pin, LOW);
  digitalWrite(motMS3Pin, LOW);
  pinMode(motStepPin, OUTPUT);
  pinMode(motDirPin, OUTPUT);
  pinMode(motMS1Pin, OUTPUT);
  pinMode(motMS2Pin, OUTPUT);
  pinMode(motMS3Pin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
}
void loop() {


  // MircoStep Reverse Forward
  if (digitalRead(buttonFrw)== LOW) {
      digitalWrite(motDirPin, 1); // direction input
      digitalWrite(motMS1Pin,1);  //[MS1][MS2][MS3] all 1 for activatin 1/16 micro ste
      digitalWrite(motMS2Pin,1);
      digitalWrite(motMS3Pin,1);
      for (int i = 0; i < 24; i++) { //reducingmicro step to have precision
      motSpeed = map(analogRead(speedPot), 0, 1023, 5000, 200);
      // advance motor one step at the pot delay setting/speed
      digitalWrite(motStepPin, HIGH);
      delayMicroseconds(motSpeed);
      digitalWrite(motStepPin, LOW);
      delayMicroseconds(motSpeed);
      }   
      delay(80);
  }
    // MircoStep Reverse
  if (digitalRead(buttonRev)== LOW ) {
      digitalWrite(motDirPin, 0); // direction input
      digitalWrite(motMS1Pin,1);  //[MS1][MS2][MS3] all 1 for activatin 1/16 micro ste
      digitalWrite(motMS2Pin,1);
      digitalWrite(motMS3Pin,1);
      for (int i = 0; i < 24; i++) { //reducingmicro step to have precision
      motSpeed = map(analogRead(speedPot), 0, 1023, 5000, 200);
      // advance motor one step at the pot delay setting/speed
      digitalWrite(motStepPin, HIGH);
      delayMicroseconds(motSpeed);
      digitalWrite(motStepPin, LOW);
      delayMicroseconds(motSpeed);
      }
      delay(80);
  }
    // Full 35mm exposure Step Forward
  if (digitalRead(buttonRun)==LOW ) {
      digitalWrite(motDirPin, 1); // direction input
      digitalWrite(motMS1Pin,0);  //[MS1][MS2][MS3] all 0 for activatin full step
      digitalWrite(motMS2Pin,0);
      digitalWrite(motMS3Pin,0);
      for (int i = 0; i < FrameLength; i++) { //reducing Full step to fit 35mm frame 110
       motSpeed = map(analogRead(speedPot), 0, 1023, 5000, 200);
      // advance motor one step at the pot delay setting/speed
      digitalWrite(motStepPin, HIGH);
      delayMicroseconds(motSpeed);
      digitalWrite(motStepPin, LOW);
      delayMicroseconds(motSpeed);
      }
      delay(400);
    }
     // Take a picture
  if (digitalRead(buttonPicture)== LOW) {    
      digitalWrite(ledPin, LOW);
      delay(100);
      digitalWrite(ledPin, HIGH);
      delay(400);
  }
}
