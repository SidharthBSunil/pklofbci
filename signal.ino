#define SAMPLE_RATE 512
#define BAUD_RATE 115200
#define INPUT_PIN A0

int ledPin = 13; // Pin to control
void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);
  
  pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop() {
  // Calculate elapsed time
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 0;
  timer -= interval;

  // Sample
  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;
    int sensor_value = analogRead(INPUT_PIN);
    Serial.println(sensor_value);
  }
  if (Serial.available()) {
        char command = Serial.read(); // Read the command from Python
        if (command == '1') {
            digitalWrite(ledPin, HIGH); // Turn pin high
        } else if (command == '0') {
            digitalWrite(ledPin, LOW); // Turn pin low
        }
    }
}