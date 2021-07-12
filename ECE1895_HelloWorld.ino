const int ledPin = 13;
const int buttonPin = 8;

void setup() {
  pinMode(ledPin, OUTPUT);    // sets the digital pin 13 as output
  pinMode(buttonPin, INPUT);
}

void loop() {
   // Check if button is being pressed
   if(digitalRead(buttonPin) == HIGH) {
      // When button is pressed, turn on LED
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(100);                  // wait for a second
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
      delay(100);        
   }
   digitalWrite(ledPin, LOW);
}
