#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <tuple>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#define SHT31_ADDR 0x45
#define soilmoistpin A4
#define co2pin A5
#define cdspin A14



Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

const char* ssid = "YOUR-SSID";
const char* password = "YOUR-PASSWORD";

// const int soilmoistpin = 4;
// const int co2pin = 5;
// const int cdspin = 14;
const int deviceNum = YOUR-DEVICE-NUMBER;
String URL = "http://153.127.199.64/recive.php";

HTTPClient http;

// To use std::tuple 
// This method is able to use multiple return value
// So, this time 
// return value 1 --> temp
// return value 2 --> humidity

std::tuple<float, float> getTempAndHumid(){
  byte command[2] = { 0x24, 0x00 };
  byte data[7];

  Wire.beginTransmission(SHT31_ADDR);
  Wire.write(command, sizeof(command));
  Wire.endTransmission();

  delay(300);

  int i = 0;
  Wire.requestFrom(SHT31_ADDR, 6);
  while (Wire.available() && i < 6) {
    data[i++] = Wire.read();
  }

  data[i] = 0;

  float temp = -50.0 + (175.0 * (unsigned int)(data[0] * 256 + data[1]) / 65535.0);
  float humidity = (100.0 * (unsigned int)(data[3] * 256 + data[4])) / 65535.0;

  return std::forward_as_tuple(temp, humidity);
}

void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  delay(10);

  // To Connect WiFi
  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Connection check
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);

  // HTTP setup
  http.begin(URL);
  http.addHeader("Content-Type", "application/json");

  // SHT31 setup
  Wire.begin(21, 22);   

  configureSensor();
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp, humid;
  int soilhumid, co2Concentrate, cdslight;
  double lux;
  int httpstatus;

  std::tie(temp, humid) = getTempAndHumid();
  soilhumid = getSoilMoist(soilmoistpin);
  co2Concentrate = getCo2(co2pin);
  cdslight = getcds(cdspin);
  lux = getLux();

  httpstatus = postDataToDB(
                    temp,
                    humid, 
                    soilhumid, 
                    co2Concentrate, 
                    cdslight, 
                    lux
                );
  
  printStatus(
            temp,
            humid, 
            soilhumid, 
            co2Concentrate, 
            cdslight, 
            lux,
            httpstatus
        );
  
  delay(10000);
}

// get soil moisture level
int getSoilMoist(int pin){
  int moist;
  moist = analogRead(A4);
  return moist>>2;  
}

// get Co2 Concentrate
int getCo2(int pin){
  int co2;
  co2 = analogRead(pin);
  return co2 >> 2;
}

// get cds light sensor
int getcds(int pin){
  int light;
  light = analogRead(pin);
  return light >> 2;
}

// get Lux
double getLux(){
  sensors_event_t event;
  tsl.getEvent(&event);
  return event.light;
}

// post data for DB
int postDataToDB(float temp, float humid, int soilhumid, int co2Concentrate, int cdslight, double lux){
  String postdata = "{\"no\" :" + String(deviceNum) + ", " + "\"temperature\" :" + String(temp) + ", " + "\"humidity\" :" + String(humid) + ", " + "\"soil_humidity\" :" + String(soilhumid) + ", " + "\"co2_concentration\" :" + String(co2Concentrate) + ", " + "\"wavelength\" :" + String(cdslight) + ", " + "\"illuminance\" :" + String(lux) + "}";
  int httpResponseCode = http.POST(postdata);
  Serial.println(postdata);
  return httpResponseCode;
}

void printStatus(float temp, float humid, int soilhumid, int co2Concentrate, int cdslight, double lux, int status){
  Serial.println(temp);
  Serial.println(humid);
  Serial.println(soilhumid);
  Serial.println(co2Concentrate);
  Serial.println(cdslight);
  Serial.println(lux);
  Serial.println(status);
  Serial.println();
}
