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
Les fichiers de projets Audacity 1.2 utilisent un nouveau format XML. Audacity 1.2 ouvrira automatiquement un projet d'une version pr�c�dente et le convertira.
</li>

<li>
Audacity 1.2 utilise <a href="http://www.underbit.com/products/mad/">libmad</a>
pour un d�codage plus rapide des fichiers MP3.  Les fichiers<a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> d'Erik de Castro Lopo offre une meilleure compatibilit� avec plusieurs format de fichiers non compress�s.
</li>

<li>
La derni�re version des librairies <a href="http://www.vorbis.com/">Vorbis</a>
est utilis�e, pour une meilleure qualit� d'encodage Ogg Vorbis.
</li>

<li>
Le dialogue "Importer et Ouvrir" permet maintenant aux utilisateurs d'Audacity d'utiliser plusieurs fichiers son � la fois et de les ouvrir dans un seul projet. Un nouveau format de fichier "LOF" permet � Audacity d'ouvrir un groupe de fichiers avec les offsets list�s dans un fichier texte.
</li>
</ul>


<h3>Interface utilisateur am�lior�e</h3>

<ul>
<li>
Nouvelles barres d'outils Edition et Mixage pour un acc�s rapide au fonctions communes.
</li>

<li>
Le nouvel outil de dessin permet l'ajustement d'�chantillons individuels quand le zoom est au maximum. Le nouveau mode Multi-Outil donne un acc�s rapide aux diff�rentes fonctions d'�dition sans avoir � changer d'outil.
</li>

<li>
Plusieurs nouvelles commandes clavier on �t� ajout�es, et les raccourcis clavier peuvent maintenant �tre personnalis�s.
</li>

<li>
Nouvelles commandes:
 <ul>
  <li>Lecture en boucle.  Pressez "L", ou maintenez la touche majuscule enfonc�e en cliquant sur Lecture.</li>
  <li>Pressez "1" pour lire une pr�visualisation d'une seconde autour du curseur.</li>
 </ul>
</li>

<li>
La roulette de la souris peut �tre utilis�e pour zoomer en avant ou en arri�re.
</li>

<li>
Les pistes peuvent maintenant �tre zoom�es verticalement en cliquant ou en d�placent les r�gles verticales.  Shift-click or click-droit pour zoomer en arri�re.  
</li>

<li>
La r�gle et la barre de statut peuvent maintenant afficher le temps dans plusieurs formats diff�rents, incluant les secondes, �chantillons ou images vid�o.
</li>

<li>
L'interface d'Audacity peut maintenant �tre traduite en d'autres langues que l'anglais. Vous pouvez contribuer pour <a href="translation/">traduire
Audacity</a> dans votre propre langue.
</li>
</ul>