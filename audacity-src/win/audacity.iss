; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=Audacity
AppVerName=Audacity 0.98
AppPublisherURL=http://audacity.sourceforge.net
AppSupportURL=http://audacity.sourceforge.net
AppUpdatesURL=http://audacity.sourceforge.net
DefaultDirName={pf}\Audacity
DefaultGroupName=Audacity
AlwaysCreateUninstallIcon=yes
LicenseFile=C:\proxima\Download\audacity\audacity-win-0.98\LICENSE.txt
InfoBeforeFile=C:\proxima\Download\audacity\audacity-win-0.98\README.txt
; uncomment the following line if you want your installation to run on NT 3.51 too.
; MinVersion=4,3.51

[Tasks]
Name: "desktopicon"; Description: "Create a &desktop icon"; GroupDescription: "Additional icons:"; MinVersion: 4,4

[Files]
Source: "C:\proxima\Download\audacity\audacity-win-0.98\audacity.exe"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "C:\proxima\Download\audacity\audacity-win-0.98\audacity.exe"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "C:\proxima\Download\audacity\audacity-win-0.98\audacity-help.htb"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "C:\proxima\Download\audacity\audacity-win-0.98\LICENSE.txt"; DestDir: "{app}"; CopyMode: alwaysoverwrite
Source: "C:\proxima\Download\audacity\audacity-win-0.98\README.txt"; DestDir: "{app}"; CopyMode: alwaysoverwrite

[Icons]
Name: "{group}\Audacity"; Filename: "{app}\audacity.exe"
Name: "{userdesktop}\Audacity"; Filename: "{app}\audacity.exe"; MinVersion: 4,4; Tasks: desktopicon

[Run]
Filename: "{app}\audacity.exe"; Description: "Launch Audacity"; Flags: nowait postinstall skipifsilent

