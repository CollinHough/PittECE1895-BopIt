int startButton = 13; //pin recieving info from push button
int buttonLED = 9; //analog pin for led in button

// USE THIS FOR EVERY COMMAND DURING BOP IT
// WILL USE AS THE MAX TIME TO COMPLETE TASK
unsigned long timerCount = 0; // variable to hold our timer info, 15 seconds
bool startTimer = false;

// Helper functions to turn led button on or off
#define LEDON() analogWrite(LED, 255)
#define LEDLOW() analogWrite(LED, 10)
#define LEDOFF() analogWrite(LED, 0)

void setup()
{
  pinMode(startButton, INPUT); //set pin as recieving info
  pinMode(buttonLED, OUTPUT); // pin for LED
  LEDOFF();
}

void loop()
{
  if (digitalRead(startButton) == HIGH && !startTimer) 
    { //if the start button has been pushed
     startTimer = true;
     timerCount = 15 * 10; //reset timer
     LEDON();
     //(15 sec * 10 * 1 deciseconds)
     //this is set up to restart the timer whenever the start 
     //button is pushed
     //not extremely exact since that is not what I needed for this project
     //if you are looking for something more exact, look into 
     //SimpleTimer() Arduino funtions and libraries:
     //http://playground.arduino.cc/Code/SimpleTimer#F_restartTimer
     Serial.println("Timer started")
    }
  else if (digitalRead(startButton) == HIGH && startTimer)
  {
    Serial.println("Button was pushed in time");
    LEDOFF();
  }
  if (timerCount != 0)
   { //if the count down timer is still running
     timerCount = timerCount - 1; 
     //count down of a decisecond (0.1 sec)
     delay(100); 
     //delay for timercCount refrence of a decisecond
   } 
   else if (startTimer) { //if the timer has run out
     Serial.println("Timer ran out");
     startTimer = false;
     LEDOFF();
   }
}
