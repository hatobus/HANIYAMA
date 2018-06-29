void setup(){
  Serial.begin(9600); 
}

void loop(){
    int val;
    val=analogRead(4);
    Serial.print("Co2 : ");
    Serial.println(val>>2);
    delay(100);
}