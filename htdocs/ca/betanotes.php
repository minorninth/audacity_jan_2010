<?php BoxTop("$releaseNotesStr $betaVersion"); ?>

<pre>
Known issues in Audacity 1.1.3:
  - It places a file called "Audacity-Commands.xml" in your home directory
    or somewhere else on your computer.  This file is necessary for
    Audacity 1.1.3 to run.  We apologize for cluttering up your computer
    and promise to put the file in a nicer place in the next version.

New features in Audacity 1.1.3:
  * User Interface
    - New Mixer toolbar allows you to control the output
      volume, input volume, and input source directly
      from Audacity.
    - Every track now has its own gain and pan controls.

  * File I/O
    - Uses improved project file format.  (Unfortunately reading
      previous formats, including 1.1.1, is not supported.)
    - Block files (stored in Audacity project directories) now
      use the standard AU format.  Though some Audacity
      meta-information is in these files, they can now be
      read by many other popular audio programs as well.
    - Fixed some bugs relating to reading/writing audio
      files with more than 16 bits per sample.
    - Import RAW is functional again, with a simpler GUI
      but support for far more file formats.  The
      autodetection algorithms are much more accurate than
      in 1.0.

  * Audio I/O
    - Completely rewritten audio I/O, with lower latency
      and minimal chance of buffer underruns while
      recording.

  * Resampling
    - Using high quality resampling algorithms, with the
      option of better quality for mixing than for real-time
      playback

    - Preliminary support for Time Tracks, for changing
      playback speed over time.

  * Many more bug fixes and new features

New features in Audacity 1.1.2:
  * User Interface
    - Fixed bug in Windows version, for track menu commands 
	  "Name..." and "Split Stereo Track"/"Make Stereo Track".
  * Effects
    - Nyquist support on Windows (supports plug-ins written 
	  in Nyquist, an interpreted functional language based 
	  on Lisp).

Nous errors de l'Audacity 1.1.0:

  * No engegueu l'ordre Benchmark en el Windows - pot petar.
    No �s una caracter�stica �til per molts usuaris - els 
    desenvolupadors l'han col�locat per jutjar la velocitat del programa en
    diferents ordinadors i sistemes operatius.

Noves caracter�stiques de l'Audacity 1.1.0:

  * Core audio processing:
    - Permet l'�s de formats de 24-bit i 32-bit
    - Automatic real-time resampling (emprant interpolaci� lineal)
  * Efectes:
    - Pemet l'�s de peda�os LADSPA en Linux / Unix
  * Formats de fitxer:
    - Nou format e XML-based Audacity project format
    - Ara permet l'�s complet del Ogg Vorbis (importar i exportar)
    - Exporta a qualsevol programa de l�nies d'ordres de l'Unix
    - Permet llegir i escriure diversos tipus d'incompresos formats
        de fitxers d'�udio, incloent-hi els fitxers ADPCM WAV.
  * Barres d'eines
    - Nou codi de dibuix de la barra d'eines; adopta autom�ticament els colors
        del vostre sistema operatiu
    - Nous botons de la barra d'eines (Skip to Start, Skip to End)
    - Nova barra d'eines
    - Els botons estan inhabilitats quan no estan disponibles
  * Interf�cie de l'usuari
    - Ordres del teclat totalment personalitzables
    - Despla�ament autom�tic mentre es reprodueix o grava
    - New Ruler, used in main view and in
        FFT Filter effect
    - La forma d'ona ara mostra el valor mig en un color llumin�s dintre dels
        valors dels pics
  * Localitzaci�
    - Ara, l'Audacity pot ser localitzat en diferents lleng�es estrangeres.

Noves llibreries de l'Audacity 1.1:

  * libmad per una r�pida importaci� de MP3
  * libid3tag per editar la informaci� dels MP3
  * libsndfile per llegir i escriure m�s formats de fitxers d'�udio
  * PortAudio per gravar i reproduir �udio multiplataforma
</pre>

<?php BoxBottom(); ?>
