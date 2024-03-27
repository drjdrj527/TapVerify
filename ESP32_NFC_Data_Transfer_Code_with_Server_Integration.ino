#include <WiFi.h> // Include the WiFi library for ESP32
#include <WiFiClientSecure.h> // Include the Secure WiFi client library
#include <HTTPClient.h> // Include the HTTP client library
#include <Wire.h> // Include the Wire library for I2C communication
#include <PN532_I2C.h> // Include the PN532 library for I2C communication
#include <PN532.h> // Include the PN532 library
#include <NfcAdapter.h> // Include the NFC adapter library
#include <NdefMessage.h> // Include the NDEF message library
#include <NdefRecord.h> // Include the NDEF record library

const char* ssid     = "YOUR_WIFI_SSID"; // Define the SSID for WiFi connection
const char* password = "YOUR_WIFI_PASSWORD"; // Define the password for WiFi connection
const char* serverName = "https://YOUR_WEBSERVER/post-esp-data.php"; // Define the server URL for HTTP requests
String apiKeyValue = "YOUR_API"; // Define the API key value for authentication

PN532_I2C pn532_i2c(Wire); // Initialize the PN532 module using I2C communication
NfcAdapter nfc = NfcAdapter(pn532_i2c); // Initialize the NFC adapter using the PN532 module

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  pinMode(LED_BUILTIN, OUTPUT); // Set the built-in LED pin as output
  WiFi.begin(ssid, password); // Begin WiFi connection with defined SSID and password
  while(WiFi.status() != WL_CONNECTED) { // Wait for WiFi connection to be established
    delay(10); // Delay for 10 milliseconds
  }
  nfc.begin(); // Initialize NFC adapter
}

void loop() {
  if (nfc.tagPresent() && WiFi.status() == WL_CONNECTED) { // Check if NFC tag is present and WiFi is connected
    NfcTag tag = nfc.read(); // Read NFC tag
    NdefMessage msg = tag.getNdefMessage(); // Get NDEF message from NFC tag
    NdefRecord record = msg.getRecord(0); // Get the first NDEF record from the message
    byte length = record.getPayloadLength(); // Get the length of the payload
    byte payload[length]; // Create a byte array to store payload data
    record.getPayload(payload); // Get payload data from the NDEF record

    String nFcData = ""; // Initialize an empty string to store NFC data
    for (int i = 0; i < length; i++) { // Loop through each byte of the payload
        if (payload[i] != '\0') { // Check for null terminator
            nFcData += (char)payload[i]; // Append byte to NFC data string
        } else {
            break; // Exit loop when null terminator is encountered
        }
    }
    nFcData.remove(0, 3); // Remove the first three characters from NFC data
    nFcData.trim(); // Remove leading and trailing whitespace
    
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED
    delay(100); // Delay for 100 milliseconds
    digitalWrite(LED_BUILTIN, LOW); // Turn off the built-in LED
    
    WiFiClientSecure *client = new WiFiClientSecure; // Create a new secure WiFi client
    client->setInsecure(); // Set client to accept insecure connections
    HTTPClient https; // Create an HTTP client object
    https.begin(*client, serverName); // Begin HTTP request to server with secure client and server URL
    https.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Add header for content type
    String httpRequestData = "api_key=" + apiKeyValue + "&Name=" + nFcData + ""; // Create HTTP request data
    Serial.println(httpRequestData); // Print HTTP request data to serial monitor
    int httpResponseCode = https.POST(httpRequestData); // Send HTTP POST request with data
    https.end(); // End HTTP request
  }
  else {
    Serial.println("WiFi Disconnected or NFC Tag is not present"); // Print message to serial monitor if WiFi is disconnected or NFC tag is not present
  }
  delay(10); // Delay for 10 milliseconds
}
