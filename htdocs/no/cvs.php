<?php BoxTop("CVS"); ?>

Vi bruker <a href="http://www.cvshome.org">CVS</a>, Concurrent Versions
System ("samtidig versjonssystem"), for � hjelpe oss med � utvikle
Audacity i samarbeid. Klikk
<a
href="http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/audacity/audacity-src/"
>her</a> for � lese gjennom kildekoden i v�r CVS-pakke.

<p>
<h3>Noter: Versjon 1.2 er n� forgreinet:</h3>
Hvis du vil ha den stabile greinen av Audacity, versjon 1.2.x, s� m� du
skrive <tt>-r AUDACITY_1_2</tt> n�r du gj�r en cvs-oppdatering eller utsjekking.
Hvis ikke vil du f� CVS HEAD, som kan bli ganske ustabilt n� som vi starter 
arbeidet p� versjon 1.3.0.

<p><h3>Rask Audacity CVS Howto:</h3>
  Hvis du vil ha tilgang til Audacity sin kildekode kan du 
  bruke en cvs-klient til � laste ned en cvs-forgreining
  p� maskinen din. N�r du har sjekket ut en grein en gang,
  vil din CVS-klientprogramvare f� muligheten til � holde din
  versjon oppdatert med de andre Audacity-utviklerne. F�lg
  instruksjonene nedenfor for � f� tak i kildekoden.
  


<h4>Anonym CVS-tilgang med en kommandolinjebasert cvs-klient:</h4>
<p>Skriv inn det f�lgende p� kommandolinjen (noter at det er en enkel
linje uten linjeskift):<br>
<ul><tt>cvs -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity
login </tt><br></ul>
og klikk enter-knappen n�r den sp�r deg for et passord.

<p>S�, <b>for � f� den seneste banebrytende koden (1.3.0)</b> (p� �n enkel linje):
<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity co
audacity</tt></ul>
eller <b>for den stabile greinen (1.2.0)</b> (p� �n enkel linje):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity co -r AUDACITY_1_2 audacity</tt></ul>
eller <b>for den gamle 1.0-greinen (1.0.0)</b> (p� �n enkel linje):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity co -r audacity-0_9-branch audacity-old</tt></ul>

<p> Alternativt kan du sette <tt>CVSROOT</tt> milj�variabelen din til 
<tt>:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity</tt>
(se nedenfor).<br>
S�, <b>for � f� den seneste ustabile greinen (1.3.0)</b>, skriv<br> 
   <ul><tt>cvs checkout audacity</tt></ul>
eller, <b>for den stabile greinen (1.2)</b>, skriv<br>
   <ul><tt>cvs checkout -r AUDACITY_1_2 audacity</tt></ul>
eller <b>for den gamle 1.0-greinen</b>, skriv<br>
   <ul><tt>cvs checkout -r audacity-0_9-branch audacity-old</tt></ul>

<p> For � sette <tt>CVSROOT</tt> milj�variabelen kan du bruke
kommandoskallet ditt sin ressursfil, eller en av de f�lgende
kommandoene:
<h5>I et bash eller bourne skall, p� �n linje:</h5>
<ul><tt>export
CVSROOT=:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity</tt><br></ul>
<h5>I csh eller dets etterf�lgere, p� �n linje:</h5>
<ul><tt>setenv CVSROOT
:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity</tt><br></ul>

<hr width="80%">

<h4>Anonym CVS-tilgang med en grafisk klient</h4>

For a en grafisk klient som wincvs, maccvs eller gcvs,
(tilgjengelig p� <a href="http://www.wincvs.org">wincvs.org</a>) m� du stille inn
<tt>CVSROOT</tt> variabelen (i undermenyen Admin|Preferences) til
<tt>:pserver:anonymous@cvs.sourceforge.net:/cvsroot/audacity</tt>
og velge "pserver" eller "Password" som autentisering. S�, under
Globals-menyen i Preferences-dialogen, sjekk at du ikke har valgt 
"Checkout read-only (CVSREAD)".  Etterp�, velg login, og trykk
retur-knappen for passordet (det er ""). Til sist, velg 
"Create|Checkout module", velg stedet hvor du vil legge den 
utsjekkede greinen, og f�lg instruksjonene nedenfor, basert
p� hvilken grein du vil ha.
Hvis du f�r en feil, sjekk at <tt>CVSROOT</tt>-variabelen din ikke
inneholder noen mellomrom/linjeskift ("white space") p� slutten--noe 
som kan skje hvis du har kopiert variablene direkte fra denne nettsiden.

<p>
<b>For � f� den seneste ustabile greinen (1.3.0):</b><br>
Under "Checkout Settings" dialogen, skriv
<tt>audacity</tt> som modulnavn. Trykk "OK" og greinen vil 
automatisk bli lastet ned p� maskinen din.
<p>
<b>For � f� den stabile (1.2.0) greinen: </b><br>
Under "Checkout Settings" dialogen, skriv
<tt>audacity</tt> som modulnavn. S�, under
"Sticky options"-menyen, velg boksen "Retrieve rev./tag/branch
(-r)" og skriv <tt>AUDACITY_1_2</tt> i boksen ved siden
av den. Trykk "OK" og greinen vil 
automatisk bli lastet ned p� maskinen din.
<p>
<b>For � f� den gamle greinen, versjon 1.0: </b><br>
Under "Checkout Settings" dialogen, skriv
<tt>audacity-old</tt> som modulnavn. S�, under
"Sticky options"-menyen, velg boksen "Retrieve rev./tag/branch
(-r)" og skriv <tt>audacity-0_9-branch</tt> i boksen ved siden
av den. Trykk "OK" og greinen vil 
automatisk bli lastet ned p� maskinen din.

<hr width="80%">
Er CVS nytt for deg? Kom i gang ved � lese Jim Blandys <a href="">Introduction
to
CVS</a>, Bob Arnsons <a
href="http://www.cvshome.org/new_users.html">CVS for new
users</a>, eller bes�k cvs-nettstedet p� <a
href="http://www.cvshome.org/">www.cvshome.org</a>.
Mer detaljert informasjon er tilgjengelig i de GPL-publiserte
kapitlene av Karl Fogel's
<a href="http://cvsbook.red-bean.com/cvsbook.html">CVS Book
p� cvsbook.red-bean.com</a>, eller den "Offisielle" <a
href="http://www.cvshome.org/docs/manual">Per
 Cederqvist manualen</a>.


<p> For spesifikk hjelp med CVS p� sourceforge.net, pr�v 
sourceforge-dokumentasjonen for platformene 
<a
href="http://sourceforge.net/docman/display_doc.php?docid=763&group_id=1">Unix</a>,
<a
href="http://sourceforge.net/docman/display_doc.php?docid=766&group_id=1">Microsoft Windows</a>, og <a
href="http://sourceforge.net/docman/display_doc.php?docid=2973&group_id=1">MacOS
(tidligere enn OS X)</a>.

<hr width="80%">

<p>
<b>Flere detaljer:</b>

</p>

<p>Audacity bruker mange bibliotek fra tredjeparter. Mange av dem
krever litt finjustering for � kompilere p� alle plattformene som vi har som m�l. 
Derfor har vi en lokal pakke for kildekoden til alle v�re 
tredjepartsbibliotek i CVS. Det fungerer slik: 
</p>
<p>Det er to pakker: 'audacity-src', som inneholder all 
koden vi har skrevet, og
'lib-src,' som inneholder kildekoden til alle bibliotekene vi bruker. 
For � garantere at Audacity og bibliotekene v�re er interoperasjonelle 
anbefaler vi at du bruker de versjonene av bibliotekene som er inneholdt 
i 'lib-src'. Men, p� et Unix-system kan du unng� � kompilere noen av 
bibliotekene ved � bruke biblioteker som du allerede har p� systemet ditt.
Skriv 'configure --help' for � se valgene.
</p>
<p>
S�, om du har lyst til � sjekke ut alt, inkludert kildekoden til bibliotekene,
sjekk ut modulen 'audacity' som vil sjekke ut audacity-src men ogs� ta med
lib-src pakken som en underkatalog av 'audacity'.
</td>
</tr>
</table>
</p>

<?php BoxBottom(); ?>

