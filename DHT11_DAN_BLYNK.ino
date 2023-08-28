#define BLYNK_TEMPLATE_ID "TMPLKYShVhOs"
#define BLYNK_DEVICE_NAME "Temperature and Humidity Sensor"
#define BLYNK_AUTH_TOKEN "fpvN3wMgYjLAzf9HAdC9ScgFH-bHE-Rk"

#define BLYNK_PRINT Serial
#include <WiFi.h>
//#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp32.h>

#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "AMALIFEL";  // type your wifi name
char pass[] = "ghifari18102000";  // type your wifi password

BlynkTimer timer;


#define DHTPIN 4 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
#define kipas 18

void setup()
{   
  pinMode (4, INPUT);
  pinMode (18, OUTPUT);

  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  dht.begin();
 
}

void loop()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);

  if (digitalRead(t) >= 30){
    digitalWrite(18, HIGH);
    delay(500);
  } else if (digitalRead(t) < 30) {
    digitalWrite(18, LOW);
    delay(500);
  }
  Blynk.run();
  timer.run();
 }