<pre>
Canvis a 1.2.0-pre3:

  * Arreglat un error que feia que l'ordre "Exporta" es vei�s en gris
    quan no hi havia res seleccionat.

  * Arreglat un error que apareixia quan s'obria l'Audacity en un ordinador
    amb targeta de so sense suport de mesclador.

  * Arreglada la importaci� de dades crues.

  * Arreglada l'ordre "Nova pista est�reo".

  * Canvis cosm�tics per al Mac OS X.

  * Afegit el suport a l'habilitador VST en Windows.

  * Arreglat l'error que es produ�a si es tancava l'Audacity amb el di�leg
    de prefer�ncies obert.

  * Arreglat l'error de lletres duplicades en les etiquetes de pistes 
    amb Mac OS X.

  * El nivell d'enregistrament en Linux ara ajusta l'IGAIN,
    en comptes d'actuar sobre el nivell de la font d'enregistrament.

  * Arreglat un error que causava corrupci� de dades en enregistraments
    est�reo de 16 bits.

  * Arreglat l'error que provocava p�rdua de dades si esborr�veu totes 
    les pistes d'un projecte desat i obr�eu un nou fitxer a la 
    mateixa finestra.

  * Afegit el suport al bot� altern d'�udio (a les prefer�ncies d'interf�cie)

  * Afegit el suport preliminar a wxX11

  * Afegida una icona transparent per a Windows XP

  * Arreglat l'error que es produia si intent�veu enregistrar (o reproduir)
    sense tenir deispositius d'�udio, o si els dispositius no suportaven
    el mode seleccionat.

  * L'Audacity ja no es col�loca com a proc�s d'alta prioritat quan enregistra
    en Windows.  Els usuaris poden continuar fent aix� des de
    l'administrador de tasques.

  * Arreglat un error que causava la p�rdua dels darrers ~100 ms de la
    selecci� quan es retallava, en Windows.

  * Arreglats els di�legs dels efectes "Filtre FFT" i "Equalitzaci�".

  * Arreglats errors en el sistema de muntatge en Unix (DESTDIR al directori
    local, escollint libsamplerate en comptes de libresample)

  * Afegit el suport als complements LADSPA en Windows, i 
    tres complements LADSPA de codi obert portats a Windows
   (reverberador GVerb, compressor SC4, i Hard Limiter)

Canvis a 1.2.0-pre2:

  * Ajuda en l�nia completada. El manual est� gaireb� acabat i es
    col�locar� a la web per poder ser consultat en breu.

  * Audacity will no longer let you do unsafe editing operations
    while playing or recording.  This eliminates many potential
    crashes.

  * Fixed ability to cancel Quit button.

  * New resampling library, with no restrictions on the maximum or
    minimum rate of resampling.

  * Audacity now supports LADSPA plug-ins on all platforms, and
    supports VST plug-ins through an optional LADSPA plug-in
    called the "VST Enabler", which you can download separately.
    Because of licensing issues, Audacity cannot be distributed
    with VST support built-in.

  * Mac OS X keyboard shortcut problems have been fixed.

  * Mac OS X audio muting problems have been fixed.

  * Mac OS X playback/recording cursor sync problems have been fixed.

  * Silence now displays a straight line again, instead of nothing.

  * Added a vertical ruler to the Waveform dB display.

  * Fixed crash in Change Pitch.

  * You can now Paste if nothing is selected.

  * Canceling an Import operation doesn't cause an extra error
    dialog to appear.

  * Audacity now handles filenames with international characters
    correctly.

  * Now outputs ID3v2.3 tags (instead of ID3v2.4), to be
    compatible with more MP3 players.

  * Minor improvements to build system on Unix systems.


Noves caracter�stiques de l'Audacity 1.2.0-pre1:

  * Interf�cie de l'usuari
    - Ampliaci� vertical de les peces.
    - S'ha millorat l'aparen�a i localitzaci� de les barres d'eines.
    - M�s cursors del ratol�.
    - Implementaci� completa de dreceres de teclat editables.
    - Troba zero-crossings.
    - La roda del ratol� pot ser utilitzada per apropar i allunyar.
    - Mode multi eina.
    - Amplificador utilitzant un entorn.
    - Les etiquetes poden emmagatzemar seleccions (com ara l'Audacity 1.0.0).

  * Efectes
    - Capacitat d'ordenar la repetici� de l'�ltim efecte.
    - S'ha millorat la compatibilitat amb el peda� VST.
    - Molts efectes ara tenen un bot� de previsualitzaci�.
    - Compressor (Rang din�mic de compressi�).
    - Canvia el to (sense canviar el temps de comp�s).
    - Canvia el temps de comp�s (sense canviar el to).
    - Canvia la velocitat (canviant tant el temps com la velocitat).
    - Repeteix (�til per crear bucles).
    - Normalitza (ajusta el volum i DC bias).

  * �udio Entrada/Sortida
    - ordre de previsualitzaci� d'un segon.
    - Reproducci� en bucleLooped.

  * Fitxer Entrada/Sortida
    -L' Audacity 1.2.0 obre fitxers de projectes de totes les versions pr�vies
      de l'Audacity des de 0.98 fins a 1.1.3.
    - Obre m�ltiples fitxers des del mateix di�leg.
    - Utilitza un fitxer de text per especificar un llistat de fitxers d'�udio a obrir amb offsets.

  * S'ha actualitzat el manual d'usuari.


Errors fixats en l'Audacity 1.2.0-pre1

  * Els fitxers de projectes amb car�cters especials han deixat de ser
    inv�lids.

  * S'han fixat els sorolls de ratllades causats per mals truncaments .

  * L'Audacity ja no exporta fitxers Ogg inv�lids i no talla els �ltims
    pocs segons dels fitxers Ogg exportats.

  * Els fitxers MP3 Mono exporten a la velocitat correcta.

  * S'ha fixat diversos resultats incorrectes des de l'eina d'entorn.

  * L'ordre de "Exportar etiquetes" ara sobreescriu correctament els
    fitxers existents.
  
  * Ara es mostra correctament el n�mero correcte de l'octava de les notes.

  * S'ha fixat diverses p�rdues de mem�ria.

  * Molts altres petits erros fixats.
</pre>