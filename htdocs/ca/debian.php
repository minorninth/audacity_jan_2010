<?php BoxTop("Debian"); ?>

<p>
L'Audacity �s una part de la distribuci� tant <b>sid</b> com <b>woody</b> 
de Debian (en prova i inestable), per tant, instal�lar l'Audacity � tan simple com:
</p>
<xmp>$ apt-get update && apt-get install audacity</xmp>
<p>
Per qualsevol que encara utilitzi el potato (Debian 2.2) us podeu descarregar el deb (des de l'<a href="http://sourceforge.net/project/showfiles.php?group_id=6235">

�rea de desc�rrega de fitxers de SourceForge</a>)
o afegir la seg�ent l�nia al vostre /etc/apt/sources.list:
</p>
<xmp>
deb http://audacity.sourceforge.net potato/
</xmp>
<p><b>Atenci�: </b>els debs de potato es troben molt desactualitzats. Des que la majoria de persones que utilitzen el Debian a l'escriptori fan servir el woody o sid, no s'ha publicat un deb des de la versi� 0.96-0.98. El temps que i esfor�os que costaria construir-los �s massa elevat comparat amb la demanda inexistent.</p>

<?php BoxBottom(); ?>