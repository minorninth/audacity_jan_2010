<h2>Forandringer i Audacity 1.2</h2>

St�rre forandringer siden v�r forrige stabile utgave, Audacity 1.0.0:

<h3>Lyd med profesjonell kvalitet</h3>

<ul>
<li>
Audacity kan n� ta opp og redigere 24-bits og 32-bits (flyttall)
datapunkt. Samme prosjekt kan ha spor med forskjellige datapunktrater, og 
Audacity vil konvertere dem i sanntid n�r enn det er n�dvendig. 
Dithering og omsampling med h�y kvalitet blir brukt for alle konverteringer.
</li>

<li>
Audacitys innlyd og utlyd er bedret. Audacity kan n� ta opp flere enn to 
kanaler samtidig. Buffering er forbedret, for � redusere sjansen for at
sporet hakker eller at bufferen g�r tom.
</li>
</ul>

<a href="screenshots.php<?php print $langQueryStr; ?>">
<img alt="screenshots" border="0" src="images/screen/linux/change-pitch.png" align="right"></a>
<h3>Effekter</h3>

<ul>
<li>
Tre nye effekter kan n� forandre toneh�yde og tempo p� et spor:
 <ul>
  <li>Forandre toneh�yde gj�r tonen p� et utvalg h�yere eller lavere,
  uten � forandre hastighet.</li>
  <li>Forandre tempo gj�r at utvalget spiller raskere eller saktere, 
  uten � forandre toneh�yde.</li>
  <li>Forandre hastighet forandrer b�de avspillingshastighet og toneh�yde,
  akkurat som n�r du forandrer hastighet p� en plate- eller kassettspiller.</li>
 </ul>
</li>

<li>
De fleste effekter vil n� ha en "Forh�ndsvisning"-knapp, som lar deg pr�ve 
ut forskjellige instillinger uten � lukke effektvinduet. En ny kommando lar
deg repetere den sist brukte effekten uten � gjen�pne vinduet.
</li>

<li>
Andre nye effekter er bl.a.:
 <ul>
  <li>Komprimering, for dynamisk omr�dekomprimering.</li>
  <li>Repeter, for � spille markeringer i l�kke.</li>
  <li>Normaliser, for � justere volum og rette "DC-bias".</li>
 </ul>
</li>
</ul>


<h3>Nye redigeringsfunksjoner</h3>

<ul>
<li>
Omhyllingsverkt�yet, brukt for � jevnt tone inn og ut et spor, kan n� bli 
brukt til � gi spor h�yere volum enn det de originalt hadde deres, i 
tillegg til lavere volum. 
</li>

<li>
Den nye "Tidsspor"-funksjonen ligner p� volumomhyllingskurven, men
isteden forandrer den jevnt avspillingshastighet mens et spor spiller.
</li>

<li>
Hvert spor har n� sine eget Forsterknings- og Panoreringskontroller,
for enklere miksing. 
<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/linux/track-controls.png" align="right"></a>
</li>

<li>
Audacity can finne nullpunkt, for � hjelpe til med � lage jevne kutt
og l�kker. Tast "Z" for � flytte markeringskanten til n�rmeste 
nullpunkt.
</li>
</ul>


<h3>Programtillegg</h3>

<ul>
<li>
P� Linux kan Audacity n� laste inn programtillegg av typen <a href="http://www.ladspa.org/">LADSPA</a>.
</li>

<li>
Audacity 1.2 bruker et digitalt signalbehandlingsspr�k kalt
<a href="nyquist.php">Nyquist</a>, som lar brukere programmere nye 
effekter i et LISP-liknende spr�k.
</li>
</ul>


<h3>Filimportering og -eksportering</h3>

<ul>
<li>
Audacity 1.2 sine prosjektfiler bruker et nytt XML-filformat. 
Audacity 1.2 vil automatisk �pne og konvertere prosjektfiler 
fra tidligere utgaver.
</li>

<li>
Audacity 1.2 bruker <a href="http://www.underbit.com/products/mad/">libmad</a>
for mye raskere dekoding av MP3-filer. Erik de Castro Lopo sin
<a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> gir 
bedret samspill med mange ukomprimerte lydfilformat.
</li>

<li>
Import- og �pne-dialogene vil n� la Audacity-brukere velge mellom flere
lydfiler p� en gang og �pne dem inn i ett enkelt prosjekt. Et nytt 
"LOF"-filformat gir en m�te for Audacity � �pne en gruppe filer
som har forskyvninger gitt p� en liste i en tekstfil.
</li>
</ul>


<h3>Forbredet brukergrensesnitt</h3>

<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/macosx/main-toolbar.png" align="right"></a>
<ul>
<li>
Nye Rediger- og Mikserverkt�y for hurtig tilgang til vanlige funksjoner.
</li>

<li>
Det nye Tegneverkt�yet tillater justering av individuelle datapunkt, n�r 
du har zoomet inn fullstendig. Den nye Multi-verkt�y-modusen gir hurtig 
tilgang til forskjellige redigeringsfunksjoner, uten at du trenger � bytte
verkt�y.
</li>

<li>
Mange nye tastaturkommandoer er lagt til og mange tastatursnarveier kan
n� skreddersys.
</li>

<li>
Nye kommandoer:
 <ul>
  <li>Spill av i l�kke. Tast "L" eller hold nede skift-knappen n�r du trykker Spill av.</li>
  <li>Tast "1" for � spille en 1-sekund lang forh�ndsvisning av lyden rundt mark�ren.</li>
 </ul>
</li>

<li>
Musehjulet kan n� brukes for � zoome inn og ut.
</li>

<li>
Du kan n� zoome vertikalt p� spor ved � klikke eller dra i de vertikale
linjalene. Skift-klikk eller h�yreklikk for � zoome ut.
</li>

<li>
Linjalen og statuslinja kan n� vise tiden i flere forskjellige format,
inkludert sekunder, datapunkt eller videorammer ("frames").
</li>

<li>
Audacitys brukergrensesnitt kan n� oversettes til andre spr�k enn engelsk.
Du kan hjelpe til med � <a href="translation/">oversette Audacity</a> 
til ditt eget morsm�l.
</li>
</ul>

