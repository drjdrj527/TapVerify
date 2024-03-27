#include <WiFi.h> // Include the WiFi library for ESP32
#include <WebServer.h> // Include the WebServer library
#include <Wire.h> // Include the Wire library for I2C communication
#include <PN532_I2C.h> // Include the PN532 library for I2C communication
#include <PN532.h> // Include the PN532 library
#include <NfcAdapter.h> // Include the NFC adapter library

const char* ssid = "YOUR_WIFI_SSID"; // Define the SSID for WiFi connection
const char* password = "YOUR_WIFI_PASSWORD"; // Define the password for WiFi connection

WebServer server(80); // Create a WebServer object listening on port 80

PN532_I2C pn532_i2c(Wire); // Initialize the PN532 module using I2C communication
NfcAdapter nfc = NfcAdapter(pn532_i2c); // Initialize the NFC adapter using the PN532 module

void handleRoot() {
  String content = "<html><body>"; // Start building HTML content for root route
  content += "<h1>NDEF Writer</h1>"; // Add heading to HTML content
  content += "<form method='post' action='/write'>"; // Add form with POST method and '/write' action to HTML content
  content += "Enter the text to be written to the NFC tag: <input type='text' name='text'><br>"; // Add text input field to HTML content
  content += "<input type='submit' value='Submit'>"; // Add submit button to HTML content
  content += "</form></body></html>"; // Close form and body tags in HTML content
  server.send(200, "text/html", content); // Send HTML content as response with status code 200 (OK)
}

void handleWrite() {
  if (nfc.tagPresent()) { // Check if NFC tag is present
    String inputText = server.arg("text"); // Get text input from form
    NdefMessage message = NdefMessage(); // Create an NDEF message object
    message.addTextRecord(inputText.c_str()); // Add text record to NDEF message
    bool success = nfc.write(message); // Write NDEF message to NFC tag
    if (success) {
      server.send(200, "text/plain", "Success."); // Send success message as response
    } else {
      server.send(500, "text/plain", "Write failed."); // Send failure message as response
    }
  } else {
    server.send(500, "text/plain", "No NFC tag present."); // Send NFC tag not present message as response
  }
}

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  delay(1000); // Delay for 1 second

  // Connect to Wi-Fi
  WiFi.begin(ssid, password); // Begin WiFi connection with defined SSID and password
  Serial.println("Connecting to WiFi..."); // Print message to serial monitor
  while (WiFi.status() != WL_CONNECTED) { // Wait for WiFi connection to be established
    delay(1000); // Delay for 1 second
    Serial.println("Connecting to WiFi..."); // Print message to serial monitor
  }
  Serial.println("Connected to WiFi"); // Print message to serial monitor

  // Start the NFC and setup the web server
  nfc.begin(); // Initialize NFC adapter
  server.on("/", HTTP_GET, handleRoot); // Handle root route with HTTP GET method
  server.on("/write", HTTP_POST, handleWrite); // Handle '/write' route with HTTP POST method
  server.begin(); // Start the web server
}

void loop() {
  server.handleClient(); // Handle client requests
}
