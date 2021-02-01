// video tutorial disponible en https://github.com/TECA-IOT
#define CLOCK_INTERRUPT_PIN 2

int pulsos = 0;

void setup() {
  
  pinMode(CLOCK_INTERRUPT_PIN, INPUT_PULLUP);
  //pinMode(CLOCK_INTERRUPT_PIN, INPUT);
  delay(1000);
  attachInterrupt(digitalPinToInterrupt(CLOCK_INTERRUPT_PIN), onAlarm, CHANGE);

}

void loop() {
  delay(1000);

}


void onAlarm() {
  pulsos++;
  //Serial.println("Alarm occured!");
  Serial.println(pulsos);
}
