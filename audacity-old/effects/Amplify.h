/**********************************************************************

  Audacity: A Digital Audio Editor

  Amplify.h

  Robert Leidle

**********************************************************************/

#ifndef __AUDACITY_EFFECT_AMPLIFY__
#define __AUDACITY_EFFECT_AMPLIFY__

class wxString;

#include "Effect.h"

class WaveTrack;

class EffectAmplify: public Effect {

public:
  EffectAmplify();

  virtual wxString GetEffectName() { return wxString("Amplify..."); }

  virtual bool Begin(wxWindow *parent);
  virtual bool DoIt(WaveTrack *t,
		    sampleCount start,
		    sampleCount len);

private:
  float ratio;
};

#endif
