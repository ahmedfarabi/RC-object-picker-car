#include <Servo.h>

Servo s1;
Servo s2;
int volatile pos;
int volatile udpos;
boolean volatile grabToggle = false;


int motor_left[] = {52, 53};
int motor_right[] = {46, 47};
int motor_left2[] = {48, 49};
int motor_right2[] = {44, 45};

//int enablePin = 5; // pin 1 on L293D IC
char state;
int flag=0;        //makes sure that the serial only prints once the state
 
void setup() {
    // Setup motors
    int i;
    for(i = 0; i < 4; i++){
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
    pinMode(motor_left2[i], OUTPUT);
    pinMode(motor_right2[i], OUTPUT);
    }
    s1.attach(9);
    s2.attach(10);
    pos = 90;
    udpos=90;
    //pinMode(enablePin, OUTPUT);
    // sets enablePin high so that motor can turn on:
    //digitalWrite(enablePin, HIGH);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
}
 
void loop() {
    //if some date is sent, reads it and saves in state
    if(Serial.available() > 0){     
      state = Serial.read();   
      flag=0;
    }
     
     if(state=='u') {
      updown(0);
    } else if(state=='d') {
      updown(1);
    } else if(state=='o' || state=='c') { //TODO
      grab();
    }
 
    
    // if the state is '0' the DC motor will turn off
    if (state == 'c') {
        digitalWrite(motor_left[0], LOW);
        digitalWrite(motor_left[1], LOW);
        digitalWrite(motor_left2[0], LOW);
        digitalWrite(motor_left2[1], LOW);
        
        
        digitalWrite(motor_right[0], LOW);
        digitalWrite(motor_right[1], LOW);
        digitalWrite(motor_right2[0], LOW);
        digitalWrite(motor_right2[1], LOW);


        
        if(flag == 0){
          Serial.println("Motor: off");
          flag=1;
        }
    }
    // if the state is '1' the motor will turn right
    else if (state == 'r') {
        digitalWrite(motor_left[0], HIGH);
        digitalWrite(motor_left[1], LOW);
        digitalWrite(motor_left2[0], HIGH);
        digitalWrite(motor_left2[1], LOW);
        
        
        digitalWrite(motor_right[0], LOW);
        digitalWrite(motor_right[1], HIGH);
        digitalWrite(motor_right2[0], LOW);
        digitalWrite(motor_right2[1], HIGH);

        
        if(flag == 0){
          Serial.println("Motor: right");
          flag=1;
        }
    }
    // if the state is '2' the motor will turn left
    else if (state == 'l') {
        digitalWrite(motor_left[0], LOW);
        digitalWrite(motor_left[1], HIGH);
        digitalWrite(motor_left2[0], LOW);
        digitalWrite(motor_left2[1], HIGH);
        
        
        digitalWrite(motor_right[0], HIGH);
        digitalWrite(motor_right[1], LOW);
        digitalWrite(motor_right2[0], HIGH);
        digitalWrite(motor_right2[1], LOW);
        if(flag == 0){
          Serial.println("Motor: left");
          flag=1;
        }
    }
    else if (state == 'f') {
        digitalWrite(motor_left[0], HIGH);
        digitalWrite(motor_left[1], LOW);
        digitalWrite(motor_left2[0], HIGH);
        digitalWrite(motor_left2[1], LOW);
        
        
        digitalWrite(motor_right[0], HIGH);
        digitalWrite(motor_right[1], LOW);
        digitalWrite(motor_right2[0], HIGH);
        digitalWrite(motor_right2[1], LOW);
        if(flag == 0){
          Serial.println("Motor: forward");
          flag=1;
        }
    }
    else if (state == 'b') {
        digitalWrite(motor_left[0], LOW);
        digitalWrite(motor_left[1], HIGH);
        digitalWrite(motor_left2[0], LOW);
        digitalWrite(motor_left2[1], HIGH);
        
        digitalWrite(motor_right[0], LOW);
        digitalWrite(motor_right[1], HIGH);
        digitalWrite(motor_right2[0], LOW);
        digitalWrite(motor_right2[1], HIGH);
        if(flag == 0){
          Serial.println("Motor: backward");
          flag=1;
        }
    }
}

  void grab() {
    if (pos == 30) {
      pos = 90;
    } else {
      pos = 30;
    }
    s1.write(pos);
    Serial.println("GRAB TOGGLE");
  }
  
  void updown(int dir) {
    if(dir==0) { //up
    Serial.println("UP");
      if(udpos<=120 && udpos>30) {
        udpos -= 30;
      }
      s2.write(udpos);
    } else { //down
    Serial.println("Down");
      if(udpos>=30 && udpos<120) {
        udpos += 30;
      }
      s2.write(udpos);
    }
  }
