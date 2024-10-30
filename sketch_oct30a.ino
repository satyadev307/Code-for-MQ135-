#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
const char *ssid = "DEV"; // Replace with your WiFi SSID
const char *password = "Estilo@4438"; // Replace with your WiFi password
const int mqPin = A0; // Analog pin for MQ2 sensor
//const int mq2Pin = A0; // Analog pin connected to the AOUT of MQ-2 sensor
const int buzzerPin = 3;
WiFiServer server(80);
AsyncWebServer asyncServer(80);
void setup() {
pinMode(buzzerPin, OUTPUT);
Serial.begin(115200);
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(250);
16 | P a g e
Serial.println("Connecting to WiFi...");
}
Serial.println("WiFi connected");
Serial.print("IP Address: ");
Serial.println(WiFi.localIP());
// Setup routes for the web server
asyncServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
String html = "<html><body>";
html += "<h1>Air Quality Monitor</h1>";
html += "<p>Butane Value: " + String(analogRead(mqPin)) + "</p>";
html += "<h6>Project By Batch-32</h6>";
html += "</body></html>";
request->send(200, "text/html", html);
});
// Start server
asyncServer.begin();
}
void loop() {
// Handle client connections
//int sensorValue = analogRead(mqPin);
17 | P a g e
WiFiClient client = server.available();
if (client) {
while (client.connected()) {
if (client.available()) {
// Handle the client request here if needed
}
}
client.stop();
}
delay(1000); // Update every 1 second
int sensorValue = analogRead(mqPin);
// Adjust this threshold based on your requirements
int threshold = 500;
if (sensorValue > threshold) {
// Gas concentration above threshold, trigger the buzzer
digitalWrite(buzzerPin, HIGH);
Serial.print("High");
delay(1000); // Buzzer on for 1 second (adjust as needed)
digitalWrite(buzzerPin, LOW);
Serial.print("Low");
delay(1000);
}
}