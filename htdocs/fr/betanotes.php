<?php BoxTop("$releaseNotesStr $betaVersion"); ?>

<pre>
Probl�mes connus avec Audacity 1.1.3:
  - Il place un fichier appel� "Audacity-Commands.xml" dans votre
    r�pertoire racine ou ailleurs sur votre disque dur. Ce fichier est
    n�cessaire � Audacity 1.1.3 pour fonctionner. Nous sommes
    d�sol�s d'emcombrer ainsi votre ordinateur et prometons de placer
    ce fichier � un meilleur endroit dans la prochaine version.

Nouvelles fonctionnalit�s d'Audacity 1.1.3:
  * Interface Utilisateur
    - Nouvelle barre d'outils de mixage vous permettant de contr�ler le
      volume de sortie, le volume d'entr�e, et la source entrante
      directement depuis Audacity.
    - Chaque piste a d�sormais son propre r�glage de gain et de pan.

  * Fichiers d'E/S 
    - Utilisation d'un format de fichier am�lior� (malheureusement,
      il n'est plus possible de lire l'ancien format de fichiers, y compris
      le 1.1.1) 
    - Les fichier blocs (stock�s dans le r�pertoire du projet Audacity)
      Utilisent maintenant le format AU standard. Comme certaines 
      m�ta-informations d'Audacity se trouvent dans ces fichiers, il
      peuvent d�sormais �tre lus par beaucoup d'autres logiciels audio.
    - Certains bugs relatifs � la lecture et l'�criture de fichier de plus de
      16 bits de r�solution ont �t� corrig�s.
    - L'import des fichiers RAW est de nouveau fonctionnel, avec une
      interface graphique am�lior�e, mais supporte bien plus de formats
      de fichiers. Les algorythmes d'autod�tection sont bien plus pr�cis
      que dans la version 1.0

  * E/S Audio
    - E/S audio compl�tements r��crites, avec une latence plus basse
      et des chances minimum de buffer underruns pendant 
      l'enregistrement.

  * R��chantillonage
    - Utilise des algorythmes de haute qualit�, avec une option de 
      meilleure qualit� pour le mixage que la lecture en temps r�el.

    - Support pr�liminaire pour des pistes de temps, pour changer
      La vitesse de lecture sur un temps donn�.

  * Plusieurs corrections de bugs et nouvelles fonctionnalit�s

Nouvelles fonctionnalit�s d'Audacity 1.1.2:
  * Interface utilisateur
    - Un bug � �t� corrig� dans la version Windows, pour les commandes
      du menu "Nom..." et "S�parer piste st�r�o"/"Cr�er piste st�r�o"
  * Effets
    - Support Nyquist sur Windows (support les plug-ins �crits en Nyquist,
      un language d'interpr�tation fonctionnel bas� sur Lisp).

Bugs connus dans Audacity 1.1.1:

  * Ne lancez pas la commande test de performances sous Windows
    Il peut "planter". Ce n'est pas une commande utile pour la plupart des
    utilisateurs -  elle � �t� con�ue pour les d�veloppeurs afin de juger
    des performances sur diff�rentes machines et syst�mes.

  * Mac OS X: De l'audio pourrait �tre perdue si vous tenez le bouton
    de la souris trop longtemps appuy� sur un menu pendant 
    l'enregistrement. Essayez de faire fonctionner Audacity seul pour
    de meilleurs r�sultats.

Nouvelles fonctionnalit�s d'Audacity 1.1.1:

  * Interface utilisateur
    - Tooltips appear in Statusbar.
    - Vertical cursor follows play/record
    - Pause button
    - Drawing tool (with three different modes)
    - Vertical Resizing of stereo tracks is more fun.
    - Adjust selection by click-dragging selection boundary
    - Toolbar button context-sensitive enabling/disabling
    - Better zooming functionality (centers region)
    - Multiple ways to display the cursor position and selection
    - Snap-to selection mode
    - Drag tracks up and down
    - Align and group align functions
    - Cursor save/restore
    - Working history window
  * Effects
    - Effects broken down into three menus: Generate, Effect, and
      Analyze
    - Generate menu lets you generate silence, noise, or a tone
    - Nyquist support (supports plug-ins written in Nyquist,
      an interpreted functional language based on Lisp)
  * Localization
    - Improved localization support
    - More languages available
    - Language selection dialog on startup
  * Mac OS X
    - Support for more audio hardware
    - Support for full-duplex (play while recording)
    - Support for MP3 exporting using LameLib Carbon
  * Unix
    - Audacity now has a man page (it describes command-line
      options and how to set the search path)
  * File Formats
    - Uses libsndfile 1.0, which fixes some bugs and
      improves performance
  * Searching for Files:
    - On Windows and Mac OS, Audacity now looks for
      translations in the "Languages" folder and all plug-ins
      in the "Plug-ins" folder, relative to the program.
    - On Unix, Audacity looks for translations in
      <prefix>/share/locale and looks for everything else
      in <prefix>/share/audacity and also in any paths in
      the AUDACITY_PATH environment variable

New features in Audacity 1.1.0:

  * Core audio processing:
    - Support for 24-bit and 32-bit sample formats
    - Automatic real-time resampling (using linear
        interpolation)
  * Effects:
    - Support LADSPA plugins on Linux / Unix
  * File formats:
    - New XML-based Audacity project format
    - Full Ogg Vorbis support now (importing and exporting)
    - Export to any command-line programs on Unix
    - Support for reading and writing many more types of
        uncompressed audio files, including ADPCM WAV files.
  * Toolbars
    - New toolbar drawing code; automatically adopts your
        operating system's colors
    - New toolbar buttons (Skip to Start, Skip to End)
    - New Edit toolbar
    - Toolbar buttons disable when they're not available
  * User Interface
    - Fully customizable keyboard commands
    - Autoscroll while playing or recording
    - New Ruler, used in main view and in
        FFT Filter effect
    - The waveform now displays the average value in a lighter
        color inside the peak values
  * Localization
    - Audacity can now be localized to different foreign
      languages.

New libraries in Audacity 1.1:

  * libmad for fast MP3 importing
  * libid3tag for editing MP3 file information
  * libsndfile to read and write more audio file formats
  * PortAudio for cross-platform audio playing and recording
</pre>

<?php BoxBottom(); ?>