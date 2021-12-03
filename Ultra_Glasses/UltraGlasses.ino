
const int trigPin = 9;
const int echoPin = 10;
int Buzzer = 3;

long duration;
int distance;
void setup() {
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(Buzzer, OUTPUT);
Serial.begin(9600);
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delay(25);
  digitalWrite(trigPin, HIGH);
  delay(25);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance= duration*0.034/2;
  Serial.print("Distance: ");
  Serial.println(distance);

    if (distance < 40){
      tone(Buzzer,400);
      
    }
    if (distance <= 20){
      tone(Buzzer,600);
    }
    
    if (distance >= 50 || distance <= 0){
      noTone(Buzzer);
    }
  
}
