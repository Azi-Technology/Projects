#include <ArduinoJson.h>

const int BUFFER_SIZE = 50;
char buf[BUFFER_SIZE];

int motor1Pin1 = 2;
int motor1Pin2 = 3;
int motor2Pin1 = 4;
int motor2Pin2 = 5;

int ENA = 6;
int ENB = 7;

int y = 0;

int carspeed = 100;
int highspeed = 255; 
int fixingspeed = carspeed;

DynamicJsonDocument doc(1024);

void forward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(ENA, carspeed);
  analogWrite(ENB, carspeed);
  //delay(x);
}
void back() {
  
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(ENA, carspeed);
  analogWrite(ENB, carspeed);
  //delay(x);
}
void right() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  analogWrite(ENA, carspeed);
  analogWrite(ENB, carspeed);
  //delay(x);
}
void left() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  analogWrite(ENA, carspeed);
  analogWrite(ENB, carspeed);
  //delay(x);
}
void stopmotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// 700s = 90 degrees


void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  
}
void loop() {

  if(Serial1.available()){
    String msg = Serial1.readStringUntil('}') +('}');
    //Serial.println(doc["D1"]);

    if(deserializeJson(doc, msg)){
      Serial.println("deserializeJson() failed");
      return;
    }
    
    carspeed = ((int) doc["D2"]);
    
    //Serial.println((int) doc["D2"]);
    Serial.println(carspeed);

    Serial.println("msg: " + msg);
    Serial.println(carspeed);
    
  
  
    if(doc["D1"] == 3){
      Serial.println("forward");
      forward(); 
    }  
    else if(doc["D1"] == 2){
      Serial.println("right");
      right();
    } 
    else if(doc["D1"] == 4){
      Serial.println("back");
      back();
    }
    else if(doc["D1"] == 1){
      Serial.println("left");
      left();
    }
    else {
      Serial.println("stop");
      stopmotors();
    }
     
  } 
    
} 
