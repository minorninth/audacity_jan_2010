<h2>Canvis des de l'Audacity 1.0</h2>

Aquesta secci� llista els canvis m�s importants des de la nostra �ltima versi� estable que va ser el llan�ament de l'Audacity 1.0.0.   Els usuaris de les nostres versions beta haurien de visitar les notes de llan�ament de
<a href="<?php print "betanotes.php$langQueryStr"; ?>">canvis des de la versi� 1.1.3 de l'Audacity</a>.

<h3>Qualitat professional d'�udio</h3>

<ul>
<li>
Audacity can now record and edit 24-bit and 32-bit (floating-point)
samples.  Tracks with different sample rates and formats can exist in
the same project, and Audacity will convert them in realtime whenever
necessary.  High-quality dithering and resampling is used for all
conversions.  Resampling now uses algorithms from the
<a href="http://www.mega-nerd.com/SRC/">SRC</a> library by
Erik de Castro Lopo.
</li>

<li>
S'ha millorat el so d'entrada i de sortida de l'Audacity.  L'Audacity pot ara gravar m�s de dos canals en un.  Latency is reduced, for lower
chances of skipping and buffer underruns.
</li>
</ul>


<h3>Efectes</h3>

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
Hi ha molts efectes que ara inclouen el bot� de "Previsualitzaci�" que permet de triar diferents par�metres sense tancar la finestra d'efecte.  Una nova ordre us permet de repetir l'�ltim efecte sense tornar a obrir la finestra.
</li>

<li>
Altres efectes nous inclosos:
 <ul>
  <li>Compressor, per a un grau din�mic de compressi�.</li>
  <li>Repetidor, per mostres en bucle.</li>
  <li>Normalitzador, per ajustar el volum i corregir bias DC.</li>
 </ul>
</li>
</ul>


<h3>Noves caracter�stiques d'edici�</h3>

<ul>
<li>
L'eina d'entorn, used for smoothly fading tracks in and out, can now be
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


<h3>Peda�os</h3>

<ul>
<li>
En Linux, l'Audacity pot carregar peda�os <a href="http://www.ladspa.org/">LADSPA</a>.
</li>

<li>
Audacity 1.2 features a digital signal processing language called
<a href="nyquist.php">Nyquist</a>, which allows users to program new effects
in a LISP-like language.
</li>
</ul>


<h3>Importaci� i exportaci� de fitxer</h3>

<ul>
<li>
Els fitxers de projecte de l'Audacity 1.2 utilitzen un nou format de fitxer XML.  L'Audacity 1.2 obrir�  i convertir� autom�ticament fitxers de projecte dels llan�aments anteriors.
</li>

<li>
L'Audacity 1.2 utilitza <a href="http://www.underbit.com/products/mad/">libmad</a>
per descodificar fitxers MP3 m�s de pressa.  Erik de Castro Lopo's
<a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> habilita la compatibilitat amb diversos formats no comprimits de fitxers d'�udio.
</li>

<li>
L'�ltima versi� de les llibreries <a href="http://www.vorbis.com/">Vorbis</a>
s�n utilitzades per a una codificaci� d'alta qualitat en Ogg Vorbis.
</li>

<li>
The import and open dialogs now allow Audacity users to select several
audio files at once, and open them into a single project.  A new "LOF"
file format provides a way for Audacity to open a group of files with
offsets listed in a text file.
</li>
</ul>


<h3>Interf�cie d'usuari millorada</h3>

<ul>
<li>
Noves barres d'eines d'edici� i barreja per accedir abans a funcions comunes.
</li>

<li>
La nova eina de dibuix us permet l'ajustament de mostres individuals quan estan totalment aproximades.  El nou mode de multi eina permet l'acc�s r�pid a diferents funcions d'edici� sense necesitar les eines de connexi�.
</li>

<li>
S'hi han afegit moltes noves ordres de teclat, i dreceres de teclat que poden ser personalitzades.
</li>

<li>
Noves ordres:
 <ul>
  <li>reproducci� en bucle.  Teclegeu "L", o pitgeu Maj mentre cliqueu a reproducci�.</li>
  <li>Teclegeu "1" per reproduir 1 segon de previsualitzaci� d'�udio a on sigui el cursor.</li>
 </ul>
</li>

<li>
La rodeta del ratol� pot ser utilitzada per augmentar i per disminuir.
</li>

<li>
Les peces es poden ampliar verticalment clicant i arrossegant en els regles verticals.  Maj-clic o clic amb la dreta per disminuir.  
</li>

<li>
El regla i la barra d'estat ara poden mostrar el temps en diversos formats diferents, incloent-hi segons, mostres, or marcs de v�deo.
</li>

<li>
La interf�cie de l'Audacity ara es pot traduir a diferents idiomes a m�s de l'angl�s.  Hi podeu ajudar <a href="translation/">traduint l'Audacity</a> al vostre idioma natiu.
</li>