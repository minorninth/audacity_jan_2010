<?php BoxTop($develNewsStr); ?>

<p>
Esta p�gina mostra em que os desenvolvedores est�o envolvidos neste momento.</p>

<p>
<b>Novos recursos da vers�o 1.1:</b>
<pre>
  * Processamento central:
    - Suporte a amostras de som em 24-bit e 32-bit;
    - Re-amostragem em tempo real com interpola��o linear.
  * Efeitos:
    - Suporte a plugins LADSPA em Linux / Unix
  * Tipos de arquivo:
    - Novo tipo de arquivo baseado em XML para os projetos;
    - Suporte completo a Ogg Vorbis;
    - Suporte a grava��o e leitura em mais tipos de �udio n�o-comprimidos 
      incluindo ADPCM-WAV.
  * Barra de ferramentas:
    - Cores que se ajustam �s do sistema operacional;
    - Novos bot�es;
    - Nova barra de edi��o.
  * Interface:
    - Dicas sobre as ferramentas na barra de status;
    - As telas rolam acompanhando o cursor durante a reprodu��o / grava��o;
    - Bot�o de Pausa;
    - Ferramenta de desenho de pontos em 3 diferentes modos;
    - Ajuste do tamanho de cada faixa na tela mais f�cil;
    - Barra de ferramentas sens�vel ao contexto;
    - Fun��es de Zoom aprimoradas com centraliza��o autom�tica;
    - Modo de sele��o "Snap-to"
    - Mudan�a de ordem das faixas pelo mouse;
    - Fun��es de alinhamento e agrupamento de �tens;
    - Salva e restaura posi��es do cursor e sele��es;
    - Janela de Hist�rico com "desfazer" ilimitados.
  * Internacionaliza��o:
    - Suporte melhorado a novas l�nguas de interface;
    - Suporte a Portugu�s do Brasil!
    - Nas vers�es para Windows e MacOS, o sistema procura por tradu��es 
      nas pastas Languages e Plug-ins do programa.
    - Na vers�o para Unix, procura por tradu��es em <prefix>/share/locale e
      em qualquer pasta dentro da vari�vel de ambiente AUDACITY_PATH
</pre>
</p>

<p>
<b>Tabela de bibliotecas necess�rias para o funcionamento da vers�o 1.1.0 e posteriores:</b>
<table border=0 cellpadding=8 cellspacing=2>
<tr>
<th>Biblioteca</th>
<th>Uso</th>
</tr>
<tr>
<td bgcolor="#ccccff"
><a href="http://www.wxwindows.org">wxWindows</a>
<td bgcolor="#ccccff"> Esta biblioteca possibilita o uso dos bot�es da interface em sistemas Windows, MacOS e Linux. O Audacity utiliza-se 100% desta biblioteca e recomendamos fortemente o seu uso para o desenvolvimento em m�ltiplas plataformas.
</tr>

<tr>
<td bgcolor="#ccccff"
><a href="http://www.mars.org/home/rob/proj/mpeg/">libmad</a>
<td bgcolor="#ccccff"
><p>"MAD" quer dizer "Mpeg Audio Decoder". Este � um dos poucos codecs para importa��o em formato MP3 dispon�veis com licen�a GPL. � tamb�m o �nico capaz de produzir sa�da de �udio em 24-bit (que ainda n�o foi totalmente aproveitada). Ainda que os �udios MP3 sejam criados com entrada em 16-bit, um importador com capacidade de sa�da em 24-bit permite uma qualidade �udio muito superior e um controle maior sobre sua produ��o. H� ainda a vantagem da extrema rapidez - comparada ao xaudio, utilizado nas vers�es anteriores. � desenvolvido por Rob Leslie. </p>
    <p>Necess�ria para a importa��o de �udio em formato MP3</p>
</tr>
<tr>
<td bgcolor="#ccccff"
><a href="http://www.mars.org/home/rob/proj/mpeg/">libid3tag</a></td>
<td bgcolor="#ccccff"
><p> Escrita por Rob Leslie (o mesmo autor da "libmad"), esta biblioteca permite a leitura das etiquetas ID3, como nome de faixa, compositor, �lbum, etc, anexados aos arquivos MP3.</p>
    <p>Esta biblioteca � opcional. Note que � distribu�da junto com o MAD.</p>
</td>
</tr>
<tr>
<td bgcolor="#ccccff"><a ref="http://www.xiph.org/ogg/vorbis/">
libogg<br>libvorbis<br>libvorbisfile</a>
</td>

<td bgcolor="#ccccff">
<p>O Ogg Vorbis � um compressor e descompressor de �udio no formato OGG. Foi desenvolvido para substituir o MP3 como formato de compress�o e � capaz de exportar �udio com qualidade superior ao seu substituto. O Audacity � capaz de importar e exportar neste formato.
</p>
</td>
</tr>
<tr>
<td bgcolor="#ccccff"
>
<a href="http://www.portaudio.com">portaudio</a>
</td>
<td bgcolor="#ccccff">
Esta biblioteca permite a entrada e sa�da de �udio utilizando uma API comum a diversas plataformas. Ela adapta as especificidades de cada E/S de som nos diferentes sistemas operacionais com boa performance. C�digo est�vel dispon�vel para Windows (MME e Directx), Unix/OSS e MacOS 9. Portabilidade para MacOS-X, Linux/ALSA e Linux/aRTs est� em desenvolvimento.
</td>
</tr>
<tr>
<td bgcolor="#ccccff"
><a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a></td>

<td bgcolor="#ccccff"> Esta biblioteca permite ler e salvar arquivos de �udio WAV, AIFF e AU. Permite a manipula��o de compress�es simples como a ADPCM, sem perdas.
</td>
</tr>
</table>
</p>


<?php BoxBottom(); ?>
