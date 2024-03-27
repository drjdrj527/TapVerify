# TapVerify

This repository implements a web-based attendance system using an ESP32 microcontroller, NFC tags, and a MySQL database for secure data storage and management.

# Features:

NFC Tag Writing: Users can write data to NFC tags for attendance marking.
NFC Tag Reading: The ESP32 reads data from tapped NFC tags, using the NFC module.
Data Transfer: communication between the ESP32 and a web server for data transmission.
Attendance Recording: Data from NFC tags is stored in a MySQL database for attendance tracking.
Web Dashboard: View attendance records through a web interface.

# Hardware Requirements:

ESP32 Development Board
PN532 NFC Module
WiFi Connection (for server communication and web interface access)

# Software Requirements:

Arduino IDE (for ESP32 code compilation)
MySQL Database Server
Web server

# Step-by-Step Guide:

Setting Up the Development Environment

Install the Arduino IDE
Install the required libraries.
Set up your MySQL database and web server.

# Tag Writing:

Upload the code ESP32_NFC_Tag_Writer_with_Web_Interface_Code.ino to your ESP32 board.
Configure the web interface settings within the code (refer to the code comments) to customize the user experience.

# Reading with Server Integration:

Upload the code ESP32_NFC_Data_Transfer_Code_with_Server_Integration.ino to your ESP32 board.
Configure your Wi-Fi credentials and database connection details in this code file, ensuring they match your network and database setup.

# Database Table Creation:

Open the Database_table_creation.txt file in a text editor.
Review the SQL script within the file. It defines a table named EspData to store attendance records.
Execute this SQL query into your MySQL database.

# Web Server Integration:

Configure the following files for the web interface:

post-esp-data.php: This script on the web server receives data from the ESP32 and stores it in the database. Edit the script's database connection details.
index.php: This script displays the attendance records on the web dashboard. Customize its appearance and data formatting as desired.

Running the System:

Power up your ESP32 board with uploaded code files.
(For writing the tag)
Access the ESP32's web interface using its IP address in a web browser.
Write the desired data to an NFC tag using the web interface.
(For reading the NFC tag and data transferring)
Tap the written NFC tag on the PN532 module for attendance recording. Data will be transferred to the server and stored in the database.
Access the web dashboard using a web browser to view attendance records.
# Schematic
![espnfcled](https://github.com/drjdrj527/TapVerify/assets/140609594/0520a988-f10b-403c-8d36-7484e633c16d)
