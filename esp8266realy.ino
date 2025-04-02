/*
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk authentication token
char auth[] = "YourAuthToken";
char ssid[] = "YourWiFiSSID";
char pass[] = "YourWiFiPassword";

#define DEVICE1_PIN D1 // Relay or output for device 1
#define DEVICE2_PIN D2 // Relay or output for device 2
#define IR_SENSOR_PIN D3 // IR sensor for switching
#define CONTROL_INPUT_PIN D4 // Control input for turning ON/OFF

bool currentDevice = 0; // 0 for Device 1, 1 for Device 2

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    pinMode(DEVICE1_PIN, OUTPUT);
    pinMode(DEVICE2_PIN, OUTPUT);
    pinMode(IR_SENSOR_PIN, INPUT_PULLUP);
    pinMode(CONTROL_INPUT_PIN, INPUT_PULLUP);

    digitalWrite(DEVICE1_PIN, LOW);
    digitalWrite(DEVICE2_PIN, LOW);
}

void loop() {
    Blynk.run();
    handleIRSwitch();
    handleDeviceControl();
}

void handleIRSwitch() {
    static bool lastState = HIGH;
    bool currentState = digitalRead(IR_SENSOR_PIN);
    
    if (currentState == LOW && lastState == HIGH) {
        currentDevice = !currentDevice; // Toggle between Device 1 and 2
        Serial.print("Switched to Device: ");
        Serial.println(currentDevice ? "2" : "1");
        delay(300); // Debounce delay
    }
    lastState = currentState;
}

void handleDeviceControl() {
    bool controlState = digitalRead(CONTROL_INPUT_PIN);
    if (currentDevice == 0) {
        digitalWrite(DEVICE1_PIN, controlState);
        digitalWrite(DEVICE2_PIN, LOW);
    } else {
        digitalWrite(DEVICE1_PIN, LOW);
        digitalWrite(DEVICE2_PIN, controlState);
    }
}
 */

#define BLYNK_TEMPLATE_ID "TMPL3FG_sX25Z"
#define BLYNK_TEMPLATE_NAME "Device"
#define BLYNK_AUTH_TOKEN "uUWw6YB1LOua4SFDhjzbOdtdgEZ-4r4Y"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Replace with your Blynk credentials
char auth[] = "uUWw6YB1LOua4SFDhjzbOdtdgEZ-4r4Y";
char ssid[] = "SpaceX";
char pass[] = "sid@2024";

// Define GPIO pins
#define DEVICE1 D1
#define DEVICE2 D2
#define IR_SENSOR A0  // Analog input

// Virtual pins
#define VIRTUAL_DEVICE1 V1
#define VIRTUAL_DEVICE2 V2
#define VIRTUAL_IR_SENSOR V3

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);
    
    pinMode(DEVICE1, OUTPUT);
    pinMode(DEVICE2, OUTPUT);
    pinMode(IR_SENSOR, INPUT);
}

BLYNK_WRITE(VIRTUAL_DEVICE1) {
    int value = param.asInt();
    digitalWrite(DEVICE1, value);
}

BLYNK_WRITE(VIRTUAL_DEVICE2) {
    int value = param.asInt();
    digitalWrite(DEVICE2, value);
}

void sendSensorData() {
    int irValue = analogRead(IR_SENSOR);
    Blynk.virtualWrite(VIRTUAL_IR_SENSOR, irValue);
}

void loop() {
    Blynk.run();
    sendSensorData();
    delay(1000); // Adjust polling rate
}

