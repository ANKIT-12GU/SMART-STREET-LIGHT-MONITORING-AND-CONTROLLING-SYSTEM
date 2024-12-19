#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>
#include <ESP8266WebServer.h>

// WiFi credentials
const char* ssid = "Bingo";
const char* password = "ankit1212";

// ThingSpeak settings
unsigned long channelID = 2758546;
const char* apiKey = "08T8NZBHR6FL8MIW";

// Pin definitions
const int irSensorPins[] = {D5, D6, D7}; // IR sensor pins (e.g., GPIO12, GPIO13, GPIO15)
const int ledPins[] = {D3, D4, D8};      // LED pins (e.g., GPIO14, GPIO2, GPIO0)
const int ldrPin = A0;                   // LDR pin (Analog input)

// WiFi and ThingSpeak client
WiFiClient client;
ESP8266WebServer server(80); // HTTP server on port 80

String serialData = ""; // String to store serial data

void handleRoot() {
  String webpage = "<html>\
  <head><title>ESP8266 Data Logger</title></head>\
  <body>\
  <h1>ESP8266 Data Logger</h1>\
  <pre>" + serialData + "</pre>\
  <script>\
  setInterval(() => { location.reload(); }, 5000);\
  </script>\
  </body>\
  </html>";
  server.send(200, "text/html", webpage);
}

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(irSensorPins[i], INPUT); // Set IR sensor pins as input
    pinMode(ledPins[i], OUTPUT);     // Set LED pins as output
  }

  Serial.begin(115200);                // Initialize Serial Monitor
  Serial.println("IR and LDR Motion Detection Initialized");

  WiFi.begin(ssid, password);        // Connect to WiFi
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);          // Initialize ThingSpeak

  server.on("/", handleRoot);        // Serve the root page
  server.begin();                    // Start the web server
}

void loop() {
  int ldrValue = analogRead(ldrPin); // Read LDR value (0-1023)
  int irStatus[3] = {0, 0, 0};       // Tracks motion detection for each IR sensor
  int ledStatus[3] = {0, 0, 0};      // Tracks LED intensity for each LED

  // Debugging the LDR value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);
  serialData += "LDR Value: " + String(ldrValue) + "\n";

  if (ldrValue < 300) { // Low light detected
    for (int i = 0; i < 3; i++) {
      analogWrite(ledPins[i], 50);  // Dim the LED at low intensity
      int irValue = digitalRead(irSensorPins[i]); // Read each IR sensor
      if (irValue == LOW) { // Motion detected by this IR sensor
        analogWrite(ledPins[i], 255); // LED at high intensity
        Serial.print("Motion detected on IR Sensor ");
        Serial.print(i + 1);
        Serial.println(": LED at high intensity (200)");
        serialData += "Motion detected on IR Sensor " + String(i + 1) + ": LED at high intensity (200)\n";
        irStatus[i] = 1;    // Motion detected
        ledStatus[i] = 255; // LED intensity
      } else { // No motion for this IR sensor
        analogWrite(ledPins[i], 50); // LED at low intensity
        Serial.print("Low light, no motion on IR Sensor ");
        Serial.print(i + 1);
        Serial.println(": LED at low intensity (50)");
        serialData += "Low light, no motion on IR Sensor " + String(i + 1) + ": LED at low intensity (50)\n";
        irStatus[i] = 0;     // No motion detected
        ledStatus[i] = 50;   // LED intensity
      }
    }
  } else { // Sufficient light
    for (int i = 0; i < 3; i++) {
      digitalWrite(ledPins[i], LOW); // Turn off all LEDs
      irStatus[i] = 0;          // No motion
      ledStatus[i] = 0;         // LED off
    }
    Serial.println("Sufficient light: All LEDs OFF");
    serialData += "Sufficient light: All LEDs OFF\n";
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    ThingSpeak.setField(1, ldrValue);        // Field 1: LDR Value
    ThingSpeak.setField(2, irStatus[0]);    // Field 2: IR Sensor 1 Status
    ThingSpeak.setField(3, irStatus[1]);    // Field 3: IR Sensor 2 Status
    ThingSpeak.setField(4, irStatus[2]);    // Field 4: IR Sensor 3 Status
    ThingSpeak.setField(5, ledStatus[0]);   // Field 5: LED 1 Status
    ThingSpeak.setField(6, ledStatus[1]);   // Field 6: LED 2 Status
    ThingSpeak.setField(7, ledStatus[2]);   // Field 7: LED 3 Status

    int responseCode = ThingSpeak.writeFields(channelID, apiKey);

    if (responseCode == 200) {
      Serial.println("Data sent to ThingSpeak successfully");
    } else {
      Serial.print("Error sending data: ");
      Serial.println(responseCode);
    }
  } else {
    Serial.println("WiFi disconnected, retrying...");
    WiFi.begin(ssid, password);
  }

  if (serialData.length() > 1000) { // Prevent excessive memory usage
    serialData = serialData.substring(serialData.length() - 1000);
  }

  server.handleClient(); // Handle HTTP requests
  delay(15000); // Wait 15 seconds between updates (ThingSpeak limit)
}