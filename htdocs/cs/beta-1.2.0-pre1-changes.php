<h2>Zm�ny v Audacity 1.2</h2>

This page lists major changes since our last stable release, Audacity
1.0.0.   Users of our beta versions should see the changelog for
<a href="<?php print "betanotes.php$langQueryStr"; ?>">changes since Audacity 1.1.0</a>.

<h3>Professional-Quality Audio</h3>

<ul>
<li>
Audacity can now record and edit 24-bit and 32-bit (floating-point)
samples.  Tracks with different sample rates and formats can exist in
the same project, and Audacity will convert them in realtime whenever
necessary.  High-quality dithering and resampling is used for all
conversions.  
</li>

<li>
Audacity's sound input and output has been improved.  Audacity can now
record more than two channels at once.  Buffering is improved, for lower
chances of skipping and buffer underruns.
</li>
</ul>

<a href="screenshots.php<?php print $langQueryStr; ?>">
<img alt="screenshots" border="0" src="images/screen/linux/change-pitch.png" align="right"></a>
<h3>Effects</h3>

<ul>
<li>
Three new effects change the pitch and tempo of a track:
 <ul>
  <li>Change Pitch raises or lowers the tone of a selection, without
  affecting the speed.</li>
  <li>Change Tempo makes the selection play faster or slower, without
  altering the pitch.</li>
  <li>Change Speed alters both the playback speed and the pitch, just
  like changing the speed of a turntable or tape player.</li>
 </ul>
</li>

<li>
Most effects now include a "Preview" button, which allows you to try
different settings without closing the effect window.  A new command
allows you to repeat the last effect without re-opening the window.
</li>

<li>
Other new effects include:
 <ul>
  <li>Compressor, for dynamic range compression.</li>
  <li>Repeat, to loop samples.</li>
  <li>Normalize, to adjust volume and correct DC bias.</li>
 </ul>
</li>
</ul>


<h3>New Editing Features</h3>

<ul>
<li>
The Envelope tool, used for smoothly fading tracks in and out, can now be
used to make tracks louder than their original volume as well as quieter.
</li>

<li>
The new "Time track" feature is similar to the volume envelope, but
instead changes the playback speed smoothly as a track plays.
</li>

<li>
Each track now has its own Gain and Pan controls, for easier mixing.
<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/linux/track-controls.png" align="right"></a>
</li>

<li>
Audacity can find zero-crossings, to help create smooth cuts and loops.
Press "Z" to move selection edges to the nearest zero-crossings.
</li>
</ul>


<h3>Plugins</h3>

<ul>
<li>
On Linux, Audacity can now load <a href="http://www.ladspa.org/">LADSPA</a>
plugins.
</li>

<li>
Audacity 1.2 features a digital signal processing language called
<a href="nyquist.php">Nyquist</a>, which allows users to program new effects
in a LISP-like language.
</li>
</ul>


<h3>File Import and Export</h3>

<ul>
<li>
Audacity 1.2 project files use a new XML file format.  Audacity 1.2 will
automatically open and convert project files from earlier releases.
</li>

<li>
Audacity 1.2 uses <a href="http://www.underbit.com/products/mad/">libmad</a>
for much faster decoding of MP3 files.  Erik de Castro Lopo's
<a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> provides
improved compatibility with many uncompressed audio file formats.
</li>

<li>
The import and open dialogs now allow Audacity users to select several
audio files at once, and open them into a single project.  A new "LOF"
file format provides a way for Audacity to open a group of files with
offsets listed in a text file.
</li>
</ul>


<h3>Improved User Interface</h3>

<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/macosx/main-toolbar.png" align="right"></a>
<ul>
<li>
New Edit and Mixer toolbars for fast access to common functions.
</li>

<li>
The new Drawing tool allows adjustment of individual samples, when fully
zoomed in.  The new Multi-Tool mode gives quick access to different editing
functions without needing to switch tools.
</li>

<li>
Many new keyboard commands have been added, and keyboard shortcuts can
now be customized.
</li>

<li>
New commands:
 <ul>
  <li>Looped play.  Type "L", or hold down shift when clicking Play.</li>
  <li>Type "1" to play a 1-second preview of the audio around the cursor.</li>
 </ul>
</li>

<li>
The mouse wheel can be used to zoom in and out.
</li>

<li>
Tracks can now be zoomed vertically by clicking or dragging in the
vertical rulers.  Shift-click or right-click to zoom out.  
</li>

<li>
The ruler and status bar can now display time in several different
formats, including seconds, samples, or video frames.
</li>

<li>
Audacity's interface can now be translated into languages other than
English.  You can volunteer to help <a href="translation/">translate
Audacity</a> into your native language.
</li>
</ul>

<?/* *********************************************************************

<h2>Zm�ny od vyd�n� Audacity 1.0</h2>

Tato sekce uv�d� seznam hlavn�ch zm�n od vyd�n� na�� posledn� stabiln� verze Audacity 1.0.0. U�ivatel� na�ich beta verz� by se m�li pod�vat na <a href="<?php print "betanotes.php$langQueryStr"; ?>">zm�ny od Audacity 1.1.3</a>.

<h3>Profesion�ln� zvukov� kvalita</h3>

<ul>
<li>
Audacity nyn� um� nahr�vat a upravovat 24 a 32 bitov� vzorky (pohybliv� �adov� ��rka). V jednom projektu mohou b�t stopy s rozd�ln�mi vzorkovac�mi frekvencemi i form�ty, p�i�em� pokud je t�eba, Audacity je zkonvertuje v re�ln�m �ase. Pro v�echny konverze je pou�ito vysoce kvalitn� p�evzorkov�n� a dithering. Pro p�evzorkov�n� se nyn� pou��v� algoritmus z knihovny <a href="http://www.mega-nerd.com/SRC/">SRC</a> od Erika de Castra Lopa.
</li>

<li>
Vstup a v�stup zvuku v Audacity byl vylep�en. Audacity nyn� m��e nahr�vat v�ce ne� dva kan�ly najednou. Kv�li sn�en� mo�nosti podte�en� vyrovn�vac� pam�ti byla sn�ena latence.
</li>
</ul>


<h3>Efekty</h3>

<ul>
<li>
T�i nov� efekty na zm�nu lad�n� a rychlosti stopy:
 <ul>
  <li>"Zm�na lad�n�" zv��� nebo sn�� zvuk v�bran� ��sti bez vlivu na rychlost.</li>
  <li>"Zm�na tempa" zrychl� nebo zpomal� vybranou ��st bez vlivu na v��ku lad�n�.</li>
  <li>"Zm�na rychlosti" zm�n� rychlost p�ehr�v�n� i v��ku lad�n�, jako kdy� zm�n�te rychlost gramofonu nebo magnetofonu.</li>
 </ul>
</li>

<li>
V�t�ina efekt� nyn� obsahuje tla��tko "Preview", kter� umo��uje vyzkou�et r�zn� nastaven� p�ed zav�en�m efektov�ho okna. Nov� p��kaz v�m umo�n� zopakovat posledn� pou�it� efekt bez op�tovn�ho otev�r�n� okna.
</li>

<li>
Dal�� nov� efekty obsahuj�:
 <ul>
  <li>Kompresor, pro dynamic range kompresi.</li>
  <li>Opakov�n�, pro vytv��en� smy�ek ze vzork�.</li>
  <li>Normalizace, pro �pravu hlasitosti a opravu DC bias.</li>
 </ul>
</li>
</ul>


<h3>Nov� edita�n� vlastnosti</h3>

<ul>
<li>
The Envelope tool, used for smoothly fading tracks in and out, can now be
used to make tracks louder than their original volume as well as quieter.
</li>

<li>
The new "Time track" feature is similar to the volume envelope, but
instead changes the playback speed smoothly as a track plays.
</li>

<li>
Each track now has its own Gain and Pan controls, for easier mixing.
</li>

<li>
Audacity can find zero-crossings, to help create smooth cuts and loops.
Press "Z" to move selection edges to the nearest zero-crossings.
</li>
</ul>


<h3>Pluginy</h3>

<ul>
<li>
On Linux, Audacity can now load <a href="http://www.ladspa.org/">LADSPA</a>
plugins.
</li>

<li>
Audacity 1.2 features a digital signal processing language called
<a href="nyquist.php">Nyquist</a>, which allows users to program new effects
in a LISP-like language.
</li>
</ul>


<h3>Import a export soubor�</h3>

<ul>
<li>
Audacity 1.2 project files use a new XML file format.  Audacity 1.2 will
automatically open and convert project files from earlier releases.
</li>

<li>
Audacity 1.2 uses <a href="http://www.underbit.com/products/mad/">libmad</a>
for much faster decoding of MP3 files.  Erik de Castro Lopo's
<a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> provides
improved compatibility with many uncompressed audio file formats.
</li>

<li>
The latest version of the <a href="http://www.vorbis.com/">Vorbis</a>
libraries are used, for higher-quality Ogg Vorbis encoding.
</li>

<li>
The import and open dialogs now allow Audacity users to select several
audio files at once, and open them into a single project.  A new "LOF"
file format provides a way for Audacity to open a group of files with
offsets listed in a text file.
</li>
</ul>


<h3>Vylep�en� u�ivatelsk� rozhran�</h3>

<ul>
<li>
New Edit and Mixer toolbars for fast access to common functions.
</li>

<li>
The new Drawing tool allows adjustment of individual samples, when fully
zoomed in.  The new Multi-Tool mode gives quick access to different editing
functions without needing to switch tools.
</li>

<li>
Many new keyboard commands have been added, and keyboard shortcuts can
now be customized.
</li>

<li>
New commands:
 <ul>
  <li>Looped play.  Type "L", or hold down shift when clicking Play.</li>
  <li>Type "1" to play a 1-second preview of the audio around the cursor.</li>
 </ul>
</li>

<li>
The mouse wheel can be used to zoom in and out.
</li>

<li>
Tracks can now be zoomed vertically by clicking or dragging in the
vertical rulers.  Shift-click or right-click to zoom out.  
</li>

<li>
The ruler and status bar can now display time in several different
formats, including seconds, samples, or video frames.
</li>

<li>
Audacity's interface can now be translated into languages other than
English.  You can volunteer to help <a href="translation/">translate
Audacity</a> into your native language.
</li>
</ul>
********************************************** ************** */ ?>
