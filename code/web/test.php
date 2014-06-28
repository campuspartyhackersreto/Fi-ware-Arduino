<?php

require_once('./curlf.php');

header("Content-type: application/json; charset=utf-8");
header("Access-Control-Allow-Origin: * ");
header("HTTP/1.1 200 OK");

$url = "http://130.206.82.44:1026/NGSI10/contextEntities/Sensor1";

$result = curl_get($url);
echo $result;

?>

