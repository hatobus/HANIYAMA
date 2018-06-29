#include <Wire.h>

// Sensor address
#define SHT31_ADDR 0x45

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);
    Serial.println("setup");

    Wire.begin(21,22); // I2C

}

void loop() {
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

    Serial.print(temp);
    Serial.print(" , ");
    Serial.println(humidity);
    delay(5000);

}