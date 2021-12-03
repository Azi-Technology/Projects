
#include <Adafruit_Fingerprint.h>
#include <Servo.h>

Servo servo;

const int servoPin = 9;
int sound[] = {300, 400};
const int duration = 500;  // 500 miliseconds

SoftwareSerial mySerial(2, 3);   // Setting our Fingerprint ports to 2 and 3

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);   // Our main object

void setup()  
{
  Serial.begin(9600);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  servo.write(0);
  delay(100);
  servo.detach();
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }   // If fingerprint sensor is not found, it's not going to do anything forever
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
}

void loop()                     // run over and over again
{
  openSafeLock();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {                   // This method gets our image we put in our Fingerprint Sensor
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {                                  // This method converts our image taken to a reasonable value 
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {                            // This method searches our fingerprint through the fingerprints that are saved
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int openSafeLock() {                                         // This method runs the whole code where if a fingerprint is matched our safelock opens 
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  servo.attach(servoPin);
  delay(1);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  servo.write(60);
  tone(8, sound[0], duration);
  delay(500);
  tone(8, sound[1], duration);
  delay(500); 
  delay(3000);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  servo.write(180);
  return finger.fingerID; 
}
