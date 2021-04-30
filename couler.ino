/*     Arduino Project - Color Sorting Machine

    by Dejan Nedelkovski, www.HowToMechatronics.com

*/
#include <Servo.h>

#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;

int frequency = 0;
int color = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  topServo.attach(7);
  bottomServo.attach(8);

  Serial.begin(1200);
}

void loop() {

  topServo.write(115);
  delay(50);

  for (int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(50);

  color = readColor();
  delay(500);

  switch (color) {
    case 1:
      bottomServo.write(50);
      break;


    case 2:
      bottomServo.write(145);
      break;
  }
  delay(30);

  for (int i = 65; i > 29; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(20);

  for (int i = 29; i < 115; i++) {
    topServo.write(i);
    delay(2);
  }
  color = 0;
}

// Custom Function - readColor()
int readColor() {

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;

  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(5);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("G= ");//printing name
  Serial.print(frequency);
  Serial.print("  ");
  delay(5);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println("  ");
  delay(5);

  if (R<125 & R>100 & G<155 & G>127) {
    color = 1; // go nut
  }
  if (R<156 & R>133 & G<190 & G>160) {
    color = 2; // nogo nut
  }
  return color;
}
