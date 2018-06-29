int cdsval = 0;

void setup(){
    Serial.begin(9600);
}

void loop(){
    cdsval = analogRead(10);
    Serial.println(cdsval);
    Serial.println(cdsval/4);
    Serial.println();
    delay(1000);
}