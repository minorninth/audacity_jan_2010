<pre>
Changements dans la version 1.2.0-pre3:

  * R�solution d'un bogue grisant Export lorsque rien n'est s�lectionn�.

  * R�solution de crash caus� par Audacity sur ordinateur �quip� d'une carte son sans support de mixage.

  * Crash r�solu lors de l'importation de donn�es Raw.

  * Stabilisation de Nouvelle piste St�r�o.

  * Am�lioration esth�tiques pour Mac OS X.

  * Support de VST Enabler ajout� � la version Windows.

  * R�solution d'un crash survenant lors de la fermeture d'Audacity alors que la bo�te de dialogue est ouverte.

  * R�solution d'un bogue de double affichage sous Mac OS X dans les pistes d'index.

  * Le contr�le du niveau d'enregistrement sous Linux ajuste maintenant l'IGAIN,
    plut�t que le niveau de passage de la source d'enregistrement.

  * R�solution d'un bogue provoquant une corruption de l'enregistrement en 16-bit st�r�o.

  * R�solution d'un bogue causant une perte de donn�es lors de l'effacement de toutes les pistes d'un projet enregistr� et de l'ouverture d'un nouveau fichier dans la m�me fen�tre .

  * Ajout d'une possibilit� de disposition ergonomique des boutons (dans Pr�f�rences > Interface)

  * Ajout d'un support pr�liminaire pour wxX11

  * Ajout d'ic�ne Windows XP totalement transparente

  * R�solution d'un crash lors de l'enregistrement (ou de la lecture) losqu'il n'existe aucun p�riph�rique audio, ou que celui-ci ne supporte pas le mode choisi.

  * Audacity ne donne plus une priorit� de t�che haute lors de l'enregistrement sous Windows.  Les utilisateurs peuvent toutefois le faire manuellement depuis le manager de t�ches.

  * R�solution d'un bogue provoquant la coupure de ~100 ms de la fin de la s�lection.

  * Dialogues d'effets pour filtres FFT et Egalisation.

  * R�solution de bogues sous syt�mes Unix (DESTDIR en r�pertoire local,
    s�lectionnant libsamplerate au lieu de libresample)

  * Ajout de support pour modules LADSPA sous Windows, et trois modules LADSPA libres port� sous Windows
    (r�verb�ration GVerb,compresseur SC4, et Hard Limiter)

Changements dans la version 1.2.0-pre2:

  * Aide en ligne compl�t�e. Le manual complet est proche de la finalisation et sera en ligne bient�t.

  * Audacity ne vous laissera plus faire des op�rations d'�dition peu s�res pendant la lecture ou l'enregistrement. Cela �limine plusieurs crashes potentiels.

  * Possibilit� d'annuler le bouton quitter corrig�e.

  * Nouvelle librairie de r��chantillonnage, sans restrictions de taux maximum ou minimum de r��chantillonnage.

  * Audacity supporte maintenant les plug-ins LADSPA sur toutes les plate-formes, et supporte les plug-ins VST � travers un plug-in LADSPA optionnel appel� "VST Enabler", que vous pouvez t�l�charger s�par�ment. Pour des questions de licences, Audacity ne peu pas �tre distribu�e avec un support VST int�gr�.

  * Mac OS X: probl�mes de raccourcis clavier corrig�s.

  * Mac OS X: probl�mes de coupures de son corrig�s.

  * Mac OS X: les probl�mes de synchro du curseur en lecture/enregistrement sont corrig�s.

  * Silence affiche de nouveau une ligne droite au lieu de rien.

  * Ajout� une r�gle verticale � l'affichage Forme d'onde dB.

  * Corrig� un crash dans changer Hauteur.

  * Vous pouvez maintenant coller si rien n'est s�lectionn�.

  * Annuler une op�ration d'importation ne fait plus apparaitre une dialogue d'erreur suppl�mentaire.

  * Audacity prend maintenant correctement en charge les noms de fichiers avec des caract�res internationaux.

  * Ecrit maintenant des tags ID3v2.3 (au lieu de ID3v2.4), pour �tre compatible avec plus de lecteurs MP3.

  * Minor improvements to build system on Unix systems.

Nouvelles fonctionnalit�s d'Audacity 1.2.0-pre1:

  * Interface utilisateur
    - Zoom vertical dans les pistes.
    - Apparence et emplacement des barres d'outils am�lior�s.
    - Nouveau curseurs de souris am�lior�s.
    - Impl�mentation compl�te des raccourcis clavier.
    - Recherche des zero-crossings.
    - La roulette de la souris peut-�tre utilis�e pour le zoom avant ou
      arri�re.
    - Mode multi-outils.
    - Amplifier en utilisant l'envelope.
    - Labels peuvent stocker les s�lections(comme Audacity 1.0.0).

  * Effets
    - R�p�ter la derni�re commande d'effet.
    - Support des plug-in VST am�lior�.
    - La plupart des effets on maintenant un bouton pr�visualisation.
    - Compresseur (Compresseur Dynamique).
    - Changer la hauteur de note(sans changer le tempo).
    - Changer le Tempo (sans changer la hauteur de note).
    - Changer la vitesse (en changeant et la hauteur de note et le tempo).
    - Repeat (utile pour cr�er des boucles).
    - Normalisation (ajuste le volume et DC bias).

  * E/S Audio
    - Commande 1-seconde de pr�visualisation.
    - Lecture en boucle.

  * E/S Fichier
    - Audacity 1.2.0 ouvre les projets de toutes les versions pr�c�dentes
      d'Audacity, de la 0.98 � la 1.1.3.
    - Ouvre plusieurs fichier depuis la m�me boite de dialogue.
    - Utilise un fichier texte pour sp�cifier un liste de fichier
      audio � ouvrir avec offsets.

  * Mode d'emploi mis � jour.


Bogues corrig�s dans Audacity 1.2.0-pre1

  * Les fichier projet contenant des caract�res sp�ciaux ne sont plus
    invalides.

  * Les bruits de "Scratch" caus�s par une saturation sont corrig�s.

  * Audacity n'exporte plus des fichiers Ogg invalides, et ne coupe plus
    les derni�res secondes des fichiers Ogg export�s.

  * Les fichiers MP3 mono sont maintenant export�s � la bonne vitesse.

  * Plusieurs r�sultats incorrects de l'outil d'enveloppe ont �t� corrig�s.

  * La commande "Exporter Labels" remplace correctement les fichiers
    existants.
  
  * La fen�tre "Plot Spectrum" affiche le nombre correct d'octaves pour les notes.

  * Plusieurs d�faillances m�moire corrig�es.

  * Plusieurs autres corrections de bugs mineurs.
</pre>

 

    
 
