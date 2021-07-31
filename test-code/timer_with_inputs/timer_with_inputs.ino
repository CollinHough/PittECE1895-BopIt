#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define encoderA 3
#define smashButton 2
#define startButton 1
#define breakBeam 5
#define led 13

unsigned long timerCount = 0; // variable to hold our timer info, 15 seconds
bool startTimer = false;
int counter = 0; 
int aState;
int aLastState;
int completedTwist = 1; // Figure out at what increment is enough for a twist

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();
  lcd.backlight();
  

  // Set up encoder
  pinMode(encoderA, INPUT);
  // Set up buttons
  pinMode(smashButton, INPUT);
  pinMode(startButton, INPUT);
  // Set up breakbeam
  pinMode(breakBeam, INPUT);
  
  lcd.print("Welcome");

}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(startButton) == HIGH && !startTimer)
  {
    startTimer = true;
    timerCount = 2000 * 10; // around 8 second timer
    aLastState = digitalRead(encoderA);
    lcd.clear();
    lcd.print("Timer started");
  }
  while (timerCount != 0 && startTimer)
  {
    // decrements the counter, delays by a decisecond
    timerCount = timerCount -1;
    delay(0.5);
    if (smashClicked())
    {
      lcd.clear();
      lcd.print("Smash button was hit");
      break;
    }
    if (breakBroke())
    {
      lcd.clear();
      lcd.print("Break beam was broken");
      break;
    }
    if (twisted())
    {
      lcd.clear();
      lcd.print("Encoder twisted");
      break;
    }
  }

  if (timerCount == 0 && startTimer)
  {
    lcd.clear();
    lcd.print("You ran out of time");
  }
  
  startTimer = false;
  

}

bool smashClicked() {
  if (digitalRead(smashButton) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool breakBroke() {
  if (digitalRead(breakBeam) == LOW)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool twisted() {
  aState = digitalRead(encoderA);
//  lcd.clear();
//  lcd.print(aState);
//  delay(200);
  if (aState != aLastState) {
    aLastState = aState;
    return true;
  }
  else
  {
    aLastState = aState;
    return false;
  }
  
}
