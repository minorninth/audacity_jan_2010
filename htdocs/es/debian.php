<?php BoxTop("Debian"); ?>

<p>
Audacity es una parte tanto de la distribuci�n <b>sid</b>
como de <b>woody</b> en Debian (de testeo e inestable), as� que
instalar Audacity es tan simple como:
</p>
<xmp>
$ apt-get update && apt-get install audacity
</xmp>
<p>
Para cualquiera a�n utilizando potato (Debian 2.2) puede descargar el
deb (de <a href="http://sourceforge.net/project/showfiles.php?group_id=6235">
el �rea de archivos de SourceForge</a>)
o agregar la siguiente l�nea a su /etc/apt/sources.list:
</p>
<xmp>
deb http://audacity.sourceforge.net potato/
</xmp>
<p><b>Advertencia: </b>los debs de potato est�n muy desactualizados. Debido a que
la mayor�a de personas que utiliza Debian en escritorio usa woody o sid, no he
publicado un deb para versiones desde la 0.96 a la 0.98. Lleva su trabajo
construirlos, y no hay mucha demanda para ellos.
</p>

<?php BoxBottom(); ?>
