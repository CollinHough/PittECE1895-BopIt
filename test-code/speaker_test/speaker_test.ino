#include "SD.h"
#define SD_ChipSelectPin 10
#include "TMRpcm.h"
#include "SPI.h"

#define led 8

TMRpcm tmrpcm;

void setup()
{
  pinMode(led, OUTPUT);
  
  tmrpcm.speakerPin=9;
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    digitalWrite(led, HIGH);
    return;
  }
  tmrpcm.setVolume(1);
  tmrpcm.play("Rapunzel3.wav");

}

void loop() {
  // put your main code here, to run repeatedly:

}
