<?php BoxTop("$releaseNotesStr 1.1.3"); ?>

<pre>
Zn�m� probl�my v Audacity 1.1.3:
  - Ve va�em dom�c�m adres��i nebo n�kde jinde v po��ta�i si vytvo��
    soubor s n�zvem "Audacity-Commands.xml".  Tento soubor je nezbytn� pro b�h
    programu. Omlouv�me se za zane��d�n� va�eho po��ta�e a slibujeme, �e 
    v dal�� verzi d�me soubor na lep�� m�sto.

Nov� vlastnosti v Audacity 1.1.3:
  * U�ivatelsk� rozhran�
    - Nov� Mixovac� panel umo�nuje nastavovat hlasitost vstupu, 
      v�stupu a vstupn�ho zdroje p��mo z Audacity.

    - Ka�d� stopa m� nyn� vlastn� nastaven� "gain" a panorama (pan).

  * Vstup a v�stup soubor� (File I/O)
    - Pou��v� se nov� vylep�en� projektov� form�t. (Bohu�el na��t�n�
      p�ede�l�ch form�t�, v�etn� 1.1.1, nen� podporov�no.)
    - Blokov� soubory (ulo�en� vadres��i projekt�) nyn�
      pou��vaj� standardn� AU form�t.  A�koliv jsou v t�chto souborech
      n�kter� meta-informace Audacity, mohou b�t na��t�ny i mnoha jin�mi
      popul�rn�mi audio programy.
    - Byly opraveny n�kter� chyby t�kaj�c� se na��t�n� a zapisov�n�
      audio soubor� s v�ce ne� 16ti bity na vzorek.
    - Import RAW je znovu funk�n� a to s jednodu���m rozhran�m (GUI)
      ale zato s podporou daleko v�ce souborov�ch form�t�.
      Autodetek�n� algoritmy jsou mnohem p�esn�j�� ne� u verze 1.0.

  * Vstup a v�stup audia (Audio I/O)
    - Vstup a v�stup audia byl kompletn� p�eps�n s ni��� latenc�
      a minim�ln� �anc� na p�ete�en� bufferu b�hem nahr�v�n�.

  * P�evzorkov�n�
    - Pou��vaj� se vysoce kvalitn� p�evzorkovac� algoritmy,
      s mo�nost� lep�� kvality pro mixov�n� ne� jak� je p�i
      real-timov�m p�ehr�v�n�.

    - P�edb�n� podpora �asov�ch stop, pro zm�ny rychlosti p�ehr�v�n� 
      over time.

  * Mnoho dal��ch oprav chyb a nov�ch vlastnost�.

Nov� vlastnosti v Audacity 1.1.2:
  * U�ivatelsk� rozhran�
    - Opravena chyba Windowsov� verze v menu stopy
  "Jm�no..." a "Rozd�lit stereo stopu"/"Vytvo�it stereo stopu".
  * Efekty
    - Podpora pro Nyquist ve Windows (podporuje pluginy napsan�
      v Nyquistu, interpretovan�m funk�n�m jazyku zalo�en�m na Lisp).

Zn�m� chyby v Audacity 1.1.1:

  * Nespou�t�jte p��kaz Benchmark na Windowsech - m��e zhavarovat.
    Pro v�t�inu u�ivatel� se jedn� o nepot�ebnou funci - je ur�ena
    v�voj���m, aby posoudili rychlost programu na r�zn�ch po��ta��ch
    a opera�n�ch syst�mech.

  * Mac OS X: ��st nahr�vky m��e b�t ztracena, pokud b�hem nahr�v�n�
    stisknete tla��tko my�i nad menu a podr��te ho p��li� dlouho.
    Zkuste b�hem nahr�v�n� nechat Audacity napokoji, obdr��te lep��
    v�sledky.

Nov� vlastnosti v Audacity 1.1.1:

  * U�ivatelsk� rozhran�
    - Tooltipy se objevuj� ve stavov�m ��dku
    - Svisl� kurzor sleduje p�ehr�v�n� i nahr�v�n�
    - Tla��tko Pause
    - N�stroj Kreslen� (s t�emi odli�n�mi re�imy)
    - Svisl� zm�na velikosti stereostop je veselej��
    - P�izp�soben� v�b�ru pomoc� kliknut� a ta�en� hranice v�b�ru
    - Kontextov� senzitivn� vysv�cov�n� tla��tek na panelech
    - Lep�� funkcionalita zv�t�ov�n� (centruje oblast)
    - V�ce zp�sob� zobrazen� pozice kurzoru a v�b�ru
    - Re�im v�b�ru "Snap-to"
    - P�etahov�n� stop nahoru a dol�
    - Zarovn�v�n� a skupinov� zarovn�v�n�
    - Ukl�d�n� a obnovov�n� kurzoru
    - Funk�n� okno historie
  * Efekty
    - Efekty jsou rozd�leny do t�� menu: Generovat, Efekt, a
      Analyzovat
    - Menu Generovat v�m umo�n� generovat ticho, �um nebo t�n
    - Podpora pro Nyquist (podporuje psan� plug-in� v Nyquistu,
      interpretovan�m funkcion�ln�m jazyce zalo�en�m na Lisp)
  * Lokalizace
    - Vylep�en� lokaliza�n� podpora
    - K dispozici je v�ce jazyk�
    - Dialog v�b�ru jazyka p�i startu
  * Mac OS X
    - Podpora v�t��ho mno�stv� audio hardware
    - Podpora pln�ho duplexu (p�ehr�v�n� b�hem nahr�v�n�)
    - Podpora pro export do MP3 s pou�it�m LameLib Carbon
  * Unix
    - Audacity m� nyn� manu�lovou str�nku (popisuje ��dkov� p��kazy
      a jak nastavit vyhled�vac� cestu)
  * Form�ty soubor�
    - Pou��v� se libsndfile 1.0, kter� opravuje n�kter� chyby
      a zlep�uje v�kon
  * Hled�n� soubor�:
    - Na Windowsech a Mac OS, Audacity nyn� hled�
      p�eklady v adres��i "Languages" a v�echny plug-iny
      v adres��i "Plug-ins", relativn� k programu.
    - Na Unixu, Audacity vyhled�v� p�eklady v
      /share/locale a v�echno ostatn� v
      /share/audacity a tak� ve v�ech cest�ch 
      v prom�nn� prost�ed� AUDACITY_PATH.

Nov� vlastnosti v Audacity 1.1.0:

  * Z�kladn� zpracov�n� zvuku:
    - Support for 24-bit and 32-bit sample formats
    - Automatic real-time resampling (using linear
        interpolation)
  * Efekty:
    - Support LADSPA plugins on Linux / Unix
  * Form�ty soubor�:
    - New XML-based Audacity project format
    - Full Ogg Vorbis support now (importing and exporting)
    - Export to any command-line programs on Unix
    - Support for reading and writing many more types of
        uncompressed audio files, including ADPCM WAV files.
  * Panely
    - New toolbar drawing code; automatically adopts your
        operating system's colors
    - New toolbar buttons (Skip to Start, Skip to End)
    - New Edit toolbar
    - Toolbar buttons disable when they're not available
  * U�ivatelsk� rozhran�
    - Fully customizable keyboard commands
    - Autoscroll while playing or recording
    - New Ruler, used in main view and in
        FFT Filter effect
    - The waveform now displays the average value in a lighter
        color inside the peak values
  * Lokalizace
    - Audacity can now be localized to different foreign
      languages.

Nov� vlastnosti v Audacity 1.1:

  * libmad for fast MP3 importing
  * libid3tag for editing MP3 file information
  * libsndfile to read and write more audio file formats
  * PortAudio for cross-platform audio playing and recording
</pre>

<?php BoxBottom(); ?>

