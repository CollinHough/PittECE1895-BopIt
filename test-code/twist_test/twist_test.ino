 #define outputA 3
 #define outputB 7
 
 int counter = 0; 
 int aState;
 int aLastState;
 int completedTwist = 1; // Figure out at what increment is enough for a twist

 void setup() { 
   pinMode (outputA,INPUT);
   pinMode (outputB,INPUT);
   pinMode(13, OUTPUT);    // led
   pinMode(8, INPUT);
   
   Serial.begin (9600);
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);   
 } 
 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (digitalRead(8) == HIGH)
   {
    counter = 0;
    delay(50);
    digitalWrite(13, HIGH); // sets the digital pin 13 on
     delay(50);            // waits for a second
     digitalWrite(13, LOW);  // sets the digital pin 13 off
     delay(50);            // waits for a second
   }
   if (aState != aLastState){     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
     
       counter ++;
     
     if (abs(counter) == completedTwist)
     {
      Serial.println("Twist completed");
      digitalWrite(13, HIGH); // sets the digital pin 13 on
     delay(50);            // waits for a second
     digitalWrite(13, LOW);  // sets the digital pin 13 off
     delay(50);            // waits for a second
     }
     Serial.print("Position: ");
     Serial.println(counter);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 }
