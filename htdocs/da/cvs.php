<?php BoxTop("CVS"); ?>

Vi bruger <a href="http://www.cvshome.org">CVS</a>, Concurrent Versions
System, for at koordinere udviklingen af Audacity. Klik  <a href="http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/audacity/audacity-src/">her</a> for at kigge i kildeteksten direkte fra vores CVS server.

<p>
<h3>Bem�rk: Version 1.2 har nu sin egen gren:</h3>
For at f� den stabile udgave af Audacity version 1.2.x skal du nu skrive <tt>-r AUDACITY_1_2</tt> for at f� en CVS opdatering eller checkout.
Ellers f�r du CVS HEAD, som kan blive ganske ustabil, n�r vi begynder at arbejde p� version 1.3.0.

<p><h3>Hurtig start med Audacity CVS:</h3>
  Hvis du vil have fat i kildekoden til Audacity, kan du bruge en CVS klient
  til at hente en bestemt CVS-gren til din computer.
  N�r du en gang har hentet grenen, vil CVS klienten kunne holde
  din version synkron med de andre Audacity udvikleres.
  F�lg disse instruktioner for at f� kildeteksten.


<h4>Anonym CVS adgang med kommando-linje klient:</h4>
<p>Skriv f�lgende p� kommandolinjen (bem�rk at det er en lang linje uden linjeskift):<br>
<ul><tt>cvs -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity login </tt><br></ul>
og tryk Enter, n�r du bliver spurgt om en adgangskode.

<p>S�, <b>hvis du vil have den allerseneste udgave (1.3.0) skriver du </b> (p� en linje):
<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co audacity</tt></ul>
eller <b>for at f� den stabile udgave (1.2.0)</b> (p� en linje):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co -r AUDACITY_1_2 audacity</tt></ul>
eller, <b>for at f� den gamle 1.0 gren (1.0.0)</b> (p� en linje):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co -r audacity-0_9-branch audacity-old</tt></ul>

<p> Alternativ kan du s�tte <tt>CVSROOT</tt> environment
variablen til
<tt>:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt>
(se nedenfor).<br>
S� <b>kan du f� den seneste udviklingsudgave (1.3.0)</b> ved at indtaste<br> 
   <ul><tt>cvs checkout audacity</tt></ul>
Eller, <b>for at f� den stabile gren (1.2)</b>, skriv <br>
   <ul><tt>cvs checkout -r AUDACITY_1_2 audacity</tt></ul>
eller <b>for at f� den gamle 1.0 gren</b>, skriv <br>
   <ul><tt>cvs checkout -r audacity-0_9-branch audacity-old</tt></ul>

<p> For at s�tte environment variablen <tt>CVSROOT</tt>, kan du
bruge din shells resource fil, eller en af disse kommandoer:
<h5>I bash eller bourne shell, p� en linje:</h5>
<ul><tt>export
CVSROOT=:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt><br></ul>
<h5>I csh og dens efterf�lgere, p� en linje:</h5>
<ul><tt>setenv CVSROOT
:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt><br></ul>

<hr width="80%">

<h4>Anonym CVS adgang med en grafisk klient</h4>

For at bruge en grafisk klient som wincvs, maccvs, eller gcvs
(kan f�s her: <a href="http://cvsgui.org">cvsgui.org</a>), skal du s�tte
<tt>CVSROOT</tt> variablen (i Admin|Preferences undermenuen) til 
<tt>:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt>
og v�lge "pserver" eller "Password" autentikering. S�, p�
fanebladet "Globals" i Indstillinger-dialogboksen, skal du
sikre dig at punktet "Checkout read-only (CVSREAD)" ikke er markeret.
Dern�st v�lger du 'login', og taster Enter for adgangskoden (som er tom).
Endelig v�lger du "Create|Checkout module", v�lger en placering for 
den kode, du henter, og f�lger instruktionerne herunder, afh�ngig af,
hvilken udgave, du vil hente.
Hvis du f�r en fejlmelding, skal du sikre dig at din <tt>CVSROOT</tt>
variabel ikke har overfl�dige mellemrum efter bogstaverne - det kan ske fx hvis du kopierer indholdet fra denne side.

<p>
<b>For at f� den seneste ikke-stabile udgave (1.3.0):</b><br>
I dialogboksen "Checkout Settings" indtaster du 
<tt>audacity</tt> som modulnavn. Klik "OK", og denne gren bliver 
automatisk overf�rt til din computere.
<p>
<b>For at f� den stabile (1.2.0) gren: </b><br>
I dialogboksen "Checkout Settings" skriver du
<tt>audacity</tt> som modulnavnet. P� fanebladet 
"Sticky options" markerer du punktet "Retrieve rev./tag/branch
(-r)" og skriver <tt>AUDACITY_1_2</tt> i tekstfeltet ved siden af.
Klik p� "OK" og du vil f� denne gren overf�rt til din computer.

<p>
<b>For at f� den gamle udgave (1.0): </b><br>
I dialogboksen "Checkout Settings" indtaster du
<tt>audacity-old</tt> som modulnavn. S� indstiller du under
"Sticky options" fanebladet punktet "Retrieve rev./tag/branch
(-r)" og skriver <tt>audacity-0_9-branch</tt> i boksen ved siden af
Klik "OK", og denne gren bliver nu overf�rt til din computer.

<hr width="80%">
CVS-begynder?  Du f�r en god introduktion ved at l�se Jim Blandy's <a href="">Introduction
to CVS</a>, Bob Arnson's <a
href="http://www.cvshome.org/new_users.html">CVS for new
users</a>, eller bes�g CVS hjemmesiden p� <a
href="http://www.cvshome.org/">www.cvshome.org</a>.
Du kan finde flere detaljer p� de GPL-licenserede kapitler i Karl
Fogel's <a href="http://cvsbook.red-bean.com/cvsbook.html">CVS Book
p� cvsbook.red-bean.com</a>, eller den "officielle" <a
href="http://www.cvshome.org/docs/manual">Per
 Cederqvist manual</a>.


<p> S�ger du specifik hj�lp omkring CVS p� SourceForge, kan du pr�ve SourceForge dcokumentationen p�
<a
href="http://sourceforge.net/docman/display_doc.php?docid=763&group_id=1">Unix</a>,
<a
href="http://sourceforge.net/docman/display_doc.php?docid=766&group_id=1">Microsoft Windows</a>, og <a
href="http://sourceforge.net/docman/display_doc.php?docid=2973&group_id=1">MacOS
(f�r OS X)</a> platforme.

<hr width="80%">

<p>
<b>Om biblioteker:</b>

</p>

<p>Audacity bruger mange tredjepartsbiblioteker. En del af dem skal tilpasses
lidt for at kunne bruges p� alle de operativsystemer, Audacity k�rer p�. Derfor
har vi en lokal kopi af alle tredjepartsbiblioteker i vort eget CVS-tr�. Det
fungerer s�dan:
</p>
<p>Der er to kodepuljer: 'audacity-src', som rummer al den kode, vi selv har
skrevet, og 'lib-src', som rummer kildeteksten til alle de biblioteker, vi 
bruger.
For at garantere at Audacity og bibliotekerne fungerer sammen, anbefaler vi,
at du bruger de versioner af bibliotekerne, der findes i 'lib-src'. 
P� den anden side kan du undg� at compilere nogle af de biblioteker, du
allerede har i din computer.
Skriv 'configure --help' for at se de mulige indstilliger.
</p>
<p>
S� hvis du vil hente alting, inklusive kildekoden til bibliotekerne, 
skal du hente modulet 'audacity' (via CVS), som vil overf�re b�de 
audacity-src og lib-src kodepuljerne som en undermappe under 'audacity'.
</td>
</tr>
</table>
</p>

<?php BoxBottom(); ?>
