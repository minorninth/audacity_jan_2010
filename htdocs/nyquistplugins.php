<?php

require_once 'main.inc.php';
$title = "Nyquist Plug-ins";
include 'top.inc.php';

?>

<?php

function plugins($process) {
 if ($dir = @opendir("nyquist/")) {
  while(($file = readdir($dir)) != false) {
    if (ereg("^(.*)\.ny$", $file, $matches)) {
      $base = $matches[1];
      system("grep -q \";type generate\" nyquist/$file", $result);
      if ($result == $process) {
        $nameline = `grep ";name" nyquist/$file`;
        if (preg_match(';name "*([0-9a-zA-Z ]*);', $nameline, $matches)) {
          $name = $matches[1];
          print "<b>$name</b> | \n";
          print "<a href=\"nyquist/$base.ny\">[$base.ny]</a>\n";
          print "<a href=\"nyquist/$base.zip\">[$base.zip]</a>\n";
	  print "<p>\n";

	  if (file_exists("nyquist/${base}1.mp3")) {
            print "Example audio clips: ";
            for($i=1; $i<=9; $i++) {
              if (file_exists("nyquist/${base}$i.mp3")) {
                print "<a href=\"nyquist/${base}$i.mp3\">[MP3 Clip $i]</a>";
                print "&nbsp;&nbsp;";
              }
            }
            print "<p>\n";
          }
	  system("cat nyquist/$base.html");
	  print "<p><hr><p>\n";
        }
        else {
          print "<li>No name from $nameline\n";
        }
      }
    }
  }
 }
}

BoxTop("Generator Nyquist Plug-ins");
plugins(0);
BoxBottom();

BoxTop("Effect Nyquist Plug-ins");
plugins(1);
BoxBottom();

include 'bottom.inc.php';

?>

