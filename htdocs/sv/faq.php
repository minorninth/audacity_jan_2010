<?php BoxTop("Frequently Asked Questions - Vanliga st�llda fr�gor"); ?>

<!--
<table width=100% cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+3">Vanliga st�llda fr�gor</font>
</td></tr></table>
-->

<p>

General:<br>
<a href="#g1">�r Audacity verkligen gratis? Varf�r?</a><br>
<a href="#g2">Vem utvecklar Audacity?</a><br>
<a href="#g3">Hur kan jag hj�lpa till med att f�rb�ttra Audacity?</a><br>
<a href="#g4">Jag har hittat en bug! Vad g�r jag nu?</a><br>

<p>

Installation:<br>

<a href="#i1">Windows: Vad g�r jag med .exe filen?</a><br>
<a href="#i2">Windows: Hur avinstallerar jag Audacity?</a><br>
<a href="#i3">Mac: Vad g�r jag med .sit filen?</a><br>
<a href="#i4">Unix: Varf�r f�r jag "failed dependencies" n�r jag installerar via RPM?</a><br>
<a href="#i5">Unix: Varf�r f�r jag ett felmeddelande n�r den laddar libwx_gtk.so?</a><br>

<p>

Anv�nda Audacity:<br>

<a href="#a1">Hur l�gger jag ihop tv� sp�r?</a><br>
<a href="#a2">Kan jag ta bort s�ngen fr�n en inspelning?</a><br>

<a href="#a3">N�r jag f�rs�ker spela in st�mmor med mig sj�lv,
varf�r �r de tv� sp�ren inte synkroniserade?</a><br>
<a href="#a4">Varf�r �r ingen MP3-kodare inkluderad?</a><br>
<a href="#a5">Kan jag spela in RealAudio eller eller annat str�mmande ljud?</a><br>
<a href="#a6">Hj�lp! Jag har tryckt "spela in" men allt jag f�r �r tystnad!</a><br>
<a href="#a7">Hur delar jag upp en fil i flera sp�r?</a><br>
<a href="#a8">Hur kan jag f� l�tar fr�n en ljud-CD?</a><br>

<p>

<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Allm�nt</font>
</td></tr></table>

<p>

<a name="g1"></a>
<font size=+1><b>
1. �r Audacity verkligen gratis? Varf�r?<br>

</b></font>

<p>

Ja,  Audacity �r inte bara distribuerad
utan kostnad, men du har ocks� m�jligheten att g�ra n�stan
vad du vill med det.
<p>
Audacity �r distribuerad under termerna f�r
<a href="http://www.gnu.org/copyleft/gpl.html"
>General Public License (GPL)</a>.
Du har friheten att anv�nda denna programvara f�r personligt eller kommersiellt
�ndam�l.  Du har ocks� friheten att fritt dela med dig av programmet eller s�lja det.
K�llkoden till detta program �r fritt tillg�nglig p�
Internet, och du har friheten att �ndra det f�r eget bruk, men
�ndringar m�ste ocks� bli distribuerade under GPL.
<p>
Audacity �r byggt med hj�lp av wxWidgets, ett mjukvarubibliotek som
�r utgiven under den mindre restriktiva LGPL.  
F�r mer information, g� till
<a href="http://wxwidgets.org/">wxwidgets.org</a>.
<p>
Utvecklarna av Audacity har valt att ge ut den under GPL
av m�nga anledningar.  M�nga av oss g�r det f�r att vara gener�sa.
N�gra g�r det f�r moralen, d�rf�r att vi tycker att
all mjukvara  borde vara gratis, medans andra tror att
det finns ett behov av b�de gratis och kommersiell mjukvara i v�rlden.
<p>
En anledning till att Audacity �r gratis �r att den blir mer allm�nt f�rekommande.
M�nga av oss skulle hellre se en miljon glada m�nniskor anv�nda
Audacity gratis �n tusen m�nniskor som betalar. De flera blir mer n�jda med programmet om det �r gratis.

<p>
�nnu en anledning �r att det fr�mjar samarbete. Om Audacity
var shareware, skulle det inte vara troligt att dussintals m�nniskor i
v�rlden skulle ha bidragit med kod, bugg-fixar, dokumentation,
och grafik.

<p>
<a name="g2"></a>
<font size=+1><b>
2. Vem utvecklar Audacity?<br>
</b></font>

<p>

Audacity-projektet startades h�sten 1999
av Dominic Mazzoni medan han var student vid Carnegie Mellon Universitet i Pittsburgh, PA, USA.
Han arbetade p� ett forskningsprojekt med hans handledare, Professor
Roger Dannenberg, och dom beh�vde ett verktyg som gav dem m�jligheten att
visualisera ljud-analysalgorithmer.  Tiden gick, och detta program
utvecklades till ett generellt ljudredigeringsprogram, och andra m�nniskor b�rjade
hj�lpa till.
<p>
Idag �r Audacity utvecklat med anv�ndandet av Sourceforge, en hemsida
som till�ter m�nniskor fr�n hela v�rlden att samarbeta med gratis
mjukvaru projekt.  Se <a href="http://www.sourceforge.net"
>sourceforge.net</a> f�r mer information.
Dussintals m�nniskor har bidragit till
Audacity, och utvecklingen forts�tter att accelerera.

<p>

<a name="g3"></a>
<font size=+1><b>
3. Hur kan jag hj�lpa till med att f�rb�ttra Audacity?<br>
</b></font>

Leta r�tt p� buggar och meddela oss.
Skriv kod.  �vers�tta det till ditt eget spr�k. Rita grafik.
Bli medlem i Audacityqnv�ndarnas postlista. Skicka pengar till oss.
<p>
Var v�nlig se v�r nya <?php print "<a href=donatetime.php?$langLinkStr>"; ?>Bidra med pengar</a> 
f�r mer detaljer om hur du kan hj�lpa till.
<p>

<a name="g4"></a>
<font size=+1><b>
4. Jag har hittat en bug! Vad g�r jag nu?<br>
</b></font>
<p>

Det viktigaste n�r du rapporterar en bugg �r att vara
s� specifik som som m�jligt.  Ge oss tillr�ckligt med information s�
vi kan �terskapa buggen sj�lva, annars �r det inte troligt
att vi kan fixa det. Skicka buggrapporter till
<a href="mailto:audacity-help@lists.sourceforge.net">
<audacity-help@lists.sourceforge.net></a>.
<br><font size=-1><?php print "$listPrivacyStr"; ?></font>
<p>
Kom ih�g att tala om vilket operativ system du k�r
(som Windows 98, MacOS 9.1, RedHat Linux 7.1, etc.)
och all annan information om din dator som du
tycker �r relevant.
<p>
Sen, kan du �terskapa buggen? Om det h�nder konstant,
ber�tta den exakta sekvensen av h�ndelser som orsakar buggen.
Om du f�r ett felmeddelande, se till att skicka med
den exakta texten av felmeddelandet.
<p>

Vi vill bli av med alla buggar!  Tack f�r att du hj�lper oss att finna dem.

<p>
<br>
<p>

<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Installation</font>
</td></tr></table>

<p>
<a name="i1"></a>
<font size=+1><b>
1. Windows: Vad g�r jag med .exe filen?<br>
</b></font>

<p>Fr�n Internet Explorer, v�lj att k�ra filen.
Detta startar Audacitys installationsprogram, som kommer att installera
Audacityprogrammets filer och skapa en genv�g fr�n Startmenyn.
<p>
Om du redan har laddat ner filen, dubbelklicka p� den f�r att starta installationen.
<p>
Om du f�redrar att inte anv�nda installationsprogrammet, kan du ocks�
ladda ner Audacity i form av en zip-fil, vilken du kan packa upp 
med hj�lp av WinZip.

<p>
<a name="i2"></a>
<font size=+1><b>
2. Windows: Hur avinstallerar jag Audacity?<br>
</b></font>

<p><font size=+0>Audacity kan avinstalleras genom att �ppna 
L�gga Till/Ta bort Program i
kontrollpanelen.  V�lj "Audacity" fr�n listan och
klicka p� knappen
"L�gg till/Ta bort".
Detta startar Audacitys avinstallationsprogram.

<p>
<a name="i3"></a> <font size=+1><b> 3. Mac: Vad g�r jag med .sit filen?<br> </b></font>

<p>
Du beh�ver en f�rsk version av StuffIt Expander, StuffIt Expander
kommer med alla Macintoshar och �r oftast konfigurerad 
med alla Mac-webbl�sare.  Om Audacity inte packar upp 
automatiskt, dra "audacity.sit" till StuffIt Expander f�r att packa upp 
filen.
<p>
Det finns inget behov att installera Audacity. Bara dra Audacity
mappen till din Applications mapp, eller vart du vill ha den.
F�r att avinstallera, bara dra mappen till soptunnan.

<p>
<a name="i4"></a>
<font size=+1><b>
4. Unix: Varf�r f�r jag "failed dependencies" n�r jag installerar via RPM?
<br></b></font>

<p><font size=+0>F�rst, se till att wxGTK �r installerat; en l�nk finns
p� v�r Linux sida - http://audacity.sourceforge.net/linux.html. Om Rpm:en
fortfarande inte installeras, �r detta en ol�st bisak.  Installera bara RPM:en
med flaggan --nodeps.</font>

<p>
<a name="i5"></a>
<font size=+1><b>

5. Unix: Varf�r f�r jag ett felmeddelande n�r den laddar libwx_gtk.so?<br></b></font>

<p><font size=+0>Detta kan vara p� grund av tv� problem:
<br>- Om du installerade wxWindows via RPM, se till att k�ra "ldconfig" /som root) s� att ditt system kan k�nna igen det nya biblioteket.

<br><br>- Om du installerade wxWidgets
med k�llkod, kan det ha blivit installerat i /usr/local, men /usr/local/lib/ kanske
inte finns i din biblioteks s�kv�g. L�gg till /usr/local/lib i filen "/etc/ld.so.conf"
och k�r sen "ldconfig". Du kanske coks� vill l�gga till "usr/local/bin" till s�kv�gen s� att program kan hitta "wx-config" verktyget.<br>

<p>
<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Anv�nda Audacity</font>
</td></tr></table>

<p>
<a name="a1"></a>
<font size=+1><b>

1. Hur l�gger jag ihop tv� sp�r?
</b></font>
<p>

Audacity l�gger ihop sp�ren automatiskt.  Allt du beh�ver g�ra �r att
importera tv� sp�r till samma projekt, vilket du kan
g�ra genom att klicka p� "Importera ljudfil" i Projektmenyn, 
eller helt enkelt att dra de tv� ljudfilerna till 
Audacity. N�r du trycker p� spela-in knappen, skapar
Audacity ett nytt sp�r automatiskt.

<p>

F�r att spara din blandning, kan du antingen Exportera projekt,
vilket automatiskt blandar alla dina sp�r tillsammans, eller
s� kan du v�lja sp�r och anv�nda "Snabbmix" fr�n Projektmenyn.

<p>
<a name="a2"></a>
<font size=+1><b>
2. Kan jag ta bort s�ngen fr�n en inspelning?
</b></font>
<p>

Med vissa stereoinspelningar, �r det m�jligt att ta bort s�ngen
p� grund av s�ttet inspelningen var mixad vid studion.
Oftast �r s�ngen placerad exakt i mitten av inspelningen,
medan alla andra instrument �r utanf�r. Om du
tar bort h�ger-kanalen fr�n v�nster-kanalen, blir s�ngen 
helt utel�mnad, och kvar blir bara instrumenten.
<p>

<b>Detta fungerar bara med vissa inspelingar!</b>
<p>
F�r att uppn� detta i Audacity, importera en stereoinspelning, klicka sedan p� sp�rets pop-up meny (den lilla ned�t-pilen bredvid sp�rets namn) och v�lj "Dela stereosp�r".
V�lj nu det nedersta sp�ret (den h�gra kanalen) och anv�nd
"Invertera" effekten (fr�n Effektmenyn).  Slutligen, anv�nd
sp�rens pop-up menyer f�r att g�ra b�da kanalerna monokanaler,
och mixa dom tillsammans med hj�lp av Snabbmix. Om du har tur
kommer st�mmorna att vara borta.

<p>
<a name="a3"></a>
<font size=+1><b>
3. N�r jag f�rs�ker spela in st�mmor med mig sj�lv,
varf�r �r de tv� sp�ren inte synkroniserade?
</b></font>
<p>
Detta �r normalt och det h�nder d�rf�r att det �r en liten f�rdr�jning
mellan det att Audacity b�rjar spela upp ljud och n�r det
kommer fram till h�gtalarna. Audacity f�rs�ker inte automatiskt
korrigera denna f�rdr�jning, utan du m�ste g�ra det manuellt.
<p>
F�r att korrigera denna f�rdr�jning, anv�nd
Time Shift verktyget f�r att flytta
en av sp�ren tills dom �r synkroniserade. Kom ih�g att du kan
anv�nda verktyget medan du lyssnar p� inspelningen.

<p>

<a name="a4"></a>
<font size=+1><b>
4. Varf�r �r ingen MP3-kodare inkluderad?
</b></font>
<p>

Oturligt nog, s� �r algoritmen f�r kodning eller skapande av MP3 filer
patenterad, och <b>Audacity</b> skulle inte kunna
inkludera en MP3 export-algoritm utan att antingen
ta betalt eller inkr�kta p� lagarna i m�nga l�nder.
<p>
Som en kompromiss, kommer Audacity med m�jligheten att anv�nda
andra MP3-kodare, vilka du m�ste ladda ner separat.
Det �r upp till dig att se till att du �r noga med att f�lja restriktionerna f�r MP3-kodare.
<p>
F�r mer information, se sidan om Exportering av MP3 filer
i v�ran Online Hj�lp.

<p>



<a name="a5"></a>
<font size=+1><b>
5. Kan jag spela in RealAudio eller eller annat str�mmande ljud?
</b></font>
</p><p>

Inte automatiskt.  Flertaler str�mmande ljud, med musik utgiven till
RealOne Player, Windows Media Player, och Quicktime, �r uttryckligen
avsett f�r att du inte ska kunna spela in det.
</p><p>
Det �r �nd� n�stan alltid m�jligt att spela in allting som din dator
kan spela genom att koppla din ljudutg�ng till din ljuding�ng/mikrofonuttag
p� din dators ljudkort.
</p><p>
Anv�nd en 1/8 tum stereo mini till 1/8 tum stereo minikabel.  Koppla en �nda
till ljudutg�ngen p� din dator eller ljudkort (d�r du
kopplar in h�gtalare eller h�rlurar - den �r oftast f�rgad gr�n).  Koppla in den andra �nden i mikrofonuttaget eller ljuding�ngen (oftast f�rgad r�d).
</p><p>
Nu kan Audacity spela in allt som datorn spelar upp. Tryck Inspelning
i Audacity, och sen tryck Spela i programmet som spelar upp ditt streamande ljud.
</p><p>

<a name="a6"></a>
<font size=+1><b>
6. Hj�lp! Jag har tryckt "spela in" men allt jag f�r �r tystnad!
</b></font>
</p><p>
Audacity spelar in fr�n den f�rinst�llda ing�ngsk�llan som �r vald av
ditt operativsystem. Om du har flera  ing�ngsk�llor (som
inbyggd mikrofon, extern mikrofon, line-in uttag, eller en
audio-CD) du m�ste v�lja en av dessa att spela in ifr�n. Om du
f�rs�ker spela in fr�n fr�n mikrofon, som exempel, men din ing�ngsk�lla
 �r inst�lld till "line-in", s� kommer Audacity bara spela in tystnad.
</p><p>
Om du anv�nder Windows, kan du st�lla in ing�ngsk�llan genom att h�gerklicka
p� volymikonen i verktygslisten (nedre h�gra h�rnet av sk�rmen).
</p><p>
Om du anv�nder Mac OS 9, anv�nd Sound control panel.  I MAc OS X, anv�nd
Sound panel i System Preferences (det finns en input-flik om du 10.2 eller h�gre).
</p><p>
I Linux, anv�nd en mixer som "xmixer" eller "kmix".
</p><p>

<a name="a7"></a>
<font size=+1><b>
7. Hur delar jag upp en fil i flera sp�r?
</b></font>
</p><p>
Ibland kan du f� en inspelning av flera s�nger som �r
i en enda fil.  Om du vill br�nna dessa l�tar p� en CD som separata
sp�r, m�ste du skapa en separat fil f�r varje s�ng.
</p><p>Det finns m�nga olika s�tt att dela upp inspelningar till flera sp�r med hj�lp av
Audacity.  H�r finns n�gra exempel:
</p><p>
Method 1: Exportera Markering
</p><ul>
<li>V�lj den region av ljud som korresponderar det f�rsta sp�ret.
</li><li>V�lj "Exportera som WAV" fr�n Arkiv-menyn, och spara det f�rsta sp�ret p� h�rddisken.
</li><li>Forts�tt s� med alla resterande sp�r.
</li></ul>
<p>
Method 2: Radera och �ngra
</p><ul>
<li>Radera allting <i>f�rutom</i> f�r det f�rsta sp�ret.
</li><li>V�lj "Exportera som WAV" fr�n Arkiv-menyn, och spara det f�rsta sp�ret p� h�rddisken.
</li><li>V�lj "�ngra" fr�n Redigera-menyn.  Forts�tt att �ngra �nda tills du har resten av ljudet tillbaka. (Audacity har obegr�nsad �ngrafunktion.)
</li><li>Forts�tt s� med alla resterande sp�r.
</li></ul>
<p>
Method 3: Dela och Exportera
</p><ul>
<li>V�lj det du vill ha som f�rsta sp�r.
</li><li>V�lj "Dela" fr�n Redigera-menyn, vilket flyttar markeringen till ett separat sp�r i Audacity.
</li><li>Forts�tt med detta tills alla l�tar �r i separata sp�r.
    Gl�m inte att du �ngra om du r�kat g�ra fel.
</li><li>G� tillbaka och anv�nd "Exportera markering som WAV" f�r att exportera varje
    ssp�r till en separat fil.  F�r att snabbt v�lja varje sp�r, klicka p� dess
    eticket (vart som helst i omr�det till v�nster om v�gformen, under
    titeln).
</li></ul>
<p>

<a name="a8"></a>
<font size=+1><b>
8. Hur kan jag f� l�tar fr�n en ljud-CD?
</b></font>
</p><p>
Audacity kan inte ta s�nger fr�n ljud-CD. Du m�ste anv�nda ett
"ripper" program f�r detta.
</p><p>
F�r Windows, rekommenderas <a href="http://cdexos.sourceforge.net/">CDex</a>.
</p><p>
F�r Mac OS (9 and X), rekommenderas Apple's <a href="http://www.apple.com/itunes/">iTunes</a>.
</p><p>
F�r Linux, pr�va <a href="http://www.xiph.org/paranoia/">Paranoia</a>.

<?php BoxBottom(); ?>
