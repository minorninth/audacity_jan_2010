<h2>Changes Since Audacity 1.0</h2>

Cette section liste les changements majeurs depuis notre derni�re version stable, Audacity 
1.0.0.  Les utilisateurs de notre version b�ta devraient consulter les notes
<a href="<?php print "betanotes.php$langQueryStr"; ?>">changements depuis Audacity 1.1.3</a>.

<h3>Qualit� audio professionnelle</h3>

<ul>
<li>
Audacity peut maintenant enregistrer et �diter des �chantillons en 24-bit et 32-bit (virgule-flottante).  Des pistes avec diff�rent taux d'�chantillonage et formats peuvent exister dans le m�me projet, et Audacity les convertira en temps r�el quand c'est n�cessaire. Un dithering et un r��chantillonage de haute qualit� sont utilis�s pour toutes les conversions.
Le r��chantillonage utilise maintenant les algorythmes de la librairie
<a href="http://www.mega-nerd.com/SRC/">SRC</a> par
Erik de Castro Lopo.
</li>

<li>
L'entr�e et la sortie son d'Audacity a �t� am�lior�e.  Audacity peut maintenant enregistrer plus de deux canaux � la fois. La latence est r�duite, pour r�duire les risques de saut et de buffer underruns.
</li>
</ul>


<h3>Effets</h3>

<ul>
<li>
Trois nouveaux effets changent la hauteur et le tempo de la piste:
 <ul>
  <li>Changer Hauteur augmente ou diminue la tonalit� de la s�lection, sans affecter la vitesse.</li>
  <li>Changer Tempo augmente ou diminue la vitesse de lecture, sans alt�rer la hauteur.</li>
  <li>Changer Vitesse alt�re et la vitesse et la hauteur, exactement comme en changeant la vitesse d'une platine tourne-disque ou K7.</li>
 </ul>
</li>

<li>
La plupart des effets incluent maintenant un bouton "Pr�visualisation", qui permet d'essayer diff�rent r�glages sans fermer la fen�tre d'effet. Une nouvelle commande vous permet de r�p�ter le dernier effet sans r�ouvrir la fen�tre.
</li>

<li>
Autres nouveaux effets inclus:
 <ul>
  <li>Compresseur, pour compression dynamique.</li>
  <li>Repeat, pour faire des boucles.</li>
  <li>Normaliser, pour ajuster le volume et corriger le DC bias.</li>
 </ul>
</li>
</ul>


<h3>Nouvelles fonctions d'�dition</h3>

<ul>
<li>
L'outil d'enveloppe, utilis� pour adoucir les transitions des Fades entre pistes, peut maintenant �tre utilis� pour augmenter ou diminuer le volume des pistes.
</li>

<li>
La nouvelle fonction "Time track" est similaire � l'enveloppe de volume mais change la vitesse de lecture en douceur pendant la lecture.
</li>

<li>
Chaque piste a maintenant son propre volume de Gain et de Panoramique, pour un mixage facilit�.
</li>

<li>
Audacity peut trouver les zero-crossings, pour aider � cr�er des coupures et des boucles sans-�-coups. Pressez "Z" pour d�placer les bords de la s�lection aux plus proches zero-crossings.
</li>
</ul>


<h3>Plugins</h3>

<ul>
<li>
Sous Linux, Audacity peut maintenant charger les plugins <a href="http://www.ladspa.org/">LADSPA</a>.
</li>

<li>
Audacity 1.2 comprend un language de traitement du signal num�rique appel� 
<a href="nyquist.php">Nyquist</a>, qui permet � l'utilisateur de programmer de nouveaux effets dans un language similaire � LISP.
</li>
</ul>


<h3>Importation et exportation de fichiers</h3>

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


<h3>Improved User Interface</h3>

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