<!DOCTYPE html>
<html>
<head>
          <script type = "text/JavaScript">
         <!--
            function AutoRefresh( t ) {
               setTimeout("location.reload(true);", t);
            }
         //-->
      </script>
<style>
  table {
    border-collapse: collapse;
    width: 100%;
    margin-bottom: 20px;
    font-family: sans-serif;
  }
  th, td {
    text-align: center;
    padding: 8px;
    border: 1px solid #ddd;
  }
  th {
    background-color: #f2f2f2;
  }
  tr:nth-child(even) {
    background-color: #f8f8f8;
  }
</style>
</head>
<body onload = "JavaScript:AutoRefresh(11000);">
   
<?php
$servername = "localhost";
$dbname = "YOUR_DATABASE_NAME";
$username = "YOUR_DATABASE_USERNAME";
$password = "YOUR_DATABASE_PASSWORD";
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$sql = "SELECT id, Name, reading_time FROM EspData ORDER BY id DESC";
echo '<h1><table cellspacing="5" cellpadding="5">
      <tr>
        <td>No.</td>
        <td>Name</td>
        <td>Timestamp</td>
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_Name = $row["Name"];
        $row_reading_time = $row["reading_time"];

        echo '<tr>
                <td>' . $row_id . '</td>
                <td>' . $row_Name . '</td>
                <td>' . $row_reading_time . '</td>
              </tr>';
    }
    $result->free();
}

$conn->close();
?>
</table></h1>
</body>
</html>
