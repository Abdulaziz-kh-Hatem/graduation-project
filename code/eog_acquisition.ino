// EOG Signal Acquisition
// Samples analog channel A0 at 250 Hz (4 ms intervals)

const unsigned long SAMPLE_INTERVAL_US = 4000; 
unsigned long previousMicros = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMicros = micros();
  
  if (currentMicros - previousMicros >= SAMPLE_INTERVAL_US) {
    previousMicros += SAMPLE_INTERVAL_US; 
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
  }
}
