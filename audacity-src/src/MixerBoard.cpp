/**********************************************************************

  Audacity: A Digital Audio Editor

  MixerBoard.cpp

  Vaughan Johnson, January 2007
  Dominic Mazzoni

**********************************************************************/

#include "Experimental.h"
#ifdef EXPERIMENTAL_MIXER_BOARD

#include <math.h>

#include <wx/dcmemory.h>
#include <wx/arrimpl.cpp>
#include <wx/settings.h> // for wxSystemSettings::GetColour and wxSystemSettings::GetMetric

#include "AColor.h"
#include "MixerBoard.h"
#include "Project.h"

#include "../images/MusicalInstruments.h"

#ifdef __WXMSW__
   #include "../images/AudacityLogo.xpm"
#else
   #include "../images/AudacityLogo48x48.xpm"
#endif


// class MixerTrackSlider

BEGIN_EVENT_TABLE(MixerTrackSlider, ASlider)
   EVT_MOUSE_EVENTS(MixerTrackSlider::OnMouseEvent)
END_EVENT_TABLE()

MixerTrackSlider::MixerTrackSlider(wxWindow * parent,
                                    wxWindowID id,
                                    wxString name,
                                    const wxPoint & pos, 
                                    const wxSize & size,
                                    int style /*= FRAC_SLIDER*/,
                                    bool popup /*= true*/,
                                    bool canUseShift /*= true*/,
                                    float stepValue /*= STEP_CONTINUOUS*/, 
                                    int orientation /*= wxHORIZONTAL*/)
: ASlider(parent, id, name, pos, size,
            style, popup, canUseShift, stepValue, orientation)
{
}

void MixerTrackSlider::OnMouseEvent(wxMouseEvent &event)
{
   ASlider::OnMouseEvent(event);

   if (event.ButtonUp())
   {
      MixerTrackCluster* pMixerTrackCluster = (MixerTrackCluster*)(this->GetParent());
      switch (mStyle)
      {
      case DB_SLIDER: pMixerTrackCluster->HandleSliderGain(true); break;
      case PAN_SLIDER: pMixerTrackCluster->HandleSliderPan(true); break;
      default: break; // no-op
      }
   }
}


// class MixerTrackCluster

#define kInset 4
#define kDoubleInset (2 * kInset)
#define kTripleInset (3 * kInset)
#define kQuadrupleInset (4 * kInset)

#define TRACK_NAME_HEIGHT 18
#define MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH 48
#define MUTE_SOLO_HEIGHT 16
#define PAN_HEIGHT 24

enum {
   ID_MUSICAL_INSTRUMENT_IMAGE = 13000, 
   ID_TOGGLEBUTTON_MUTE, 
   ID_TOGGLEBUTTON_SOLO,
   ID_SLIDER_PAN,
   ID_SLIDER_GAIN,
};

BEGIN_EVENT_TABLE(MixerTrackCluster, wxPanel)
   EVT_CHAR(MixerTrackCluster::OnKeyEvent)
   EVT_MOUSE_EVENTS(MixerTrackCluster::OnMouseEvent)
   EVT_COMMAND(ID_TOGGLEBUTTON_MUTE, wxEVT_COMMAND_BUTTON_CLICKED, MixerTrackCluster::OnButton_Mute)
   EVT_COMMAND(ID_TOGGLEBUTTON_SOLO, wxEVT_COMMAND_BUTTON_CLICKED, MixerTrackCluster::OnButton_Solo)
   EVT_PAINT(MixerTrackCluster::OnPaint)
   EVT_SLIDER(ID_SLIDER_PAN, MixerTrackCluster::OnSlider_Pan)
   EVT_SLIDER(ID_SLIDER_GAIN, MixerTrackCluster::OnSlider_Gain)
   //v EVT_COMMAND_SCROLL(ID_SLIDER_GAIN, MixerTrackCluster::OnSliderScroll_Gain)
END_EVENT_TABLE()

MixerTrackCluster::MixerTrackCluster(wxWindow* parent, 
                                       MixerBoard* grandParent, AudacityProject* project, 
                                       WaveTrack* pLeftTrack, WaveTrack* pRightTrack /*= NULL*/, 
                                       const wxPoint& pos /*= wxDefaultPosition*/, 
                                       const wxSize& size /*= wxDefaultSize*/) 
: wxPanel(parent, -1, pos, size)
{
   mMixerBoard = grandParent;
   mProject = project;
   mLeftTrack = pLeftTrack;
   mRightTrack = pRightTrack;

   this->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE)); 

   // Create the controls programmatically.
   
   // Not sure why, but sizers weren't getting offset vertically, 
   // probably because not using wxDefaultPosition, 
   // so positions are calculated explicitly below, and sizers code was removed.
   // (Still available in Audacity_UmixIt branch off 1.2.6.)

   // track name
   wxPoint ctrlPos(kInset, kInset);
   wxSize ctrlSize(size.GetWidth() - kDoubleInset, TRACK_NAME_HEIGHT);
   mStaticText_TrackName = 
      new wxStaticText(this, -1, mLeftTrack->GetName(), ctrlPos, ctrlSize, 
                        wxALIGN_CENTRE | wxST_NO_AUTORESIZE | wxSUNKEN_BORDER);
   //v Useful when different tracks are different colors, but not now.   
   //    mStaticText_TrackName->SetBackgroundColour(this->GetTrackColor());

   
   // musical instrument image
   ctrlPos.x = (size.GetWidth() - MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH) / 2; // center
   ctrlPos.y += TRACK_NAME_HEIGHT + kDoubleInset;
   ctrlSize = wxSize(MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH, MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH);
   wxBitmap* bitmap = mMixerBoard->GetMusicalInstrumentBitmap(mLeftTrack);
   wxASSERT(bitmap);
   mStaticBitmap_MusicalInstrument = 
      new wxStaticBitmap(this, -1, *bitmap, ctrlPos, ctrlSize);

   
   int nHalfWidth = (size.GetWidth() / 2);

   // pan slider
   ctrlPos.x = (size.GetWidth() / 10);
   ctrlPos.y += MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH + kQuadrupleInset;
   ctrlSize = wxSize((size.GetWidth() * 4 / 5), PAN_HEIGHT);

   // The width of the pan slider must be odd (don't ask)
   if (!(ctrlSize.x & 1))
      ctrlSize.x--;

   /* i18n-hint: Title of the Pan slider, used to move the sound left or right */
   mSlider_Pan = 
      new MixerTrackSlider(this, ID_SLIDER_PAN, _("Pan"), ctrlPos, ctrlSize, PAN_SLIDER, true); 

   this->UpdatePan();


   // gain slider at left
   ctrlPos.x = kDoubleInset;
   ctrlPos.y += PAN_HEIGHT + kQuadrupleInset;

   // Instead of an even split of the cluster width, give extra pixels to the meter
   const int kExtraWidthForMeter = 16;
   const int kGainSliderHeight = 
      size.GetHeight() - ctrlPos.y - kQuadrupleInset;
   ctrlSize = 
      wxSize((nHalfWidth - kQuadrupleInset - kExtraWidthForMeter), 
               kGainSliderHeight);

   /* i18n-hint: Title of the Gain slider, used to adjust the volume */
   mSlider_Gain = 
      new MixerTrackSlider(
            this, ID_SLIDER_GAIN, _("Gain"), 
            ctrlPos, ctrlSize, DB_SLIDER, true, 
            true, 0.0, wxVERTICAL);

   // too much color:   mSlider_Gain->SetBackgroundColour(this->GetTrackColor());
   // too dark:   mSlider_Gain->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW));
   //#ifdef __WXMAC__
   //   mSlider_Gain->SetBackgroundColour(wxColour(220, 220, 220));
   //#else
   //   mSlider_Gain->SetBackgroundColour(wxColour(192, 192, 192));
   //#endif

   this->UpdateGain();


   // meter and other controls at right
   ctrlPos.x = nHalfWidth - kExtraWidthForMeter;
   const int kReqdHeightBelowMeter = 
      (2 * (kDoubleInset + MUTE_SOLO_HEIGHT)) + kDoubleInset; // mute/solo buttons stacked at bottom right
   const int kMeterHeight = kGainSliderHeight - kReqdHeightBelowMeter;
   ctrlSize.Set(nHalfWidth - kInset + kExtraWidthForMeter, kMeterHeight);
   mMeter = 
      new Meter(this, -1, // wxWindow* parent, wxWindowID id, 
                false, // bool isInput
                ctrlPos, ctrlSize, // const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                Meter::MixerTrackCluster); // Style style = HorizontalStereo, 

   // mute/solo buttons stacked below meter
   ctrlPos.y += kMeterHeight + kDoubleInset;
   ctrlSize = wxSize(mMixerBoard->mMuteSoloWidth, MUTE_SOLO_HEIGHT);
   mToggleButton_Mute = 
      new AButton(this, ID_TOGGLEBUTTON_MUTE, 
                  ctrlPos, ctrlSize, 
                  *(mMixerBoard->mImageMuteUp), *(mMixerBoard->mImageMuteOver), 
                  *(mMixerBoard->mImageMuteDown), *(mMixerBoard->mImageMuteDisabled), 
                  true); // toggle button
   mToggleButton_Mute->SetAlternateImages(
      *(mMixerBoard->mImageMuteUp), *(mMixerBoard->mImageMuteOver), 
      *(mMixerBoard->mImageMuteDown), *(mMixerBoard->mImageMuteDisabled));
   this->UpdateMute();

   ctrlPos.y += kDoubleInset + MUTE_SOLO_HEIGHT;
   mToggleButton_Solo = 
      new AButton(this, ID_TOGGLEBUTTON_SOLO, 
                  ctrlPos, ctrlSize, 
                  *(mMixerBoard->mImageSoloUp), *(mMixerBoard->mImageSoloOver), 
                  *(mMixerBoard->mImageSoloDown), *(mMixerBoard->mImageSoloDisabled), 
                  true); // toggle button
   this->UpdateSolo();

   #if wxUSE_TOOLTIPS
      mStaticText_TrackName->SetToolTip(_T("Track Name"));
      mToggleButton_Mute->SetToolTip(_T("Mute"));
      mToggleButton_Solo->SetToolTip(_T("Solo"));
      mMeter->SetToolTip(_T("Signal Level Meter"));
   #endif // wxUSE_TOOLTIPS

   #ifdef __WXMAC__
      wxSizeEvent dummyEvent;
      this->OnSize(dummyEvent);
      UpdateGain();
   #endif
}

void MixerTrackCluster::HandleSliderGain(const bool bWantPushState /*= false*/)
{
   float fValue = mSlider_Gain->Get();
   mLeftTrack->SetGain(fValue);
   if (mRightTrack)
      mRightTrack->SetGain(fValue);

   // Update the TrackPanel correspondingly. 
   mProject->RefreshTPTrack(mLeftTrack);

   if (bWantPushState)
      mProject->TP_PushState(_("Moved gain slider"), _("Gain"), true /* consolidate */);
}

void MixerTrackCluster::HandleSliderPan(const bool bWantPushState /*= false*/)
{
   float fValue = mSlider_Pan->Get();
   mLeftTrack->SetPan(fValue);
   if (mRightTrack)
      mRightTrack->SetPan(fValue);

   // Update the TrackPanel correspondingly. 
   mProject->RefreshTPTrack(mLeftTrack);

   if (bWantPushState)
      mProject->TP_PushState(_("Moved pan slider"), _("Pan"), true /* consolidate */);
}

void MixerTrackCluster::ResetMeter()
{
   mMeter->Reset(mLeftTrack->GetRate(), true);
}

void MixerTrackCluster::UpdateHeight() // For wxSizeEvents, update gain slider and meter.
{
   wxSize scrolledWindowClientSize = this->GetParent()->GetClientSize();   
   const int newClusterHeight = 
      scrolledWindowClientSize.GetHeight() - 
      wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y) + // wxScrolledWindow::GetClientSize doesn't account for its scrollbar size.
      kDoubleInset;
   
   this->SetSize(-1, newClusterHeight); 

   // Change the heights of only mSlider_Gain and mMeter.
   const int kGainSliderHeight = 
      newClusterHeight - 
      (kInset + // margin above mStaticText_TrackName
         TRACK_NAME_HEIGHT + kDoubleInset + // mStaticText_TrackName + margin
         MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH + kQuadrupleInset + // musical instrument icon + margin
         PAN_HEIGHT + kQuadrupleInset) - // pan slider
      kQuadrupleInset; // margin below gain slider and meter 

   // -1 doesn't work right to preserve width for wxSlider, and it doesn't implement GetSize(void). //vvvvv Still true?
   //    mSlider_Gain->SetSize(-1, kGainSliderHeight);
   int oldWidth; 
   int oldHeight;
   mSlider_Gain->GetSize(&oldWidth, &oldHeight);
   mSlider_Gain->SetSize(oldWidth, kGainSliderHeight); 

   const int kReqdHeightBelowMeter = 
      (2 * (kDoubleInset + MUTE_SOLO_HEIGHT)) + kDoubleInset; // mute/solo buttons stacked at bottom right
   const int kMeterHeight = kGainSliderHeight - kReqdHeightBelowMeter;
   mMeter->SetSize(-1, kMeterHeight);

   // Reposition mute/solo buttons.
   int newMuteSoloX;
   int newMuteSoloY;
   mMeter->GetPosition(&newMuteSoloX, &newMuteSoloY);
   newMuteSoloY += kMeterHeight + kDoubleInset;
   mToggleButton_Mute->Move(-1 , newMuteSoloY);
   newMuteSoloY += kDoubleInset + MUTE_SOLO_HEIGHT;
   mToggleButton_Solo->Move(-1 , newMuteSoloY);
}


// These are used by TrackPanel for synchronizing control states, etc.

// Update the controls that can be affected by state change.
void MixerTrackCluster::UpdateForStateChange() 
{
   this->UpdateName();
   this->UpdatePan();
   this->UpdateGain();
}

void MixerTrackCluster::UpdateName()
{
   mStaticText_TrackName->SetLabel(mLeftTrack->GetName()); 
   mStaticBitmap_MusicalInstrument->SetBitmap(*(mMixerBoard->GetMusicalInstrumentBitmap(mLeftTrack)));
}

void MixerTrackCluster::UpdateMute()
{
   mToggleButton_Mute->SetAlternate(mLeftTrack->GetSolo());
   if (mLeftTrack->GetMute())
      mToggleButton_Mute->PushDown(); 
   else 
      mToggleButton_Mute->PopUp(); 
}

void MixerTrackCluster::UpdateSolo()
{
   bool bValue = mLeftTrack->GetSolo();
   if (bValue)
      mToggleButton_Solo->PushDown(); 
   else 
      mToggleButton_Solo->PopUp(); 
   mToggleButton_Mute->SetAlternate(bValue);
}

void MixerTrackCluster::UpdatePan()
{
   mSlider_Pan->Set(mLeftTrack->GetPan());
}

void MixerTrackCluster::UpdateGain()
{
   mSlider_Gain->Set(mLeftTrack->GetGain()); 
}

void MixerTrackCluster::UpdateMeter(const double t0, const double t1)
{
   if ((t0 < 0.0) || (t1 < 0.0) || (t0 >= t1) || // bad time value or nothing to show
         ((mMixerBoard->HasSolo() || mLeftTrack->GetMute()) && !mLeftTrack->GetSolo()))
   {
      this->ResetMeter();
      return;
   }

   const int kFramesPerBuffer = 4; 
   float min; // A dummy, since it's not shown in meters. 
   float* maxLeft = new float[kFramesPerBuffer];
   float* rmsLeft = new float[kFramesPerBuffer];
   float* maxRight = new float[kFramesPerBuffer];
   float* rmsRight = new float[kFramesPerBuffer];
   const sampleCount kSampleCount = mLeftTrack->TimeToLongSamples(t1 - t0);
   
   bool bSuccess = true;
   const double kFrameInterval = (t1 - t0) / (double)kFramesPerBuffer;
   double dFrameT0 = t0;
   double dFrameT1 = t0 + kFrameInterval;
   unsigned int i = 0;
   while (bSuccess && (i < kFramesPerBuffer))
   {
      bSuccess &= 
         mLeftTrack->GetMinMax(&min, &(maxLeft[i]), dFrameT0, dFrameT1) && 
         mLeftTrack->GetRMS(&(rmsLeft[i]), dFrameT0, dFrameT1);
      if (bSuccess && mRightTrack)
         bSuccess &=
            mRightTrack->GetMinMax(&min, &(maxRight[i]), dFrameT0, dFrameT1) && 
            mRightTrack->GetRMS(&(rmsRight[i]), dFrameT0, dFrameT1);
      else
      {
         // Mono: Start with raw values same as left. 
         // To be modified by bWantPostFadeValues and channel pan/gain.
         maxRight[i] = maxLeft[i];
         rmsRight[i] = rmsLeft[i];
      }
      dFrameT0 += kFrameInterval;
      dFrameT1 += kFrameInterval;
      i++;
   }

   bool bWantPostFadeValues = true; //vvv Turn this into a pref, default true.
   if (bSuccess && bWantPostFadeValues)
   {
      for (i = 0; i < kFramesPerBuffer; i++)
      {
         float gain = mLeftTrack->GetChannelGain(0);
         maxLeft[i] *= gain;
         rmsLeft[i] *= gain;
         if (mRightTrack)
            gain = mRightTrack->GetChannelGain(1);
         else
            gain = mLeftTrack->GetChannelGain(1);
         maxRight[i] *= gain;
         rmsRight[i] *= gain;
      }
   }

   if (bSuccess)
      mMeter->UpdateDisplay(
         2, // If mono, show left track values in both meters, as in MeterToolBar.      kNumChannels, 
         kFramesPerBuffer, 
         maxLeft, rmsLeft, 
         maxRight, rmsRight, 
         kSampleCount);

   delete[] maxLeft;
   delete[] rmsLeft;
   delete[] maxRight;
   delete[] rmsRight;
}

// private

wxColour MixerTrackCluster::GetTrackColor()
{
   //#if (AUDACITY_BRANDING == BRAND_UMIXIT)
   //   return AColor::GetTrackColor((void*)mLeftTrack);
   //#else
      return wxColour(102, 255, 102); // same as Meter playback color
   //#endif
}


// event handlers

void MixerTrackCluster::OnKeyEvent(wxKeyEvent & event)
{
   mProject->HandleKeyDown(event);
}

void MixerTrackCluster::OnMouseEvent(wxMouseEvent& event)
{
   if (event.ButtonUp()) 
   {
      if (event.ShiftDown()) 
      {
         // ShiftDown => Just toggle selection on this track.
         bool bSelect = !mLeftTrack->GetSelected();
         mLeftTrack->SetSelected(bSelect);
         if (mRightTrack)
            mRightTrack->SetSelected(bSelect);

         // Refresh only this MixerTrackCluster and WaveTrack in TrackPanel.
         this->Refresh(true); 
         mProject->RefreshTPTrack(mLeftTrack);
      }
      else
      {
         // exclusive select
         mProject->SelectNone();
         mLeftTrack->SetSelected(true);
         if (mRightTrack)
            mRightTrack->SetSelected(true);

         if (mProject->GetSel0() >= mProject->GetSel1())
         {
            // No range previously selected, so use the range of this track. 
            mProject->mViewInfo.sel0 = mLeftTrack->GetOffset();
            mProject->mViewInfo.sel1 = mLeftTrack->GetEndTime();
         }

         // Exclusive select, so refresh all MixerTrackClusters.
         //    This could just be a call to wxWindow::Refresh, but this is 
         //    more efficient and when ProjectLogo is shown as background, 
         //    it's necessary to prevent blinking.
         mMixerBoard->RefreshTrackClusters(false);
      }
   }
}

void MixerTrackCluster::OnPaint(wxPaintEvent &evt)
{
   wxPaintDC dc(this);

   #ifdef __WXMAC__
      // Fill with correct color, not scroller background. Done automatically on Windows.
      AColor::Medium(&dc, false);
      dc.DrawRectangle(this->GetClientRect());
   #endif

   wxSize clusterSize = this->GetSize();
   wxRect bev(0, 0, clusterSize.GetWidth() - 1, clusterSize.GetHeight() - 1);
   if (mLeftTrack->GetSelected())
   {
      for (unsigned int i = 0; i < 2; i++) 
      {
         bev.Inflate(-1, -1);
         AColor::Bevel(dc, false, bev);
      }
   }
   else
      AColor::Bevel(dc, true, bev);
}


void MixerTrackCluster::OnButton_Mute(wxCommandEvent& event)
{
   // Shift-click mutes this track and unmutes other tracks. Tell mMixerBoard to handle it.
   if (mToggleButton_Mute->WasShiftDown())
   {
      mMixerBoard->UniquelyMuteOrSolo(mLeftTrack, false); //vvvvv
      return;
   }

   bool bValue = mToggleButton_Mute->IsDown();
   mLeftTrack->SetMute(bValue);
   if (mRightTrack)
      mRightTrack->SetMute(bValue);
   mToggleButton_Mute->SetAlternate(mLeftTrack->GetSolo());

   // Update the TrackPanel correspondingly. 
   mProject->RefreshTPTrack(mLeftTrack);
}

void MixerTrackCluster::OnButton_Solo(wxCommandEvent& event)
{
   // Shift-click solos this track and unsolos other tracks. Tell mMixerBoard to handle it.
   if (mToggleButton_Solo->WasShiftDown())
   {
      mMixerBoard->UniquelyMuteOrSolo(mLeftTrack, true); //vvvvv
      return;
   }

   bool bValue = mToggleButton_Solo->IsDown();
   mLeftTrack->SetSolo(bValue);
   if (mRightTrack)
      mRightTrack->SetSolo(bValue);
   mMixerBoard->IncrementSoloCount(bValue ? 1 : -1);
   mToggleButton_Mute->SetAlternate(bValue);

   // Update the TrackPanel correspondingly. 
   mProject->RefreshTPTrack(mLeftTrack);
}

void MixerTrackCluster::OnSlider_Gain(wxCommandEvent& event)
{
   this->HandleSliderGain();
}

void MixerTrackCluster::OnSlider_Pan(wxCommandEvent& event)
{
   this->HandleSliderPan();
}

//v void MixerTrackCluster::OnSliderScroll_Gain(wxScrollEvent& event)
//{
   //int sliderValue = (int)(mSlider_Gain->Get()); //v mSlider_Gain->GetValue();
   //#ifdef __WXMSW__
   //   // Negate because wxSlider on Windows has min at top, max at bottom. 
   //   // mSlider_Gain->GetValue() is in [-6,36]. wxSlider has min at top, so this is [-36dB,6dB]. 
   //   sliderValue = -sliderValue;
   //#endif
   //wxString str = _T("Gain: ");
   //if (sliderValue > 0) 
   //   str += "+";
   //str += wxString::Format("%d dB", sliderValue);
   //mSlider_Gain->SetToolTip(str);
//}


// class MusicalInstrument

MusicalInstrument::MusicalInstrument(wxBitmap* pBitmap, const wxString strXPMfilename)
{
   mBitmap = pBitmap;

   size_t nFirstCharIndex = 0;
   int nUnderscoreIndex;
   wxString strFilename = strXPMfilename;
   strFilename.MakeLower(); // Make sure, so we don't have to do case insensitive comparison.
   wxString strKeyword;
   while ((nUnderscoreIndex = strFilename.Find(wxT('_'))) != -1) 
   {
      strKeyword = strFilename.Left(nUnderscoreIndex);
      mKeywords.Add(strKeyword);
      strFilename = strFilename.Mid(nUnderscoreIndex + 1);
   }
   if (!strFilename.IsEmpty()) // Skip trailing underscores.
      mKeywords.Add(strFilename); // Add the last one. 
}

MusicalInstrument::~MusicalInstrument()
{
   delete mBitmap;
   mKeywords.Clear();
}

WX_DEFINE_OBJARRAY(MusicalInstrumentArray);


// class MixerBoardScrolledWindow 

// wxScrolledWindow ignores mouse clicks in client area, 
// but they don't get passed to Mixerboard.
// We need to catch them to deselect all track clusters.

BEGIN_EVENT_TABLE(MixerBoardScrolledWindow, wxScrolledWindow)
   EVT_MOUSE_EVENTS(MixerBoardScrolledWindow::OnMouseEvent)
END_EVENT_TABLE()

MixerBoardScrolledWindow::MixerBoardScrolledWindow(AudacityProject* project, 
                                                   MixerBoard* parent, wxWindowID id /*= -1*/, 
                                                   const wxPoint& pos /*= wxDefaultPosition*/, 
                                                   const wxSize& size /*= wxDefaultSize*/, 
                                                   long style /*= wxHSCROLL | wxVSCROLL*/)
: wxScrolledWindow(parent, id, pos, size, style)
{
   mMixerBoard = parent;
   mProject = project;
}

MixerBoardScrolledWindow::~MixerBoardScrolledWindow()
{
}

void MixerBoardScrolledWindow::OnMouseEvent(wxMouseEvent& event)
{
   if (event.ButtonUp()) 
   {
      //v Even when I implement MixerBoard::OnMouseEvent and call event.Skip() 
      // here, MixerBoard::OnMouseEvent never gets called.
      // So, added mProject to MixerBoardScrolledWindow and just directly do what's needed here.
      mProject->SelectNone();
   }
   else
      event.Skip();
}


// class MixerBoard

#define MIXER_BOARD_MIN_HEIGHT      460
#define MIXER_TRACK_CLUSTER_WIDTH   96
#define MIXER_BOARD_MIN_WIDTH       kDoubleInset + MIXER_TRACK_CLUSTER_WIDTH + kDoubleInset


BEGIN_EVENT_TABLE(MixerBoard, wxWindow)
   EVT_SIZE(MixerBoard::OnSize)
END_EVENT_TABLE()

MixerBoard::MixerBoard(AudacityProject* pProject, 
                        wxFrame* parent, 
                        const wxPoint& pos /*= wxDefaultPosition*/, 
                        const wxSize& size /*= wxDefaultSize*/)
: wxWindow(parent, -1, pos, size)
{
   // public data members

   // mute & solo button images: Create once and store on MixerBoard for use in all MixerTrackClusters.
   mImageMuteUp = NULL;
   mImageMuteOver = NULL;
   mImageMuteDown = NULL;
   mImageMuteDownWhileSolo = NULL;
   mImageMuteDisabled = NULL;
   mImageSoloUp = NULL;
   mImageSoloOver = NULL;
   mImageSoloDown = NULL;
   mImageSoloDisabled = NULL;

   mMuteSoloWidth = 44; //v good estimate, but really set in MixerBoard::CreateMuteSoloImages

   // private data members
   this->LoadMusicalInstruments(); // Set up mMusicalInstruments.
   mProject = pProject;
   
   mScrolledWindow = 
      new MixerBoardScrolledWindow(
         pProject, // AudacityProject* project,
         this, -1, // wxWindow* parent, wxWindowID id = -1, 
         this->GetClientAreaOrigin(), // const wxPoint& pos = wxDefaultPosition, 
         size, // const wxSize& size = wxDefaultSize, 
         wxHSCROLL); // long style = wxHSCROLL | wxVSCROLL, const wxString& name = "scrolledWindow")

   // Set background color to same as TrackPanel background.
   #ifdef EXPERIMENTAL_THEMING
      mScrolledWindow->SetBackgroundColour(this->GetParent()->GetBackgroundColour());
   #else
      mScrolledWindow->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_3DSHADOW)); 
   #endif
   
   mScrolledWindow->SetScrollRate(10, 0); // no vertical scroll
   mScrolledWindow->SetVirtualSize(size);

   /* This doesn't work to make the mScrolledWindow automatically resize, so do it explicitly in OnSize.
         wxBoxSizer* pBoxSizer = new wxBoxSizer(wxVERTICAL);
         pBoxSizer->Add(mScrolledWindow, 0, wxExpand, 0);
         this->SetAutoLayout(true);
         this->SetSizer(pBoxSizer);
         pBoxSizer->Fit(this);
         pBoxSizer->SetSizeHints(this);
      */

   mSoloCount = 0;
   mPrevT1 = 0.0;
   mTracks = mProject->GetTracks();
}

MixerBoard::~MixerBoard()
{
   // public data members
   delete mImageMuteUp;
   delete mImageMuteOver;
   delete mImageMuteDown;
   delete mImageMuteDownWhileSolo;
   delete mImageMuteDisabled;
   delete mImageSoloUp;
   delete mImageSoloOver;
   delete mImageSoloDown;
   delete mImageSoloDisabled;

   // private data members
   mMusicalInstruments.Clear();
}

void MixerBoard::UpdateTrackClusters() 
{
   if (mImageMuteUp == NULL) 
      this->CreateMuteSoloImages();

   const int kClusterHeight = mScrolledWindow->GetClientSize().GetHeight() - kDoubleInset;
   const size_t kClusterCount = mMixerTrackClusters.GetCount();
   unsigned int nClusterIndex = 0;
   TrackListIterator iterTracks(mTracks);
   MixerTrackCluster* pMixerTrackCluster = NULL;
   Track* pLeftTrack;
   Track* pRightTrack;

   pLeftTrack = iterTracks.First();
   while (pLeftTrack) {
      pRightTrack = pLeftTrack->GetLinked() ? iterTracks.Next() : NULL;

      if (pLeftTrack->GetKind() == Track::Wave) 
      {
         if (nClusterIndex < kClusterCount)
         {
            // Already showing it. 
            // Track clusters are maintained in the same order as the WaveTracks.
            // Track pointers can change for the "same" track for different states 
            // on the undo stack, so update the pointers and display name.
            mMixerTrackClusters[nClusterIndex]->mLeftTrack = (WaveTrack*)pLeftTrack;
            mMixerTrackClusters[nClusterIndex]->mRightTrack = (WaveTrack*)pRightTrack;
            mMixerTrackClusters[nClusterIndex]->UpdateForStateChange();
         }
         else
         {
            // Not already showing it. Add a new MixerTrackCluster.
            wxPoint clusterPos(
               (kInset +                                       // extra inset to left for first one.
                  (nClusterIndex * 
                     (kInset + MIXER_TRACK_CLUSTER_WIDTH)) +   // left margin and width for each to its left
                  kInset),                                     // plus left margin for new cluster
               kInset); 
            wxSize clusterSize(MIXER_TRACK_CLUSTER_WIDTH, kClusterHeight);
            pMixerTrackCluster = 
               new MixerTrackCluster(mScrolledWindow, this, mProject, 
                                       (WaveTrack*)pLeftTrack, (WaveTrack*)pRightTrack, 
                                       clusterPos, clusterSize);
            if (pMixerTrackCluster)
            {
               mMixerTrackClusters.Add(pMixerTrackCluster);
               this->IncrementSoloCount((int)(pLeftTrack->GetSolo()));
            }
         }
         nClusterIndex++;
      }
      pLeftTrack = iterTracks.Next();
   }

   if (pMixerTrackCluster)
   {
      // Added at least one MixerTrackCluster.
      this->UpdateWidth();
      for (nClusterIndex = 0; nClusterIndex < mMixerTrackClusters.GetCount(); nClusterIndex++)
         mMixerTrackClusters[nClusterIndex]->UpdateHeight();
   }
   else if (nClusterIndex < kClusterCount)
   {
      // We've got too many clusters. 
      // This can only on things like Undo New Audio Track or Undo Import
      // that don't call RemoveTrackCluster explicitly. 
      // We've already updated the track pointers for the clusters to the left, so just remove these.
      for (; nClusterIndex < kClusterCount; nClusterIndex++)
         this->RemoveTrackCluster(mMixerTrackClusters[nClusterIndex]->mLeftTrack);
   }
}

int MixerBoard::GetTrackClustersWidth()
{
   return 
      kInset +                                     // extra margin at left for first one
      (mMixerTrackClusters.GetCount() *            // number of tracks times
         (kInset + MIXER_TRACK_CLUSTER_WIDTH)) +   //    left margin and width for each
      kDoubleInset;                                // plus final right margin
}

void MixerBoard::MoveTrackCluster(const WaveTrack* pLeftTrack, 
                                  bool bUp) // Up in TrackPanel is left in MixerBoard.
{
   MixerTrackCluster* pMixerTrackCluster;
   int nIndex = this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
   if (pMixerTrackCluster == NULL) 
      return; // Couldn't find it.

   wxPoint pos;
   if (bUp)
   {  // Move it up (left).
      wxASSERT(nIndex > 0); // Shouldn't be called if already first.

      pos = pMixerTrackCluster->GetPosition();
      mMixerTrackClusters[nIndex] = mMixerTrackClusters[nIndex - 1];
      mMixerTrackClusters[nIndex]->Move(pos);

      mMixerTrackClusters[nIndex - 1] = pMixerTrackCluster;
      pMixerTrackCluster->Move(pos.x - (kInset + MIXER_TRACK_CLUSTER_WIDTH), pos.y);
   }
   else
   {  // Move it down (right).
      wxASSERT(((unsigned int)nIndex + 1) < mMixerTrackClusters.GetCount()); // Shouldn't be called if already last.

      pos = pMixerTrackCluster->GetPosition();
      mMixerTrackClusters[nIndex] = mMixerTrackClusters[nIndex + 1];
      mMixerTrackClusters[nIndex]->Move(pos);

      mMixerTrackClusters[nIndex + 1] = pMixerTrackCluster;
      pMixerTrackCluster->Move(pos.x + (kInset + MIXER_TRACK_CLUSTER_WIDTH), pos.y);
   }
}

void MixerBoard::RemoveTrackCluster(const WaveTrack* pLeftTrack)
{
   // Find and destroy.
   MixerTrackCluster* pMixerTrackCluster;
   int nIndex = this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
   if (pMixerTrackCluster == NULL) 
      return; // Couldn't find it.
      
   mMixerTrackClusters.RemoveAt(nIndex);
   pMixerTrackCluster->Destroy(); // delete is unsafe on wxWindow.

   // Close the gap, if any.
   wxPoint pos;
   int targetX;
   for (unsigned int i = nIndex; i < mMixerTrackClusters.GetCount(); i++)
   {
      pos = mMixerTrackClusters[i]->GetPosition();
      targetX = 
         (i * (kInset + MIXER_TRACK_CLUSTER_WIDTH)) + // left margin and width for each
         kInset; // plus left margin for this cluster
      if (pos.x != targetX)
         mMixerTrackClusters[i]->Move(targetX, pos.y);
   }

   this->UpdateWidth();
}


wxBitmap* MixerBoard::GetMusicalInstrumentBitmap(const WaveTrack* pLeftTrack)
{
   if (mMusicalInstruments.IsEmpty())
      return NULL;

   // random choice:    return mMusicalInstruments[(int)pLeftTrack % mMusicalInstruments.GetCount()].mBitmap; 
   
   const wxString strTrackName(pLeftTrack->GetName().MakeLower());
   size_t nBestItemIndex = 0;
   unsigned int nBestScore = 0;
   unsigned int nInstrIndex = 0;
   unsigned int nKeywordIndex;
   unsigned int nNumKeywords;
   unsigned int nPointsPerMatch;
   unsigned int nScore;
   for (nInstrIndex = 0; nInstrIndex < mMusicalInstruments.GetCount(); nInstrIndex++)
   {
      nScore = 0;

      nNumKeywords = mMusicalInstruments[nInstrIndex].mKeywords.GetCount();
      if (nNumKeywords > 0)
      {
         nPointsPerMatch = 10 / nNumKeywords;
         for (nKeywordIndex = 0; nKeywordIndex < nNumKeywords; nKeywordIndex++)
            if (strTrackName.Contains(mMusicalInstruments[nInstrIndex].mKeywords[nKeywordIndex]))
            {
               nScore += 
                  nPointsPerMatch + 
                  // Longer keywords get more points.
                  (2 * mMusicalInstruments[nInstrIndex].mKeywords[nKeywordIndex].Length());
            }
      }

      // Choose later one if just matching nBestScore, for better variety, 
      // and so default works as last element.
      if (nScore >= nBestScore) 
      {
         nBestScore = nScore;
         nBestItemIndex = nInstrIndex;
      }
   }
   return mMusicalInstruments[nBestItemIndex].mBitmap;
}

bool MixerBoard::HasSolo() 
{  
   return (mSoloCount > 0); 
}

void MixerBoard::IncrementSoloCount(int nIncrement /*= 1*/) 
{  
   mSoloCount += nIncrement; 
}

void MixerBoard::RefreshTrackCluster(const WaveTrack* pLeftTrack, bool bEraseBackground /*= true*/)
{
   MixerTrackCluster* pMixerTrackCluster;
   this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
   if (pMixerTrackCluster) 
      pMixerTrackCluster->Refresh(bEraseBackground);
}

void MixerBoard::RefreshTrackClusters(bool bEraseBackground /*= true*/)
{
   for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
      mMixerTrackClusters[i]->Refresh(bEraseBackground);
}

void MixerBoard::ResetMeters()
{
   mPrevT1 = 0.0;

   if (!this->IsShown())
      return;

   for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
      mMixerTrackClusters[i]->ResetMeter();
}

void MixerBoard::UniquelyMuteOrSolo(const WaveTrack* pTargetLeftTrack, bool bSolo) //vvvvv
{
   wxASSERT(mTracks && !mTracks->IsEmpty());
   TrackListIterator iterTracks(mTracks);
   Track* pLeftTrack = iterTracks.First();
   while (pLeftTrack) {
      if (pLeftTrack->GetKind() == Track::Wave) {
         if (bSolo)
            pLeftTrack->SetSolo(pLeftTrack == pTargetLeftTrack);
         else 
            pLeftTrack->SetMute(pLeftTrack == pTargetLeftTrack);
      }
      if (pLeftTrack->GetLinked()) 
         pLeftTrack = iterTracks.Next(); // Skip the right track.
      pLeftTrack = iterTracks.Next();
   }

   if (bSolo)
   {
      mSoloCount = 1;
      this->UpdateSolo(); // Update all the MixerTrackCluster solo buttons.
   }
   else 
      this->UpdateMute(); // Update all the MixerTrackCluster mute buttons.

   mProject->RedrawProject(); // Update all the TrackLabel mute/solo buttons.
}


void MixerBoard::UpdateName(const WaveTrack* pLeftTrack)
{
   MixerTrackCluster* pMixerTrackCluster;
   this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
   if (pMixerTrackCluster) 
      pMixerTrackCluster->UpdateName();
}

void MixerBoard::UpdateMute(const WaveTrack* pLeftTrack /*= NULL*/) // NULL means update for all tracks.
{
   if (pLeftTrack == NULL) 
   {
      for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
         mMixerTrackClusters[i]->UpdateMute();
   }
   else 
   {
      MixerTrackCluster* pMixerTrackCluster;
      this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
      if (pMixerTrackCluster) 
         pMixerTrackCluster->UpdateMute();
   }
}

void MixerBoard::UpdateSolo(const WaveTrack* pLeftTrack /*= NULL*/) // NULL means update for all tracks.
{
   if (pLeftTrack == NULL) 
   {
      for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
         mMixerTrackClusters[i]->UpdateSolo();
   }
   else 
   {
      MixerTrackCluster* pMixerTrackCluster;
      this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
      if (pMixerTrackCluster) 
         pMixerTrackCluster->UpdateSolo();
   }
}

void MixerBoard::UpdatePan(const WaveTrack* pLeftTrack)
{
   MixerTrackCluster* pMixerTrackCluster;
   this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
   if (pMixerTrackCluster) 
      pMixerTrackCluster->UpdatePan();
}

void MixerBoard::UpdateGain(const WaveTrack* pLeftTrack)
{
   MixerTrackCluster* pMixerTrackCluster;
   this->FindMixerTrackCluster(pLeftTrack, &pMixerTrackCluster);
   if (pMixerTrackCluster) 
      pMixerTrackCluster->UpdateGain();
}

void MixerBoard::UpdateMeters(const double t1, const bool bLoopedPlay)
{
   if (!this->IsShown())
      return;

   // In loopedPlay mode, at the end of the loop, mPrevT1 is set to 
   // selection end, so the next t1 will be less, but we do want to 
   // keep updating the meters.
   if (t1 <= mPrevT1)
   {
      if (bLoopedPlay)
      {
         this->ResetMeters();
         mPrevT1 = t1;
      }
      return;
   }

   for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
      mMixerTrackClusters[i]->UpdateMeter(mPrevT1, t1);

   mPrevT1 = t1;
}


void MixerBoard::UpdateWidth()
{
   int newWidth = this->GetTrackClustersWidth(); 

   // Min width is one cluster wide, plus margins.
   if (newWidth < MIXER_BOARD_MIN_WIDTH)
      newWidth = MIXER_BOARD_MIN_WIDTH;

   mScrolledWindow->SetVirtualSize(newWidth, -1);
   this->GetParent()->SetSize(newWidth + kDoubleInset, -1);
}

//
// private methods
//

void MixerBoard::CreateMuteSoloImages()
{
   // Much of this is taken TrackLabel::DrawMuteSolo 
   wxMemoryDC dc;
   wxString str = _("Mute"); 
   long textWidth, textHeight;

   int fontSize = 10;
   #ifdef __WXMSW__
      fontSize = 8;
   #endif
   dc.SetFont(wxFont(fontSize, wxSWISS, wxNORMAL, wxNORMAL));
   dc.GetTextExtent(str, &textWidth, &textHeight);
   mMuteSoloWidth = textWidth + (3 * kInset);

   wxBitmap bitmap(mMuteSoloWidth, MUTE_SOLO_HEIGHT);
   dc.SelectObject(bitmap);
   wxRect bev(0, 0, mMuteSoloWidth - 1, MUTE_SOLO_HEIGHT - 1);

   // mute button images
   AColor::Mute(&dc, false, false, false);
   dc.DrawRectangle(bev);

   wxCoord x = bev.x + (bev.width - textWidth) / 2;
   wxCoord y = bev.y + (bev.height - textHeight) / 2;
   dc.DrawText(str, x, y);

   AColor::Bevel(dc, true, bev);

   mImageMuteUp = new wxImage(bitmap.ConvertToImage());
   mImageMuteOver = new wxImage(bitmap.ConvertToImage()); // Same as up, for now.

   AColor::Mute(&dc, true, true, false);
   dc.DrawRectangle(bev);
   dc.DrawText(str, x, y);
   AColor::Bevel(dc, false, bev);
   mImageMuteDown = new wxImage(bitmap.ConvertToImage());

   AColor::Mute(&dc, true, true, true);
   dc.DrawRectangle(bev);
   dc.DrawText(str, x, y);
   AColor::Bevel(dc, false, bev);
   mImageMuteDownWhileSolo = new wxImage(bitmap.ConvertToImage());

   mImageMuteDisabled = new wxImage(mMuteSoloWidth, MUTE_SOLO_HEIGHT); // Leave empty because unused.


   // solo button images
   AColor::Solo(&dc, false, false);
   dc.DrawRectangle(bev);

   str = _("Solo");
   dc.GetTextExtent(str, &textWidth, &textHeight);
   x = bev.x + (bev.width - textWidth) / 2;
   y = bev.y + (bev.height - textHeight) / 2;
   dc.DrawText(str, x, y);

   AColor::Bevel(dc, true, bev);

   mImageSoloUp = new wxImage(bitmap.ConvertToImage());
   mImageSoloOver = new wxImage(bitmap.ConvertToImage()); // Same as up, for now.

   AColor::Solo(&dc, true, true);
   dc.DrawRectangle(bev);
   dc.DrawText(str, x, y);
   AColor::Bevel(dc, false, bev);
   mImageSoloDown = new wxImage(bitmap.ConvertToImage());

   mImageSoloDisabled = new wxImage(mMuteSoloWidth, MUTE_SOLO_HEIGHT); // Leave empty because unused.
}

int MixerBoard::FindMixerTrackCluster(const WaveTrack* pLeftTrack, 
                                      MixerTrackCluster** hMixerTrackCluster) const
{
   *hMixerTrackCluster = NULL;
   for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
   {
      if (mMixerTrackClusters[i]->mLeftTrack == pLeftTrack)
      {
         *hMixerTrackCluster = mMixerTrackClusters[i];
         return i;
      }
   }
   return -1;
}

void MixerBoard::LoadMusicalInstruments()
{
   wxRect bev(1, 1, MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH - 2, MUSICAL_INSTRUMENT_HEIGHT_AND_WIDTH - 2);
   wxBitmap* bitmap;
   wxMemoryDC dc;
   MusicalInstrument* pMusicalInstrument;


   bitmap = new wxBitmap((const char**)acoustic_guitar_gtr_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("acoustic_guitar_gtr"));
   mMusicalInstruments.Add(pMusicalInstrument);
   
   bitmap = new wxBitmap((const char**)acoustic_piano_pno_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("acoustic_piano_pno"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)back_vocal_bg_vox_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("back_vocal_bg_vox"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)clap_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("clap"));
   mMusicalInstruments.Add(pMusicalInstrument);


   bitmap = new wxBitmap((const char**)drums_dr_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("drums_dr"));
   mMusicalInstruments.Add(pMusicalInstrument);
  
   bitmap = new wxBitmap((const char**)electric_bass_guitar_bs_gtr_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("electric_bass_guitar_bs_gtr"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)electric_guitar_gtr_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("electric_guitar_gtr"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)electric_piano_pno_key_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("electric_piano_pno_key"));
   mMusicalInstruments.Add(pMusicalInstrument);


   bitmap = new wxBitmap((const char**)kick_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("kick"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)loop_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("loop"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)organ_org_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("organ_org"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)perc_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("perc"));
   mMusicalInstruments.Add(pMusicalInstrument);


   bitmap = new wxBitmap((const char**)sax_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("sax"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)snare_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("snare"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)string_violin_cello_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("string_violin_cello"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)synth_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("synth"));
   mMusicalInstruments.Add(pMusicalInstrument);


   bitmap = new wxBitmap((const char**)tambo_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("tambo"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)trumpet_horn_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("trumpet_horn"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)turntable_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("turntable"));
   mMusicalInstruments.Add(pMusicalInstrument);

   bitmap = new wxBitmap((const char**)vibraphone_vibes_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("vibraphone_vibes"));
   mMusicalInstruments.Add(pMusicalInstrument);


   bitmap = new wxBitmap((const char**)vocal_vox_xpm);
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxT("vocal_vox"));
   mMusicalInstruments.Add(pMusicalInstrument);


   // This one must be last, so it wins when best score is 0.
   bitmap = new wxBitmap((const char**)_default_instrument_xpm); 
   dc.SelectObject(*bitmap);
   AColor::Bevel(dc, false, bev);
   pMusicalInstrument = new MusicalInstrument(bitmap, wxEmptyString);
   mMusicalInstruments.Add(pMusicalInstrument);
}

// event handlers

void MixerBoard::OnSize(wxSizeEvent &evt)
{
   // this->FitInside() doesn't work, and it doesn't happen automatically. Is wxScrolledWindow wrong?
   mScrolledWindow->SetSize(evt.GetSize());
   
   for (unsigned int i = 0; i < mMixerTrackClusters.GetCount(); i++)
      mMixerTrackClusters[i]->UpdateHeight();
   this->RefreshTrackClusters(true);
}


// class MixerBoardFrame

BEGIN_EVENT_TABLE(MixerBoardFrame, wxFrame)
   EVT_CLOSE(MixerBoardFrame::OnCloseWindow)
   EVT_MAXIMIZE(MixerBoardFrame::OnMaximize)
   EVT_SIZE(MixerBoardFrame::OnSize)
END_EVENT_TABLE()

// Default to fitting one track.
const wxSize kDefaultSize = 
   wxSize(MIXER_BOARD_MIN_WIDTH, MIXER_BOARD_MIN_HEIGHT); 

MixerBoardFrame::MixerBoardFrame(AudacityProject* parent)
: wxFrame(parent, -1,
            wxString::Format(_("Audacity Mixer Board%s"), 
                              ((parent->GetName() == wxEmptyString) ? 
                                 wxT("") : 
                                 wxString::Format(wxT(" - %s"),
                                                parent->GetName().c_str()).c_str())), 
            wxDefaultPosition, kDefaultSize, 
            //vvv Bug in wxFRAME_FLOAT_ON_PARENT:
            // If both the project frame and MixerBoardFrame are minimized and you restore MixerBoardFrame, you can't restore project frame until you close
            // MixerBoardFrame, but then project frame and MixerBoardFrame are restored but MixerBoardFrames is unresponsive because it thinks it's not shown.
            //    wxDEFAULT_FRAME_STYLE | wxFRAME_FLOAT_ON_PARENT)
            wxDEFAULT_FRAME_STYLE)
{
   mMixerBoard = new MixerBoard(parent, this, wxDefaultPosition, kDefaultSize);
  
   this->SetSizeHints(MIXER_BOARD_MIN_WIDTH, MIXER_BOARD_MIN_HEIGHT); 

   mMixerBoard->UpdateTrackClusters();

   // loads either the XPM or the windows resource, depending on the platform
   #if !defined(__WXMAC__) && !defined(__WXX11__)
      #ifdef __WXMSW__
         wxIcon ic(wxICON(AudacityLogo));
      #else
         wxIcon ic(wxICON(AudacityLogo48x48));
      #endif
      SetIcon(ic);
   #endif
}

MixerBoardFrame::~MixerBoardFrame()
{
}

// event handlers
void MixerBoardFrame::OnCloseWindow(wxCloseEvent &WXUNUSED(event))
{
   this->Hide();
}

void MixerBoardFrame::OnMaximize(wxMaximizeEvent &event)
{
   // Update the size hints to show all tracks before skipping to let default handling happen.
   mMixerBoard->UpdateWidth();
   event.Skip();
}

void MixerBoardFrame::OnSize(wxSizeEvent &event)
{
   mMixerBoard->SetSize(this->GetClientSize());
}

#endif // EXPERIMENTAL_MIXER_BOARD