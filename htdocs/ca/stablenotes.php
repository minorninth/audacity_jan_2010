<?php BoxTop("$releaseNotesStr $stableVersion"); ?>

<pre>
Problemes coneguts:

* Windows: La paleta d'eines flotant no immnimitza en
  minimitzar la finestra del projecte.  Ara per ara, la millorsoluci� 
  seria deixar la paleta encastada a la finestra del projecte.

* Linux: Duplex complet (reproducci� d'una pe�a mentre se'n grava una altra)
  no sembla funcionar, fins i tot si la vostra targeta de so ho permet.
  Per aquest problema de moment estem utilitzant OSS.

* Linux: Les targetes de so nom�s reparteixen quan m�s de dos
  canals encara no es poden fer servir.

-------------------------------------------------------------

Canvis de la 1.0:

  * Mac OS:

    - L'Audacity ja no finalitza quan tanqueu l'�ltima finestra.
      La barra del men� hi queda i podeu obrir una finestra nova.

    - S'ha fixat un error que xausava que el di�leg de prefer�ncies
      no aparegu�s en Mac OS 9 amb el plaf� de control ATM

    - S'ha fixat un error que prevenia gravar a velocitats baixes
      en Mac OS 9
      
    - Reconeix els fitxers MP3 per l'extensi� de fitxer i codi teclejat

    - L'Audacity �s ara m�s estable i funcional en MacOS X

  * Noves caracter�stiques:

    - S'ha afegit el di�leg "Desa els canvis" a totes les plataformes

    - R�tols indocadors de funci�

    - Noves dreceres i ordres de teclat

    - Les etiquetes de peces ara es poden fer servir per marcar regions
      de selecci�. -- vegeu el manual d'usuari.

  * Unix:

    - S'ha fixat un error que provocava que l'�udio es reprodu�s massa
      r�pid (especialment en sistemes Mandrake).

    - S'ha fixat un error que corrompia els fitxers quan s'exportava un
      fitxer sobreescrivint-ne un altre.

  * Altres:

    - Els efectes VST es procesen m�s de pressa

    - Miscel�l�nia d'errors fixats

Chanvis en la 0.98b (llan�ament amb nom�s fixacions pel Windows):

  - S'ha fixat la fallada de l'"extractor de soroll"

  - S'ha afegit el fi�leg "Desa els canvis"

  - Torna a permetre l'�s de marcadors ID3 en el Windows

  - M�s fixacions d'errors

Canvis en la 0.98:

* Efectes

  - Nou efecte d'inversi�

  - Nou efecte de revertiment

  - Millores en l'efecte d'extaccci� de soroll

* Fixacions d'errors

  - You can now safely copy and paste between projects.

  - Fixed bugs loading, saving, and undoing envelopes.

  - You're not allowed to open the same project in two different
    windows anymore (it just would have caused data loss).

  - Projects now save the channel of each track, it's no longer
    forgotten

  - Better handling of case when temp directory is invalid at
    start of program

  - Doesn't overwrite a file the project was depending on anymore
    (it renames the old file).  You can now export to a file
	 with the same as the file you imported without any problems.

  - Save As... for a project doesn't destroy the old project anymore.

  - Undo information is thrown away when you close a project,
    saving disk space that had been wasted in previous versions.

  - Save As... recovers gracefully when you try to save to a
    bad location

  - Duplicate of a track with an offset now works

  - Fixed another crash in Amplify... (if no data is selected in
    one of the tracks)

  - Windows: recording/playback devices are no longer reversed
    in the preferences!

  - Windows: VST plug-ins are found no matter how Audacity is
    launched.

  - Windows: You can now import Ogg Vorbis files.

  - If recording fails, a phantom track is no longer created.

  - Changing the export format now changes the menu bar.

  - More minor bug fixes...

* Unix:

  - New OSS code, should provide better playback and record on
    almost all OSS Unix systems.

  - Preliminary support for the KDE/aRts soundserver (a compile-time
    option; must be configured to use this in place of OSS code)

  - Bug fixes to "make install" script

Canvis en el 0.97:

* Instal�laci�/configuraci�

  - Nou instal�lador del Windows

  - M�s opcions a l'escript de configuraci� de l'Unix

* Interf�cie d'usuari:

  - Fixed Effects menu bug that would freeze if some but
    not all tracks were selected.

  - S'ha afegit l'efecte d'extracci� de soroll (Dominic)

  - Improved click-drag zoom.

  - Support drag-and-drop to import audio files (Windows only)

  - Improved Export file dialog (asks about strange extensions)

  - Altres fixacions d'errors

* MacOS:

  - Fixed autoscrolling bug (would sometimes appear if you
    release the cursor outside the window while selecting).

* Unix:

  - Fixed Amplify bug (would sometimes freeze trying to
    open the dialog).

Canvis en el in 0.96:

* Usuari general d'interf�cie:

  - S'ha afegit els botons silenci/solo

* Importaci� d'�udio:

  - Fixed regression bug in 0.95 which caused stereo files to be imported as
    two mono tracks
    
  - Importaci� de marcadors MP3 ID3

* Exportaci� d'�udio:

  - Exporting MP3 now works, if the appropriate version of the LAME DLL is
    installed (Joshua)
  
  - Allows editing of MP3 ID3 tags with export.

* Prefer�ncies:

  - Added Audio I/O selectors on Mac (Dominic) and Windows (Joshua)

* Efectes:

  - Added progress dialog support to all effects (which also allows
    effects to be cancelled)
  
  - Added support for stereo effects and effects that add or
    remove tracks, or require multiple passes.
  
  - Improved Amplify effect and fixed all known bugs (Dominic)
  
  - Improved Bass Boost effect
  
  - Added Filter effect (Dominic)
  
  - Added Phaser effect (Paul)
  
  - Added Wahwah effect (Paul)

Canvis en el 0.95:

* Instal�laci�/Compilaci�:

  - Improved configure script on unix systems (Joshua)

* General User Interface:

  - Menu items are now disabled when unavailable

  - Online help added (Dominic and Logan)

* Importing Audio:

  - Lazy import added, speeding up importing of PCM files by 2x

  - Added support for the Free libmpeg3 library on unix 
    to replace the proprietary xaudio (Joshua)

  - Importing MP3 and Ogg Vorbis files is now handled automatically
    by the Open and Import commands.

  - Fixed the Import Raw Data feature, so now you can
    import files of almost any arbitrary format (as long
    as it's uncompressed).

* Main window:

  - New track labels with a single integrated pop-up menu
    to handle all track options

  - Vertical ruler added, along with preliminary support for
    vertical zooming

  - Stereo tracks can be linked together so changes affect
    both tracks

  - Point-sample display takes over when you zoom very far in

  - Two new wave displays: a dB (logarithmic) wave display and
    a spectral pitch display (using enhanced autocorrelation)

* Preferences:

  - New spectral display preferences

  - Temp directory can be set in preferences

* Frequency display:

  - Many new frequency window enhancements, including support for
    cepstrum, autocorrelation, and enhanced autocorrelation.

* Envelope editor:

  - Envelopes are now interpolated using decibels, making
    cross-fades sound much better

* Effects:

  - Fixed a bug that caused incompatibility with many VST plug-ins.

  - Added Maximize Amplitude effect

  - Added Bass Boost effect (Paul)

* Other:

  - Improved memory management over long Undo histories

  - Many more bug fixes

Changes in 0.94:

* Preferences dialog (Joshua Haberman)

* OGG Vorbis import (Joshua Haberman)

* Silence, Insert Silence commands

* Split and Duplicate commands

* Mac OS X support

* Supports recording on Mac OS 8 and 9

* Many bug fixes

Changes in 0.93:

* Displays playback/recording position indicator

* Keeps track of some preferences

* Supports arbitrary project sample rate

* Mac: opens documents from the Finder

* Floating tool palette is now dockable
  (and docked by default)

* Fixed bugs in handling multiple open projects

* Supports recording (Windows, Linux)

* Frequency Window displays note names (i.e. C4, G#5)

* Many bug fixes for effects, including VST plug-in effects

Changes in 0.92:

* Added Frequency Plot window and improved Spectrum display

* Fixed bug in File:Open when the file to be opened was
  actually a large WAV file

Changes in 0.91:

* Uses xaudio library to import mp3 files

* Zoom menu

Changes in 0.9:

* New floating tool palette with four tools (selection,
  sliding, zooming, and envelope editing) plus play and
  stop buttons

* Playback now mixes tracks, and you can work with the
  document while listening.  The stop button works.

* Rewritten file handling functions.  The main view
  is no longer dependent on the wxWindows DocView
  classes, so we can handle files ourselves.  The
  project file format is now text-based for easy
  debugging.  Eventually it will probably move to XML.

* Improved handling of wave tracks: as before, the data
  is stored in blocks, but now, the blocks are correctly
  limited to betweek n and 2n bytes each (for some n),
  which guarantees editing operations always take the
  same amount of time, while also ensuring that projects
  don't get more fragmented over time.

* Rewritten user interface code.  The shades of gray
  are taken from the OS, and the project window has been
  redesigned to have more consistent layout across all
  platforms.

* Selecting "Open" now does the smart thing, opening a
  project if you give it a project, or importing a WAV
  file if you give it that.

* Flashing cursor indicates the current editing position

* Much improved ruler - besides looking nicer, the ruler
  now displays the selection and the cursor.

* The zoom tool centers on the cursor so you can zoom
  into wherever you are.

</pre>

<?php BoxBottom(); ?>
