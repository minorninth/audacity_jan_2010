/**********************************************************************

  Audacity: A Digital Audio Editor

  MixerToolBar.cpp

  Dominic Mazzoni
 
  See MixerToolBar.h for details

**********************************************************************/

#include "MixerToolBar.h"

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/defs.h>
#include <wx/choice.h>
#include <wx/dcmemory.h>
#include <wx/event.h>
#include <wx/brush.h>
#include <wx/intl.h>
#include <wx/log.h>
#include <wx/settings.h>
#include <wx/statbmp.h>
#endif

#include <wx/image.h>
#include <wx/tooltip.h>

#include "Audacity.h"
#include "AudioIO.h"
#include "ImageManipulation.h"
#include "widgets/ASlider.h"
#include "Prefs.h"
#include "Project.h"
#include "AColor.h"

#if USE_PORTMIXER
#include "AudioIO.h"
#endif

#include "../images/MixerImages.h"

////////////////////////////////////////////////////////////
/// Methods for MixerToolBar
////////////////////////////////////////////////////////////

enum {
   FirstID = 2000,
   OutputVolumeID,
   InputVolumeID,
   InputSourceID
};


BEGIN_EVENT_TABLE(MixerToolBar, ToolBar)
   EVT_PAINT(MixerToolBar::OnPaint)
   EVT_SLIDER(OutputVolumeID, MixerToolBar::SetMixer)
   EVT_SLIDER(InputVolumeID, MixerToolBar::SetMixer)
   EVT_CHOICE(InputSourceID, MixerToolBar::SetMixer)
END_EVENT_TABLE()

//Standard contructor
MixerToolBar::MixerToolBar(wxWindow * parent):
   ToolBar()
{
   InitToolBar( parent,
                MixerBarID,
                _("Audacity Mixer Toolbar"),
                _("Mixer") );
}

MixerToolBar::~MixerToolBar()
{
   delete mPlayBitmap;
   delete mRecordBitmap;
   delete mInputSlider;
   delete mOutputSlider;
   if (mInputSourceChoice)
      delete mInputSourceChoice;
}

void MixerToolBar::RecreateTipWindows()
{
   // Hack to make sure they appear on top of other windows
   mInputSlider->RecreateTipWin();
   mOutputSlider->RecreateTipWin();
}

void MixerToolBar::Populate()
{
   wxColour backgroundColour =
       wxSystemSettings::GetColour(wxSYS_COLOUR_3DFACE);
   wxColour origColour(204, 204, 204);

   wxImage *speaker = new wxImage(wxBitmap(Speaker).ConvertToImage());
   wxImage *speakerAlpha = new wxImage(wxBitmap(SpeakerAlpha).ConvertToImage());
   wxImage *bkgnd = CreateSysBackground(25, 25, 1,
                                        backgroundColour);
   wxImage *speakerFinal = OverlayImage(bkgnd, speaker, speakerAlpha, 0, 0);
   wxImage *mic = new wxImage(wxBitmap(Mic).ConvertToImage());
   wxImage *micAlpha = new wxImage(wxBitmap(MicAlpha).ConvertToImage());
   wxImage *micFinal = OverlayImage(bkgnd, mic, micAlpha, 0, 0);

   mPlayBitmap = new wxBitmap(speakerFinal);
   mRecordBitmap = new wxBitmap(micFinal);

   delete speaker;
   delete speakerAlpha;
   delete bkgnd;
   delete speakerFinal;
   delete mic;
   delete micAlpha;
   delete micFinal;

   Add( new wxStaticBitmap( this,
                            wxID_ANY, 
                            *mPlayBitmap ), 0, wxALIGN_CENTER );

   mOutputSlider = new ASlider(this, OutputVolumeID, _("Output Volume"),
                               wxDefaultPosition, wxSize(130, 25));
   mOutputSlider->SetLabel( wxT("Slider-Output") );
   Add( mOutputSlider, 0, wxALIGN_CENTER );

   Add( new wxStaticBitmap( this,
                            wxID_ANY, 
                            *mRecordBitmap ), 0, wxALIGN_CENTER );

   mInputSlider = new ASlider(this, InputVolumeID, _("Input Volume"),
                              wxDefaultPosition, wxSize(130, 25));
   mInputSlider->SetLabel( wxT("Slider-Input") );
   Add( mInputSlider, 0, wxALIGN_CENTER );

   mInputSourceChoice = NULL;

#if USE_PORTMIXER
   unsigned int    j;
   int leftPosition = 355;

   wxArrayString inputSources = gAudioIO->GetInputSourceNames();

   wxString *choices = new wxString[ inputSources.GetCount() ];
   for( j = 0; j < inputSources.GetCount(); j++ )
   {
      choices[ j ] = inputSources[ j ];
   }

   mInputSourceChoice = new wxChoice(this, InputSourceID,
                                     wxDefaultPosition,
                                     wxDefaultSize,
                                     j,
                                     choices );
   delete [] choices;
   Add( mInputSourceChoice, 0, wxALIGN_CENTER );

   if (inputSources.GetCount() == 0)
      mInputSourceChoice->Enable(false);

   // Set choice control to default value
   float inputVolume;
   float playbackVolume;
   int inputSource;
   gAudioIO->GetMixer(&inputSource, &inputVolume, &playbackVolume);
   mInputSourceChoice->SetSelection(inputSource);

   UpdateControls();

#endif
}

void MixerToolBar::UpdateControls()
{
#if USE_PORTMIXER
   float inputVolume;
   float playbackVolume;
   int inputSource;

   gAudioIO->GetMixer(&inputSource, &inputVolume, &playbackVolume);

   // This causes weird GUI behavior and isn't really essential.
   // We could enable it again later.
   //if (inputSource != mInputSourceChoice->GetSelection())
   //    mInputSourceChoice->SetSelection(inputSource);
   mOutputSlider->Set(playbackVolume);
   mInputSlider->Set(inputVolume);
#endif // USE_PORTMIXER
}

void MixerToolBar::SetMixer(wxCommandEvent &event)
{
#if USE_PORTMIXER
   float inputVolume = mInputSlider->Get();
   float outputVolume = mOutputSlider->Get();
   int inputSource = mInputSourceChoice->GetSelection();

   gAudioIO->SetMixer(inputSource, inputVolume, outputVolume);
#endif // USE_PORTMIXER
}

// Indentation settings for Vim and Emacs and unique identifier for Arch, a
// version control system. Please do not modify past this point.
//
// Local Variables:
// c-basic-offset: 3
// indent-tabs-mode: nil
// End:
//
// vim: et sts=3 sw=3
// arch-tag: 6a50243e-9fc9-4f0f-b344-bd3044dc09ad

