<?php

/**
* Send a GET requst using cURL
* @param string $url to request
* @return string
*/

function curl_get($url)
{

  $ch = curl_init($url);

  // Configuring curl options
  $options = array(
	CURLOPT_RETURNTRANSFER => true,
	CURLOPT_HTTPHEADER => array('Accept: application/json')
  );

  // Setting curl options
  curl_setopt_array( $ch, $options );

  if( ! $result = curl_exec($ch)) {
        trigger_error(curl_error($ch));
  }
  curl_close($ch);
  return $result;
}

?>
