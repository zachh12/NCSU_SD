#include <SPI.h>

String motor;
String steps;
String dir;
String direc;

String xEND;
String yEND;


int steps_x;
int steps_y;

int PUL_T_x = 32; //define Pulse pin for motor 1
int DIR_T_x = 40; //define Direction pin for motor 1
int ENA_T_x = 36; //define Enable Pin for motor 

int PUL_T_y = 44; //define Pulse pin for motor 2
int DIR_T_y = 52; //define Direction pin for motor 2
int ENA_T_y = 48; //define Enable Pin for motor 2


int home_switch1 = 26; //define homing switches pin

void movex(int steps, int dir) {
    for (int i = 0; i < steps && digitalRead(home_switch1); i++) {
        digitalWrite(ENA_T_x,HIGH);
        digitalWrite(PUL_T_x,HIGH);
        digitalWrite(DIR_T_x,dir);
        digitalWrite(PUL_T_y,LOW);
        digitalWrite(ENA_T_y,LOW);
        delay(1);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        digitalWrite(DIR_T_x,dir);
        digitalWrite(PUL_T_y,LOW);
        digitalWrite(ENA_T_y,LOW);
        delay(1);
    }
    if (!digitalRead(home_switch1)){ //if switch is activated, back off switch
        for (int i = 0; i < 100; i++) {
          digitalWrite(ENA_T_x,HIGH);
          digitalWrite(PUL_T_x,HIGH);
          digitalWrite(DIR_T_x,abs(1-dir));
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
          digitalWrite(PUL_T_x,LOW);
          digitalWrite(ENA_T_x,LOW);
          digitalWrite(DIR_T_x,abs(1-dir));
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
      }
    }

}


int movex_toEND(int dir) {
    //int StepsToEnd = steps_x - steps;
    int stepCount = 0;  // number of steps the motor has taken
    
    while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
      digitalWrite(DIR_T_x, dir);      // (HIGH = anti-clockwise / LOW = clockwise)
      digitalWrite(PUL_T_x, HIGH);
      delay(2);                       // Delay to slow down speed of Stepper
      digitalWrite(PUL_T_x, LOW);
      delay(2);
      stepCount++;
      }
      
    for (int i = 0; i < 100; i++) { //Back off switch
            digitalWrite(ENA_T_x,HIGH);
            digitalWrite(PUL_T_x,HIGH);
            digitalWrite(DIR_T_x,abs(1-dir));
            digitalWrite(PUL_T_y,LOW);
            digitalWrite(ENA_T_y,LOW);
            delay(1);
            digitalWrite(PUL_T_x,LOW);
            digitalWrite(ENA_T_x,LOW);
            digitalWrite(DIR_T_x,abs(1-dir));
            digitalWrite(PUL_T_y,LOW);
            digitalWrite(ENA_T_y,LOW);
            delay(1);
        }
   
      
  return stepCount;
}

void movey(int steps, int dir) {
  for (int i = 0; i < steps && digitalRead(home_switch1); i++) {
      digitalWrite(ENA_T_y,HIGH);
      digitalWrite(PUL_T_y,HIGH);
      digitalWrite(DIR_T_y,dir);
      digitalWrite(PUL_T_x,LOW);
      digitalWrite(ENA_T_x,LOW);
      delayMicroseconds(800);
      digitalWrite(PUL_T_y,LOW);
      digitalWrite(ENA_T_y,LOW);
      digitalWrite(DIR_T_y,dir);
      digitalWrite(PUL_T_x,LOW);
      digitalWrite(ENA_T_x,LOW);
      delayMicroseconds(800);
    }

    if (!digitalRead(home_switch1)) { //if switch is activated, back off switch
      for (int i = 0; i < 100; i++) {
            digitalWrite(ENA_T_y,HIGH);
            digitalWrite(PUL_T_y,HIGH);
            digitalWrite(DIR_T_y,abs(1-dir));
            digitalWrite(PUL_T_x,LOW);
            digitalWrite(ENA_T_x,LOW);
            delayMicroseconds(800);
            digitalWrite(PUL_T_y,LOW);
            digitalWrite(ENA_T_y,LOW);
            digitalWrite(DIR_T_y,abs(1-dir));
            digitalWrite(PUL_T_x,LOW);
            digitalWrite(ENA_T_x,LOW);
            delayMicroseconds(800);
          }

    }
}

int movey_toEND(int dir) {
    //int StepsToEnd = steps_y - steps;
    int stepCount = 0;  // number of steps the motor has taken
    
    while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
      digitalWrite(DIR_T_y, dir);
      digitalWrite(PUL_T_y, HIGH);
      delay(1);                       // Delay to slow down speed of Stepper
      digitalWrite(PUL_T_y, LOW);
      delay(1);
      stepCount++;
      }
    for (int i = 0; i < 100; i++) { //Back off switch
          digitalWrite(ENA_T_y,HIGH);
          digitalWrite(PUL_T_y,HIGH);
          digitalWrite(DIR_T_y,abs(1-dir));
          digitalWrite(PUL_T_x,LOW);
          digitalWrite(ENA_T_x,LOW);
          delayMicroseconds(800);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          digitalWrite(DIR_T_y,abs(1-dir));
          digitalWrite(PUL_T_x,LOW);
          digitalWrite(ENA_T_x,LOW);
          delayMicroseconds(800);
        }
     
  return stepCount;
}


void Calibration() {
  // Move to home position in x direction
  while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_x, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_x, HIGH);
    delay(3);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_x, LOW);
    delay(3);
   }

  delay(1000);

  for (int i = 0; i < 300; i++) {    //Back off switch
          digitalWrite(ENA_T_x,HIGH);
          digitalWrite(PUL_T_x,HIGH);
          digitalWrite(DIR_T_x,LOW);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
          digitalWrite(PUL_T_x,LOW);
          digitalWrite(ENA_T_x,LOW);
          digitalWrite(DIR_T_x,LOW);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
      }

  
  delay(1000);

  // Move to home position in y direction

   while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_y, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y, HIGH);
    delayMicroseconds(800);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_y, LOW);
    delayMicroseconds(800);  
   }


  delay(1000);

  for (int i = 0; i < 300; i++) {    //Back off switch
        digitalWrite(ENA_T_y,HIGH);
        digitalWrite(PUL_T_y,HIGH);
        digitalWrite(DIR_T_y,HIGH);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        delayMicroseconds(800);
        digitalWrite(PUL_T_y,LOW);
        digitalWrite(ENA_T_y,LOW);
        digitalWrite(DIR_T_y,HIGH);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        delayMicroseconds(800);
      }

  
  delay(1000);

  
  // Find number of steps it takes to go from home to switch in x and y directions

  steps_x = 0;  // Reset x position variable to zero
  steps_y = 0;  // Reset y position variable to zero

  while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_x, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_x, HIGH);
    delay(3);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_x, LOW);
    delay(3);
    steps_x++;
   }


  delay(1000);

  for (int i = 0; i < 100; i++) {    //Back off switch
          digitalWrite(ENA_T_x,HIGH);
          digitalWrite(PUL_T_x,HIGH);
          digitalWrite(DIR_T_x,HIGH);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
          digitalWrite(PUL_T_x,LOW);
          digitalWrite(ENA_T_x,LOW);
          digitalWrite(DIR_T_x,HIGH);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
      }

  delay(1000);

// Count in y direction

  while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_y, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y, HIGH);
    delay(1);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_y, LOW);
    delay(1);
    steps_y++;
   }
   

  delay(1000);

  for (int i = 0; i < 100; i++) {    //Back off switch
        digitalWrite(ENA_T_y,HIGH);
        digitalWrite(PUL_T_y,HIGH);
        digitalWrite(DIR_T_y,LOW);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        delayMicroseconds(800);
        digitalWrite(PUL_T_y,LOW);
        digitalWrite(ENA_T_y,LOW);
        digitalWrite(DIR_T_y,LOW);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        delayMicroseconds(800);
      }


  delay(1000);
  
  // Move to home position in x direction

  while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_x, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_x, HIGH);
    delay(3);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_x, LOW);
    delay(3);
   }


  delay(1000);

  for (int i = 0; i < 100; i++) {    //Back off switch
          digitalWrite(ENA_T_x,HIGH);
          digitalWrite(PUL_T_x,HIGH);
          digitalWrite(DIR_T_x,LOW);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
          digitalWrite(PUL_T_x,LOW);
          digitalWrite(ENA_T_x,LOW);
          digitalWrite(DIR_T_x,LOW);
          digitalWrite(PUL_T_y,LOW);
          digitalWrite(ENA_T_y,LOW);
          delay(1);
      }

  delay(1000);

  // Move to home position in y direction

   while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_y, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y, HIGH);
    delay(1);                          // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_y, LOW);
    delay(1);   
   }


  delay(1000);

  for (int i = 0; i < 100; i++) {    //Back off switch
        digitalWrite(ENA_T_y,HIGH);
        digitalWrite(PUL_T_y,HIGH);
        digitalWrite(DIR_T_y,HIGH);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        delayMicroseconds(800);
        digitalWrite(PUL_T_y,LOW);
        digitalWrite(ENA_T_y,LOW);
        digitalWrite(DIR_T_y,HIGH);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        delayMicroseconds(800);
      }


//Serial.println(steps_x);
//Serial.println(steps_y);
  
}



void setup() {
  // put your setup code here, to run once:
  pinMode (PUL_T_x, OUTPUT);
  pinMode (DIR_T_x, OUTPUT);
  pinMode (ENA_T_x, OUTPUT);
  Serial.begin(9600);
  digitalWrite(DIR_T_x, HIGH);
  digitalWrite(ENA_T_x,LOW);
  

  pinMode (PUL_T_y, OUTPUT);
  pinMode (DIR_T_y, OUTPUT);
  pinMode (ENA_T_y, OUTPUT);
  Serial.begin(9600);
  digitalWrite(DIR_T_y, HIGH);
  digitalWrite(ENA_T_y,LOW);


  pinMode(home_switch1, INPUT_PULLUP);
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

    else if(motor == "xEND"){
    int step_end = movex_toEND(direc.toInt());
    Serial.println(step_end);
    }

    else if(motor == "yEND"){
    int step_end = movey_toEND(direc.toInt());
    Serial.println(step_end);
    }

    
    else if(motor == "Calibration"){
    Calibration();
    Serial.println(steps_x);
    Serial.println(steps_y);
    }
  }

}
