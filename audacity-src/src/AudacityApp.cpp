/**********************************************************************

  Audacity: A Digital Audio Editor

  AudacityApp.cpp

  Dominic Mazzoni

**********************************************************************/

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/defs.h>
#include <wx/app.h>
#include <wx/window.h>
#include <wx/intl.h>
#endif

#include <wx/fs_zip.h>
#include <wx/image.h>

#ifdef __WXGTK__
#include <unistd.h>
#endif

#ifdef __WXMAC__
# ifdef __UNIX__
#  include <ApplicationServices/ApplicationServices.h>
# else
#  include <AEDataModel.h>
#  include <AppleEvents.h>
# endif
#endif

#include "AudacityApp.h"
#include "AudioIO.h"
#include "Benchmark.h"
#include "effects/LoadEffects.h"
#include "FreqWindow.h"
#include "Help.h"
#include "Prefs.h"
#include "Project.h"
#include "WaveTrack.h"


class ToolBar;
class ControlToolBar;

#ifdef __WXGTK__
void wxOnAssert(const char *fileName, int lineNumber, const char *msg)
{
   if (msg)
      printf("ASSERTION FAILED: %s\n%s: %d\n", msg, fileName, lineNumber);
   else
      printf("ASSERTION FAILED!\n%s: %d\n", fileName, lineNumber);

   // Force core dump
   int *i = 0;
   if (*i)
      exit(1);

   exit(0);
}
#endif

wxFrame *gParentFrame = NULL;
wxWindow *gParentWindow = NULL;
ToolBarStub *gControlToolBarStub = NULL;
ToolBarStub *gEditToolBarStub = NULL;

void QuitAudacity()
{
   // Try to close each open window.  If the user hits Cancel
   // in a Save Changes dialog, don't continue.
   int len = gAudacityProjects.Count();
   for (int i = 0; i < len; i++) {
      if (!gAudacityProjects[i]->Close())
         return;
   }


   if (gFreqWindow)
      gFreqWindow->Destroy();


   if (gParentFrame)
      gParentFrame->Destroy();

   gFreqWindow = NULL;
   gParentFrame = NULL;



   if (gControlToolBarStub) {
      delete gControlToolBarStub;
      gControlToolBarStub = NULL;
   }

   if (gEditToolBarStub) {
      delete gEditToolBarStub;
      gEditToolBarStub = NULL;
   }


   QuitHelp();

   FinishPreferences();
}

IMPLEMENT_APP(AudacityApp)
#ifdef __WXMAC__
pascal OSErr AEQuit(const AppleEvent * theAppleEvent,
                    AppleEvent * theReply, long Refcon)
{
   QuitAudacity();
   return noErr;
}

/* prototype of MoreFiles fn, included in wxMac already */
#ifdef __UNIX__
extern "C" {
pascal OSErr FSpGetFullPath(const FSSpec * spec,
		     short *fullPathLength, Handle * fullPath);
};
#else
pascal OSErr FSpGetFullPath(const FSSpec * spec,
                            short *fullPathLength, Handle * fullPath);
#endif

pascal OSErr AEOpenFiles(const AppleEvent * theAppleEvent,
                         AppleEvent * theReply, long Refcon)
{
   AEDescList docList;
   AEKeyword keywd;
   DescType returnedType;
   Size actualSize;
   long itemsInList;
   FSSpec theSpec;
   CInfoPBRec pb;
   Handle nameh;
   short namelen;
   OSErr err;
   short i;

   err =
       AEGetParamDesc(theAppleEvent, keyDirectObject, typeAEList,
                      &docList);
   if (err != noErr)
      return err;

   err = AECountItems(&docList, &itemsInList);
   if (err != noErr)
      return err;

   for (i = 1; i <= itemsInList; i++) {
      AEGetNthPtr(&docList, i, typeFSS, &keywd, &returnedType,
                  (Ptr) & theSpec, sizeof(theSpec), &actualSize);

      if (noErr == FSpGetFullPath(&theSpec, &namelen, &nameh)) {
         HLock(nameh);
         char *str = new char[namelen + 1];
         memcpy(str, (char *) *nameh, namelen);
         str[namelen] = 0;
         HUnlock(nameh);
         DisposeHandle(nameh);

         AudacityProject *project = GetActiveProject();

         if (project == NULL || !project->GetTracks()->IsEmpty()) {
            project = CreateNewAudacityProject(gParentWindow);
         }
         project->OpenFile(str);

         delete[]str;
      }
   }

   return noErr;
}
#endif

BEGIN_EVENT_TABLE(AudacityApp, wxApp)
    EVT_CHAR(AudacityApp::OnKey)
END_EVENT_TABLE()

// The `main program' equivalent, creating the windows and returning the
// main frame
bool AudacityApp::OnInit()
{
   // mChecker = new wxSingleInstanceChecker(GetAppName());
   ::wxInitAllImageHandlers();

   wxFileSystem::AddHandler(new wxZipFSHandler);

   #ifdef __WXMSW__

   //BG: On Windows, associate the aup file type with Audacity
   {
      wxRegKey associateFileTypes;

      associateFileTypes.SetName("HKCR\\.AUP");
      associateFileTypes.Create(true);
      associateFileTypes = "Audacity.Project";

      associateFileTypes.SetName("HKCR\\Audacity.Project");
      associateFileTypes.Create(true);
      associateFileTypes = "Audacity Project File";

      associateFileTypes.SetName("HKCR\\Audacity.Project\\shell");
      associateFileTypes.Create(true);
      associateFileTypes = "";

      associateFileTypes.SetName("HKCR\\Audacity.Project\\shell\\open");
      associateFileTypes.Create(true);

      associateFileTypes.SetName("HKCR\\Audacity.Project\\shell\\open\\command");
      associateFileTypes.Create(true);
      associateFileTypes = (wxString)argv[0] + (wxString)" %1";
   }

   #endif

   InitPreferences();
   InitAudioIO();

   // Locale
   // wxWindows 2.3 has a much nicer wxLocale API.  We can make this code much
   // better once we move to wx 2.3/2.4.

   wxString lang = gPrefs->Read("/Locale/Language", "en");

   if (lang != "en") {
      mLocale = new wxLocale("", lang, "", true, true);
      mLocale->AddCatalog("audacity");
   } else
      mLocale = NULL;

   LoadEffects();

#ifdef __WXMAC__
   AEInstallEventHandler(kCoreEventClass,
                         kAEOpenDocuments,
                         NewAEEventHandlerUPP(AEOpenFiles), 0, 0);
   AEInstallEventHandler(kCoreEventClass,
                         kAEQuitApplication,
                         NewAEEventHandlerUPP(AEQuit), 0, 0);
#endif

   SetExitOnFrameDelete(true);

   //Initiate pointers to toolbars here, and create 
   //the toolbars that should be loaded at startup.


   //Initiate globally-held toolbar stubs here.
   gControlToolBarStub = new ToolBarStub(gParentWindow, ControlToolBarID);
   
   // Changing the following to NULL will make the application
   // load without the toolbar in memory at all.
   
   bool editToolBar;
   gPrefs->Read("/GUI/EnableEditToolBar", &editToolBar, true);
   if(editToolBar)
      gEditToolBarStub =  new ToolBarStub(gParentWindow, EditToolBarID);
   else
      gEditToolBarStub = NULL;


   InitFreqWindow(gParentWindow);
   AudacityProject *project = CreateNewAudacityProject(gParentWindow);
   SetTopWindow(project);

   // Can't handle command-line args on Mac OS X yet...
   #if !(defined(__WXMAC__) && defined(__UNIX__))

   // Parse command-line arguments

   if (argc > 1) {
      for (int option = 1; option < argc; option++) {
         if (!argv[option])
            continue;
         bool handled = false;

         if (!wxString("-help").CmpNoCase(argv[option])) {
            printf(_("Command-line options supported:\n"
                     "  -help (this message)\n"
                     "  -test (run self diagnostics)\n"
                     "  -blocksize ### (set max disk block size in bytes)\n"
                     "\n"
                     "In addition, specify the name of an audio file or "
                     "Audacity project\n" "to open it.\n" "\n"));
            exit(0);
         }

         if (option < argc - 1 &&
             argv[option + 1] &&
             !wxString("-blocksize").CmpNoCase(argv[option])) {
            long theBlockSize;
            if (wxString(argv[option + 1]).ToLong(&theBlockSize)) {
               if (theBlockSize >= 256 && theBlockSize < 100000000) {
                  fprintf(stderr, _("Using block size of %ld\n"),
                          theBlockSize);
                  WaveTrack::SetMaxDiskBlockSize(theBlockSize);
               }
            }
            option++;
            handled = true;
         }

         if (!handled && !wxString("-test").CmpNoCase(argv[option])) {
            RunBenchmark(NULL);
            exit(0);
         }

         if (argv[option][0] == '-' && !handled) {
            printf(_("Unknown command line option: %s\n"), argv[option]);
            exit(0);
         }

         if (!handled)
            project->OpenFile(argv[option]);

      }                         // for option...
   }                            // if (argc>1)

   #endif // not Mac OS X

   return TRUE;
}

void AudacityApp::OnKey(wxKeyEvent& event)
{
   AudacityProject *audacityPrj = GetActiveProject();
   wxString newStr = "";

   long key = event.GetKeyCode();

   if(event.ControlDown())
      newStr += "Ctrl+";

   if(event.AltDown())
      newStr += "Alt+";

   if(event.ShiftDown())
      newStr += "Shift+";

   if (event.ControlDown() && key >= 1 && key <= 26)
      newStr += (char)(64 + key);
   else if (key >= 33 && key <= 126)
      newStr += (char)key;
   else if (key == WXK_BACK)
      newStr = "Backspace";
   else if (key == WXK_DELETE)
      newStr = "Delete";
   else if (key == WXK_SPACE)
      newStr = "Spacebar";
   else
   {
      event.Skip();
      return; // Don't change it if we don't recognize the key
   }

   int commandIndex = audacityPrj->FindCommandByCombos(newStr);

   if(audacityPrj->GetCommandState(commandIndex) == enabledMenu)
   {
      audEventFunction audFunc = audacityPrj->GetCommandFunc(commandIndex);

      if(audFunc)
         (audacityPrj->*((wxEventFunction) audFunc))(event);
   }

   event.Skip();
}

int AudacityApp::OnExit()
{
   while(Pending())
   {
      Dispatch();
   }

//   delete mChecker;
   return 0;
}
