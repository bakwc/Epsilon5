<?php

include 'Credis.php';

$redis = new Credis_Client();
   

$r = $redis->zRange('score', -3,-1, "withscores");
$r_C = count($r);
for($i=0;$i<$r_C;$i+=2){
	echo ' '.$r[$i].' - '.$r[$i+1].'<br>';
}

?>
<a href=".">home</a>
