#define SENSORPIN 4 // ir signal pin 

// variables will change:
int sensorState = 0, lastState=0;         // variable for reading the beam status

void setup() {     
  // initialize the sensor pin as an input:
  pinMode(SENSORPIN, INPUT);
  // WILL NEED A 10K RESISTOR, DONT HAVE A INTERNAL PULLUP 
  //digitalWrite(SENSORPIN, HIGH); // turn on the pullup
  
  Serial.begin(9600);
}

void loop(){
  // read the state of the ir beam value:
  sensorState = digitalRead(SENSORPIN);

  // check if the sensor beam is broken
  // if it is, the sensorState is LOW:
  if (sensorState == LOW) {     
    Serial.println("Broke beam") 
  } 
  
  // Below code can be used if we are worried about the door rod landing between beams
  // could work based on toggling, has to go from broken to unbroken to broken again
//  if (sensorState && !lastState) {
//    Serial.println("Unbroken");
//  } 
//  if (!sensorState && lastState) {
//    Serial.println("Broken");
//  }
  lastState = sensorState;
}
