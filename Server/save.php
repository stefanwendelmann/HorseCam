<?php
	// Humback: https://www.youtube.com/watch?v=iTOnRNS0fhw
	$uploaddir = 'uploads/'; 
	$uploadfile=$_GET['n'];

	if (is_uploaded_file($_FILES['photo']['tmp_name'])) {
		   move_uploaded_file($_FILES['photo']['tmp_name'], $uploaddir.$uploadfile);
	}

?>