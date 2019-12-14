#include <SPI.h>

String motor;
String steps;
String dir;
String direc;

String xEND;
String yEND;


int steps_x;
int steps_y;

int PUL_T_x = 42; //define Pulse pin for motor 1
int DIR_T_x = 44; //define Direction pin for motor 1
int ENA_T_x = 40; //define Enable Pin for motor 1

int PUL_T_y1 = 30; //define Pulse pin for motor 2
int DIR_T_y1 = 32; //define Direction pin for motor 2
int ENA_T_y1 = 28; //define Enable Pin for motor 2

int PUL_T_y2 = 50; //define Pulse pin for motor 3
int DIR_T_y2 = 52; //define Direction pin for motor 3
int ENA_T_y2 = 48; //define Enable Pin for motor 3

int home_switch1 = 7; //define homing switches pin

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


  pinMode(home_switch1, INPUT_PULLUP);

  // Move to home position in x direction

  while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_x, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_x, HIGH);
    delay(3);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_x, LOW);
    delay(3);
   }


  while (!digitalRead(home_switch1)){ // Do this until the switch is not activated
    digitalWrite(DIR_T_x, LOW); 
    digitalWrite(PUL_T_x, HIGH);
    delay(10);                       // More delay to slow even more while moving away from switch
    digitalWrite(PUL_T_x, LOW);
    delay(10);
  }

  delay(1000);

  // Move to home position in y direction

   while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_y1, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y1, HIGH);
    digitalWrite(DIR_T_y2, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y2, HIGH);
    delay(1);                          // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_y1, LOW);
    digitalWrite(PUL_T_y2, LOW);
    delay(1);   
   }


  while (!digitalRead(home_switch1)) { // Do this until the switch is not activated
    digitalWrite(DIR_T_y1, HIGH); 
    digitalWrite(PUL_T_y1, HIGH);
    digitalWrite(DIR_T_y2, HIGH); 
    digitalWrite(PUL_T_y2, HIGH);
    delay(5);                     // More delay to slow even more while moving away from switch
    digitalWrite(PUL_T_y1, LOW);
    digitalWrite(PUL_T_y2, LOW);
    delay(5);
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

  while (!digitalRead(home_switch1)){ // Do this until the switch is not activated
    digitalWrite(DIR_T_x, HIGH); 
    digitalWrite(PUL_T_x, HIGH);
    delay(10);                       // More delay to slow even more while moving away from switch
    digitalWrite(PUL_T_x, LOW);
    delay(10);
  }

  delay(1000);

// Count in y direction

  while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_y1, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y1, HIGH);
    digitalWrite(DIR_T_y2, HIGH);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y2, HIGH);
    delay(1);                       // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_y1, LOW);
    digitalWrite(PUL_T_y2, LOW);
    delay(1);
    steps_y++;
   }

  while (!digitalRead(home_switch1)) { // Do this until the switch is not activated
    digitalWrite(DIR_T_y1, LOW); 
    digitalWrite(PUL_T_y1, HIGH);
    digitalWrite(DIR_T_y2, LOW); 
    digitalWrite(PUL_T_y2, HIGH);
    delay(5);                     // More delay to slow even more while moving away from switch
    digitalWrite(PUL_T_y1, LOW);
    digitalWrite(PUL_T_y2, LOW);
    delay(5);
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


  while (!digitalRead(home_switch1)){ // Do this until the switch is not activated
    digitalWrite(DIR_T_x, LOW); 
    digitalWrite(PUL_T_x, HIGH);
    delay(10);                       // More delay to slow even more while moving away from switch
    digitalWrite(PUL_T_x, LOW);
    delay(10);
  }

  delay(1000);

  // Move to home position in y direction

   while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
    digitalWrite(DIR_T_y1, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y1, HIGH);
    digitalWrite(DIR_T_y2, LOW);      // (HIGH = anti-clockwise / LOW = clockwise)
    digitalWrite(PUL_T_y2, HIGH);
    delay(1);                          // Delay to slow down speed of Stepper
    digitalWrite(PUL_T_y1, LOW);
    digitalWrite(PUL_T_y2, LOW);
    delay(1);   
   }


  while (!digitalRead(home_switch1)) { // Do this until the switch is not activated
    digitalWrite(DIR_T_y1, HIGH); 
    digitalWrite(PUL_T_y1, HIGH);
    digitalWrite(DIR_T_y2, HIGH); 
    digitalWrite(PUL_T_y2, HIGH);
    delay(5);                     // More delay to slow even more while moving away from switch
    digitalWrite(PUL_T_y1, LOW);
    digitalWrite(PUL_T_y2, LOW);
    delay(5);
  }

  delay(1000);


Serial.println(steps_x);
Serial.println(steps_y);
  
}

void movex(int steps, int dir) {
    for (int i = 0; i < steps && digitalRead(home_switch1); i++) {
        digitalWrite(ENA_T_x,HIGH);
        digitalWrite(PUL_T_x,HIGH);
        digitalWrite(DIR_T_x,dir);
        digitalWrite(PUL_T_y1,LOW);
        digitalWrite(ENA_T_y1,LOW);
        digitalWrite(PUL_T_y2,LOW);
        digitalWrite(ENA_T_y2,LOW);
        delay(1);
        digitalWrite(PUL_T_x,LOW);
        digitalWrite(ENA_T_x,LOW);
        digitalWrite(DIR_T_x,dir);
        digitalWrite(PUL_T_y1,LOW);
        digitalWrite(ENA_T_y1,LOW);
        digitalWrite(PUL_T_y2,LOW);
        digitalWrite(ENA_T_y2,LOW);
        delay(1);
    }
    while (!digitalRead(home_switch1)){ // Do this until the switch is not activated
      digitalWrite(DIR_T_x, abs(1-dir)); 
      digitalWrite(PUL_T_x, HIGH);
      delay(10);                     // More delay to slow even more while moving away from switch
      digitalWrite(PUL_T_x, LOW);
      delay(10);
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
      
    while (!digitalRead(home_switch1)){ // Do this until the switch is not activated
      digitalWrite(DIR_T_x, abs(1-dir)); 
      digitalWrite(PUL_T_x, HIGH);
      delay(10);                       // More delay to slow even more while moving away from switch
      digitalWrite(PUL_T_x, LOW);
      delay(10);
  }
   
      
  return stepCount;
}

void movey(int steps, int dir) {
  for (int i = 0; i < steps && digitalRead(home_switch1); i++) {
      digitalWrite(ENA_T_y1,HIGH);
      digitalWrite(PUL_T_y1,HIGH);
      digitalWrite(ENA_T_y2,HIGH);
      digitalWrite(PUL_T_y2,HIGH);
      digitalWrite(DIR_T_y1,dir);
      digitalWrite(DIR_T_y2,dir);
      digitalWrite(PUL_T_x,LOW);
      digitalWrite(ENA_T_x,LOW);
      delayMicroseconds(800);
      digitalWrite(PUL_T_y1,LOW);
      digitalWrite(ENA_T_y1,LOW);
      digitalWrite(PUL_T_y2,LOW);
      digitalWrite(ENA_T_y2,LOW);
      digitalWrite(DIR_T_y1,dir);
      digitalWrite(DIR_T_y2,dir);
      digitalWrite(PUL_T_x,LOW);
      digitalWrite(ENA_T_x,LOW);
      delayMicroseconds(800);
    }

    while (!digitalRead(home_switch1)) { // Do this until the switch is not activated
      digitalWrite(DIR_T_y1, abs(1-dir)); 
      digitalWrite(PUL_T_y1, HIGH);
      digitalWrite(DIR_T_y2, abs(1-dir)); 
      digitalWrite(PUL_T_y2, HIGH);
      delay(5);                     // More delay to slow even more while moving away from switch
      digitalWrite(PUL_T_y1, LOW);
      digitalWrite(PUL_T_y2, LOW);
      delay(5);
    }
}

int movey_toEND(int dir) {
    //int StepsToEnd = steps_y - steps;
    int stepCount = 0;  // number of steps the motor has taken
    
    while (digitalRead(home_switch1)) {  // Do this until the switch is activated   
      digitalWrite(DIR_T_y1, dir);
      digitalWrite(DIR_T_y2, dir);
      digitalWrite(PUL_T_y1, HIGH);
      digitalWrite(PUL_T_y2, HIGH);
      delay(1);                       // Delay to slow down speed of Stepper
      digitalWrite(PUL_T_y1, LOW);
      digitalWrite(PUL_T_y2, LOW);
      delay(1);
      stepCount++;
      }
    while (!digitalRead(home_switch1)) { // Do this until the switch is not activated
      digitalWrite(DIR_T_y1, abs(1-dir)); 
      digitalWrite(PUL_T_y1, HIGH);
      digitalWrite(DIR_T_y2, abs(1-dir)); 
      digitalWrite(PUL_T_y2, HIGH);
      delay(5);                     // More delay to slow even more while moving away from switch
      digitalWrite(PUL_T_y1, LOW);
      digitalWrite(PUL_T_y2, LOW);
      delay(5);
  }     
  return stepCount;
}


void loop() {
  // put your main code here, to run repeatedly:
    if(Serial.available()>0) {
    motor = Serial.readStringUntil(',');
    steps = Serial.readStringUntil(',');
    direc = Serial.readStringUntil('\n');
    
    int stepCount = 0;  // number of steps the motor has taken
    
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
  }

}
