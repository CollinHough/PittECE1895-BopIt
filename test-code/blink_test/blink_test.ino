#define led 8

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);

}

void loop() {
  digitalWrite(led, HIGH);
  //delay(6000); //Should be 6 seconds
  delay(500);
  digitalWrite(led, LOW);
  //delay(6000);
  delay(500);

}
