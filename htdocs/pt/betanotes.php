<?php BoxTop("$releaseNotesStr $betaVersion"); ?>

<pre>
Problemas encontrados na vers�o 1.1.3:
  - O programa insere um arquivo chamado "Audacity-Commands.xml" em alguma pasta no computador onde est� instalado. Este arquivo � necess�rio para executar o Audacity. Na pr�xima vers�o, este arquivo ser� salvo na pasta do pr�prio programa. 

New features in Audacity 1.1.3: (Em ingl�s, apenas para refer�ncia)
  * User Interface
    - New Mixer toolbar allows you to control the output
      volume, input volume, and input source directly
      from Audacity.
    - Every track now has its own gain and pan controls.

  * File I/O
    - Uses improved project file format.  (Unfortunately reading
      previous formats, including 1.1.1, is not supported.)
    - Block files (stored in Audacity project directories) now
      use the standard AU format.  Though some Audacity
      meta-information is in these files, they can now be
      read by many other popular audio programs as well.
    - Fixed some bugs relating to reading/writing audio
      files with more than 16 bits per sample.
    - Import RAW is functional again, with a simpler GUI
      but support for far more file formats.  The
      autodetection algorithms are much more accurate than
      in 1.0.

  * Audio I/O
    - Completely rewritten audio I/O, with lower latency
      and minimal chance of buffer underruns while
      recording.

  * Resampling
    - Using high quality resampling algorithms, with the
      option of better quality for mixing than for real-time
      playback

    - Preliminary support for Time Tracks, for changing
      playback speed over time.

  * Many more bug fixes and new features




Problemas encontrados na vers�o 1.1.1:

  * N�o utilize a op��o "Executar Diagn�stico" do menu Ajuda - al�m de inst�vel, 
    pode fazer o sistema parar.
    Esta fun��o � feita para uso avan�ado apenas e n�o afeta a edi��o de �udio.

  * Mac OS X: Alguns segundos de �udio podem se perder se o bot�o do mouse for 
    mantido pressionado durante a captura. Deixe o sistema livre de interrup��es 
    volunt�rias enquanto � feita a capptura de �udio.


Novos recursos da vers�o 1.1.1:

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
  * Efeitos:
    - Efeitos divididos em tr�s categorias: Inserir, Efeitos e Analisar;
    - O menu Inserir permite a inser��o de Sil�ncio, Ru�do branco ou Tom
    - Suporte a efeitos escritos em linguagem Nyquist
  * Internacionaliza��o:
    - Suporte melhorado a novas l�nguas de interface;
    - Suporte a Portugu�s do Brasil!
    - Nas vers�es para Windows e MacOS, o sistema procura por tradu��es 
      nas pastas Languages e Plug-ins do programa.
    - Na vers�o para Unix, procura por tradu��es em <prefix>/share/locale e
      em qualquer pasta dentro da vari�vel de ambiente AUDACITY_PATH
  * Mac OS X:
    - Suporte a novas placas de som;
    - �udio full-duplex
    - Exporta��o em formato MP3 via LameLib Carbon
  * Unix:
    - O Audacity agora disp�e de uma p�gina descrevendo suas op��es de 
      linha de comando.
      options and how to set the search path)
  * Tipos de arquivo:
    - A nova vers�o utiliza a biblioteca libsndfile 1.0, com problemas corrigidos 
      e uma melhor performance.




Novos recursos da vers�o 1.1.0:

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


Novas bibliotecas do Audacity 1.1:

  * libmad - para importa��o em MP3;
  * libid3tag  - para edi��o das propriedades do MP3;
  * libsndfile - leitura e grava��o em novos formatos de �udio
  * PortAudio  - para leitura e grava��o em m�ltiplas plataformas.
</pre>

<?php BoxBottom(); ?>
