<h2>�nderungen seit Audacity 1.0</h2>

<h3>Audio in Profiqualit�t</h3>

<ul>
<li>
Mit Audacity k�nnen jetzt 24-Bit und 32-Bit (Floating Point) Dateien aufgezeichnet und bearbeitet werden. Tracks mit unterschiedlichen Sampleraten/Sampleformaten innerhalb eines Projektes konvertiert Audacity -falls notwendig- in Echtzeit. Dithering und Resampling erfolgt bei allen Konvertierungen in hoher Qualit�t. Fuer das Resampling werden nun die Algorithmen der Bibliothek von <a href="http://www.mega-nerd.com/SRC/">SRC</a>Erik de Castro Lopo.
</li> angewandt.

<li>
Audacity's Audio-Ein/Ausgabe wurde verbessert. Aufnahmen von mehr als zwei Kan�len sind damit m�glich.  Zur Vermeidung von Spr�ngen und Buffer Underruns wurde die Latenzeit verringert.
</li>
</ul>


<h3>Effekte</h3>

<ul>
<li>
Three new effects change the pitch and Tempo of a track:
 <ul>
  <li>"Pitch" hebt oder senkt die Tonlage innerhalb einer Auswahl ohne die Geschwindigkeit zu beeinflussen.</li>
  <li>"Tempo" wirkt sich anhebend bzw. absenkend auf die Geschwindigkeit der ausgew�hlten Daten aus, bleibt jedoch ohne Auswirkung auf die Tonh�he.</li>
  <li>Die Option "Speed" dagegen �ndert sowohl die Geschwindigkeit als auch die Tonh�he, �hnlich der �nderung der Geschwindigkeit beim Plattenspieler oder Tonbandger�t.</li>
 </ul>
</li>

<li>
Die meisten Effekte enthalten jetzt eine M�glichkeit zum "Vorh�ren". So besteht die M�glichkeit, verschiedene Einstellungen auszuprobieren, ohne das Fenster schliessen zu m�ssen. Eine neue Funktion erlaubt es au�erdem, den zuletzt angewandten Effekt zu wiederholen, ohne das Fenster erneut �ffnen zu m�ssen.
</li>

<li>
Weitere neue Effekte beinhalten:
 <ul>
  <li>Dynamik Kompressor</li>
  <li>Repeat-Funktion (Wiederholung) f�r Samples in Endlosschleifen</li>
  <li>Normalisierung - Korrektur von Lautst�rke und Gleichspannungsabstand</li>
 </ul>
</li>
</ul>


<h3>Neue Editorfunktionen</h3>

<ul>
<li>
Das H�llkurvenwerkzeug, normalerweise f�r weiche Ein- und Ausblendungen benutzt, kann jetzt die Lautstaerke ganzer Tracks anheben oder absenken.
</li>

<li>
Das neue "Time Track"-Feature �hnelt in der Funktion dem vorgenannten H�llkurvenwerkzeug, sorgt jedoch f�r saubere Wechsel der Geschwindigkeit beim Abspielen der Spur.
</li>

<li>
Jede Spur hat jetzt ihre eigenen Lautst�rke- und Balanceregler zum bequemeren Mischen.
</li>

<li>
Audacity kann �berschneidungen finden, die einen weichen Schnitt und saubere Endlosschleifen erlauben. Durch das Dr�cken von "Z" werden die Enden jeweils an die beste Position verschoben.
</li>
</ul>


<h3>Plugins</h3>

<ul>
<li>
Audacity kann jetzt auch unter Linux <a href="http://www.ladspa.org/">LADSPA-Plugins</a> laden.
</li>

<li>
Audacity 1.2.0 verwendet zur digitalen Signalverarbeitung Nyquist, eine Programmiersprache die es Usern erlaubt, Effekte in einer LISP-�hnlichen Sprache zu programmieren.
</li>
</ul>


<h3>Im- und Export von Dateien</h3>

<ul>
<li>
Audacity 1.2 arbeitet mit Projektdateien in einem neuen XML-Format.  Audacity 1.2 �ffnet und konvertiert automatisch Projektdateien der Vorg�ngerversionen.
</li>

<li>
Audacity 1.2.0 verwendet <a href="http://www.underbit.com/products/mad/">Libmad</a>
f�r ein schnelleres Umrechnen der MP3-Dateien..  Erik de Castro Lopo's
<a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> verspricht eine bessere Kompatibilit�t mit vielen nicht komprimierten Audioformaten.
</li>

<li>
Fuer einen Ogg Vorbis-Export werden die aktuellsten <a href="http://www.vorbis.com/">Vorbis Bibliotheken</a> genutzt.
</li>

<li>
Audacity erlaubt jetzt die Auswahl mehrerer Dateien f�r das �ffnen/Importieren in ein einzelnes Projekt.  Das neue "LOF" Dateiformat erm�glicht es dem Anwender an Hand einer Textdatei mit Positionsangaben, gleichzeitig eine Vielzahl zu importierender Dateien zu laden und in einem einzigen Audacity-Projekt zu �ffnen.
</li>
</ul>


<h3>Verbesserte Oberfl�che</h3>

<ul>
<li>
Neue Bearbeitungs- und Mixwerkzeugleisten erlauben schnellen Zugriff auf die wichtigsten Funktionen.
</li>

<li>
Das neue Zeichenwerkzeug erlaubt die eingezoomte Bearbeitung sehr feiner Samples.  Das neue Multifunktionswerkzeug gew�hrt schnellsten Zugriff auf verschiedenste Bearbeitungsfunktionen ohne l�stiges Wechseln der Werkzeuge.
</li>

<li>
Viele neue Tastenfunktionen wurden hinzugefuegt, die Shortcuts k�nnen jetzt angepasst werden.
</li>

<li>
Neue Funktionen:
 <ul>
  <li>Endloswiedergabe durch Dr�cken der Taste "L" oder Gedr�ckt halten der Shift-Taste beim Mausklick auf Wiedergabe.</li>
  <li>Dr�cken der Taste "1", um einen Ausschnitt mit einer L�nge von einer Sekunde ab Cursor anzuspielen.</li>
 </ul>
</li>

<li>
Das Mausrad kann zum Ein- und Auszoomen benutzt werden.
</li>

<li>
In Tracks kann jetzt Durch Klicken oder Ziehen in die vertikalen Lineale eingezoomt werden. Mit Shift+Mausklick oder einfachen Rechtsklick kann wieder ausgezoomt werden.
</li>

<li>
Lineale und Statusleiste k�nnen Zeitangaben in verschiedenen Formaten darstellen, u.B. in Sekunden, Samples oder in Einzelbildern (Video Frames).</li>

<li>
Die Benutzeroberfl�che von Audacity kann jetzt anderen Sprachen neben Englisch verf�gbar gemacht werden. Unter <a href="translation/">Audacity �bersetzen</a> k�nnen Sie helfen, Audacity in Ihre Sprache zu �bersetzen.
</li>
</ul>