#include <Arduino.h>
#include <Servo.h>

#define ECHO_A 30
#define ECHO_B 25
#define ECHO_C 32

#define TRIG_A 31
#define TRIG_B 24
#define TRIG_C 33

#define IN_1 29
#define IN_2 28
#define IN_3 26
#define IN_4 27

#define button_A 36
#define button_B 37

#define button_state_A 0
#define button_state_B 0

#define servo_R 72
#define servo_L 15
#define servo_C 42

unsigned long tiempo;
unsigned long tiempo2 = 0;

Servo dir_Servo;

void setup_principal(){
  pinMode(ECHO_A, INPUT);
  pinMode(ECHO_B, INPUT);
  pinMode(ECHO_C, INPUT);
  
  pinMode(TRIG_A, INPUT);
  pinMode(TRIG_B, INPUT);
  pinMode(TRIG_B, INPUT);
  
  dir_Servo.attach(35);
  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  
  pinMode(button_A, INPUT);
  pinMode(button_B, INPUT);

  digitalWrite(TRIG_A, LOW);
  digitalWrite(TRIG_B, LOW);
  digitalWrite(TRIG_C, LOW);
}

void crono(int TI) {
  tiempo = millis();

  Serial.print(tiempo);

  if (tiempo - tiempo2 == TI){

    tiempo2 = tiempo;
    abort();
  }
}

int dist_I() {
  unsigned long time_A;
  unsigned long distance_A;

  digitalWrite(TRIG_A, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_A, LOW);

  time_A = pulseIn(ECHO_A, HIGH);
  distance_A = time_A / 59;

  return distance_A;

  delay(100);
}

int dist_F() {
  unsigned long time_B;
  unsigned long distance_B;

  digitalWrite(TRIG_B, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_B, LOW);

  time_B = pulseIn(ECHO_B, HIGH);
  distance_B = time_B / 59;

  return distance_B;

  delay(100);
}

int dist_D() {
  unsigned long time_C;
  unsigned long distance_C;

  digitalWrite(TRIG_C, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_C, LOW);

  time_C = pulseIn(ECHO_C, HIGH);
  distance_C = time_C / 59;

  return distance_C;

  delay(100);
}

void forward() {
  analogWrite(IN_1, 125);
  digitalWrite(IN_2, LOW);
  analogWrite(IN_3, 125);
  digitalWrite(IN_4, LOW);
}

void backward() {
  digitalWrite(IN_1, LOW);
  analogWrite(IN_2, 125);
  digitalWrite(IN_3, LOW);
  analogWrite(IN_4, 125);
}

void brake() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void choque_Front_ACW() {
  brake();
  delay(500);
  backward();
  delay(500);
  brake();
  delay(100);
  dir_Servo.write(servo_L);
  brake();
  delay(100);
}

void choque_Front_CW() {
  brake();
  delay(500);
  backward();
  delay(500);
  brake();
  delay(100);
  dir_Servo.write(servo_R);
  brake();
  delay(100);
}

void main_CW() {
  int D_I = dist_I();
  int D_F = dist_F();
  int D_D = dist_D();

  forward();

  crono(180000); 

  if (D_F <= 47 && D_F >= 15) {
    dir_Servo.write(servo_R);
  } else {
    dir_Servo.write(servo_C);
    delay(100);
  }

  if (D_I <= 20) {
    dir_Servo.write(servo_R);
    delay(500);
    dir_Servo.write(servo_C);
    delay(100);
  }

  if (D_D <= 20) {
    dir_Servo.write(servo_L);
    delay(500);
    dir_Servo.write(servo_C);
    delay(100);
  }

  if (D_F <= 10) {
    choque_Front_CW();
  }
}

void main_ACW() {
  int D_I = dist_I();
  int D_F = dist_F();
  int D_D = dist_D();

  forward();

  crono(180000); 

  if (D_F <= 47 && D_F >= 15) {
    dir_Servo.write(servo_L);
  } else {
    dir_Servo.write(servo_C);
    delay(100);
  }

  if (D_I <= 20) {
    dir_Servo.write(servo_R);
    delay(500);
    dir_Servo.write(servo_C);
    delay(100);
  }

  if (D_D <= 20) {
    dir_Servo.write(servo_L);
    delay(500);
    dir_Servo.write(servo_C);
    delay(100);
  }

  if (D_F <= 10) {
    choque_Front_ACW();
  }
}

void func_buttons() { 
  button_state_B == digitalRead(button_B); 
  button_state_A == digitalRead(button_A); 

  if (button_state_B == HIGH) {
    main_CW();
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  if (button_state_A == HIGH) {
    main_ACW();
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}