<h2>Canvis a l'Audacity 1.2</h2>

Principals canvis des de l'anterior versi� estble, Audacity 1.0.0:

<h3>�udio de qualitat professional</h3>

<ul>
<li>
L'Audacity pot ara enregistrar i eitar mostres de 24 bits i 32 bits (coma flotant).  
En un mateix projecte poden coexisitr pistes amb diferents freq��ncies i formats, i l'Audacity 
les convertir� n temps real quan sigui necessari.  En totes les conversions es fan servir t�cniques 
d'arrodoniment d'alta qualitat.
</li>

<li>
L'entrada i sortida de so de l'Audacity han estat millorades.  L'Audacity pot ara enregistrar m�s de 
dos canals alhora. L'�s de mem�ria cau ha estat millorat, per reduir les possibilitats de trobar-se 
amb situacions de desbordament de mem�ria.
</li>
</ul>

<a href="screenshots.php<?php print $langQueryStr; ?>">
<img alt="screenshots" border="0" src="images/screen/linux/change-pitch.png" align="right"></a>
<h3>Effects</h3>

<ul>
<li>
Tres nous efectes que poden canviar el to i el tempo d'una pista:
 <ul>
  <li><b>Canvia el to</b> puja o baixa el to del fragment seleccionat, sense que es vegi afectada la velocitat.</li>
  <li><b>Canvia el temps</b> fa que el fragment seleccionat s'escolti m�s de pressa o m�s poc a poc, sense modificar-ne el to.</li>
  <li><b>Canvia la velocitat</b> afecta tant la velocitat de reproducci� com el to, tal com passa si canvieu la velocitat de gir d'un tocadiscs.</li>
 </ul>
</li>

<li>
La major part d'efectes inclouen un bot� de vista preliminar, que us permet provar 
diferents configuracions sense tancar la finestra d'efectes.  Una nova funci� us permet 
repetir el darrer efecte sense haver de tornar a obrir la finestra.
</li>

<li>
Altres efectes inclouen:
 <ul>
  <li>Compresor, per compressi� de rang din�mic.</li>
  <li>Repeteix, per escoltar les mostres en cicle.</li>
  <li>Normalitza, per ajustar el volum i corregir la desviaci� del punt central de l'ona.</li>
 </ul>
</li>
</ul>


<h3>Noves funcionalitats d'edici�</h3>

<ul>
<li>
L'eina d'envolupant, emprada per produir f�dings d'inici i final, es pot fer servir ara tamb� 
per a pujar o baixar el volum global de les pistes.
</li>

<li>
La nova funcionalitat "Pista de temps" �s similar a l'envolupant de volum, per� en lloc de canviar la 
intensitat del so srveix per a produir canvis progressius en la velocitat d'interpretaci� de la pista.
</li>

<li>
Cada pista t� ara els seus propis controls de guany i panor�mica, per facilitar les mescles.
<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/linux/track-controls.png" align="right"></a>
</li>

<li>
L'Audacity pot trobar punts de creuament amb el zero, per ajudar a crear talls i bucles suaus.
Premeu "Z" per moure els l�mits de la selecci� als punts de creuament amb el zero m�s propers.
</li>
</ul>


<h3>Endollats</h3>

<ul>
<li>
En Linux, l'Audacity pot carregar ara endollats <a href="http://www.ladspa.org/">LADSPA</a>.
</li>

<li>
L'Audacity 1.2 ofereix un llenguatge de proc�s de senyals digitals anomenat 
<a href="nyquist.php">Nyquist</a>, que permet als usuaris programar nous efectes 
en un llenguatge similar al LISP.
</li>
</ul>


<h3>Importaci� i exportaci� de fitxers</h3>

<ul>
<li>
Els fitxers de projecte de l'Audacity 1.2 fan servir un nou format XML.  L'Audacity 1.2 
obrir� i convertir� autom�ticament els fitxers de projecte de versions anteriors.
</li>

<li>
L'Audacity 1.2 fa servir la biblioteca <a href="http://www.underbit.com/products/mad/">libmad</a>
per a una descompressi� r�pida dels fitxers MP3.  La biblioteca <a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a>,
 d'Erik de Castro Lopo, ofereix una compatibilitat millorada amb la majoria de formats de fitxers d'�udio no comprimit.
</li>

<li>
Les finestres de di�leg d'importar i obrir permeten ara als usuaris de l'Audacity seleccionar 
diversos fitxers cada vegada, i obrir-los users junts en un mateix projecte.  
Un nou format de fitxer "LOF" permet a l'Audacity obrir grups de fitxers, fins i tot indicant punts de despla�ament (offsets), 
mitjan�ant una llista escrita en un fitxer de text.
</li>
</ul>


<h3>Interf�cie d'usuari millorada</h3>

<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/macosx/main-toolbar.png" align="right"></a>
<ul>
<li>
Noves barres d'edici� i mesclador, per un acc�s m�s r�pid a les funcions m�s comunes.
</li>

<li>
La nova eina de dibuix permet ajustar les mostres una per una, quan s'est� en la modalitat de zoom total. 
La nova eina d'usos m�ltiples ofereix un acc�s r�pid a diverses funcionalitats d'edici� sense que calgui 
canviar d'eina.
</li>

<li>
S'hn afegit moltes drecres de teclat, que poden ser personalitzades.
</li>

<li>
Noves funcions:
 <ul>
  <li>Interpretaci� en bucle.  Premeu "L", o mantingueu premuda la tecla de maj�scules mentre feu clic a "Interpreta".</li>
  <li>Premeu "1" per escoltar un fragment d'un segon de durada de l'�udio que hi ha al voltant del cursor.</li>
 </ul>
</li>

<li>
La roda del ratol� es pot fer servir per a fer zoom cap a dins i cap a fora.
</li>

<li>
Les pistes es poden augmentar verticalment fent clic o arrossegant les barres verticals. Feu maj�scules-clic 
o clic amb el bot� dret per fer zoom enrere.  
</li>

<li>
La barra d'estat pot mostrar ara el temps en diversos formats, incloent 
segons, mostres o fotogrames de v�deo.
</li>

<li>
L'interf�cie de l'Audacity es pot traduir ara a idiomes diferents de l'angl�s.  Podeu fer-vos voluntaris 
per ajudar a <a href="translation/">traduir l'Audacity</a> al vostre idioma.
</li>
</ul>
