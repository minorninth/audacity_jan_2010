<h2>Zm�ny v Audacity 1.2</h2>

Tato str�nka obsahuje popis nejv�znamn�j��ch zm�n od vyd�n� na�� posledn� stabiln� verze Audacity 1.0.0. U�ivatel� betaverz� by se m�li pod�vat na changelog <a href="<?php print "betanotes.php$langQueryStr"; ?>">zm�ny od vyd�n� Audacity 1.1.0</a>.

<h3>Zvuk v profesion�ln� kvalit�</h3>

<ul>
<li>
Audacity nyn� um� nahr�vat a upravovat 24 a 32 bitov� vzorky (pohybliv� �adov� ��rka). V jednom projektu mohou b�t stopy s rozd�ln�mi vzorkovac�mi frekvencemi i form�ty, p�i�em� pokud je t�eba, Audacity je zkonvertuje v re�ln�m �ase. Pro v�echny konverze je pou�ito vysoce kvalitn� p�evzorkov�n� a dithering.
</li>

<li>
Vstup a v�stup zvuku v Audacity byl vylep�en. Audacity nyn� m��e nahr�vat v�ce ne� dva kan�ly najednou. Aby se p�ede�lo p�eskakov�n� a podte�en� vyrovn�vac� pam�ti (buffer underruns), byla zlep�ena pr�ce s bufferem.
</li>
</ul>

<a href="screenshots.php<?php print $langQueryStr; ?>">
<img alt="screenshots" border="0" src="images/screen/linux/change-pitch.png" align="right"></a>
<h3>Efekty</h3>

<!--
-->

<ul>
<li>
T�i nov� efekty na zm�nu lad�n� a rychlosti stopy:
 <ul>
<li>"Zm�na lad�n�" zv��� nebo sn�� zvuk vybran� ��sti bez vlivu na rychlost.</li>
<li>"Zm�na tempa" zrychl� nebo zpomal� vybranou ��st bez vlivu na v��ku lad�n�.</li>
<li>"Zm�na rychlosti" zm�n� rychlost p�ehr�v�n� i v��ku lad�n�, jako kdy� zm�n�te rychlost gramofonu nebo magnetofonu.</li>
 </ul>
</li>

<li>
V�t�ina efekt� nyn� obsahuje tla��tko "Preview", kter� umo��uje vyzkou�et r�zn� nastaven� p�ed zav�en�m efektov�ho okna. Nov� p��kaz v�m umo�n� zopakovat posledn� pou�it� efekt bez op�tovn�ho otev�r�n� okna.
</li>

<li>
Dal�� nov� efekty obsahuj�:
 <ul>
<li>Kompresor, pro dynamic range kompresi.</li>
<li>Opakov�n�, pro vytv��en� smy�ek ze vzork�.</li>
<li>Normalizace, pro �pravu hlasitosti a opravu DC bias.</li>
 </ul>
</li>
</ul>


<h3>Nov� edita�n� vlastnosti</h3>

<ul>
<li>
N�strojem Ob�lka, d��ve pou��van�mu k postupn�mu zesilov�n� a zeslabov�n� stop, m��ete nyn� tak� dos�hnout toho, aby stopy byly hlasit�j�� nebo slab�� ne� je origin�ln� hlasitost.
</li>

<li>
Nov� vlastnost "Time track" je podobn� ob�lce hlasitosti, ale rychlost se d� m�nit p��mo p�i p�ehr�v�n�.
</li>

<li>
Ka�d� stopa m� nyn� v z�jmu jednodu���ho mixov�n� vlastn� nastaven� Gain (zisk) a Pan (panorama).
<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/linux/track-controls.png" align="right"></a>
</li>

<li>
Audacity nyn� um� naj�t nulov� p�echody, ��m� napom�h� snadn�j��mu vytv��en� st�ih� a smy�ek. Stiskn�te "Z" a hranice v�b�ru se p�esunou na nejbli��� nulov� p�echod.
</li>
</ul>


<h3>Pluginy</h3>

<ul>
<li>
V Linuxu um� Audacity na��tat <a href="http://www.ladspa.org/">LADSPA</a> pluginy.
</li>

<li>
Audacity 1.2 p�in�� jazyk pro manipulaci s digit�ln�m sign�lem, zvan� <a href="nyquist.php">Nyquist</a>, kter� u�ivatel�m umo��uje naprogramovat nov� efekty v jazyce podobn�m LISPu.
</li>
</ul>


<h3>Import a export soubor�</h3>

<ul>
<li>
Projektov� soubory Audacity 1.2 pou��vaj� form�t XML. Projektov� soubory ze star��ch verz� se automaticky otev�raj� a konvertuj�.
</li>

<li>
Audacity 1.2 pou��v� pro mnohem rychlej�� dek�dov�n� soubor� MP3 <a href="http://www.underbit.com/products/mad/">libmad</a>. <a href="http://www.zip.com.au/~erikd/libsndfile/">Libsndfile</a> od Erika de Castro Lopo poskytuje zlep�enou kompatibilitu s mnoha nekomprimovan�mi zvukov�mi souborov�mi form�ty.
</li>

<li>
Dialog pro otev�r�n� a import nyn� dovoluje u�ivatel�m Audacity zvolit n�kolik zvukov�ch soubor� najednou a otev��t je v jednom projektu. Nov� souborov� form�t "LOF" umo��uje Audacity otev��t skupinu soubor� s offsety popsan�mi v textov�m souboru.
</li>
</ul>


<h3>Vylep�en� u�ivatelsk� rozhran�</h3>

<a href="screenshots.php<?php print $langQueryStr; ?>"><img alt="screenshots" border="0" src="images/screen/macosx/main-toolbar.png" align="right"></a>
<ul>
<li>
Nov� edita�n� a mixovac� panely umo��uj�c� rychl� p��stup k b�n�m funkc�m.
</li>

<li>
Nov� n�stroj Kreslen� umo��uje �pravy jednotliv�ch vzork� p�i pln�m zv�t�en�. 
</li>
<li>
V�cen�strojov� re�im poskytuje rychl� p��stup k r�zn�m edita�n�m funkc�m bez p�ep�n�n� mezi n�stroji.
</li>

<li>
Bylo p�id�no mnoho kl�vesov�ch p��kaz� a kl�vesov� zkratky jsou nyn� nastaviteln�.
</li>

<li>
Nov� p��kazy:
 <ul>
  <li>P�ehr�v�n� ve smy�ce.  Stiskn�te "L", nebo p�i kliknut� na Play podr�te shift.</li>
  <li>Stisknut�m "1" p�ehrajete jednovte�inovou uk�zku zvuku kolem kurzoru.</li>
 </ul>
</li>

<li>
Kole�ko my�i se d� pou��t ke zv�t�ov�n� a zmen�ov�n�.
</li>

<li>
Stopy mohou b�t svisle zv�t�ov�ny kliknut�m nebo ta�en�m na svisl�ch prav�tk�ch. Op�tovn�ho zmen�en� lze dos�hnout podr�en�m shiftu p�i kliknut� nebo kliknut�m prav�m tla��tkem.
</li>

<li>
Prav�tko a stavov� ��dek nyn� mohou zobrazovat �as v n�kolika r�zn�ch form�tech, v�etn� vte�in, vzork� nebo video r�m�.
</li>

<li>
U�ivatelsk� rozhran� Audacity m��e nyn� b�t p�elo�eno do dal��ch jazyk�. S p�ekladem do va�� rodn� �e�i m��ete dobrovoln� <a href="translation/">pomoci i vy</a>.
</li>
</ul>

<?/*  */ ?>
