#define BLYNK_TEMPLATE_ID "TMPL3sJLnxheb"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "aaPPG5ynfC6O4OSokKfxrF0-QKeX2FMi"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Galaxy F23 5G";
char pass[] = "sandishsandish";

#define SOIL_SENSOR_PIN A0
#define RELAY_PIN D1
#define MOISTURE_THRESHOLD 300  // Adjust this threshold as needed

BlynkTimer timer;

void checkSoilMoisture() {
  int soilMoistureValue = analogRead(SOIL_SENSOR_PIN);
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);
  
  Blynk.virtualWrite(V1, soilMoistureValue);

  if (soilMoistureValue < MOISTURE_THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn on the relay (and pump)
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn off the relay (and pump)
  }
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(SOIL_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure the relay is off initially

  timer.setInterval(2000L, checkSoilMoisture); // Check soil moisture every 2 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}