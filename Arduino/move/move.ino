
#include <SPI.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor


// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
String command;
int stepCount = 0;  // number of steps the motor has taken

int PUL_T = 26; //define Pulse pin
int DIR_T = 24; //define Direction pin
int ENA_T = 22; //define Enable Pin
int LED = 13;

void setup() {
  pinMode (PUL_T, OUTPUT);
  pinMode (DIR_T, OUTPUT);
  pinMode (ENA_T, OUTPUT);
  pinMode (LED, OUTPUT);
  Serial.begin(9600);
  //Serial.begin(115200);
  digitalWrite(DIR_T, LOW);
  digitalWrite(ENA_T,LOW);
  //SPI.begin();
}

void move(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(ENA_T,HIGH);
    digitalWrite(PUL_T,HIGH);
    digitalWrite(LED, HIGH);
    delayMicroseconds(200);
    digitalWrite(PUL_T,LOW);
    digitalWrite(ENA_T,LOW);
    digitalWrite(LED, LOW);
    delayMicroseconds(1000);
  }
  return;
}

void loop() {
  if(Serial.available()>0) {
    command = Serial.readString();
    move(command.toInt());
  }
}
