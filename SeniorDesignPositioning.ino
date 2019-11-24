#include <SPI.h>

const int stepsPerRevolution = 200;  // number of steps per revolution

//char command;
String motor;
String steps;
String dir;
String direc;


int stepCount = 0;  // number of steps the motor has taken

int PUL_T_x = 30; //define Pulse pin for motor 1
int DIR_T_x = 32; //define Direction pin for motor 1
int ENA_T_x = 34; //define Enable Pin for motor 1

int PUL_T_y1 = 22; //define Pulse pin for motor 2
int DIR_T_y1 = 24; //define Direction pin for motor 2
int ENA_T_y1 = 26; //define Enable Pin for motor 2

int PUL_T_y2 = 40; //define Pulse pin for motor 3
int DIR_T_y2 = 42; //define Direction pin for motor 3
int ENA_T_y2 = 44; //define Enable Pin for motor 3

int LASER = 53;

void setup() {
  // put your setup code here, to run once:
  
  pinMode (PUL_T_x, OUTPUT);
  pinMode (DIR_T_x, OUTPUT);
  pinMode (ENA_T_x, OUTPUT);
  Serial.begin(9600);
  digitalWrite(DIR_T_x, HIGH);
  digitalWrite(ENA_T_x,LOW);
  

  pinMode (PUL_T_y1, OUTPUT);
  pinMode (DIR_T_y1, OUTPUT);
  pinMode (ENA_T_y1, OUTPUT);
  Serial.begin(9600);
  digitalWrite(DIR_T_y1, HIGH);
  digitalWrite(ENA_T_y1,LOW);


  pinMode (PUL_T_y2, OUTPUT);
  pinMode (DIR_T_y2, OUTPUT);
  pinMode (ENA_T_y2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(DIR_T_y2, HIGH);
  digitalWrite(ENA_T_y2,LOW);

  pinMode (LASER, OUTPUT);
  digitalWrite(LASER, HIGH);


}

void movex(int steps, int dir) {
  for (int i = 0; i < steps; i++) {
    
    digitalWrite(ENA_T_x,HIGH);
    digitalWrite(PUL_T_x,HIGH);
    digitalWrite(DIR_T_x,dir);
    digitalWrite(PUL_T_y1,LOW);
    digitalWrite(ENA_T_y1,LOW);
    digitalWrite(PUL_T_y2,LOW);
    digitalWrite(ENA_T_y2,LOW);
    delayMicroseconds(1000);
    digitalWrite(PUL_T_x,LOW);
    digitalWrite(ENA_T_x,LOW);
    digitalWrite(DIR_T_x,dir);
    digitalWrite(PUL_T_y1,LOW);
    digitalWrite(ENA_T_y1,LOW);
    digitalWrite(PUL_T_y2,LOW);
    digitalWrite(ENA_T_y2,LOW);
    delayMicroseconds(1000);
  }
  return;
}

void movey(int steps, int dir) {
  for (int i = 0; i < steps; i++) {
    

    digitalWrite(ENA_T_y1,HIGH);
    digitalWrite(PUL_T_y1,HIGH);
    digitalWrite(ENA_T_y2,HIGH);
    digitalWrite(PUL_T_y2,HIGH);
    digitalWrite(DIR_T_y1,dir);
    digitalWrite(DIR_T_y2,dir);
    digitalWrite(PUL_T_x,LOW);
    digitalWrite(ENA_T_x,LOW);
    delayMicroseconds(1000);
    digitalWrite(PUL_T_y1,LOW);
    digitalWrite(ENA_T_y1,LOW);
    digitalWrite(PUL_T_y2,LOW);
    digitalWrite(ENA_T_y2,LOW);
    digitalWrite(DIR_T_y1,dir);
    digitalWrite(DIR_T_y2,dir);
    digitalWrite(PUL_T_x,LOW);
    digitalWrite(ENA_T_x,LOW);
    delayMicroseconds(1000);
  }
  return;
}


void loop() {
  // put your main code here, to run repeatedly:
    if(Serial.available()>0) {
    motor = Serial.readStringUntil(',');
    steps = Serial.readStringUntil(',');
    direc = Serial.readStringUntil('\n');
    if(motor == String('x')){
    movex(steps.toInt(), direc.toInt());
    }
    else if(motor == String('y')){
    movey(steps.toInt(), direc.toInt());
    }
  }

}
