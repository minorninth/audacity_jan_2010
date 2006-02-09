/**********************************************************************

  Audacity: A Digital Audio Editor

  
  ControlToolbar.h
 
  Dominic Mazzoni
  Shane T. Mueller
 
  This class, which is a child of Toolbar, creates the
  window containing the tool selection (ibeam, envelope,
  move, zoom), the rewind/play/stop/record/ff buttons, and
  the volume control. The window can be embedded within a
  normal project window, or within a ToolbarFrame that is
  managed by a global ToolBarStub called
  gControlToolBarStub.

  All of the controls in this window were custom-written for
  Audacity - they are not native controls on any platform -
  however, it is intended that the images could be easily
  replaced to allow "skinning" or just customization to
  match the look and feel of each platform.

**********************************************************************/

#ifndef __AUDACITY_CONTROL_TOOLBAR__
#define __AUDACITY_CONTROL_TOOLBAR__

#include "ToolBar.h"

class AButton;
class ControlToolBar;
class ToolBar;
class AudacityProject;
class wxGridBagSizer;
class TrackList;

class wxImage;
class wxSize;
class wxPoint;

class ControlToolBar:public ToolBar {

 public:
   ControlToolBar() {};
   ControlToolBar(wxWindow * parent);
   virtual ~ControlToolBar();

   void UpdatePrefs();

   virtual void OnKeyEvent(wxKeyEvent & event);

   // msmeyer: These are public, but it's far better to
   // call the "real" interface functions like PlayCurrentRegion() and
   // StopPlaying() which are defined below.
   void OnRewind(wxCommandEvent &evt);
   void OnPlay(wxCommandEvent &evt);
   void OnStop(wxCommandEvent &evt);
   void OnBatch(wxCommandEvent &evt);
   void OnRecord(wxCommandEvent &evt);
   void OnFF(wxCommandEvent &evt);
   void OnPause(wxCommandEvent &evt);

   //These allow buttons to be controlled externally:
   void SetPlay(bool down);
   void SetStop(bool down);
   void SetRecord(bool down);

   // Play currently selected region, or if nothing selected,
   // play from current cursor.
   void PlayCurrentRegion(bool looped = false, bool cutpreview = false);

   // Play the region [t0,t1]
   void PlayPlayRegion(double t0, double t1,
                       bool looped = false,
                       bool cutpreview = false);

   // Stop playing
   void StopPlaying();

   void Populate();
   virtual void Repaint( wxDC *dc );
   virtual void EnableDisableButtons();

   void OnShiftDown(wxKeyEvent & event);
   void OnShiftUp(wxKeyEvent & event);

   void SetVUMeters(AudacityProject *p);

   DECLARE_EVENT_TABLE()
   ;
 private:

   AButton *MakeButton(char const **foreground, char const **disabled,
                       char const **alpha, int id, bool processdownevents,
                       const wxChar *label, const wxChar *tip);

   void MakeLoopImage();

   void ArrangeButtons();
   
   void SetupCutPreviewTracks(double playStart, double cutStart,
                             double cutEnd, double playEnd);
   void ClearCutPreviewTracks();

   enum
   {
      ID_PLAY_BUTTON,
      ID_RECORD_BUTTON,
      ID_PAUSE_BUTTON,
      ID_STOP_BUTTON,
      ID_FF_BUTTON,
      ID_REW_BUTTON,
      ID_BATCH_BUTTON,

      BUTTON_COUNT
   };

   AButton *mRewind;
   AButton *mPlay;
   AButton *mBatch;
   AButton *mRecord;
   AButton *mPause;
   AButton *mStop;
   AButton *mFF;

   static AudacityProject *mBusyProject;

   wxImage *upPattern;
   wxImage *downPattern;
   wxImage *hilitePattern;

   // Maybe button state values shouldn't be duplicated in this toolbar?
   bool mPaused;         //Play or record is paused or not paused?
   bool mAlwaysEnablePause;
   
   // Activate ergonomic order for transport buttons
   bool mErgonomicTransportButtons;

   // Show/hide cleanspeech button
   bool mCleanSpeechMode;

   wxBoxSizer *mBatchGroup;
   wxBoxSizer *mSizer;

   TrackList* mCutPreviewTracks;
};

#endif

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: bb2858b8-2c70-48df-9d72-bcdef94be4e3

