<?php BoxTop("$releaseNotesStr 1.1.3"); ?>

<pre>
Problemes coneguts de l'Audacity 1.1.3:
  - Es crea un fitxer anomenat "Audacity-Commands.xml" en el directori de l'usuari
    o en algun altre lloc de l'ordinador.  Aquest fitxer �s necessari per
    tal que l'Audacity 1.1.3 pugui funcionar. Us demanem disculpes per destorbar
    el vostre ordinador i prometem col�locar aquest fitxer en un lloc m�s adient
    en la propera versi�.

Noves funcionalitats de l'Audacity 1.1.3:
  * Interf�cie d'usuari
    - Nova barra del mesclador, que us permet controlar el volum de sortida
      el volum i la font d'entrada directament des de l'Audacity.
    - Ara cada pista t� els seus controls de guany i panor�mica.

  * E/S de fitxers
    - �s d'un nou format millorat de fitxer de projecte.  (Desafortunadament, la lectura
      dels formats antics, incloent l'1.1.1, no est� suportada.)
    - Els fitxers de blocs (emmagatzemats en les carpetes de projecte de l'Audacity) ara
      fan servir el format est�ndard AU. Tot i que l'Audacity col�loca algunes meta-dades
      en aquests fitxers, ara es poden llegir tamb� amb altres programes d'�udio.
    - S'han arreglat algunes errades relatives a la lectura i escriptura de fitxers
      d'�udio amb m�s de 16 bits per mostra.
    - La importaci� de dades crues (RAW) torna a ser funcional, amb una interf�cie d'usuari
      senzilla per� que suporta molts m�s formats de fitxer. Els algorismes de detecci�
      autom�tica s�n molt m�s acurats que e la versi� 1.0.

  * E/S d'�udio
    - S'ha rescrit totalment l'E/S d'�udio, obtenint una lat�ncia m�nima i reduint dr�sticament
      la possibilitat de provocar un desbordament del magatzem de mem�ria mentre s'enregistra.

  * Delmatge (resampling)
    - �s d'algorismes de delmatge d'alta qualitat, amb l'opci�
      d'obtenir una qualitat superior en mesclar que reproduint en temps real.

    - Suport preliminar a les pistes de temps, per canviar la velocitat
      de reproducci� al llarg del temps.

  * Moltes m�s correccions i noves funcionalitats


Noves funcionalitats de l'Audacity 1.1.2:
  * Interf�cie d'usuari
    - S'ha corregit una errada en la versi� Windows, relativa a les instruccions del men� "pista"
	  "Nom..." i "Separar una pista est�reo"/"Convertir en pista est�reo".
  * Efectes
    - Suport de Nyquist a Windows (suporta complements escrits en
	  Nyquist, un llenguatge funcional interpretat que es basa en el Lisp).


Errors coneguts de l'Audacity 1.1.1:

  * No engegueu l'ordre Benchmark en la versi� per a Windows - podria penjar-se.
    No �s una funcionalitat �til per a la majoria d'usuaris - est� pensada
    perqu� els desenvolupadors puguin valorar la velocitat del programa en diferents
    ordinadors i sistemes operatius.

  * Mac OS X: es pot perdre �udio si premeu el bot� del ratol�
    durant molta estona sobre un men� mentre s'enregistra. Per obtenir bons resultats intenteu
    deixar l'Audacity com a �nica aplicaci� funcionant mentre s'enregistra.

Noves funcionalitats de l'Audacity 1.1.1:

  * Interf�cie d'usuari
    - Els consells apareixen a la barra d'estat.
    - El cursor vertical segueix el punt de reproducci� o enregistrament
    - Bot� de pausa
    - Eina de dibuix (amb tres modalitats diferents)
    - El redimensionament vertical de les pistes estereof�niques �s m�s agradable.
    - Ajustament de la selecci� clicant i arrossegant els l�mits.
    - Activaci�/Desactivaci� dels botons de la barra d'eines segons el context.
    - Funci� de zoom millorada (centra la regi�)
    - Diverses maneres de mostrar la posici� del cursor i la selecci�
    - Mode de selecci� "Enganxat a"
    - Arrossegament de pistes amunt i avall
    - Funcions d'alineament
    - Desar i recuperar el cursor
    - Finestra d'historial de treball
  * Efectes
    - Els efectes s'organitzen en tres men�s: Generaci�, Efecte, i
      An�lisi
    - El men� de generaci� permet crear silenci, soroll o un to
    - Suport del Nyquist (se suporten els complements escrits en Nyquist,
      un llenguatge funcional interpretat basat en el Lisp)
  * Localitzaci�
    - Suport millorat a la localitzaci�
    - M�s idiomes disponibles
    - Di�leg de selecci� d'idioma en engegar
  * Mac OS X
    - M�s maquinari d'�udio suportat
    - Suport del full-duplex (interpretar mentre s'enregistra)
    - Suport de l'exportaci� a MP3 mitjan�ant la biblioteca LameLib Carbon
  * Unix
    - L'Audacity t� ara una p�gina "man" (s'hi descriuen les opcions de l�nia d'ordres
      i com indicar els camins de cerca)
  * Formats de fitxers
    - �s del libsndfile 1.0, que arregla alguns errors i millora
      el rendiment
  * Cerca de fitxers:
    - En Windows i Mac OS, l'Audacity busca ara les traduccions a la
      carpeta "Languages", i tots els complements 
      a la carpeta "Plug-ins", relativa a la ubicaci� del programa.
    - A Unix, l'Audacity cerca les traduccions a
      <prefix>/share/locale i cerca qualsevol cosa
      a <prefix>/share/audacity aix� com en tots els camins indicats
      a la variable d'entorn AUDACITY_PATH


Noves funcionalitats de l'Audacity 1.1.0:

  * Proc�s d'�udio:
    - Permet l'�s de formats de 24-bit i 32-bit
    - Automatic real-time resampling (emprant interpolaci� lineal)
  * Efectes:
    - Pemet l'�s de peda�os LADSPA en Linux / Unix
  * Formats de fitxer:
    - Nou format basat en XML per als projectes Audacity
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
    - Despla�ament autom�tic mentre es reprodueix o s'enregistra
    - Nou Ruler, que s'utilitza en la finestra principal i en el filtre FFT
    - La forma d'ona ara mostra el valor mig en un color llumin�s dintre dels
      valors dels pics
  * Localitzaci�
    - Ara, l'Audacity pot ser localitzat en diferents idiomes.

Noves biblioteques de l'Audacity 1.1.0:

  * libmad per una r�pida importaci� de MP3
  * libid3tag per editar la informaci� dels MP3
  * libsndfile per llegir i escriure m�s formats de fitxers d'�udio
  * PortAudio per enregistrar i reproduir �udio multiplataforma
</pre>

<?php BoxBottom(); ?>
