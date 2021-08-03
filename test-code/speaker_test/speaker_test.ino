#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
#include "SPI.h"

#define led 8
#define button 1

TMRpcm tmrpcm;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  
  tmrpcm.speakerPin=9;
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin))
  {
    Serial.println("SD fail");
    //digitalWrite(led, HIGH);
    return;
  }
  Serial.println("SD success");
  tmrpcm.setVolume(4);
  //tmrpcm.play("SC.wav");

}

void loop() {
  // put your main code here, to run repeatedly:
//  delay(10000);
    if (digitalRead(button) == HIGH && tmrpcm.isPlaying())
    {
      digitalWrite(led,HIGH);
      tmrpcm.stopPlayback();
    }
    else if (digitalRead(button) == HIGH)
    {
      tmrpcm.play("SC.wav");
      delay(5000);
      tmrpcm.play("Panthers.wav");
    }
}
