#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal.h>

 
#define SS_PIN 10
#define RST_PIN 8
int reset = 5;
int Contrast=100;

#define SERVO_PIN a1
Servo myservo;

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal lcd(7,6,5,4,3,2);
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  myservo.attach(A1);
  myservo.write( 70 );
  delay(2000);
  myservo.write( A1 );
  Serial.println("Put your card to the reader...");
  Serial.println();
  pinMode(9, OUTPUT);
  analogWrite(9,Contrast);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Access Control ");
  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card>>");
  //pinMode(3, OUTPUT);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
   {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
   }
   Serial.println();
   Serial.print("Message : ");
   content.toUpperCase();
   if (content.substring(1) == "55 C4 45 0A") //change here the UID of the card
   {
     lcd.setCursor(1,1);
     lcd.print(" rohan ");
     Serial.println("rohan chawan");
     Serial.println();
     myservo.write(180);
     digitalWrite(9,HIGH);
     delay(500);
     lcd.clear();
     myservo.write(0);
     digitalWrite(9,LOW);
     digitalWrite(reset,HIGH);

   }
   else if(content.substring(1) == "B6 C1 98 00"){
     lcd.setCursor(1,1);
     lcd.print(" Access Granted! to kalyan");
     Serial.println("kalyan");
     Serial.println();
     myservo.write(180);
     digitalWrite(9,HIGH);
     delay(500);
     lcd.clear();
     myservo.write(0);
     digitalWrite(9,LOW);
     digitalWrite(reset,HIGH);

   }
   else if(content.substring(1) == "55 C8 56 0A"){
     lcd.setCursor(1,1);
     lcd.print(" sanjay ");
     Serial.println("sanjay");
     Serial.println();
     myservo.write(180);
     digitalWrite(9,HIGH);
     delay(500);
     lcd.clear();
     myservo.write(0);
     digitalWrite(9,LOW);
     digitalWrite(reset,HIGH);

   }
    
 
   else   {
     Serial.println("Acces Denied");
     lcd.clear();
     lcd.print(" Access Control ");
     lcd.setCursor(0, 1);
     lcd.print("Scan Your Card>>");
     delay(DENIED_DELAY);

   }

}