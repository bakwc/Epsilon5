<?php
include 'Credis.php';
if(isset($_POST['nick'])){
 $redis = new Credis_Client();
   $pass = $redis->hGet('player_'.$_POST['nick'], 'password');
   if(md5($_POST['pass']) === $pass){
   echo '+';
   }else{
   echo '-';
   }
}

?>

<form action="" method="post">

<input type="text" name="nick"/>
<input type="password" name="pass">
<input type="submit" value="Проверить">
</form>