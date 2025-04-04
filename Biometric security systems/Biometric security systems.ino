#include <Adafruit_Fingerprint.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#if (defined(AVR) || defined(ESP8266)) && !defined(AVR_ATmega2560)
#define ACCESS_DELAY    1000
#include<Servo.h>
int reset = 5;
int Contrast=100;
int led = 4;
int buz = 6;

Servo myservo; 

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// Set up the serial port to use softwareserial..
SoftwareSerial mySerial(2, 3);

#else
// On Leonardo/M0/etc, others with hardware serial, use hardware serial!
// #0 is green wire, #1 is white
#define mySerial Serial1

#endif


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
//LiquidCrystal lcd(7,6,5,4,3,2);

void setup()
{
  Serial.begin(9600);
  myservo.attach(8);
  pinMode(led,OUTPUT);  // set the data rate for the sensor serial port
  pinMode(buz,OUTPUT);  // set the data rate for the sensor serial port  
  finger.begin(57600);
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FingerPrint Lock");
  lcd.setCursor(0, 1);
  lcd.print("Scan your Finger");
  //
  delay(5);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}

void loop()                     // run over and over again
{
  getFingerprintID();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
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
  switch (p) {
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
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    if(finger.fingerID == 1){
      lcd.clear();
      lcd.setCursor(0,0);
      Serial.println(" Name : Ritesh");
      lcd.print(" Name : Ritesh");
      lcd.setCursor(0,1);
      lcd.print(" Access Approved");
    }
    else if(finger.fingerID == 2){
      Serial.println(" Name : Vara Lakshmi");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Name:VaraLakshmi");
      lcd.setCursor(0,1);
      lcd.print(" Access Approved");
    }
    else if(finger.fingerID == 3){
      //lcd.setCursor(1,1);
      lcd.clear();
      Serial.println(" Name is Pradeep");
      lcd.print(" Name : Pradeep");
      lcd.setCursor(0,1);
      lcd.print(" Access Approved");
    }
    else if(finger.fingerID == 5){
      //lcd.setCursor(1,1);
      lcd.clear();
      Serial.println(" Name is jagadhiswar");
      lcd.print("Name:jagadhiswar"); 
      lcd.setCursor(0,1);
      lcd.print(" Access Approved");
    }   
    else if(finger.fingerID == 7){
      //lcd.setCursor(1,1);
      lcd.clear(); 
      Serial.println(" Name is abhilash");
      lcd.print("Name : abhilash");
      lcd.setCursor(0,1);
      lcd.print(" Access Approved");
    }     
    else if(finger.fingerID == 11){
      //lcd.setCursor(1,1);
      lcd.clear();  
      Serial.println(" Name is Bhavana");
      lcd.print("Name : Bhavana");
      lcd.setCursor(0,1);
      lcd.print(" Access Approved");
    }   
      digitalWrite(led, HIGH);
      myservo.write(180);
      delay(1000);

      //digitalWrite(RELAY_PIN, LOW);
      delay(ACCESS_DELAY);
      myservo.write(0);
      digitalWrite(led, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FingerPrint Lock");
      lcd.setCursor(0, 1);
      lcd.print("Scan your Finger");

      //digitalWrite(RELAY_PIN, HIGH); 
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
      Serial.println("Did not find a match");
      lcd.clear();
      lcd.print("Fingerprint not");
      lcd.setCursor(0,1);
      lcd.print("registered");
      digitalWrite(buz, HIGH);    
      delay(500);
      digitalWrite(buz, LOW);
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
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;



  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}