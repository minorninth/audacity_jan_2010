<?php BoxTop("$releaseNotesStr $betaVersion"); ?>

<pre>
Problemas conocidos en Audacity 1.1.3:
  - Coloca un archivo llamado "Audacity-Commands.xml" en tu directorio
    principal u otra parte de tu computadora. Este archivo es necesario
    para el funcionamiento de Audacity 1.1.3. Pedimos disculpas por
    desordenar tu computadora y prometemos colocar el archivo en un
    lugar m�s agradable en la pr�xima versi�n.

Nuevas capacidades en Audacity 1.1.3:
  * Interface del Usuario
    - Nueva barra de herramientas Mezcladora te permite controlar
      el volumen de salida, volumen de entrada, y el dispositivo
      de entrada directo desde Audacity.

  * Archivo E/S
    - Utiliza un formato de achivo de proyecto mejorado.
      (Desafortunadamente la lectura de formatos previos,
      incluyendo 1.1.1, no es soportada.)
    - Archivos de bloque (guardados en directorios de proyecto de
      Audacity) ahora utilizan el formato est�ndar AU. Aunque hay
      un poco de meta-informaci�n de Audacity en estos archivos,
      ahora pueden ser leidos tambi�n por muchos otros programas
      populares de audio.
    - Se solucionaron algunos errores relacionados con la
      lectura/escritura de archivos de audio con m�s de 16 bits
      por muestreo.
    - Importar archivos en bruto (RAW) funciona nuevamente, con
      una interface gr�fica m�s simple pero con soporte para muchos
      m�s formatos de archivo. Los algoritmos de autodetecci�n son
      mucho m�s precisos que en 1.0.

  * Audio E/S
    - Audio E/S completamente reescrito, con menor tardanza
      y m�nima posibilidad de *buffer underruns* mientras
      se graba.

  * Remuestreo
    - Utilizando algoritmos de remuestreo de alta calidad, con
      la opci�n de mejor calidad para el mezclado que para
      reproducci�n en tiempo-real.

    - Soporte preliminar para Pistas de Tiempo, para cambiar
      la velocidad de reproducci�n en el tiempo.

  * Muchos m�s errores reparados y nuevas capacidades

Nuevas capacidades en Audacity 1.1.2:
  * Interface del Usuario
    - Error solucionado en la versi�n de Windows, para comandos
      del men� de pista
      "Nombre..." y "Partir Pista Est�reo"/"Hacer Pista Est�reo".
  * Efectos
    - Soporte para Nyquist en Windows (soporta plug-ins escritos
      en Nyquist, un lenguaje funcional interpretado basado
      en Lisp).

Errores(bugs) conocidos en Audacity 1.1.1:

  * No corras el comando Benchmark (test de rendimiento) en
    Windows - puede terminar el programa. No es una opci�n muy
    �til para la mayor�a de usuarios - est� pensada para que los
    desarrolladores juzguen la velocidad del programa en distintas
    computadoras y sistemas operativos.

  * Mac OS X: puede perderse audio si mantienes el bot�n del mouse
    demasiado tiempo sobre un men� mientras grabas. Intenta liberar
    a Audacity mientras grabas para mejores resultados.

Nuevas caracter�sticas en Audacity 1.1.1:

  * Interface del Usuario
    - Aparecen *Tooltips* en la Barra de Estado.
    - Cursor vertical sigue reproducci�n/grabaci�n
    - Bot�n de Pausa
    - Herramienta de Dibujo (con tres modos diferentes)
    - Cambio de tama�o vertical de pistas est�reo es m�s amigable.
    - Ajustar selecci�n cliqueando-arrastrando l�mite de selecci�n
    - Habilitar/deshabilitar Barra de Herramientas sensible a
      contexto
    - Mejor funcionalidad de Zoom (centra la regi�n)
    - M�ltiples formas de mostrar la posici�n del cursor y
      selecci�n.
    - Modo de selecci�n Saltar-Hacia
    - Arrastrar pistas hacia arriba y abajo
    - Funciones alinear y alinear grupo
    - Guardar/restaurar cursor
    - Ventana de historia de trabajo
  * Efectos
    - Efectos repartidos en tres men�es: Generar, Efectos, y
      Analizar
    - El men� Generar te permite generar silencio, ruido, o un
      tono
    - Soporte para Nyquist (soporta plug-ins escritos en Nyquist,
      un lenguaje funcional interpretado basado en Lisp)
  * Localizaci�n
    - Soporte mejorado de localizaci�n
    - M�s lenguajes disponibles
    - Cuadro de di�logo para selecci�n de lenguaje al comenzar.
  * Mac OS X
    - Soporte para mas hardware de audio.
    - Soporte para full-duplex (reproducir mientras grabas)
    - Soporte para exportaci�n de MP3 utilizando LameLib Carbon
  * Unix
    - Audacity ahora tiene una *man page* (describe opciones de
      l�nea de comandos y c�mo configurar el path de b�squeda)
  * Formatos de Archivo
    - Utiliza libsndfile 1.0, que arregla algunos errores(bugs)
      y mejora el rendimiento
  * B�squeda de Archivos:
    - En Windows y Mac OS, Audacity ahora busca traducciones en
      la carpeta "Languages" y todos los plug-ins en la carpeta
      "Plug-ins", relativas al programa.
    - En Unix, Audacity busca traducciones en
      <prefijo>/share/locale y busca por todo lo dem�s
      en <prefijo>/share/audacity y tambi�n en cualquier path en
      la variable de entorno AUDACITY_PATH

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