
#include <SPI.h>

// initialize the stepper library on pins 8 through 11:
//Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
String command;
int stepCount = 0;  // number of steps the motor has taken

//int ENA_T = 40; //define Enable Pin
//int PUL_T = 42; //define Pulse pin
//int DIR_T = 44; //define Direction pin

int ENA_T = 28; //define Enable Pin
int PUL_T = 30; //define Pulse pin
int DIR_T = 32; //define Direction pin

int ENA_T2 = 48; //define Enable Pin
int PUL_T2 = 50; //define Pulse pin
int DIR_T2 = 52; //define Direction pin
void setup() {
  pinMode (PUL_T, OUTPUT);
  pinMode (DIR_T, OUTPUT);
  pinMode (ENA_T, OUTPUT);
  pinMode (PUL_T2, OUTPUT);
  pinMode (DIR_T2, OUTPUT);
  pinMode (ENA_T2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(DIR_T, LOW);
  digitalWrite(ENA_T,LOW);
  digitalWrite(DIR_T2, LOW);
  digitalWrite(ENA_T2,LOW);
}

void move(int steps) {
  for (int i = 0; i < steps; i++) {
    digitalWrite(ENA_T,HIGH);
    digitalWrite(PUL_T,HIGH);
    digitalWrite(ENA_T2,HIGH);
    digitalWrite(PUL_T2,HIGH);
    delayMicroseconds(2000);
    digitalWrite(PUL_T,LOW);
    digitalWrite(ENA_T,LOW);
    digitalWrite(PUL_T2,LOW);
    digitalWrite(ENA_T2,LOW);
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
