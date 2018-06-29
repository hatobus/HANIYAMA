#include <DHTesp.h>

DHTesp dht;

TaskHandle_t tempTaskHandle = NULL;

int dhtPin = 17;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.setup(dhtPin, DHTesp::DHT11);
}

void loop() {
  // put your main code here, to run repeatedly:
  TempAndHumidity lastValues = dht.getTempAndHumidity();

  Serial.println("Temperature: " + String(lastValues.temperature,0));
  Serial.println("Humidity: " + String(lastValues.humidity,0));

  delay(1000);
}