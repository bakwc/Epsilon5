<?php
include 'Credis.php';
if(isset($_POST['nick'])){
$username = $_POST['nick'];
if (preg_match('/^[a-z\d_]{5,20}$/i', $username)) {
   $redis = new Credis_Client();
   $redis->hSet('player_'.$username, 'password', md5($_POST['pass']));
} else {
    echo "Wrong username format.";
}
}

?>

<form action="" method="post">
<input type="text" name="nick"/>
<input type="password" name="pass"/>
<input type="submit" name="go"/>
</form>