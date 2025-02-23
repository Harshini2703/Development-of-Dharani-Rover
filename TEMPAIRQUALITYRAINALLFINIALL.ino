#define BLYNK_TEMPLATE_ID "TMPL3IavJwNSa"
#define BLYNK_TEMPLATE_NAME "Temparature Humidity Monitoring System"
#define BLYNK_AUTH_TOKEN "4lh5DQhbDFQsVMaq5vPoKZ77XwX-6qSU"
 

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

#include <DHT.h>

#include <Wire.h> 

              
char auth[] = "4lh5DQhbDFQsVMaq5vPoKZ77XwX-6qSU"; //Enter the Auth Token send by Blynk
char ssid[] = "BGS";  //Enter your WIFI Name
char pass[] = "bhuvangs2026";  //Enter your WIFI Password

BlynkTimer timer;

int gas = A0;
int sensorThreshold = 10;

#define DHTPIN D2//Connect Out pin to D4 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
#define RAIN_SENSOR_PIN D1


void sendSensor()
{

  int rainDetected = digitalRead(RAIN_SENSOR_PIN);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 

     if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if (rainDetected == LOW) { // Assuming LOW indicates rain detected
    Serial.println("Rain detected!");
    //Blynk.notify("Rain detected!");
    Blynk.virtualWrite(V4, "Rain detected!");
  } else {
    Serial.println("No rain detected.");
    Blynk.virtualWrite(V4, "No rain detected.");
  }
   int analogSensor = analogRead(gas);
  Blynk.virtualWrite(V3, analogSensor);
  Serial.print("Airquality: ");
    Serial.println(analogSensor);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    
   
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
    
    
 
}

void setup()
{   
  
  Serial.begin(115200);
  
 //pinMode(gas, INPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);

 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }