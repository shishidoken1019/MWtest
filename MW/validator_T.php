<?php

require_once('validator.inc');

$data = "010";
$type = "numeric";

// static
if (validator::chk($data, $type)) {
  print "ok \n";
} else {
  print "ng \n";
}

// nomal
$obj = new validator;



?>
