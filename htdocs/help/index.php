<?php
/*
 * Copyright 2004 - 2008 Matt Brubeck, Gale Andrews
 * This file is licensed under a Creative Commons license:
 * http://creativecommons.org/licenses/by/2.0/
 */
  require_once "main.inc.php";
  $pageId = "";
  $pageTitle = _("Documentation and Support");
  include "../include/header.inc.php";
?>

<h2><?=$pageTitle?></h2>

<?php
echo _('<p><b>Questions?</b> First, check our <a href="faq">Frequently Asked Questions</a> and the following resources:</p>

<p>
 <ul>
   <li><a href="documentation">Documentation</a> - Read the user manual and quick reference.</li>
   <li><a href="http://audacityteam.org/wiki">Audacity Wiki</a> is an extensive user-editable help resource including:
    <ul><li><a href="http://wiki.audacityteam.org/wiki/Category:Tutorial">Tutorials</a> - step-by-step guides on performing common tasks in Audacity, such as making ringtones, removing vocals, mixing, creating podcasts and transferring tapes and records to computer. Some <a href="http://audacityteam.org/wiki/index.php?title=MultiLingual">foreign language tutorials</a> are available.</li>
     <li><a href="http://wiki.audacityteam.org/wiki/Category:Tips">Tips</a> - these articles will help you work with and understand Audacity and your audio hardware.</li>
    </ul>
  </li>
 </ul>
</p>')?>

<?php
// i18n-hint: If there are any special sources of help (local forums, lists) for
// Audacity users in your language (other than our Russian, French, German
// and Spanish forums), please add links to them at the end of this paragraph
// and at \htdocs\contact\index.php. If there is any translated documentation,
// please add links to it at the bottom of \htdocs\help\documentation.php

echo _('<p><b>Still need help?</b> Please <a href="../contact/">contact us</a>.</p>')?>

<?php
  include "../include/footer.inc.php";
?>
