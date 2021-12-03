
const int trigPin = 9;
const int echoPin = 10;

const int Buzzer = 3;

const int buttonPin = 2;           
int buttonState = 0;

long duration;
int distance;

void Alarm() {
  tone(Buzzer,600);
  delay(100);
  noTone(Buzzer);
  delay(100);
}

void setup() 
{
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

   buttonState = digitalRead(buttonPin);


    if (distance <= 40){
      
      while (!(buttonState == HIGH)) {
      buttonState = digitalRead(buttonPin);
      Alarm();
      }
      
    }
    
   
}
