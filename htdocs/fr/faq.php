<?php BoxTop("Foire Aux Questions"); ?>

<!--
<table width=100% cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+3">Frequently Asked Questions</font>
</td></tr></table>
-->

<p>

G�n�ralit�s:<br>
<a href="#g1">Audacity est-il vraiment gratuit?  Pourquoi?</a><br>
<a href="#g2">Qui a d�velopp� Audacity?</a><br>
<a href="#g3">Comment puis-je contribuer � am�liorer Audacity?</a><br>
<a href="#g4">J'ai trouv� un bogue!  Qu'est-ce que je fais?</a><br>
<p>
Installation:<br>

<a href="#i1">Windows: Que faire avec le fichier .exe?</a><br>
<a href="#i2">Windows: Comment d�sinstaller Audacity?</a><br>
<a href="#i3">Mac: Que faire avec le fichier .sit?</a><br>
<a href="#i4">Unix: Pourquoi ai-je des "failed dependencies" lorsque j'installe � partir de RPM?</a><br>
<a href="#i5">Unix: J'obtiens un message d'erreur quand je charge la biblioth�que partag�e libwx_gtk.so</a><br>
<p>
Utilisation d'Audacity:<br>
<a href="#a1">Comment combiner deux pistes?</a><br>
<a href="#a2">Peut-on �liminer la voix d'un enregistrement?</a><br>

<a href="#a3">Pourquoi les pistes sont-elles d�cal�es lorsque j'essaie d'enregistrer des harmonisations avec moi-m�me?</a><br>
<a href="#a4">Pourquoi Audacity n'inclut-il pas avec un encodeur MP3?</a><br>
<p>

<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">G�n�ralit�s</font>
</td></tr></table>

<p>

<a name="g1"></a>
<font size=+1><b>
1. Audacity est-il vraiment gratuit?  Pourquoi?<br>

</b></font>

<p>

Oui, et en plus d'�tre gratuit, vous �tes libre d'en faire ce que vous voulez.
<p>
Audacity est rendu disponible en vertu de la <a href="http://www.gnu.org/copyleft/gpl.html"
>License Publique G�n�rale GNU</a> (GNU GPL).
Vous pouvez utiliser librement ce programme � des fins personnelles ou commerciales.  Vous pouvez �galement le distribuer et le vendre.
Le code source du logiciel est disponible gratuitement sur la toile, et vous pouvez le modifier selon vos besoins.  Cependant, tous les changements que vous apportez doivent �galement �tre distribu�s en vertu de la license GPL.
<p>
Audacity est d�velopp� � l'aide de wxWindows, une biblioth�que de programmes distribu�e en vertu de la license LGPL, moins restrictive. Pour plus d'informations, veuillez voir le site 
<a href="http://www.wxwindows.org">wxwindows.org</a>.
<p>
Les cr�ateurs d'Audacity ont d�cid� de distribuer le logiciel en vertu de la license GPL pour plusieurs raisons.  Certains le font par g�n�rosit�. Certains le font par principe, parce qu'ils croient que tous les logiciels devraient �tre gratuits, alors que d'autres croient que les logiciels commerciaux et les logiciels gratuits ont tous leur raison d'�tre.
<p>
Un des bienfaits de la gratuit� d'Audacity, c'est qu'il sera ainsi plus populaire. Plusieurs d'entre nous pr�f�rent que le logiciel soit utilis� gratuitement par un million d'utilisateurs heureux plut�t qu'achet� par seulement quelques milliers d'utilisateurs.  Et la plupart des utilisateurs sont plus avenants lorsqu'ils obtiennent quelque chose gratuitement.

<p>
Une autre  bonne raison, c'est que �a encourage la coop�ration.  Si Audacity �tait un partagiciel, il est peu probable que des dizaines de personnes � travers le monde s'impliquent en programmant, en corrigeant des bogues, en r�digeant la documentation et en cr�ant les graphismes.

<p>
<a name="g2"></a>
<font size=+1><b>
2. Qui a d�velopp� Audacity?<br>
</b></font>

 <p>

Dominic Mazzoni a cr�� Audacity � l'automne 1999 alors qu'il �tait �tudiant en doctorat � l'universit� Carnegie Mellon � Pittsburgh aux �tats-Unis. Il travaillait sur un projet avec son directeur de recherche, le professeur Roger Dannenberg, et ils avaient besoin d'un outil qui leur permettrait de visualiser les algorithmes d'analyse audio.  Avec le temps, ce programme est devenu un logiciel g�n�ral de traitement sonore et d'autres personnes se sont impliqu�es.

<p>
Maintenant, Audacity est d�velopp� avec l'aide de Sourceforge, un site internet
qui permet aux gens des quatre coins du monde de collaborer � des projets de logiciels gratuits.  Pour plus d'informations, visitez le site <a href="http://www.sourceforge.net"
>sourceforge.net</a>. 
Des dizaines de personnes ont particip� au d�veloppement d'Audacity et le projet �volue de plus en plus rapidement.

<p>

<a name="g3"></a>
<font size=+1><b>
3. Comment puis-je contribuer � am�liorer Audacity?<br>
</b></font>

Rapportez-nous les bogues que vous trouvez. Programmez.  Traduisez-le dans votre langue.  Concevez les �l�ments graphiques. Inscrivez-vous sur la liste de diffusion des utilisateurs d'Audacity.  Envoyez-nous de l'argent.
<p>
Visitez notre nouvelle page <?php print "<a href=donatetime.php?$langLinkStr>"; ?>Dons</a> 
pour d�couvrir d'autres fa�ons de nous aider.
<p>

<a name="g4"></a>
<font size=+1><b>
4. J'ai trouv� un bogue!  Qu'est-ce que je fais?<br>
</b></font>
<p>

Lorsque vous rapportez un bogue, il est important d'�tre aussi pr�cis que possible. Donnez-nous suffisamment d'informations pour que nous puissions le reproduire, sans quoi il nous sera difficile de le corriger. Envoyez vos rapports de bogues � 
<a href="mailto:audacity-help@lists.sourceforge.net">
<audacity-help@lists.sourceforge.net></a>.
<p>
N'oubliez pas de mentionner votre syst�me d'exploitation (par exemple Windows 98, MacOS 9.1, RedHat Linux 7.1, etc.) ainsi que toute caract�ristique de votre ordinateur que vous jugez pertinente.
<p>
Pouvez-vous le reproduire? S'il se pr�sente de fa�on syst�matique, dites-nous exactement toutes les manipulations que vous faites pour le provoquer.  Si vous obtenez un message d'erreur, rapportez-nous le texte exact de ce message.
<p>

Nous voulons �liminer tous les bogues!  Nous vous sommes reconnaissants de nous aider � les identifier tous.
<p>
<br>
<p>

<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Installation</font>
</td></tr></table>

<p>
<a name="i1"></a>
<font size=+1><b>
1. Windows: Que faire avec le fichier .exe?<br>
</b></font>

<p>Dans l'explorateur, s�lectionnez l'option:"Ex�cuter � partir de l'emplacement actuel".  Cela active l'installateur d'Audacity qui installera les fichiers et ajoutera un item au menu D�marrer.
<p>
Si vous avez d�j� t�l�charg� le fichier, il suffit de double-cliquer sur son ic�ne pour lancer l'installateur.
<p>
Si vous pr�f�rez ne pas utiliser le programme d'installation, vous pouvez aussi t�l�charger Audacity en fichier ZIP que vous d�compresserez avec WinZip.
<p>
<a name="i2"></a>
<font size=+1><b>
2. Windows: Comment d�sinstaller Audacity?<br>
</b></font>

<p><font size=+0>Audacity peut �tre d�sinstall� par le panneau de configuration Ajout/Suppression de programmes. Dans la liste, s�lectionnez "Audacity" et cliquez sur "Ajouter/Supprimer...". Ceci lance le programme de d�sinstallation d'Audacity.
<p>
<a name="i3"></a> <font size=+1><b> 3. Mac: Que faire avec le fichier .sit?<br> </b></font>

<p>
Il vous faut une version r�cente de StuffIt Expander.  StuffIt Expander est inclus sur tous les Macintoshs et il est habituellement s�lectionn� par d�faut sur tous les navigateurs pour Mac. Dans le cas o� Audacity ne se d�compresserait pas automatiquement, glissez le fichier "audacity.sit" sur l'icone de StuffIt Expander pour le d�compresser.
<p>
Audacity ne requiert aucune installation particuli�re.  Il suffit de glisser la chemise Audacity dans la chemise Applications ou � tout autre endroit que vous jugez pratique.  Pour d�sinstaller, il suffit de glisser tout le dossier dans la corbeille.

<p>
<a name="i4"></a>
<font size=+1><b>
4. Unix: Pourquoi ai-je des "failed dependencies" lorsque j'installe � partir de RPM?
<br></b></font>

<p><font size=+0>D'abord, assurez-vous que wxGTK est install�; vous trouverez un lien pour le t�l�charger sur notre page pour Linux - http://audacity.sourceforge.net/linux.html. Si RPM
refuse de s'installer, this is an unresolved issue.  Installez simplement RPM
� l'aide du flag --nodeps.</font>

<p>
<a name="i5"></a>
<font size=+1><b>

5. Unix: J'obtiens un message d'erreur quand je charge la biblioth�que partag�e libwx_gtk.so<br></b></font>

<p><font size=+0>Il y a deux possibilit�s:
<br>- Si vous avez install� wxWindows RPM, assurez-vous d'ex�cuter "ldconfig" (as
root) afin que la nouvelle biblioth�que soit reconnue par le syst�me.

<br><br>- Si vous avez install� wxWindows
� partir de la source, il est peut-�tre bien install� dans in /usr/local, mais /usr/local/lib n'est peut-�tre pas dans le chemin d'acc�s de la biblioth�que. Ajoutez /usr/local/lib au fichier "/etc/ld.so.conf" et ex�cutez "ldconfig". Vous pouvez �galement ajouter "/usr/local/bin" au chemin d'acc�s pour que le programme puisse trouver l'utilitaire "wx-config".<br>

<p>
<table cellpadding=6 width=100%><tr><td bgcolor="#ffd0d0" align="center">
<font size="+1">Utilisation d'Audacity</font>
</td></tr></table>

<p>
<a name="a1"></a>
<font size=+1><b>

1. Comment combiner deux pistes?
</b></font>
<p>

Audacity combine les pistes automatiquement.  Il suffit d'importer les deux pistes dans le m�me projet, ce qui peut �tre fait en utilisant l'item "Importation audio" du menu Projet ou simplement en glissant les deux fichiers audio dans la fen�tre Audacity.  Aussi, en appuyant sur le bouton d'enregistrement, Audacity g�n�re automatiquement une nouvelle piste.
<p>

Pour sauvegarder le r�sultat, vous pouvez soit Exporter le projet, ce qui combinera automatiquement toutes les pistes, soit s�lectionner les pistes en question et utiliser l'item "Quick Mix" du menu Projet.

<p>
<a name="a2"></a>
<font size=+1><b>
2. Est-il possible d'�liminer la voix d'un enregistrement?
</b></font>
<p>

Il est possible d'�liminer la voix de certains enregistrements st�r�o selon la fa�on dont le mixage  a �t� fait en studio. Souvent, la partie vocale est positionn�e exactement au centre alors que les instruments sont sur les c�t�s.  En soustrayant le canal droit du canal gauche, la voix se trouve annul�e, ne laissant que les instruments.
<p>

<b>Ceci ne fonctionne que sur certains enregistrements!</b>
<p>Pour le faire avec Audacity, ouvrez un enregistrement st�r�o. Dans le menu d�roulant de la piste (cliquez sur la petite fl�che apr�s le nom de la piste pour le faire appara�tre), s�lectionnez "Split Stereo Track".  S�lectionnez ensuite la piste du bas (le canal droit) et utilisez l'effet Inversion du menu Effet. Enfin, convertissez chaque piste en Mono � l'aide du  menu d�roulant devant chacune et combinez-les avec Quick Mix. Si vous �tes chanceux, la voix aura disparu. 

<p>
<a name="a3"></a>
<font size=+1><b>
3. Pourquoi les pistes sont-elles d�cal�es lorsque j'essaie d'enregistrer des harmonisations avec moi-m�me?
</b></font>
<p>
Ce ph�nom�ne est normal et est caus� par le petit d�lai entre le moment o� Audacity joue un son et le moment o� ce son atteint les hauts-parleurs. Audacity ne corrige pas automatiquement ce d�lai, il faut donc le corriger manuellement.
<p>
Pour le corriger, utilisez l'outil de d�callage temporel pour glisser une des pistes jusqu'� ce qu'elle soit align�e avec les autres.  Notez qu'il est possible d'utiliser l'outil pendant l'�coute de l'enregistrement.

<p>

<a name="a4"></a>
<font size=+1><b>
4. Pourquoi Audacity n'inclut-il pas avec un encodeur MP3?
</b></font>
<p>

Malheureusement, l'algorithme pour cr�er des fichiers MP3 est brevet�, et inclure un tel encodeur dans <b>Audacity</b> serait impossible sans ajouter des frais ou sans enfreindre la loi de plusieurs pays.
<p>
En guise de compromis, Audacity a la capacit� d'utiliser d'autres encodeurs MP3 t�l�chargeables s�par�ment.  Il est de votre devoir de respecter les licences de ces encodeurs MP3.
<p>
Pour plus d'informations, rendez-vous � la page Exporter des fichers MP3 dans l'Aide en ligne.
</p>

<p>N.B. Dans ce site, seul le masculin est utilis� dans le but d'all�ger le texte.
</p>
<?php BoxBottom(); ?>
