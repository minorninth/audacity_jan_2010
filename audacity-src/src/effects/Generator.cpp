/**********************************************************************

  Audacity: A Digital Audio Editor

  Generator.h

  Two Abstract classes, Generator, and BlockGenerator, that effects which
  generate audio should derive from.  
  
  Block Generator breaks the synthesis task up into smaller parts.

  Dominic Mazzoni
  Vaughan Johnson

**********************************************************************/
#include "Generator.h"


bool Generator::Process()
{
   if (mDuration < 0.0)
      return false;

   BeforeGenerate();

   // Set up mOutputTracks. This effect needs Track::All because it uses ClearAndPaste
   // that need to have label tracks.
   this->CopyInputTracks(Track::All);

   // Iterate over the tracks
   bool bGoodResult = true;
   int ntrack = 0;
   TrackListIterator iter(mOutputTracks);
   Track* t = iter.First();

   // we only do a "group change" in the first selected track of the group. 
   // ClearAndPaste has a call to Paste that does changes to the group tracks
   bool first = true;

   while (t != NULL)
   {
      if (t->GetKind() == Track::Label)
         first = true;
      else if (t->GetKind() == Track::Wave && t->GetSelected()) {
         WaveTrack* track = (WaveTrack*)t;
         
         bool editClipCanMove;
         gPrefs->Read(wxT("/GUI/EditClipCanMove"), &editClipCanMove, true);

         if (!editClipCanMove && mT0 < track->GetStartTime() && mT0 + mDuration > track->GetStartTime()) {
            wxMessageBox(
               _("There is not enough room available to generate the audio"),
               _("Error"), wxICON_STOP);   
            Failure();
            return false;
         }

         if (mDuration > 0.0)
         {
            // Create a temporary track
            WaveTrack *tmp = mFactory->NewWaveTrack(track->GetSampleFormat(),
                                                    track->GetRate());
            BeforeTrack(*track);

            // Fill it with data
            if (!GenerateTrack(tmp, *track, ntrack))
               bGoodResult = false;
            else {
               // Transfer the data from the temporary track to the actual one
               tmp->Flush();
               if (first) {
                  bGoodResult = track->ClearAndPaste(mT0, mT1, tmp, true, true, mOutputTracks);
                  first = false;
               }
               else {
                  bGoodResult = track->HandleClear(mT0, mT1, false, false);
                  if (bGoodResult)
                     bGoodResult = track->HandlePaste(mT0, tmp);
               }
               delete tmp;
            }

            if (!bGoodResult) {
               Failure();
               return false;
            }
         }
         else
         {
            // If the duration is zero, there's no need to actually
            // generate anything
            track->Clear(mT0, mT1);
         }

         ntrack++;
      }
      // Move on to the next track
      t = iter.Next();
   }

   Success();

   this->ReplaceProcessedTracks(bGoodResult);

   mT1 = mT0 + mDuration; // Update selection.

   return true;
}

bool BlockGenerator::GenerateTrack(WaveTrack *tmp,
                                   const WaveTrack &track,
                                   int ntrack)
{
   bool bGoodResult = true;
   numSamples = track.TimeToLongSamples(mDuration);
   sampleCount i = 0;
   float *data = new float[tmp->GetMaxBlockSize()];
   sampleCount block = 0;

   while ((i < numSamples) && bGoodResult) {
      block = tmp->GetBestBlockSize(i);
      if (block > (numSamples - i))
         block = numSamples - i;

      GenerateBlock(data, track, block);

      // Add the generated data to the temporary track
      tmp->Append((samplePtr)data, floatSample, block);
      i += block;

      // Update the progress meter
      if (TrackProgress(ntrack, (double)i / numSamples))
         bGoodResult = false;
   }
   delete[] data;
   return bGoodResult;
}
