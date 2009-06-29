; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; compiler-related directives
OutputBaseFilename=audacity-1.3.8a-win-unicode
SetupIconFile=audacity.ico

WizardImageFile=audacity_InnoWizardImage.bmp
WizardSmallImageFile=audacity_InnoWizardSmallImage.bmp

SolidCompression=yes

; installer-related directives
AppName=Audacity 1.3 Alpha (Unicode)
AppVerName=Audacity 1.3.8 (Unicode)
AppPublisher=Audacity Team
AppPublisherURL=http://audacity.sourceforge.net
AppSupportURL=http://audacity.sourceforge.net
AppUpdatesURL=http://audacity.sourceforge.net
ChangesAssociations=yes
DefaultDirName={pf}\Audacity 1.3 Alpha (Unicode)
; Always warn if dir exists, because we'll overwrite previous Audacity.
DirExistsWarning=yes
DisableProgramGroupPage=yes
UninstallDisplayIcon="{app}\audacity.exe"
; No longer force them to accept the license, just display it.   LicenseFile=..\LICENSE.txt
InfoBeforeFile=..\LICENSE.txt
InfoAfterFile=..\README.txt
; min versions: Win95, NT 4.0
MinVersion=4.0,4.0

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "basque"; MessagesFile: "compiler:Languages\Basque.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "catalan"; MessagesFile: "compiler:Languages\Catalan.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "slovak"; MessagesFile: "compiler:Languages\Slovak.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: desktopicon; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4
; No longer allow user to choose whether to associate AUP file type with Audacity.
; Name: associate_aup; Description: "&Associate Audacity project files"; GroupDescription: "Other tasks:"; Flags: checkedonce; MinVersion: 4,4


[Files]
; Don't display in separate window, rather as InfoAfterFile.   Source: "..\README.txt"; DestDir: "{app}"; Flags: ignoreversion isreadme
Source: "..\README.txt"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\LICENSE.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\win\unicode release\audacity.exe"; DestDir: "{app}"; Flags: ignoreversion

; wxWidgets DLLs. Be specific (not *.dll) so we don't accidentally distribute avformat.dll, for example.
; Don't use the WXWIN environment variable, because...
; 1) Can't get the documented {%WXWIN|default dir} parsing to work.
; 2) Need the DLL's in the release dir for testing, anyway.
Source: "..\win\unicode release\wxbase28u_net_vc_custom.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\win\unicode release\wxbase28u_vc_custom.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\win\unicode release\wxmsw28u_adv_vc_custom.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\win\unicode release\wxmsw28u_core_vc_custom.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\win\unicode release\wxmsw28u_html_vc_custom.dll"; DestDir: "{app}"; Flags: ignoreversion

; MSVC runtime DLLs. Some users can't put these in the system dir, so just put them in the EXE dir.
; It's legal, per http://www.fsf.org/licensing/licenses/gpl-faq.html#WindowsRuntimeAndGPL .
; This is not an ideal solution, but should need the least tech support.
; We'll know we have the right version, don't step on anybody else's older version, and
; it's easy to make the zip (and they match better).
Source: "C:\Program Files\Microsoft Visual Studio 8\VC\redist\x86\Microsoft.VC80.CRT\Microsoft.VC80.CRT.manifest"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Program Files\Microsoft Visual Studio 8\VC\redist\x86\Microsoft.VC80.CRT\msvcp80.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Program Files\Microsoft Visual Studio 8\VC\redist\x86\Microsoft.VC80.CRT\msvcr80.dll"; DestDir: "{app}"; Flags: ignoreversion

Source: "..\win\unicode release\languages\*"; DestDir: "{app}\Languages\"; Flags: ignoreversion recursesubdirs
Source: "..\win\unicode release\modules\*"; DestDir: "{app}\Modules\"; Flags: ignoreversion recursesubdirs skipifsourcedoesntexist
Source: "..\win\unicode release\nyquist\*"; DestDir: "{app}\Nyquist\"; Flags: ignoreversion
Source: "..\win\unicode release\plug-ins\*"; DestDir: "{app}\Plug-Ins\"; Excludes: "analyze.ny, fadein.ny, fadeout.ny, undcbias.ny"; Flags: ignoreversion
; not yet in cvs:   Source: "..\help\manual\*"; DestDir: "{app}\Help\"; Flags: ignoreversion recursesubdirs


[Icons]
Name: "{commonprograms}\Audacity 1.3 Alpha (Unicode)"; Filename: "{app}\audacity.exe"
Name: "{userdesktop}\Audacity 1.3 Alpha (Unicode)"; Filename: "{app}\audacity.exe"; MinVersion: 4,4; Tasks: desktopicon

[InstallDelete]
; Get rid of Audacity 1.0.0 stuff that's no longer used.
Type: files; Name: "{app}\audacity-help.htb"
Type: files; Name: "{app}\audacity-1.2-help.htb"
; Don't think we want to do this because user may have stored their own.
;   Type: filesandordirs; Name: "{app}\vst"

; We've switched from a folder in the start menu to just the Audacity.exe at the top level.
; Get rid of 1.0.0 folder and its icons.
Type: files; Name: "{commonprograms}\Audacity\audacity.exe"
Type: files; Name: "{commonprograms}\Audacity\unins000.exe"
Type: dirifempty; Name: "{commonprograms}\Audacity"

[Registry]
; No longer allow user to choose whether to associate AUP file type with Audacity.
; Leaving this one commented out example of the old way.
; Root: HKCR; Subkey: ".AUP"; ValueType: string; ValueData: "Audacity.Project"; Flags: createvalueifdoesntexist uninsdeletekey; Tasks: associate_aup
Root: HKCR; Subkey: ".AUP"; ValueType: string; ValueData: "Audacity.Project"; Flags: createvalueifdoesntexist uninsdeletekey;
Root: HKCR; Subkey: "Audacity.Project\OpenWithList\audacity.exe"; Flags: createvalueifdoesntexist uninsdeletekey;
Root: HKCR; Subkey: "Audacity.Project"; ValueType: string; ValueData: "Audacity Project File"; Flags: createvalueifdoesntexist uninsdeletekey;
Root: HKCR; Subkey: "Audacity.Project\shell"; ValueType: string; ValueData: ""; Flags: createvalueifdoesntexist uninsdeletekey;
Root: HKCR; Subkey: "Audacity.Project\shell\open"; Flags: createvalueifdoesntexist uninsdeletekey;
Root: HKCR; Subkey: "Audacity.Project\shell\open\command"; ValueType: string; ValueData: """{app}\audacity.exe"" ""%1"""; Flags: createvalueifdoesntexist uninsdeletekey;
;The following would allow a following 'help' installer to know where to put the 'help' files.
;Root: HKCR; Subkey: "Audacity.Project\Path";  ValueType: string; ValueData: {app}; Flags: createvalueifdoesntexist uninsdeletekey;

[Run]
Filename: "{app}\audacity.exe"; Description: "Launch Audacity"; Flags: nowait postinstall skipifsilent

