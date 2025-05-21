#include <Arduino.h>
#include <esp32-hal-ledc.h>

volatile float Left_photosensitive;
volatile float Right_photosensitive;
volatile int Lightseeking_Degree;
volatile float f;
volatile int speed_value;
#define L_light_PIN 35
#define R_light_PIN 34
#define ENA 3
#define ENA_PIN 25
#define IN1 27
#define IN2 26
#define IN3 12
#define IN4 14
#define ENB 4
#define ENB_PIN 13
#define carSpeed 250


void Forward(){ 
  ledcWrite(ENA, carSpeed); //enable L298n A channel
  ledcWrite(ENB, carSpeed); //enable L298n B channel
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("Forward");
}

void Back() {
  ledcWrite(ENA, carSpeed); //enable L298n A channel
  ledcWrite(ENB, carSpeed); //enable L298n B channel
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Serial.println("Back");
}

void Left() {
  ledcWrite(ENA, carSpeed); //enable L298n A channel
  ledcWrite(ENB, carSpeed); //enable L298n B channel
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  //Serial.println("Left");
}

void Right() {
  ledcWrite(ENA, carSpeed); //enable L298n A channel
  ledcWrite(ENB, carSpeed); //enable L298n B channel
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Serial.println("Right");
}

void Stop() {
  ledcWrite(ENA, 0); //enable L298n A channel
  ledcWrite(ENB, 0); //enable L298n B channel
  //Serial.println("Stop!");
} 

void Light_Seeking() {
  Left_photosensitive = analogRead(L_light_PIN) / 35;
  Right_photosensitive = analogRead(R_light_PIN) / 35;
  Serial.print("Left_photosensitive:");
  Serial.println(Left_photosensitive);
  Serial.print("Right_photosensitive:");
  Serial.println(Right_photosensitive);
  Serial.println("");
  if (Left_photosensitive > 40 && Right_photosensitive > 40) {
    Stop();
  } else {
    if (Left_photosensitive > Right_photosensitive) {
      Lightseeking_Degree = ((float)(Right_photosensitive / Left_photosensitive)) * 90;
    } else if (Left_photosensitive <= Right_photosensitive) {
      Lightseeking_Degree = 180 - ((float)(Left_photosensitive / Right_photosensitive)) * 90;
    }
    if (Lightseeking_Degree < 90) {
      f = ((float)(Lightseeking_Degree)) / 90;
      ledcWrite(ENA, carSpeed* 0.5*f); //enable L298n A channel
      ledcWrite(ENB, carSpeed); //enable L298n B channel
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    if (Lightseeking_Degree > 90) {
      f = ((float)(180 - Lightseeking_Degree)) / 90;
      ledcWrite(ENA, carSpeed); //enable L298n A channel
      ledcWrite(ENB, carSpeed* 0.5*f); //enable L298n B channel
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH); 
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    if (Lightseeking_Degree == 90) {
      f = ((float)(Lightseeking_Degree)) / 90;
      Forward();
    }
  }
}

void setup(){
  Left_photosensitive = 0;
  Right_photosensitive = 0;
  Lightseeking_Degree = 0;
  f = 0;
  Serial.begin(9600);
  pinMode(L_light_PIN, INPUT);
  pinMode(R_light_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  ledcSetup(ENA,5000,8);
  ledcSetup(ENB,5000,8);
  ledcAttachPin(ENA_PIN,ENA);
  ledcAttachPin(ENB_PIN,ENB);
}

void loop(){
  Light_Seeking();

}
