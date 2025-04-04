#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

 
#define SS_PIN 10 //SS is SDA
#define RST_PIN 5

Servo servo;
int red=6;
int white=3;
int green=9;
int buzz=8;

#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(white,OUTPUT);
  pinMode(buzz,OUTPUT);
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522


  delay(2000);
  servo.attach(7);
  Serial.println("Put your card to the reader...");
  Serial.println();


  //pinMode(3, OUTPUT);
}
void loop() 
{
       digitalWrite(red,HIGH);
      delay(1000);
           digitalWrite(red,LOW);
      delay(500);
           digitalWrite(white,HIGH);
      delay(1000);
                 digitalWrite(white,LOW);
      delay(500);
           digitalWrite(green,HIGH);
      delay(1000);
                 digitalWrite(green,LOW);
      delay(500);
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
   if (content.substring(1) == "91 9E DD 1B") //change here the UID of the card
   {

     Serial.println("Ambulance is on the way");
     Serial.println();
     digitalWrite(green,HIGH);
     digitalWrite(buzz,HIGH);
   delay(1500);
     servo.write(180);
     delay(3000);
     servo.write(0);
    digitalWrite(green,LOW);
    digitalWrite(buzz,LOW);


   }


}