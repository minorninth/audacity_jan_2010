/**********************************************************************

  Audacity: A Digital Audio Editor

  Project.cpp

  Dominic Mazzoni

  In Audacity, the main window you work in is called a project.
  AudacityProjects can contain an arbitrary number of tracks of many
  different types, but if a project contains just one or two
  tracks then it can be saved in standard formats like WAV or AIFF.
  This window is the one that contains the menu bar (except on
  the Mac).

**********************************************************************/

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/app.h>
#include <wx/dc.h>
#include <wx/dcmemory.h>
#include <wx/string.h>
#endif

#ifndef __WXMAC__
#include <wx/dragimag.h>
#endif

#include <wx/filedlg.h>
#include <wx/msgdlg.h>
#include <wx/textfile.h>

#include "AudacityApp.h"
#include "AColor.h"
#include "APalette.h"
#include "AudioIO.h"
#include "FreqWindow.h"
#include "Import.h"
#include "ImportMP3.h"
#include "ImportOGG.h"

#include "LabelTrack.h"
#include "Mix.h"
#include "NoteTrack.h"
#include "Prefs.h"
#include "Project.h"
#include "Track.h"
#include "TrackPanel.h"
#include "WaveTrack.h"
#include "effects/Effect.h"

TrackList *AudacityProject::msClipboard = new TrackList();
double     AudacityProject::msClipLen = 0.0;

#ifdef __WXMAC__
const int sbarSpaceWidth = 15;
const int sbarControlWidth = 16;
const int sbarExtraLen = 1;
#endif
#ifdef __WXMSW__
const int sbarSpaceWidth = 16;
const int sbarControlWidth = 16;
const int sbarExtraLen = 0;
#endif
#ifdef __WXGTK__
const int sbarSpaceWidth = 15;
const int sbarControlWidth = 15;
const int sbarExtraLen = 0;
#endif

#if defined(__WXGTK__) || defined(__WXMOTIF__)
#include "xpm/AudacityLogo.xpm"
#endif

int gAudacityDocNum = 0;
AProjectArray gAudacityProjects;
AudacityProject *gActiveProject;

AudacityProject *GetActiveProject()
{
  return gActiveProject;
}

void SetActiveProject(AudacityProject *project)
{
  gActiveProject = project;
  wxTheApp->SetTopWindow(project);
}

AudacityProject *CreateNewAudacityProject(wxWindow *parentWindow)
{
  wxPoint where;
  where.x = 10;
  where.y = 10;

  int width = 600;
  int height = 400;

  if (gWindowedPalette) {
	where.y += 75;
	height -= 75;
  }

  #ifdef __WXMAC__
  where.y += 50;
  #endif

  where.x += gAudacityDocNum*25;
  where.y += gAudacityDocNum*25;

  AudacityProject *p =
	new AudacityProject(parentWindow, -1, 
						where, wxSize(width, height));

  p->Show(true);

  gAudacityDocNum = (gAudacityDocNum+1)%10;

  SetActiveProject(p);

  return p;
}

void RedrawAllProjects()
{
  int len = gAudacityProjects.Count();
  for(int i=0; i<len; i++)
	gAudacityProjects[i]->RedrawProject();
}

enum {
  FirstID = 1000,

  // Window controls

  HSBarID,
  VSBarID,
  TrackPanelID
};

#define AUDACITY_MENUS_ENUM
#include "Menus.h"
#undef AUDACITY_MENUS_ENUM

BEGIN_EVENT_TABLE(AudacityProject, wxFrame)
  EVT_MOUSE_EVENTS(AudacityProject::OnMouseEvent)
  EVT_PAINT(AudacityProject::OnPaint)
  EVT_CLOSE(AudacityProject::OnCloseWindow)
  EVT_SIZE (AudacityProject::OnSize)
  EVT_ACTIVATE (AudacityProject::OnActivate)
  EVT_COMMAND_SCROLL  (HSBarID,   AudacityProject::OnScroll)
  EVT_COMMAND_SCROLL  (VSBarID,   AudacityProject::OnScroll)

  #define AUDACITY_MENUS_EVENT_TABLE
  #include "Menus.h"
  #undef AUDACITY_MENUS_EVENT_TABLE
  
END_EVENT_TABLE()

AudacityProject::AudacityProject(wxWindow *parent, wxWindowID id,
								 const wxPoint& pos, const wxSize& size) :
  wxFrame(parent, id, "Audacity", pos, size),
  mDirty(false),
  mTrackPanel(NULL),
  mAPalette(NULL),
  mRate((double)gPrefs->Read("/SamplingRate/DefaultProjectSampleRate", 44100)),
  mDrag(NULL),
  mAutoScrolling(false)
{

  //
  // Create track list
  //
  
  mTracks = new TrackList();
  mLastSavedTracks = NULL;

  //
  // Initialize view info (shared with TrackPanel)
  //

  // Selection
  mViewInfo.sel0 = 0.0;
  mViewInfo.sel1 = 0.0;

  // Horizontal scrollbar
  mViewInfo.total = 1.0;
  mViewInfo.screen = 1.0;
  mViewInfo.h = 0.0;
  mViewInfo.zoom = 44100.0 / 512.0;
  mViewInfo.lastZoom = mViewInfo.zoom;

  // Vertical scrollbar
  mViewInfo.vpos = 0;

  mViewInfo.scrollStep = 16;

  mViewInfo.sbarH = 0;
  mViewInfo.sbarScreen = 1;
  mViewInfo.sbarTotal = 1;

  CreateMenuBar();

  int left=0, top=0, width, height;
  GetClientSize(&width, &height);

  //
  // Create the Palette (if we're not using a windowed palette)
  // 

  if (!gWindowedPalette) {
	int h = GetAPaletteHeight();

  int ptop = 0;
  #ifdef __WXMSW__
    ptop++;
  #endif

	mAPalette = new APalette(this, 0,
							 wxPoint(10, ptop),
							 wxSize(width-10, h));
	
	top += h+1+ptop;
	height -= h+1+ptop;
  }

  //
  // Create the status bar
  //

  int sh = GetStatusHeight();

  mStatus = new AStatus(this, 0,
						wxPoint(0, height-sh),
						wxSize(width, sh),
						mRate,
						this);
  height -= sh;

  mStatus->SetField("Welcome to Audacity version " 
					AUDACITY_VERSION_STRING, 0);

  //
  // Create the TrackPanel and the scrollbars
  //

  mTrackPanel = new TrackPanel(this, TrackPanelID,
							   wxPoint(left, top),
							   wxSize(width-sbarSpaceWidth, height-sbarSpaceWidth),
							   mTracks, &mViewInfo,
							   this);

  int hoffset = mTrackPanel->GetLabelOffset()-1;
  int voffset = mTrackPanel->GetRulerHeight();
  
  #ifdef __WXMAC__
  width++;
  height++;
  #endif
  
  mHsbar =
	new wxScrollBar(this, HSBarID, 
					wxPoint(hoffset, top+height-sbarSpaceWidth),
					wxSize(width-hoffset-sbarSpaceWidth+sbarExtraLen, sbarControlWidth),
					wxSB_HORIZONTAL);

  mVsbar =
	new wxScrollBar(this, VSBarID,
					wxPoint(width-sbarSpaceWidth, top+voffset),
					wxSize(sbarControlWidth, height-sbarSpaceWidth-voffset+sbarExtraLen),
					wxSB_VERTICAL);

  InitialState();
  FixScrollbars();

  //
  // Set the Icon
  //

  // loads either the XPM or the windows resource, depending on the platform
  wxIcon ic(wxICON(AudacityLogo)); 
  SetIcon(ic);

  // Min size, max size
  SetSizeHints(250,200,20000,20000);

  gAudacityProjects.Add(this);
}

AudacityProject::~AudacityProject()
{
  // TODO delete mTracks;

  gAudacityProjects.Remove(this);

  if (gAudacityProjects.IsEmpty())
	QuitAudacity();
}

void AudacityProject::RedrawProject()
{
  FixScrollbars();
  mTrackPanel->Refresh(false);
}

DirManager *AudacityProject::GetDirManager()
{
  return &mDirManager;
}

wxString AudacityProject::GetName()
{
  wxString n = mName;

  return n;
}

double AudacityProject::GetRate()
{
  return mRate;
}

void AudacityProject::AS_SetRate(double rate)
{
  mRate = rate;
}

double AudacityProject::GetSel0()
{
  return mViewInfo.sel0;
}

double AudacityProject::GetSel1()
{
  return mViewInfo.sel1;
}

TrackList *AudacityProject::GetTracks()
{
  return mTracks;
}

APalette *AudacityProject::GetAPalette()
{
  if (mAPalette)
	return mAPalette;
  else
	return &(gAPaletteFrame->mPalette);
}

void AudacityProject::FinishAutoScroll()
{
  // Set a flag so we don't have to generate two update events
  mAutoScrolling = true;

  // Call our Scroll method which updates our ViewInfo variables
  // to reflect the positions of the scrollbars
  wxScrollEvent *dummy = new wxScrollEvent();
  OnScroll(*dummy);
  delete dummy;

  mAutoScrolling = false;
}

void AudacityProject::OnScrollLeft()
{
  int pos = mHsbar->GetThumbPosition();
  int max = mHsbar->GetRange() - mHsbar->GetThumbSize();

  if (pos > 0) {
	mHsbar->SetThumbPosition(pos-1);
	FinishAutoScroll();
  }
}

void AudacityProject::OnScrollRight()
{
  int pos = mHsbar->GetThumbPosition();
  int max = mHsbar->GetRange() - mHsbar->GetThumbSize();

  if (pos < max) {
	mHsbar->SetThumbPosition(pos+1);
	FinishAutoScroll();
  }
}

void AudacityProject::FixScrollbars()
{
  bool rescroll = false;

  int totalHeight = (mTracks->GetHeight() + 32);

  int panelWidth, panelHeight;
  mTrackPanel->GetTracksUsableArea(&panelWidth, &panelHeight);

  mViewInfo.total = mTracks->GetMaxLen() + 1.0;
  mViewInfo.screen = ((double)panelWidth) / mViewInfo.zoom;

  if (mViewInfo.h > mViewInfo.total - mViewInfo.screen) {
  	mViewInfo.h = mViewInfo.total - mViewInfo.screen;
  	rescroll = true;
  }
  if (mViewInfo.h < 0.0) {
  	mViewInfo.h = 0.0;
  	rescroll = true;
  }

  mViewInfo.sbarTotal = (int)(mViewInfo.total * mViewInfo.zoom)
	/ mViewInfo.scrollStep;
  mViewInfo.sbarScreen = (int)(mViewInfo.screen * mViewInfo.zoom)
	/ mViewInfo.scrollStep;

  mViewInfo.sbarH = (int)(mViewInfo.h * mViewInfo.zoom)
	/ mViewInfo.scrollStep;

  mViewInfo.vpos =
	mVsbar->GetThumbPosition() * mViewInfo.scrollStep;

  if (mViewInfo.vpos >= totalHeight)
	mViewInfo.vpos = totalHeight-1;
  if (mViewInfo.vpos < 0)
	mViewInfo.vpos = 0;

  #ifdef __WXGTK__
  mHsbar->Show(mViewInfo.screen < mViewInfo.total);
  mVsbar->Show(panelHeight < totalHeight);
  #else
  mHsbar->Enable(mViewInfo.screen < mViewInfo.total);
  mVsbar->Enable(panelHeight < totalHeight);
  #endif

  if (panelHeight >= totalHeight && mViewInfo.vpos != 0) {
	mViewInfo.vpos = 0;
	mTrackPanel->Refresh();
	//REDRAW(trackPanel);
	//REDRAW(rulerPanel);
	rescroll = false;
  }
  if (mViewInfo.screen >= mViewInfo.total && mViewInfo.sbarH != 0) {
	mViewInfo.sbarH = 0;
	mTrackPanel->Refresh();
	//REDRAW(trackPanel);
	//REDRAW(rulerPanel);
	rescroll = false;
  }

  mHsbar->SetScrollbar(mViewInfo.sbarH, mViewInfo.sbarScreen,
					   mViewInfo.sbarTotal, mViewInfo.sbarScreen, TRUE);
  mVsbar->SetScrollbar(mViewInfo.vpos / mViewInfo.scrollStep,
					   panelHeight / mViewInfo.scrollStep,
					   totalHeight / mViewInfo.scrollStep,
					   panelHeight / mViewInfo.scrollStep,
					   TRUE);

  mViewInfo.lastZoom = mViewInfo.zoom;
  
  if (rescroll && mViewInfo.screen < mViewInfo.total) {
	mTrackPanel->Refresh();
	//REDRAW(trackPanel);
	//REDRAW(rulerPanel);
  }
}

void AudacityProject::HandleResize()
{
  if (mTrackPanel) {
	
	int left=0, top=0;
    int width, height;
    GetClientSize(&width, &height);

	if (!gWindowedPalette) {
	  int h = GetAPaletteHeight();

    int ptop = 0;
    #ifdef __WXMSW__
        ptop++;
    #endif
	  
	  mAPalette->SetSize(10, ptop, width-10, h);
	  
	  top += h+1+ptop;
	  height -= h+1+ptop;
	}

	int sh = GetStatusHeight();

	mStatus->SetSize(0, top+height-sh,
					 width, sh);
	height -= sh;

    mTrackPanel->SetSize(left, top,
  					     width-sbarSpaceWidth, height-sbarSpaceWidth);

    int hoffset = mTrackPanel->GetLabelOffset()-1;
    int voffset = mTrackPanel->GetRulerHeight();

    mHsbar->SetSize(hoffset, top+height-sbarSpaceWidth,
				    width-hoffset-sbarSpaceWidth+sbarExtraLen, sbarControlWidth);
    mVsbar->SetSize(width-sbarSpaceWidth, top+voffset-sbarExtraLen,
				    sbarControlWidth, height-sbarSpaceWidth-voffset+2*sbarExtraLen);

    FixScrollbars();
  }
}

void AudacityProject::OnSize(wxSizeEvent &event)
{
  HandleResize();
}

void AudacityProject::OnScroll(wxScrollEvent &event)
{
  int  hlast = mViewInfo.sbarH;
  int  vlast = mViewInfo.vpos;
  int  hoffset = 0;
  int  voffset = 0;

  mViewInfo.sbarH = mHsbar->GetThumbPosition();

  if (mViewInfo.sbarH != hlast) {
	  mViewInfo.h = (mViewInfo.sbarH * mViewInfo.scrollStep) / mViewInfo.zoom;
	  if (mViewInfo.h > mViewInfo.total - mViewInfo.screen)
		  mViewInfo.h = mViewInfo.total - mViewInfo.screen;
	  if (mViewInfo.h < 0.0)
		  mViewInfo.h = 0.0;
		hoffset = (mViewInfo.sbarH - hlast) * mViewInfo.scrollStep;
  }

  mViewInfo.vpos = mVsbar->GetThumbPosition() * mViewInfo.scrollStep;
  voffset = mViewInfo.vpos - vlast;

  /*
	TODO: add back fast scrolling code

	// Track panel is updated either way, but it is smart and only redraws
	// what is needed
	trackPanel->FastScroll(-hoffset, -voffset);
	
	// Ruler panel updated if we scroll horizontally
	if (hoffset) {
      REDRAW(rulerPanel);
	}
  */

  SetActiveProject(this);

  if (!mAutoScrolling) {
	mTrackPanel->Refresh(false);
    #ifdef __WXMAC__
	  mTrackPanel->MacUpdateImmediately();
    #endif
  }
}

bool AudacityProject::ProcessEvent(wxEvent& event)
{
  int numEffects = Effect::GetNumEffects();

  if (event.GetEventType() == wxEVT_COMMAND_MENU_SELECTED &&
      event.GetId() >= FirstEffectID &&
      event.GetId() < FirstEffectID + numEffects) {

	TrackListIterator iter(mTracks);
    VTrack *t = iter.First();
    int count = 0;

    while(t) {
      if (t->selected && t->GetKind() == (VTrack::Wave))
        count++;      
      t = iter.Next();
    }

    if (count==0 || mViewInfo.sel0 == mViewInfo.sel1) {
      wxMessageBox("No audio data is selected.");
      return true;
    }

    Effect *f = Effect::GetEffect(event.GetId() - FirstEffectID);

    if (!f->Begin(this))
        return true;

    int index = 0;

    t = iter.First();

    while(t) {
      if (t->selected && t->GetKind() == (VTrack::Wave)) {

        bool success = f->DoInPlaceEffect((WaveTrack *)t,
                            mViewInfo.sel0, mViewInfo.sel1,
                            index, count);

        if (!success) {
            wxMessageBox("Effect unsuccessful.");
            break;
        }
      }
      
      t = iter.Next();
    }

    f->End();
    
    PushState();
    
    FixScrollbars();

	mTrackPanel->Refresh(false);
    
    // This indicates we handled the event.
    return true;
  }

  return wxFrame::ProcessEvent(event);
}

void AudacityProject::OnPaint(wxPaintEvent& event)
{
  // Draw a colored strip on the right and bottom edges of
  // the window to fill in the small area not covered by
  // the TrackPanel or the scrollbars.

  wxPaintDC dc(this);
  int width, height;
  GetClientSize(&width, &height);
    
  AColor::Medium(&dc, false);

  int top = 0;

  if (!gWindowedPalette) {
	int h = GetAPaletteHeight();

#ifdef __WXMSW__
  h++;
#endif
	
	top += h+1;
	height -= h+1;
  }

  int sh = GetStatusHeight();
  height -= sh;  
  
  wxRect r;
  r.x = width-sbarSpaceWidth;
  r.y = 0;
  r.width = sbarSpaceWidth;
  r.height = height;
  dc.DrawRectangle(r);
  
  // If we're displaying the palette inside the window,
  // draw little bumps to the left of the palette to
  // indicate it's grabable

  if (!gWindowedPalette) {
	int h = GetAPaletteHeight();

	r.x = 0;
	r.y = 0;
	r.width = 10;
	r.height = h;
	dc.DrawRectangle(r);

	int i;

	AColor::Light(&dc, false);
	for(i=h/2-20; i<h/2+20; i+=4)
	  dc.DrawLine(3,i,6,i);
	AColor::Dark(&dc, false);
	for(i=h/2-19; i<h/2+21; i+=4)
	  dc.DrawLine(3,i,6,i);

	dc.SetPen(*wxBLACK_PEN);
	dc.DrawLine(9, 0, 9, h);

#ifdef __WXMSW__
	dc.DrawLine(0, 0, width, 0);
        dc.DrawLine(0, 0, 0, h);
#endif

  dc.DrawLine(0, h, width, h);
  }

  // Fill in space on sides of scrollbars

  dc.SetPen(*wxBLACK_PEN);
  dc.DrawLine(width-sbarSpaceWidth, top,
			  width-sbarSpaceWidth, top+height-sbarSpaceWidth+1);
  dc.DrawLine(0, top+height-sbarSpaceWidth,
			  width-sbarSpaceWidth, top+height-sbarSpaceWidth);

  wxRect f;
  f.x = 0;
  f.y = top+height-sbarSpaceWidth+1;
  f.width = mTrackPanel->GetLabelOffset()-2;
  f.height = sbarSpaceWidth-2;
  AColor::Medium(&dc, false);
  dc.DrawRectangle(f);
  AColor::Bevel(dc, true, f);
}

void AudacityProject::OnActivate(wxActivateEvent& event)
{
  SetActiveProject(this);
  
  event.Skip();
}

void AudacityProject::ShowPalette()
{
  if (!mAPalette) {
	int h = GetAPaletteHeight();

	int width, height;
	GetSize(&width, &height);
	
	mAPalette = new APalette(this, 52,
							 wxPoint(10, 0),
							 wxSize(width-10, h));
  }
  HandleResize();
}

void AudacityProject::HidePalette()
{
  if (mAPalette) {
	delete mAPalette;
	mAPalette = NULL;
  }
  HandleResize();
}

void AudacityProject::OnMouseEvent(wxMouseEvent& event)
{
  SetActiveProject(this);

  wxPoint hotspot;
  hotspot.x = event.m_x;
  hotspot.y = event.m_y;

  wxPoint mouse = ClientToScreen(hotspot);

  if (event.ButtonDown() && !mDrag &&
	  !gWindowedPalette &&
	  event.m_x<10 && event.m_y < GetAPaletteHeight()) {

	int width, height;
	mAPalette->GetSize(&width, &height);

    #ifdef __WXMAC__
    
    Point startPt;
    startPt.h = hotspot.x;
    startPt.v = hotspot.y;
    Rect limitRect, slopRect, r;
    SetRect(&limitRect, -32767,-32767,32767,32767);
    SetRect(&slopRect, -32767,-32767,32767,32767);
    SetRect(&r, 10, 0, 10+width, height);
    int axis = noConstraint;
    RgnHandle theRgn = NewRgn();
    RectRgn(theRgn, &r);

    int result = DragGrayRgn(theRgn, startPt, &limitRect, &slopRect, axis, NULL);
    
    if (result == 0x80008000)
      return;
    
    mouse -= hotspot;
    mouse.x += (short)(result & 0xFFFF);
    mouse.y += (short)((result & 0xFFFF0000)>>16);
    
    ShowWindowedPalette(&mouse);
    
    #else

	wxClientDC dc(this);

	wxBitmap *bitmap = new wxBitmap(width, height);
	wxMemoryDC *memDC = new wxMemoryDC();
	memDC->SelectObject(*bitmap);
	memDC->Blit(0, 0, width, height, &dc, 10, 0);
    delete memDC;

	mDrag = new wxDragImage(*bitmap);

    delete bitmap;

	mDrag->BeginDrag(hotspot, this, true);
	mDrag->Move(mouse);
	mDrag->Show();
	mPaletteHotspot = hotspot;
	
	#endif
  }

  #ifndef __WXMAC__
  if (event.Dragging() && mDrag) {
	mDrag->Move(mouse);
  }
  
  if (event.ButtonUp() && mDrag) {
	mDrag->Hide();
	mDrag->EndDrag();
	delete mDrag;
	mDrag = NULL;

	mouse -= mPaletteHotspot;
	ShowWindowedPalette(&mouse);
  }
  #endif
}

void AudacityProject::OnClose(wxCommandEvent& event)
{
  Destroy();
}

void AudacityProject::OnCloseWindow(wxCloseEvent& event)
{
  Destroy();
}

void AudacityProject::OpenFile(wxString fileName)
{
#ifdef MP3SUPPORT
  // Check for .MP3 suffix

  if (!fileName.Right(3).CmpNoCase("mp3")) {
    if (mDirty || !mTracks->IsEmpty()) {
	    AudacityProject *project = CreateNewAudacityProject(gParentWindow);
	    project->ImportMP3(fileName);
      return;
    }
    else {
	    ImportMP3(fileName);
		if (!mTracks->IsEmpty()) {
		  mFileName = fileName;
		  mName = wxFileNameFromPath(mFileName);
		  SetTitle(mName);
		}
	    return;
    }
  }
#endif /* MP3SUPPORT */

#ifdef USE_LIBVORBIS
  // Check for .OGG suffix

  if (!fileName.Right(3).CmpNoCase("ogg")) {
    if (mDirty || !mTracks->IsEmpty()) {
	    AudacityProject *project = CreateNewAudacityProject(gParentWindow);
	    project->ImportOGG(fileName);
      return;
    }
    else {
	    ImportOGG(fileName);
		if (!mTracks->IsEmpty()) {
		  mFileName = fileName;
		  mName = wxFileNameFromPath(mFileName);
		  SetTitle(mName);
		}
	    return;
    }
  }
#endif /* USE_LIBVORBIS */

  // Check for .WAV, .AIFF, .AIF, .AU, or .IRCAM suffix

  if (!fileName.Right(3).CmpNoCase("wav") ||
      !fileName.Right(4).CmpNoCase("aiff") ||
      !fileName.Right(3).CmpNoCase("aif") ||
      !fileName.Right(2).CmpNoCase("au") ||
      !fileName.Right(3).CmpNoCase("snd") ||
      !fileName.Right(5).CmpNoCase("ircam")) {
    if (mDirty || !mTracks->IsEmpty()) {
	    AudacityProject *project = CreateNewAudacityProject(gParentWindow);
#ifdef MP3SUPPORT
	    project->ImportMP3(fileName);
#endif
      return;
    }
    else {
	    ImportFile(fileName);
      if (!mTracks->IsEmpty()) {
        mFileName = fileName;
        mName = wxFileNameFromPath(mFileName);
        SetTitle(mName);
      }
	    return;
    }
  }
  
  // If it didn't end in any of those extensions, next we check to see
  // if it's a project file (should end in .aup, but we don't care).

  // We want to open projects using wxTextFile, but if it's NOT a project
  // file (but actually a WAV file, for example), then wxTextFile will spin
  // for a long time searching for line breaks.  So, we look for our signature
  // at the beginning of the file first:

  bool isProjectFile;
  wxString firstLine = "AudacityProject";
  char temp[16];

  wxFile ff(fileName);
  if (!ff.IsOpened()) {
    wxMessageBox("Couldn't open "+mFileName);
    return;
  }
  ff.Read(temp, 15);
  temp[15] = 0;
  isProjectFile = (firstLine == temp);
  ff.Close();

  // If we think it's a project file, try to open it using wxTextFile

  wxTextFile f;

  if (isProjectFile) {
    f.Open(fileName);
    if (!f.IsOpened()) {
	  wxMessageBox("Couldn't open "+mFileName);
	  return;
    }
  }

  // If not, try to import it as a WAV file or some other recognized format

  if (!isProjectFile || f.GetFirstLine() != firstLine) {
    f.Close();
    if (mDirty || !mTracks->IsEmpty()) {
	    AudacityProject *project = CreateNewAudacityProject(gParentWindow);
	    project->ImportFile(fileName);
      return;
    }
    else {
	    ImportFile(fileName);
      if (!mTracks->IsEmpty()) {
        mFileName = fileName;
        mName = wxFileNameFromPath(mFileName);
        SetTitle(mName);
      }

      // TODO:
      // If we get here, we have no idea what the file format is.
      // Later this could pop up the "Import Raw Data..." dialog.

	    return;
    }
  }

  mFileName = fileName;
  mName = wxFileNameFromPath(mFileName);
  SetTitle(mName);

  ///
  /// Parse project file
  ///

  wxString projName;
  wxString projPath;
  wxString version;
  long longVpos;

  if (f.GetNextLine() != "Version") goto openFileError;
  version = f.GetNextLine();
  if (version != AUDACITY_FILE_FORMAT_VERSION &&
	  version != "0.9") {
	wxMessageBox("This project was saved by a different version of "
				 "Audacity and is no longer supported.");
	return;
  }

  if (f.GetNextLine() != "projName") goto openFileError;
  projName = f.GetNextLine();
  projPath = wxPathOnly(mFileName);
  if (!mDirManager.SetProject(projPath, projName, false)) return;

  if (f.GetNextLine() != "sel0") goto openFileError;
  if (!(f.GetNextLine().ToDouble(&mViewInfo.sel0))) goto openFileError;
  if (f.GetNextLine() != "sel1") goto openFileError;
  if (!(f.GetNextLine().ToDouble(&mViewInfo.sel1))) goto openFileError;
  if (f.GetNextLine() != "vpos") goto openFileError;
  if (!(f.GetNextLine().ToLong(&longVpos))) goto openFileError;
  mViewInfo.vpos = longVpos;
  if (f.GetNextLine() != "h") goto openFileError;
  if (!(f.GetNextLine().ToDouble(&mViewInfo.h))) goto openFileError;
  if (f.GetNextLine() != "zoom") goto openFileError;
  if (!(f.GetNextLine().ToDouble(&mViewInfo.zoom))) goto openFileError;
  if (version != "0.9") {
	if (f.GetNextLine() != "rate") goto openFileError;
	if (!(f.GetNextLine().ToDouble(&mRate))) goto openFileError;
	mStatus->SetRate(mRate);
  }

  mTracks->Clear();
  InitialState();

  mTracks->Load(&f, &mDirManager);

  // By making a duplicate set of pointers to the existing blocks
  // on disk, we add one to their reference count, guaranteeing
  // that their reference counts will never reach zero and thus
  // the version saved on disk will be preserved until the
  // user selects Save().

  if (1) {
	VTrack *t;
	TrackListIterator iter(mTracks);
	mLastSavedTracks = new TrackList();
	t = iter.First();
	while(t) {
	  mLastSavedTracks->Add(t->Duplicate());
	  t = iter.Next();
	}
  }

  f.Close();

  FixScrollbars();
  mTrackPanel->Refresh(false);

  return;

openFileError:
  wxMessageBox(wxString::Format(
    "Error reading Audacity Project %s in line %d",
	(const char *)mFileName,
	f.GetCurrentLine()));
  f.Close();
  return;
}

void AudacityProject::Save(bool overwrite /* = true */,
						   bool fromSaveAs /* = false */)
{
  if (!fromSaveAs && mDirManager.GetProjectName() == "") {
	SaveAs();
	return;
  }

  //
  // Always save a backup of the original project file
  //

  wxString safetyFileName = "";
  if (wxFileExists(mFileName)) {

	#ifdef __WXGTK__
	safetyFileName = mFileName+"~";
	#else
	safetyFileName = mFileName+".bak";
	#endif

	if (wxFileExists(safetyFileName))
	  wxRemoveFile(safetyFileName);

	wxRename(mFileName, safetyFileName);
  }

  wxString project = mFileName;
  if (project.Len() > 4 && project.Mid(project.Len()-4)==".aup")
	project = project.Mid(0, project.Len()-4);
  wxString projName = wxFileNameFromPath(project) + "_data";
  wxString projPath = wxPathOnly(project);
  bool success = mDirManager.SetProject(projPath, projName, !overwrite);

  if (!success) {
	wxMessageBox(wxString::Format(
	  "Could not save project because the directory %s could not be created.",
      (const char *)project));

	if (safetyFileName)
	  wxRename(safetyFileName, mFileName);

	return;
  }

  wxTextFile f(mFileName);
  #ifdef __WXMAC__
  wxFile *temp = new wxFile();
  temp->Create(mFileName);
  delete temp;
  #else
  f.Create();
  #endif
  f.Open();
  if (!f.IsOpened()) {
	wxMessageBox("Couldn't write to "+mFileName);

	if (safetyFileName)
	  wxRename(safetyFileName, mFileName);

	return;
  }

  f.AddLine("AudacityProject");
  f.AddLine("Version");
  f.AddLine(AUDACITY_FILE_FORMAT_VERSION);
  f.AddLine("projName");
  f.AddLine(projName);
  f.AddLine("sel0");
  f.AddLine(wxString::Format("%g", mViewInfo.sel0));
  f.AddLine("sel1");
  f.AddLine(wxString::Format("%g", mViewInfo.sel1));
  f.AddLine("vpos");
  f.AddLine(wxString::Format("%d", mViewInfo.vpos));
  f.AddLine("h");
  f.AddLine(wxString::Format("%g", mViewInfo.h));
  f.AddLine("zoom");
  f.AddLine(wxString::Format("%g", mViewInfo.zoom));
  f.AddLine("rate");
  f.AddLine(wxString::Format("%g", mRate));

  f.AddLine("BeginTracks");

  mTracks->Save(&f, overwrite);

#ifdef __WXMAC__
  f.Write(wxTextFileType_Mac);
#else
  f.Write();
#endif
  f.Close();
  
#ifdef __WXMAC__
  FSSpec spec ;

	wxUnixFilename2FSSpec( mFileName , &spec ) ;
	FInfo finfo ;
	if ( FSpGetFInfo( &spec , &finfo ) == noErr )
	{
		finfo.fdType = AUDACITY_PROJECT_TYPE;
		finfo.fdCreator = AUDACITY_CREATOR;
		FSpSetFInfo( &spec , &finfo ) ;
	}
#endif

  if (mLastSavedTracks) {

	TrackListIterator iter(mLastSavedTracks);
	VTrack *t = iter.First();
	while(t) {
	  if (t->GetKind() == VTrack::Wave && !overwrite)
		((WaveTrack *)t)->DeleteButDontDereference();
	  else
		delete t;
	  t = iter.Next();
	}

	delete mLastSavedTracks;
  }

  mLastSavedTracks = new TrackList();
  TrackListIterator iter(mTracks);
  VTrack *t = iter.First();
  while(t) {
    mLastSavedTracks->Add(t->Duplicate());
    t = iter.Next();
  }

  mStatus->SetField(wxString::Format("Saved %s",
									 (const char *)mFileName), 0);
}

void AudacityProject::SaveAs()
{
  wxString fName = mFileName;
  if (fName == "")
    fName = ".aup";

  fName = wxFileSelector("Save Project As:",
                         NULL,
                         fName,
                         "aup",
                         "*.aup",
                         wxSAVE,
                         this);

  // wxString fName = wxSaveFileSelector("", "aup");

  if (fName == "")
	return;

  mFileName = fName;
  mName = wxFileNameFromPath(mFileName);
  SetTitle(mName);

  Save(false, true);
}

void AudacityProject::ImportFile(wxString fileName)
{
  WaveTrack *left = 0;
  WaveTrack *right = 0;

  if (ImportWAV(this, fileName, &left, &right, &mDirManager)) {

	if (left || right) {

	  SelectNone();

	  if (mTracks->IsEmpty()) {
		if (left)
		  mRate = left->rate;
		else
		  mRate = right->rate;

		mStatus->SetRate(mRate);
	  }
	  else {
		if ((left && left->rate != mRate) ||
			(right && right->rate != mRate)) {
		  wxMessageBox("Warning: your file has multiple sampling rates.  "
					   "Audacity will ignore any track which is not at "
					   "the same sampling rate as the project.");
		}
	  }

	}

	if (left) {
	  if (right) {
		left->channel = VTrack::LeftChannel;
		right->channel = VTrack::RightChannel;
	  }
	  else
		left->channel = VTrack::MonoChannel;
	}
	else
	  right->channel = VTrack::MonoChannel;

    if (left) {
      mTracks->Add(left);
	  left->selected = true;
    }

    if (right) {
      mTracks->Add(right);
	  right->selected = true;
    }

    PushState();
	
	ZoomFit();
  }
}

#ifdef MP3SUPPORT
void AudacityProject::ImportMP3(wxString fileName)
{
  WaveTrack *left = 0;
  WaveTrack *right = 0;

  if (::ImportMP3(this, fileName, &left, &right, &mDirManager)) {

    if (left || right) {
      SelectNone();
    }
    
    if (left) {
      mTracks->Add(left);
      left->selected = true;
    }
    
    if (right) {
      mTracks->Add(right);
      right->selected = true;
    }
    
    PushState();
    
	ZoomFit();

  }
}
#endif /* MP3SUPPORT */

#ifdef USE_LIBVORBIS
void AudacityProject::ImportOGG(wxString fileName)
{
	WaveTrack **channels = 0;
	int numChannels = 0;

	if(::ImportOGG(this, fileName, &channels, &numChannels, &mDirManager)) {
		for(int c = 0; c < numChannels; c++) {
			mTracks->Add(channels[c]);
			channels[c]->selected = true;
		}
		
		// TODO: delete array of channels (does this occur anywhere else?)

		PushState();

		ZoomFit();
	}
}
#endif /* USE_LIBVORBIS */

//
// Zoom methods
//

void AudacityProject::ZoomFit()
{
  double len = mTracks->GetMaxLen();
  int w, h;
  mTrackPanel->GetTracksUsableArea(&w, &h);
  w -= 10;
  
  mViewInfo.zoom = w / len;
  FixScrollbars();
  mTrackPanel->Refresh(false);
}

//
// Undo/History methods
//

void AudacityProject::InitialState()
{
  mUndoManager.ClearStates();
  PushState(false);
}

void AudacityProject::PushState(bool makeDirty /* = true */)
{
  TrackList *l = new TrackList(mTracks);

  mUndoManager.PushState(l, mViewInfo.sel0, mViewInfo.sel1);
  delete l;

  if (makeDirty)
	mDirty = true;
}

void AudacityProject::PopState(TrackList *l)
{
  mTracks->Clear();
  TrackListIterator iter(l);
  VTrack *t = iter.First();
  while(t) {
	//    printf("Popping track with %d samples\n",
	//           ((WaveTrack *)t)->numSamples);
    //	((WaveTrack *)t)->Debug();
    mTracks->Add(t->Duplicate());
    t = iter.Next();
  }
}

//
// Clipboard methods
//

void AudacityProject::ClearClipboard()
{
  TrackListIterator iter(msClipboard);
  VTrack *n = iter.First();
  while(n) {
    delete n;
    n = iter.Next();
  }
  
  msClipLen = 0.0;
  
  msClipboard->Clear();
}

void AudacityProject::Clear()
{
  TrackListIterator iter(mTracks);

  VTrack *n = iter.First();

  while(n) {
	if (n->selected)
	  n->Clear(mViewInfo.sel0, mViewInfo.sel1);
	n = iter.Next();
  }

  mViewInfo.sel1 = mViewInfo.sel0;

  PushState();
  FixScrollbars();
  mTrackPanel->Refresh(false);
}

void AudacityProject::SelectNone()
{
  TrackListIterator iter(mTracks);

  VTrack *t = iter.First();
  while(t) {
	t->selected = false;
	t = iter.Next();
  }
  mTrackPanel->Refresh(false);
}

// TrackPanel callback method
void AudacityProject::TP_DisplayStatusMessage(const char *msg, int fieldNum)
{
  mStatus->SetField(msg, fieldNum);
}

// TrackPanel callback method
int  AudacityProject::TP_GetCurrentTool()
{
  return GetAPalette()->GetCurrentTool();
}

// TrackPanel callback method
void AudacityProject::TP_OnPlayKey()
{ 
  APalette *palette = GetAPalette();

  if (gAudioIO->IsBusy()) {
	palette->OnStop();
	palette->SetPlay(false);
	palette->SetStop(true);
  }
  else {
	palette->OnPlay();
	palette->SetPlay(true);
	palette->SetStop(false);
  }
}

// TrackPanel callback method
void AudacityProject::TP_PushState()
{
  PushState();
}

// TrackPanel callback method
void AudacityProject::TP_ScrollLeft()
{
  OnScrollLeft();
}

// TrackPanel callback method
void AudacityProject::TP_ScrollRight()
{
  OnScrollRight();
}

// TrackPanel callback method
void AudacityProject::TP_RedrawScrollbars()
{
  FixScrollbars();
}

// TrackPanel callback method
void AudacityProject::TP_HasMouse()
{
  SetActiveProject(this);
  mTrackPanel->SetFocus();
}



