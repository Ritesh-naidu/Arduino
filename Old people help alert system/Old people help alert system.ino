
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL35Zc-vvmU"
#define BLYNK_TEMPLATE_NAME "smart alert system for patients or old age people"
#define BLYNK_AUTH_TOKEN "HuEuBLzM0eiwapRglKdXesqB-rCqy4BR"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "realme 9 Pro+";
char pass[] = "1234567890";
int PB = D3;
int buzz = D2;

void setup() {
  // Debug console
  Serial.begin(9600);
  pinMode(PB, INPUT);
  pinMode(buzz, OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  int pb = digitalRead(PB);
  Serial.println(pb);

  if (pb == 0) {
    Blynk.logEvent("alert","Please attend me");
    digitalWrite(buzz, HIGH);
    delay(1000);
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(buzz, HIGH);
    delay(1000);
    digitalWrite(buzz, LOW);
    delay(500);
    digitalWrite(buzz, HIGH);
    delay(1000);
    digitalWrite(buzz, LOW);
    delay(500);
    
   
  } 
  else {
    Serial.println("No problem");
  }
}