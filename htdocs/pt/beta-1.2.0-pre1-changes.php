<h2>O que h� de novo desde o Audacity 1.0</h2>

Esta se��o lista as principais altera��es da vers�o mais recente em rela��o � �ltima vers�o est�vel do programa.
Usu�rios das vers�es beta devem visitar a <a href="<?php print "betanotes.php?$langLinkStr"; ?>">p�gina de vers�es beta</a> para saber as altera��es desde a vers�o 1.1.3.



<h3>�udio de qualidade profissional</h3>

<ul>
<li>
O Audacity agora grava e edita �udio captado com amostragens a 24-bit e 32-bit (ponto-flutuante). Faixas com amostragens diferentes podem ser editadas no mesmo projeto e o programa se encarrega de converter as taxas onde for necess�rio, utilizando algoritmos de convers�o de alta-qualidade .
As convers�es agora utilizam algoritmos da
<a href="http://www.mega-nerd.com/SRC/">SRC</a>, de Erik de Castro Lopo.
</li>

<li>
A importa��o e exporta��o de som foi melhorada. O programa agora pode gravar mais de duas faixas simultaneamente. O tempo de lat�ncia foi reduzido, diminuindo as chances de falhas na capta��o de som.
</li>
</ul>


<h3>Efeitos</h3>

<ul>
<li>
Tr�s novos efeitos alteram a altura, tempo e velocidade das faixas de �udio:
 <ul>
  <li>"Alterar Altura" aumenta ou diminui o tom do trecho selecionado, sem afetar a velocidade.</li>
  <li>"Alterar Tempo" faz a sele��o ser executada mais r�pido ou mais devagar, sem alterar a altura.</li>
  <li>"Alterar Velocidade" opera simultaneamente Altura e Tempo, similar a aumentar a velocidade de um disco de vinil ou uma fita cassete.</li>
 </ul>
</li>

<li>
A maioria dos efeitos inclui agora a op��o "Preview" que permite experimentar diferentes efeitos sem ter de abrir e fechar a janela diversas vezes. H� tamb�m a op��o "Repetir efeito", que aplica o �ltimo efeito novamente � sele��o.
</li>

<li>
Inclui tamb�m outros efeitos:
 <ul>
  <li>Compressor, para compress�o de extens�o din�mnica ("dynamic range compression").</li>
  <li>Repetir, executa amostras repetidamente ("loop").</li>
  <li>Normalizar, ajusta o volume e corrige desvios DC.</li>
 </ul>
</li>
</ul>


<h3>Novos recursos de edi��o:</h3>

<ul>
<li>
A ferramenta Envelope, usada para efeitos de "fading" (diminuir e aumentar o volume), agora pode ser utilizada tamb�m para aumentar o volume do som para al�m do original, ou torn�-lo mais baixo.
</li>

<li>
O novo recurso "Faixa de Tempo" (Time track) executa fun��es semelhantes �s da ferramenta Envelope, alterando a velocidade da faixa durante a reprodu��o.
</li>

<li>
� poss�vel ajustar o Ganho e Balan�o de cada faixa individualmente.
</li>

<li>
O Audacity agora encontra cruzamentos em zero (zero-crossings), que ajudam na cria��o de sons cont�nuos ("loopings"). Pressionar Z move o cursor de sele��o para o cruzamento em zero mais pr�ximo.
</li>
</ul>


<h3>Plugins</h3>

<ul>
<li>
Em sistemas rodando Linux, o Audacity agora pode abrir efeitos <a href="http://www.ladspa.org/">LADSPA</a>.
</li>

<li>
Esta vers�o oferece suporte ao processador digital de sinais <a href="nyquist.php">Nyquist</a>, que permite a cria��o de novos efeitos baseados em linguagem de programa��o semelhante � LISP.
</li>
</ul>


<h3>Importa��o e Exporta��o de arquivos</h3>

<ul>
<li>
O Audacity 1.2 apresenta seu novo formato de arquivos de projeto, baseado em XML. � poss�vel que os arquivos salvos em qualquer vers�o anterior do programa sejam lidos.
</li>

<li>
O Audacity 1.2 utiliza a nova biblioteca <a href="http://www.underbit.com/products/mad/">libmad</a> para a importa��o mais r�pida de arquivos do tipo MP3. A biblioteca <a href="http://www.zip.com.au/~erikd/libsndfile/">libsndfile</a> de Erik de Castro Lopo oferece compatibilidade melhorada com outros tipos de arquivo de �udio n�o-comprimidos.
</li>

<li>
A �ltima vers�o dos arquivos da <a href="http://www.vorbis.com/">Vorbis</a> est� inclu�da com o programa, para uma melhor exporta��o em formato OGG Vorbis.
</li>

<li>
As janelas de "Importar" e "Abrir" agora permitem a sele��o de v�rios arquivos para serem abertos/importandos ao mesmo tempo  em um mesmo projeto. O novo formato "LOF" permite que o programa abra um grupo de arquivos com compensa��o offset em um arquivo de texto.
</li>
</ul>


<h3>Nova interface:</h3>

<ul>
<li>
As novas barras de ferramentas "Edi��o" e "Mixagem" trazem r�pido acesso �s fun��es mais comuns.
</li>

<li>
A nova ferramenta "Desenhar" permite o ajuste de amostras individualmente, estando com o Zoom m�ximo. E a nova "Multi-ferramenta" acessa diferentes comandos de edi��o simultaneamente.
</li>

<li>
Novos atalhos de teclado foram adicionados, podendo agora ser personalizados completamente pelo usu�rio.
</li>

<li>
Novos comandos:
 <ul>
  <li>Reprodu��o cont�nua.  Pressione "L", segure Shift ao clicar em Executar.</li>
  <li>Pressione "1" para executar uma amostra de 1 segundo ao redor do cursor.</li>
 </ul>
</li>

<li>
A rodinha do mouse agora opera os comandos de Aproximar e Diminuir o Zoom.
</li>

<li>
As faixas de �udio podem ter o zoom ampliado verticalmente, clicando nas r�guas verticais ao lado de cada faixa. Segure Shift ao clicar ou use o bot�o direito para diminuir o zoom.
</li>

<li>
As r�guas de tempo e a barra de status podem exibir o tempo com diversas medidas diferentes, incluindo segundos, amostras e quadros de v�deo PAL, NTSC e Filme
</li>

<li>
A interface agora est� dispon�vel em diferentes l�nguas, gra�as ao trabalho de times de tradutores volunt�rios. Voc� tamb�m pode ajudar <a href="translation/">traduzindo o Audacity</a>.
</li>
</ul>
