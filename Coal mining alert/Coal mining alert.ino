#define BLYNK_TEMPLATE_ID "TMPL3EPryl8LP"
#define BLYNK_TEMPLATE_NAME "Coal"
#define BLYNK_AUTH_TOKEN "A77gxTLUQSPvza2_dGerDlv82CMedKNO"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <DHT_U.h>

 //#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
              

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Galaxy A50s302";  // Enter your Wifi Username
char pass[] = "qidm8392";
  // Enter your Wifi password


  BlynkTimer timer;

int gas = A0;
int sensorThreshold = 100;

int vib = D1;
int vol = D2;
int red = D6;
int green = D5;


#define dhtpin D3
#define dhttype DHT11
DHT dhtsensor(dhtpin, dhttype);
void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  pinMode(vib,INPUT);
  pinMode(vol,INPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);



  
  pinMode(gas, INPUT);
  

 

 Wire.begin();



  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Air Quality");
  lcd.setCursor(3,1);
  lcd.print("Monitoring");
  delay(2000);
  lcd.clear();
  }



void loop(){
{
  Blynk.run();
  int t = dhtsensor.readTemperature();
  int h = dhtsensor.readHumidity();
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h); 
  delay(2000);
  {
    if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   int analogSensor = analogRead(gas);
  Blynk.virtualWrite(V2, analogSensor);
  Serial.print("Gas Value: ");
    Serial.println(analogSensor);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
   
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
    
  Blynk.run();
  timer.run();

  int gasValue = analogRead(gas);
  lcd.setCursor(0,0);
  lcd.print("Temperature "); 
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.setCursor(6,1);
  lcd.write(1);
  // lcd.createChar(1, degree_symbol);
  lcd.setCursor(7,1);
  lcd.print("C");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity ");
  lcd.print(h);
  lcd.print("%");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
 lcd.print(gasValue);
 lcd.clear();
  if(gasValue<400)
  {
    lcd.setCursor(0,0);
    lcd.print("Gas Value: ");
    lcd.print(gasValue);
    lcd.setCursor(0, 1);
    lcd.print("Fresh Air");
    digitalWrite(green,HIGH);
    digitalWrite(red,LOW);

    Serial.println("Fresh Air");
    delay(2000);
    lcd.clear();
  }
  else if(gasValue>400)
  {
    lcd.setCursor(0,0);
    lcd.print(gasValue);
    lcd.setCursor(0, 1);
    lcd.print("Bad Air, CO Carbon Monoxide Dectected");
    Serial.println("BBad Air, CO Carbon Monoxide Dectected");
    digitalWrite(green,LOW);

    digitalWrite(red,HIGH);

    delay(2000);
    lcd.clear();
  }

   if(gasValue > 3){
//    Blynk.email("princeritesh011099@gmail.com", "Alert", "Bad Air!");
    Blynk.logEvent("pollution_alert","Bad Air");
  }
 
}
}

}