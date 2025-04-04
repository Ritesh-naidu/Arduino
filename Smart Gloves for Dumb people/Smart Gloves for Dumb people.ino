#include <SPI.h>
#include <LiquidCrystal.h>
//#define SS_PIN 10
//#define RST_PIN 8

int Contrast=100;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to

LiquidCrystal lcd(7,6,5,4,3,2);

int thumb;
int first_finger;
int second_finger;
int third_finger;
int fourth_finger;
int TF1=thumb&&first_finger;
int TF2=first_finger&&second_finger;
int TF3=second_finger&&third_finger;
int TF4=third_finger&&fourth_finger;
int TF5=fourth_finger&&thumb;
int buzzer = 8;


void setup() {
  SPI.begin();   
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  analogWrite(9,Contrast);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  
}

void loop() {
  // put your main code here, to run repeatedly:
int thumb = analogRead(A0);
int first_finger = analogRead(A1);
int second_finger = analogRead(A2);
int third_finger = analogRead(A3);
int fourth_finger = analogRead(A4);
Serial.print(thumb);
Serial.print("\t");



Serial.print(first_finger);
Serial.print("\t");


Serial.print(second_finger);
Serial.print("\t");


Serial.print(third_finger);
Serial.print("\t");



Serial.println(fourth_finger);
Serial.print("\t");


if(thumb <= 20 )
{
  lcd.clear();
  digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("I NEED WATER");
Serial.println("I NEED WATER");
delay(500);
digitalWrite(buzzer,LOW);
  
  }
else if((thumb <= 20 ) && (thumb == TF1<=20))
{
  lcd.clear();
digitalWrite(buzzer,LOW);
lcd.setCursor(1,0);
lcd.print("I have exam");
Serial.println("I have exam");
delay(500);
digitalWrite(buzzer,HIGH);
}



else if(first_finger <=10 )
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("I NEED FOOD");
Serial.println("I NEED FOOD");
delay(500);
//digitalWrite(buzzer,HIGH);  
  }
else if((TF2) &&(first_finger <=20 && second_finger <=20))
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("In next month");
Serial.println("In next month");
delay(500);
//digitalWrite(buzzer,HIGH);
}
else if(second_finger <=20 )
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("RESTROOM");
Serial.println("RESTROOM");
delay(500);
//digitalWrite(buzzer,HIGH);
}
else if((TF3) &&(second_finger <=20 && third_finger <=20))
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("IN  my college only");
Serial.println("IN  my college only");
delay(500);
//digitalWrite(buzzer,HIGH);
}


 else if(third_finger <=20 )
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("MY NAME IS OMAR"); 
Serial.println("MY NAME IS OMAR"); 
delay(500);
//digitalWrite(buzzer,HIGH);
}

 else if(TF4  && (third_finger && fourth_finger))
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("In same class"); 
Serial.println("In same class"); 
delay(500);
//digitalWrite(buzzer,HIGH);
}
else if(fourth_finger <=20 )
{
  lcd.clear();
  digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("I AM FROM MSCS");
Serial.println("I AM FROM MSCS");
delay(500);
//digitalWrite(buzzer,HIGH);

  
  }
  else if((TF5) &&(fourth_finger <=20&& thumb <=20))
{
  lcd.clear();
digitalWrite(buzzer,HIGH);
lcd.setCursor(1,0);
lcd.print("Roll NO");
Serial.println("Roll NO");
delay(500);
//digitalWrite(buzzer,LOW);

  
  }

  else{
     lcd.clear();
     digitalWrite(buzzer,LOW);
    lcd.setCursor(1,0);
    lcd.print("NOTHING");
    Serial.println("NOTHING");
    delay(500);
    }






}