<?php

$servername = "localhost"; // Define the server name for database connection

// REPLACE with your Database name
$dbname = "YOUR_DATABASE_NAME"; // Define the database name
// REPLACE with Database user
$username = "YOUR_DATABASE_USERNAME"; // Define the database username
// REPLACE with Database user password
$password = "YOUR_DATABASE_PASSWORD"; // Define the database password

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "YOUR_API"; // Define the API key value

$api_key= $Name = ""; // Initialize variables for API key and Name

if ($_SERVER["REQUEST_METHOD"] == "POST") { // Check if the request method is POST
    $api_key = test_input($_POST["api_key"]); // Get API key from POST data
    if($api_key == $api_key_value) { // Check if API key matches the predefined value
        $Name = test_input($_POST["Name"]); // Get Name from POST data
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname); // Create a new MySQLi connection
        // Check connection
        if ($conn->connect_error) { // Check if connection to database failed
            die("Connection failed: " . $conn->connect_error); // Terminate script and display error message
        } 
        
        $sql = "INSERT INTO EspData (Name)
        VALUES ('" . $Name . "')"; // Define SQL query to insert data into EspData table
        
        if ($conn->query($sql) === TRUE) { // Execute SQL query and check if successful
            echo "New record created successfully"; // Print success message
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error; // Print error message if query execution fails
        }
    
        $conn->close(); // Close database connection
    }
    else {
        echo "Wrong API Key provided."; // Print message for incorrect API key
    }
}
else {
    echo "No data posted with HTTP POST."; // Print message if no data is posted with HTTP POST
}

function test_input($data) {
    $data = trim($data); // Remove whitespace from beginning and end of string
    $data = stripslashes($data); // Remove backslashes from string
    $data = htmlspecialchars($data); // Convert special characters to HTML entities
    return $data; // Return sanitized data
}
