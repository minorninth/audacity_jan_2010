<?php BoxTop("$releaseNotesStr $betaVersion"); ?>

<pre>
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
