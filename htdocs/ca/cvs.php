<?php BoxTop("CVS"); ?>

Per coordinar el treball col�laboratiu de desenvolupament fem servir 
el sistema <a href="http://www.cvshome.org">CVS</a>, (Concurrent Versions 
System). Feu clic <a 
href="http://cvs.sourceforge.net/cgi-bin/viewcvs.cgi/audacity/audacity-src/"
>aqu�</a> per consultar el nostre repositori CVS de codi font.

<p>
<h3>Nota: La versi� 1.2 es troba actualment bifurcada:</h3>
Si voleu la branca estable de l'Audacity, versi� 1.2.x, heu d'escriure 
<tt>-r AUDACITY_1_2</tt> quan feu servir els comandaments cvs "update" o "checkout". 
Altrament anireu a la cap�alera del CVS, que pot ser for�a inestable 
actualment, ja que hem comen�at a treballar en la versi� 1.3.0.

<p><h3>Guia r�pida del CVS de l'Audacity:</h3>
  Si voleu accedir al codi font de l'Audacity, feu servir 
  un client cvs per descarregar una branca cvs al vostre ordinador. 
  Quan hagueu fet un "checkout", el vostre client CVS 
  ser� capa� d'ajudar-vos a mantenir la vostra versi� actualitzada 
  amb la dels altre4s desenvolupadors de l'Audacity. Seguiu les 
  instruccions seg�ents per obtenir el codi font:


<h4>Acc�s CVS an�nim amb un client cvs de l�nia d'ordres:</h4>
<p>Escriviu aquesta l�nia d'ordres (tingueu en compte que �s 
una sola l�nia, sense retorns de carro):<br>
<ul><tt>cvs -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity
login </tt><br></ul>
i premeu la tecla de retorn quan us demani la contrasenya.

<p>Tot seguit, <b>per obtenir el codi m�s recent (1.3.0)</b> (en una �nica l�nia):
<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co
audacity</tt></ul>
o <b>per la branca estable (1.2.0)</b> (en una �nica l�nia):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co -r AUDACITY_1_2 audacity</tt></ul>
o <b>per la branca antiga (1.0.0)</b> (en una �nica l�nia):<br>
   <ul><tt>cvs -z3 -d:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity co -r audacity-0_9-branch audacity-old</tt></ul>

<p> Tamb� podeu definir la variable d'entorn <tt>CVSROOT</tt> com a 
<tt>:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt> 
(vegeu m�s avall).<br>
Si feu aix�, per <b>obtenir la branca ,�s recent i inestable (1.3.0)</b>, escriviu<br> 
   <ul><tt>cvs checkout audacity</tt></ul>
o, <b>per la branca estable (1.2)</b>, escriviu <br>
   <ul><tt>cvs checkout -r AUDACITY_1_2 audacity</tt></ul>
o <b>per la branca antiga 1.0</b>, escriviu <br>
   <ul><tt>cvs checkout -r audacity-0_9-branch audacity-old</tt></ul>

<p> Per fixar la variable d'entorn <tt>CVSROOT</tt> podeu fer servir 
el fitxer de recursos del vostre shell, o una de les ordres seg�ents: 
<h5>Als shells bash o bourne, en una �nica l�nia:</h5>
<ul><tt>export
CVSROOT=:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt><br></ul>
<h5>Amb csh or els seus descendents, en una sola l�nia:</h5>
<ul><tt>setenv CVSROOT
:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt><br></ul>

<hr width="80%">

<h4>Acc�s an�nim al CVS amb un client gr�fic</h4>

Si feu servir un client gr�fic com ara wincvs, maccvs, o gcvs, 
(disponibles a <a href="http://www.wincvs.org">wincvs.org</a>) heu d'establir la variable d'entorn 
<tt>CVSROOT</tt> (al submen� Admin|Preferences) per tal que sigui 
<tt>:pserver:anonymous@cvs.audacity.sourceforge.net:/cvsroot/audacity</tt>
i seleccionar l'autenticaci� "pserver" o "Password". Tot seguit, 
en la pestanya Globals del di�leg Preferences, assegureu-vos que 
heu desmarcat la casella "Checkout read-only (CVSREAD)".  A continuaci�, 
escolliu login, i feu clic a la tecla de retorn quan demani la contrasenya (�s 
""). Finalment, escolliu "Create|Checkout module", escolliu una ubicaci� 
on vulgueu col�locar la branca seleccionada, i seguiu 
les instruccions seg�ents segons quina branca vulgueu.
Si us d�na un error, assegureu-vos que la variable d'entorn <tt>CVSROOT</tt> 
no contingui cap espai en blanc al final --cosa que pot passar 
si copieu les variables directament des d'aquesta p�gina web.

<p>
<b>Per obtenir la branca inestable m�s recent (1.3.0):</b><br>
Al di�leg "Checkout Settings", escriviu 
<tt>audacity</tt> com a nom del m�dul. Cliqueu a "OK" i la branca 
es descarregar� autom�ticament al vostre ordinador.
<p>
<b>Per obtenir la branca estable (1.2.0): </b><br>
Al di�leg "Checkout Settings", escriviu 
<tt>audacity</tt> com a nom del m�dul.  Tot seguit, a la pestanya 
"Sticky options", marqueu la casella "Retrieve rev./tag/branch 
(-r)" i escriviu <tt>AUDACITY_1_2</tt> a la caixeta que hi ha 
al costat. Cliqueu a "OK" i la branca es descarregar� autom�ticament 
al vostre ordinador.
<p>
<b>Per obtenir la branca de la versi� antiga 1.0: </b><br>
Al di�leg "Checkout Settings", escriviu 
<tt>audacity-old</tt> com a nom del m�dul.  Despr�s, a la pestanya 
"Sticky options", marqueu la casella "Retrieve rev./tag/branch 
(-r)" i escriviu <tt>audacity-0_9-branch</tt> a la caixeta 
que hi ha al costat. Cliqueu a "OK" i la branca es descarregar� 
autom�ticament al vostre ordinador.

<hr width="80%">
Sou novells en el CVS?  Comenceu per llegir els articles de Jim Blandy's <a href="">Introduction 
to CVS</a>, o de Bob Arnson <a
href="http://www.cvshome.org/new_users.html">CVS for new users</a>, o visiteu la p�gina web del cvs a <a 
href="http://www.cvshome.org/">www.cvshome.org</a>.
Trobareu informaci� m�s detallada als cap�tols GPLitzats del llibre de Karl 
Fogel <a href="http://cvsbook.red-bean.com/cvsbook.html">CVS Book
at cvsbook.red-bean.com</a>, o a l'"Oficial" <a href="http://www.cvshome.org/docs/manual">Per
 Cederqvist manual</a>.


<p> Per a informaci� espec�fica sobre el CVS de sourceforge.net, mireu-vos 
la documentaci� corresponent a les plataformes 
<a 
href="http://sourceforge.net/docman/display_doc.php?docid=763&group_id=1">Unix</a>,
<a 
href="http://sourceforge.net/docman/display_doc.php?docid=766&group_id=1">Microsoft Windows</a>, i <a 
href="http://sourceforge.net/docman/display_doc.php?docid=2973&group_id=1">MacOS 
(anterior a OS X)</a>.

<hr width="80%">

<p>
<b>M�s detalls:</b>

</p>

<p>L'Audacity fa servir for�a biblioteques de tercers. La majoria d'elles necessiten ajustaments fins 
per compilar el programa en les diverses plataformes a les que ens adrecem. Amb tot, mantenim 
un repositori local de tot el codi font de tercers en el CVS. Aix� �s com funciona:
</p>
<p>Hi ha dos repositoris: 'audacity-src', que cont� tot el 
codi que hem escrit nosaltres, i 
'lib-src,' que cont� el codi font de totes les 
biblioteques que fem servir.
Per tal de garantir la interoperabilitat entre l'Audacity i 
les biblioteques, us recomanem que feu servir les versions de les biblioteques 
que hi ha a 'lib-src'.  Amb tot, en sistemes Unix podeu estalviar-vos de compilar 
alguna de les biblioteques fent servir les que ja tingueu al vostre sistema. 
Escriviu 'configure --help' per veure les opcions. 
</p>
<p>
Amb tot, si voleu comprovar-ho tot, fins i tot el codi font de les biblioteques, 
feu un checkout al m�dul 'audacity' que descarregar� audacity-src juntament amb 
el repositori lib-src com a subdirectori d''audacity'.
</td>
</tr>
</table>
</p>

<?php BoxBottom(); ?>
