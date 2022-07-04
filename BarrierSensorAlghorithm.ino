#define SECONDS_TO_TRACK_BARRIER 2
#define SENSOR_PIN 3
#define LED_PIN 0

int previousSensorValue = 0;
bool previousSensorValueWasTracked = false;
unsigned long barrierStartTime = 0;
int billNumber = 0;

void setupWIFI(int ledPin);
void trackToTelegram(int billNumber);

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  setupWIFI(LED_PIN);
}

bool sensorValueStableEnough() {
  return (millis() - barrierStartTime) >= (SECONDS_TO_TRACK_BARRIER * 1000);
}

void loop() {
  int currentSensorValue = !digitalRead(SENSOR_PIN); // Sensor sends 1 if NO barrier
  if (previousSensorValue != currentSensorValue) { // Sensor changed value
    Serial.println("number changed!!!!");
    barrierStartTime = millis();                   // Start counting time for current sensor value
  }
  else if (sensorValueStableEnough()) {            // If we have stable value for a long time
    switch (currentSensorValue) {
      case 0:                                      // Mark that there are no barriers for a long time,`
        previousSensorValueWasTracked = false;     // so we can prepare to track next
        digitalWrite(LED_PIN, LOW);
        break;
      case 1:
        if (!previousSensorValueWasTracked) {      // Check if in current sequence with barrier
          billNumber++;
      //    Serial.println("--TELEGA");
          trackToTelegram(billNumber);             // we did not track current barried
      //    Serial.println("LED");
          previousSensorValueWasTracked = true;    // Mark that current barrier tracked
        }
        digitalWrite(LED_PIN, HIGH);
        break;
    }
  }
  
  previousSensorValue = currentSensorValue;
}
