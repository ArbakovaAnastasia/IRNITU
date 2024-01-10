<?php
include 'connect.php';

if($_POST['text']){
	$text = $_POST['text'];
	$sql = "INSERT INTO text (message) VALUES ('".$text."')";
	$conn->query($sql);
}
if($_POST['get']){
	$sql = "SELECT * FROM text";
	$result = $conn->query($sql);
	while($row = $result->fetch_assoc()){
		echo "<li>"$row['message']."</li>";
	};
}
?>