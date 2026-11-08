#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Hello from the setup");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Hello from the loop");
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}
