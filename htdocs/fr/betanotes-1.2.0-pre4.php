<pre>
Modifications dans la version 1.2.0-pre4:

  * R�solution de probl�mes apparaissant lors de l'importation certain
    fichiers audio PCM non cherchables, tels que GSM610.

  * Fixed bug that was causing the samples to shift off-screen
    horizonally when zoomed in very far and the track had a
    time-shift offset.

  * R�solution d'un bogue du nouveau r��chantillonneur qui ajoutait du bruit � l'audio r��chantillonn� sur certains syst�mes. Si vous obteniez du bruit lors de l'exportation en WAV, MP3 ou fichier OGG vous pouvez avoir �t� touch� par ce bogue.
  
  * R�solution d'un bogue provoquant des crashes occasionels  lors de l'utilisation de l'outil de d�callage temporel avec un facteur de zoom important.
    
  * Le lissage n'est appliqu� que si n�cessaire lors de l'export (par exemple lors de la conversion d'un �chantillonnage flottant en 16 bit).
    
  * Les fichiers contenant des pistes mono sont d�sormais automatiquement esport�s en tant que fichiers st�r�o s'ils contiennent des pistes qui sont en panoramique droit ou gauche.
    
  * La touche d'effacement peut d�sormais �tre utilis�e pour effacer la s�lection courante, en plus de la touche effacement arri�re.

  * R�solution d'un bogue dans lequel Audacity ne demande ni d'enregistrer les modifications si vous fermez le projet ou quittez durant l'enregistrement.

  * Mac OS X: Supports Playthrough (listen to what you're recording
    while recording it) if your hardware device supports it.

  * Mac OS X: Audacity is now a package (you can right-click on
    Audacity.app and select 'Show Package Contents').  Launch time
    has improved significantly.

  * MS Windows: Fixed problem that caused Windows XP to use 
    the short name of a file ("TESTFI~1.AUP"), which led to 
    problems when the file was later opened again using the 
    long file name.
    
  * MS Windows: Fixed bug that caused file exports to fail 
    if the destination directory was the root folder of a 
    Windows drive.

  * MS Windows: Audacity's application information which 
    is written to the Windows registry now always contains 
    the full path to the executable. 

  * MS Windows: Fixed problems in trying to set the Windows 
    registry as non-admin user, for file-type associations.

  * Make sure the "Save" command is enabled after changing
    gain and pan sliders.

  * Updated translations.  Added translator credits to localized
    versions of Audacity.

</pre>
