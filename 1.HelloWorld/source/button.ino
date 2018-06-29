const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int buttonNumber = 0;

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {

    // buttonNumber increment
    // But, ButtonNumver = 10
    // To change buttonNumber is 0

    if(buttonState == 10){
        buttonNumber = 0;
    } 
    
    else{ 
        buttonNumber++;
    }

    Serial.println(buttonNumber);
  } 

  delay(100);
}