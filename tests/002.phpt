--TEST--
test1() Basic test
--EXTENSIONS--
sdl_ttf
--FILE--
<?php
$ret = test1();

var_dump($ret);
?>
--EXPECT--
The extension sdl_ttf is loaded and working!
NULL
