#include <Servo.h>

Servo s1;
Servo s2;
int volatile pos;
int volatile udpos;
boolean volatile grabToggle = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ENTER NOW");
  s1.attach(9);
  s2.attach(10);
  pos = 90;
  udpos=90;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char state = Serial.read();
    if(state=='u') {
      updown(0);
    } else if(state=='d') {
      updown(1);
    } else if(state=='o' || state=='c') { //TODO
      grab();
    }
  }
}

boolean drive(Servo sv, int start, int finish, int dir, int pos) {
  //todo
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
