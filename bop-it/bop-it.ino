
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "SD.h"
#include "TMRpcm.h"
#include "SPI.h"

#define SD_ChipSelectPin 4
#define encoder 3
#define walkSignButton 2
#define startButton 1
#define breakBeam 5
#define led 8
#define startTime 450000
#define victoryLight 7

unsigned long timerCount = 0; // variable to hold our timer info
unsigned long roundTime = 0;
bool startGame = false;
int encoderState;
int encoderLastState;
int breakBeamLastState;
int completedTwist = 1; // Figure out at what increment is enough for a twist
long randNumber;
int points = 0;
int roundNum = 0;
int inputHit = -1;
char str[] = "P I T T        ";

TMRpcm tmrpcm;
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  randomSeed(analogRead(A3));

  lcd.init();
  lcd.backlight();
  //lcd.autoscroll();
  
  // Set up encoder
  pinMode(encoder, INPUT);
  // Set up buttons
  pinMode(walkSignButton, INPUT);
  pinMode(startButton, INPUT);
  // Set up breakbeam
  pinMode(breakBeam, INPUT);
  // Set up victory lights
  pinMode(victoryLight, OUTPUT);

  // Set up test led
  pinMode(led, OUTPUT);

  tmrpcm.speakerPin=9;
  if(!SD.begin(SD_ChipSelectPin))
  {
    digitalWrite(led, HIGH);
    return;
  }

  // Play intro song, the victory song
  tmrpcm.loop(1);
  //tmrpcm.play("SC.wav");
  //delay(20000);
  //tmrpcm.play("Penn.wav");
  tmrpcm.play("VS.wav");

  lcd.clear();
  lcd.autoscroll();
  lcd.setCursor(15, 0);
  for (int i = 0; i < strlen(str); i++)
  {
    lcd.print(str[i]);
    delay(500);
  }

  lcd.noAutoscroll();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("P I T T");
  lcd.setCursor(0,1);
  lcd.print("Start");
  

}

void loop() {
    
  // Start first round
  if (digitalRead(startButton) == HIGH && !startGame)
  {
    // Stop intro song
    //tmrpcm.disable();
    tmrpcm.loop(0);
    
    digitalWrite(led, HIGH);

    // Flag for game currently playing
    startGame = true;
    // Timer variable for round timing
    timerCount = startTime; // around 8 second timer
    roundTime = startTime;

    // Set the last states to be used when comparing 
    encoderLastState = digitalRead(encoder);
    breakBeamLastState = digitalRead(breakBeam);

    // Points and round number
    points = 0;
    roundNum = 1;

    // Randomly selects command
    randNumber = random(1,4);

    // Sets up lcd
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Game is about to");
    lcd.setCursor(0,1);
    lcd.print("start");
    delay(4000);

    // Display and play audio for command
    displayCommand(randNumber);
  }
  
  while (timerCount != 0 && startGame)
  {
    // decrements the counter, delays by a decisecond
    timerCount = timerCount - 1;
    delay(0.5);

    // Checks for any input
    if (walkButtonClicked())
    {
      inputHit = 1;
      break;
    }
    if (breakBroke())
    {
      inputHit = 2;
      break;
    }
    if (twisted())
    {
      inputHit = 3;
      break;
    }
  }

  // Timer ran out, player lost
  if (timerCount == 0 && startGame)
  {
    digitalWrite(led, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You lost!");
    lcd.setCursor(0,1);
    lcd.print("Final score: " + String(points));
    startGame = false;

    // Play loosing audio
    //tmrpcm.disable();
    //delay(1000);
    tmrpcm.play("Penn.wav");
  }
  else if (inputHit == randNumber && startGame)// User hit correct input
  {
    lcd.clear();
    lcd.print("Correct!");

    // Play audio for correct input
    playSuccessAudio(inputHit);
    
    // Can add wait between rounds 
    delay(3000);
    
    points += 1;
    roundNum += 1;
    randNumber = random(1,4);
    roundTime = roundTime * 0.9;
    timerCount = roundTime;

    // Update last states for new round
    encoderLastState = digitalRead(encoder);
    breakBeamLastState = digitalRead(breakBeam); 

    if (roundNum == 11)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("You Won!");
      lcd.setCursor(0,1);
      lcd.print("Final Score: " + String(points));
      startGame = false;

      //Play sweet caroline
      tmrpcm.loop(1);
      tmrpcm.play("SC.wav");
    }
    else
    {
      // New command for user
      displayCommand(randNumber);
    }
    
  }
  else if (startGame) // User hit wrong input
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("You lost!");
    lcd.setCursor(0,1);
    lcd.print("Final score: " + String(points));
    startGame = false;

    // Play loosing audio
    //tmrpcm.stopPlayback();
    tmrpcm.play("Penn.wav");
  }
  

}

bool walkButtonClicked() {
  if (digitalRead(walkSignButton) == HIGH)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool breakBroke() {
  if (digitalRead(breakBeam) != breakBeamLastState)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool twisted() {
  encoderState = digitalRead(encoder);
  if (encoderState != encoderLastState) {
    encoderLastState = encoderState;
    return true;
  }
  else
  {
    encoderLastState = encoderState;
    return false;
  }
}

// Displays and plays audio for new command
void displayCommand(int command)
{
  lcd.clear();
  lcd.setCursor(0,0);
  switch(command) {
    case 1:
        lcd.print("Push Walk Button");
        tmrpcm.play("PushIt.wav");
        break;
    case 2:
        lcd.print("Spin Doors");
        tmrpcm.play("SpinIt.wav");
        break;
    case 3:
        lcd.print("Twist It");
        tmrpcm.play("TwistIt.wav");
        break;
  }
}

void playSuccessAudio(int input)
{
  switch(input) {
    case 1:
        tmrpcm.play("WS.wav");
        break;
    case 2:
        tmrpcm.play("EC.wav");
        break;
    case 3:
        tmrpcm.play("Panthers.wav");
        break;
  }
}
