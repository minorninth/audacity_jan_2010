/**********************************************************************

   Audacity: A Digital Audio Editor

   ExportFFmpeg.cpp

   Audacity(R) is copyright (c) 1999-2008 Audacity Team.
   License: GPL v2.  See License.txt.

   LRN

******************************************************************//**

\class ExportFFmpeg
\brief Controlling class for FFmpeg exporting.  Creates the options 
dialog of the appropriate type, adds tags and invokes the export 
function.

*//*******************************************************************/


#include "../Audacity.h"   // keep ffmpeg before wx because they interact
#include "../FFmpeg.h"     // and Audacity.h before FFmpeg for config*.h

#include <wx/choice.h>
#include <wx/intl.h>
#include <wx/timer.h>
#include <wx/msgdlg.h>
#include <wx/progdlg.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/window.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>

#include "../FileFormats.h"
#include "../Internat.h"
#include "../LabelTrack.h"
#include "../Mix.h"
#include "../Prefs.h"
#include "../Project.h"
#include "../Tags.h"
#include "../Track.h"
#include "../WaveTrack.h"

#include "Export.h"

#include "ExportFFmpegDialogs.h"

#if defined(USE_FFMPEG)

extern FFmpegLibs *FFmpegLibsInst;


//----------------------------------------------------------------------------
// ExportFFmpeg
//----------------------------------------------------------------------------

class ExportFFmpeg : public ExportPlugin
{
public:

   ExportFFmpeg();
   void Destroy();

   /// Format intialization
   bool Init(const char *shortname, AudacityProject *project);
   
   /// Codec intialization
   bool InitCodecs(AudacityProject *project);

   /// Writes metadata
   bool AddTags(Tags *metadata);

   /// Encodes audio
   bool EncodeAudioFrame(int16_t *pFrame, int frameSize);

   /// Flushes audio encoder
   bool Finalize();

   /// Shows options dialog
   ///\param format - index of export type
   bool DisplayOptions(AudacityProject *project = NULL, int format = 0);

   /// Check whether or not current project sample rate is compatible with the export codec
   bool CheckSampleRate(int rate, int lowrate, int highrate, const int *sampRates);

   /// Asks user to resample the project or cancel the export procedure
   int  AskResample(int bitrate, int rate, int lowrate, int highrate, const int *sampRates);

   /// Exports audio
   ///\param project Audacity project
   ///\param fName output file name
   ///\param selectedOnly true if exporting only selected audio
   ///\param t0 audio start time
   ///\param t1 audio end time
   ///\param mixerSpec mixer
   ///\param metadata tags to write into file
   ///\param subformat index of export type
   ///\return true if export succeded
   bool Export(AudacityProject *project,
      int channels,
      wxString fName,
      bool selectedOnly,
      double t0,
      double t1,
      MixerSpec *mixerSpec = NULL,
      Tags *metadata = NULL,
      int subformat = 0);

private:

   AVFormatContext *	mEncFormatCtx;			   // libavformat's context for our output file
   AVOutputFormat  *	mEncFormatDesc;			// describes our output file to libavformat

   AVStream        *	mEncAudioStream;			// the output audio stream (may remain NULL)
   AVCodecContext  *	mEncAudioCodecCtx;		// the encoder for the output audio stream
   uint8_t         *	mEncAudioEncodedBuf;		// buffer to hold frames encoded by the encoder
   int			      mEncAudioEncodedBufSiz;		
   AVFifoBuffer		mEncAudioFifo;				// FIFO to write incoming audio samples into
   uint8_t         *	mEncAudioFifoOutBuf;		// buffer to read _out_ of the FIFO into

   bool              mCancelled;
   wxString          mName;

   int               mSubFormat;
   int               mBitRate;
   int               mSampleRate;
   int               mChannels;
   bool              mSupportsUTF8;
};

ExportFFmpeg::ExportFFmpeg()
:  ExportPlugin()
{

   PickFFmpegLibs();
   int newfmt;
   // Adds export types from the export type list
   for (newfmt = 0; newfmt < FMT_LAST; newfmt++)
   {
      int fmtindex = AddFormat() - 1;
      SetFormat(fmts[newfmt].name,fmtindex);
      AddExtension(fmts[newfmt].extension,fmtindex);
      // For some types add other extensions
      switch(newfmt)
      {
      case FMT_M4A:
         AddExtension(wxString(wxT("mov")),fmtindex);
         AddExtension(wxString(wxT("3gp")),fmtindex);
         AddExtension(wxString(wxT("mp4")),fmtindex);
         break;
      case FMT_WMA2:
         AddExtension(wxString(wxT("asf")),fmtindex);
         AddExtension(wxString(wxT("wmv")),fmtindex);
         break;
      default:
         break;
      }

     SetMaxChannels(fmts[newfmt].maxchannels,fmtindex);
     SetCanMetaData(fmts[newfmt].canmetadata,fmtindex);
     SetDescription(fmts[newfmt].description,fmtindex);
   }

   mEncFormatCtx = NULL;			// libavformat's context for our output file
   mEncFormatDesc = NULL;			// describes our output file to libavformat
   mEncAudioStream = NULL;			// the output audio stream (may remain NULL)
   mEncAudioCodecCtx = NULL;		// the encoder for the output audio stream
   mEncAudioEncodedBuf = NULL;	// buffer to hold frames encoded by the encoder
   #define MAX_AUDIO_PACKET_SIZE (128 * 1024)
   mEncAudioEncodedBufSiz = 4*MAX_AUDIO_PACKET_SIZE;
   mEncAudioFifoOutBuf = NULL;	// buffer to read _out_ of the FIFO into
   mSampleRate = 0;
   mSupportsUTF8 = true;
}

void ExportFFmpeg::Destroy()
{
   DropFFmpegLibs();
   delete this;
}

bool ExportFFmpeg::Init(const char *shortname,AudacityProject *project)
{
   int err;
   FFmpegLibsInst->LoadLibs(NULL,true);

   if (!FFmpegLibsInst->ValidLibsLoaded()) return false;

   FFmpegLibsInst->av_log_set_callback(av_log_wx_callback);

   AVFormatParameters	fpOutFile;

   // See if libavformat has modules that can write our output format. If so, mEncFormatDesc
   // will describe the functions used to write the format (used internally by libavformat)
   // and the default video/audio codecs that the format uses.
   if ((mEncFormatDesc = FFmpegLibsInst->guess_format(shortname, OSFILENAME(mName), NULL)) == NULL)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't determine format description for file \"%s\"."), mName.c_str());
      return false;
   }

   // mEncFormatCtx is used by libavformat to carry around context data re our output file.
   if ((mEncFormatCtx = FFmpegLibsInst->av_alloc_format_context()) == NULL)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't allocate output format context."));
      return false;
   }

   // Initialise the output format context.
   mEncFormatCtx->oformat = mEncFormatDesc;
   wxString tName(mName);
   memcpy(mEncFormatCtx->filename,OSFILENAME(mName),strlen(OSFILENAME(mName))+1);
   
   // At the moment Audacity can export only one audio stream
   if ((mEncAudioStream = FFmpegLibsInst->av_new_stream(mEncFormatCtx, 1)) == NULL)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't add audio stream to output file \"%s\"."), mName.c_str());
      return false;
   }

   mEncFormatCtx->timestamp = 0;

   // Open the output file.
   if (!(mEncFormatDesc->flags & AVFMT_NOFILE))
   {
      if ((err = FFmpegLibsInst->url_fopen(&mEncFormatCtx->pb, mEncFormatCtx->filename, URL_WRONLY)) < 0)
      {
         wxLogMessage(wxT("FFmpeg : ERROR - Can't open output file \"%s\" to write. Error code is %d."), mName.c_str(),err);
         return false;
      }
   }

   // Set default parameters on the format context.
   memset(&fpOutFile, 0, sizeof(AVFormatParameters));
   if ((err = FFmpegLibsInst->av_set_parameters(mEncFormatCtx, &fpOutFile)) < 0)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't set output parameters for output file \"%s\". Error code is %d."), mName.c_str(),err);
      return false;
   }

   // I have no idea what is this
   mEncFormatCtx->preload   = (int)(0.5 * AV_TIME_BASE);
   mEncFormatCtx->max_delay = (int)(0.7 * AV_TIME_BASE);

   // Open the audio stream's codec and initialise any stream related data.
   if (!InitCodecs(project))
      return false;

   // Write headers to the output file.
   if ((err = FFmpegLibsInst->av_write_header(mEncFormatCtx)) < 0)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't write headers to output file \"%s\". Error code is %d."), mName.c_str(),err);

      return false;
   }

   return true;
}

bool ExportFFmpeg::CheckSampleRate(int rate, int lowrate, int highrate, const int *sampRates)
{
   if (rate < lowrate || rate > highrate) return false;
   for (int i = 0; sampRates[i] > 0; i++)
      if (rate == sampRates[i]) return true;
   return false;
}

bool ExportFFmpeg::InitCodecs(AudacityProject *project)
{
   AVCodec *	codec = NULL;

   // Configure the audio stream's codec context.
   mEncAudioCodecCtx = mEncAudioStream->codec;
  
   FFmpegLibsInst->avcodec_get_context_defaults(mEncAudioCodecCtx);

   mEncAudioCodecCtx->codec_id = fmts[mSubFormat].codecid;
   mEncAudioCodecCtx->codec_type = CODEC_TYPE_AUDIO;
   mEncAudioCodecCtx->codec_tag = FFmpegLibsInst->av_codec_get_tag(mEncFormatCtx->oformat->codec_tag,mEncAudioCodecCtx->codec_id);
   mSampleRate = (int)project->GetRate();
   mEncAudioCodecCtx->global_quality = -1; //quality mode is off by default;

   // Each export type has it's own settings
   switch (mSubFormat)
   {
   case FMT_M4A:
      mEncAudioCodecCtx->bit_rate = 0;
      mEncAudioCodecCtx->bit_rate *= mChannels;
      mEncAudioCodecCtx->profile = FF_PROFILE_AAC_LOW;
      mEncAudioCodecCtx->cutoff = mSampleRate/2;
      mEncAudioCodecCtx->global_quality = gPrefs->Read(wxT("/FileFormats/AACQuality"),-1);
      if (!CheckSampleRate(mSampleRate,iAACSampleRates[0],iAACSampleRates[11],&iAACSampleRates[0]))
         mSampleRate = AskResample(mEncAudioCodecCtx->bit_rate,mSampleRate,iAACSampleRates[0],iAACSampleRates[11],&iAACSampleRates[0]);
      break;
   case FMT_AC3:
      mEncAudioCodecCtx->bit_rate = gPrefs->Read(wxT("/FileFormats/AC3BitRate"), 192000);
      if (!CheckSampleRate(mSampleRate,iAC3SampleRates[0],iAC3SampleRates[2],&iAC3SampleRates[0]))
         mSampleRate = AskResample(mEncAudioCodecCtx->bit_rate,mSampleRate,iAC3SampleRates[0],iAC3SampleRates[2],&iAC3SampleRates[0]);
      break;
   case FMT_GSMAIFF:
   case FMT_GSMMSWAV:
      mSampleRate = 8000;
      mEncAudioCodecCtx->bit_rate = 13000;
      break;
   case FMT_AMRNB:
      mSampleRate = 8000;
      mEncAudioCodecCtx->bit_rate = gPrefs->Read(wxT("/FileFormats/AMRNBBitRate"), 12200);
      break;
   case FMT_AMRWB:
      mSampleRate = 16000;
      mEncAudioCodecCtx->bit_rate = gPrefs->Read(wxT("/FileFormats/AMRWBBitRate"), 23850);
      break;
   case FMT_WMA2:
      mEncAudioCodecCtx->bit_rate = gPrefs->Read(wxT("/FileFormats/WMABitRate"), 198000);
      //Can't find any samplerate restrictions for WMA.
      break;
   case FMT_OTHER:
      memcpy(mEncAudioStream->language,gPrefs->Read(wxT("/FileFormats/FFmpegLanguage"),wxT("")).c_str(),4);
      mEncAudioCodecCtx->sample_rate = gPrefs->Read(wxT("/FileFormats/FFmpegSampleRate"),(long)0);
      if (mEncAudioCodecCtx->sample_rate != 0) mSampleRate = mEncAudioCodecCtx->sample_rate;
      mEncAudioCodecCtx->bit_rate = gPrefs->Read(wxT("/FileFormats/FFmpegBitRate"), (long)0);
      memcpy(&mEncAudioCodecCtx->codec_tag,gPrefs->Read(wxT("/FileFormats/FFmpegTag"),wxT("")).c_str(),4);
      mEncAudioCodecCtx->global_quality = gPrefs->Read(wxT("/FileFormats/FFmpegQuality"),(long)-1);
      mEncAudioCodecCtx->cutoff = gPrefs->Read(wxT("/FileFormats/FFmpegCutOff"),(long)0);
      mEncAudioCodecCtx->use_lpc = gPrefs->Read(wxT("/FileFormats/FFmpegUseLPC"),true);
      mEncAudioCodecCtx->flags2 = 0;
      if (gPrefs->Read(wxT("/FileFormats/FFmpegBitReservoir"),true)) mEncAudioCodecCtx->flags2 |= CODEC_FLAG2_BIT_RESERVOIR;
      mEncAudioCodecCtx->use_lpc = gPrefs->Read(wxT("/FileFormats/FFmpegUseLPC"),true);
      mEncAudioCodecCtx->compression_level = gPrefs->Read(wxT("/FileFormats/FFmpegCompLevel"),-1);
      mEncAudioCodecCtx->frame_size = gPrefs->Read(wxT("/FileFormats/FFmpegFrameSize"),(long)0);
      mEncAudioCodecCtx->lpc_coeff_precision = gPrefs->Read(wxT("/FileFormats/FFmpegLPCCoefPrec"),(long)0);
      mEncAudioCodecCtx->min_prediction_order = gPrefs->Read(wxT("/FileFormats/FFmpegMinPredOrder"),(long)-1);
      mEncAudioCodecCtx->max_prediction_order = gPrefs->Read(wxT("/FileFormats/FFmpegMaxPredOrder"),(long)-1);
      mEncAudioCodecCtx->min_partition_order = gPrefs->Read(wxT("/FileFormats/FFmpegMinPartOrder"),(long)-1);
      mEncAudioCodecCtx->max_partition_order = gPrefs->Read(wxT("/FileFormats/FFmpegMaxPartOrder"),(long)-1);
      mEncAudioCodecCtx->prediction_order_method = gPrefs->Read(wxT("/FileFormats/FFmpegPredOrderMethod"),(long)0);
      mEncFormatCtx->mux_rate = gPrefs->Read(wxT("/FileFormats/FFmpegMuxRate"),(long)0);
      mEncFormatCtx->packet_size = gPrefs->Read(wxT("/FileFormats/FFmpegPacketSize"),(long)0);
      mEncAudioCodecCtx->codec_id = (CodecID)gPrefs->Read(wxT("/FileFormats/FFmpegCodec"), mEncFormatDesc->audio_codec);
      break;
   default:
      return false;
   }

   // This happens if user refused to resample the project
   if (mSampleRate == 0) return false;

   if (mEncAudioCodecCtx->global_quality >= 0)
   {
      mEncAudioCodecCtx->bit_rate = 0;
      mEncAudioCodecCtx->flags |= CODEC_FLAG_QSCALE;
   }
   mEncAudioCodecCtx->sample_rate = mSampleRate;
   mEncAudioCodecCtx->channels = mChannels;
   mEncAudioCodecCtx->time_base.num = 0;
   mEncAudioCodecCtx->time_base.den = 1;
   mEncAudioCodecCtx->sample_fmt = SAMPLE_FMT_S16;
   mEncAudioCodecCtx->strict_std_compliance = FF_COMPLIANCE_STRICT;

   // Is the required audio codec compiled into libavcodec?
   if ((codec = FFmpegLibsInst->avcodec_find_encoder(mEncAudioCodecCtx->codec_id)) == NULL)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't find audio codec 0x%x."),mEncAudioCodecCtx->codec_id);
      wxMessageBox(wxString::Format(wxT("FFmpeg cannot find audio codec 0x%x.\nSupport for this codec is probably not compiled in."),mEncAudioCodecCtx->codec_id));
      return false;
   }

   if (mEncFormatCtx->oformat->flags & AVFMT_GLOBALHEADER)
   {
      mEncAudioCodecCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
      mEncAudioStream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
   }

   // Open the codec.
   if (FFmpegLibsInst->avcodec_open(mEncAudioCodecCtx, codec) < 0) 
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't open audio codec 0x%x."),mEncAudioCodecCtx->codec_id);
      return false;
   }
 
   wxLogMessage(wxT("FFmpeg : Audio Output Codec Frame Size: %d samples."), mEncAudioCodecCtx->frame_size);

   if ((mEncAudioCodecCtx->codec_id >= CODEC_ID_PCM_S16LE) && (mEncAudioCodecCtx->codec_id <= CODEC_ID_PCM_DVD))
   {
      mEncAudioEncodedBufSiz = FF_MIN_BUFFER_SIZE;
   }
   // Allocate a buffer for the encoder to store encoded audio frames into.
   if ((mEncAudioEncodedBuf = (uint8_t*)FFmpegLibsInst->av_malloc(mEncAudioEncodedBufSiz)) == NULL)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't allocate buffer to hold encoded audio."));
      return false;
   }

   // The encoder may require a minimum number of raw audio samples for each encoding but we can't
   // guarantee we'll get this minimum each time an audio frame is decoded from the input file so 
   // we use a FIFO to store up incoming raw samples until we have enough for one call to the codec.
   FFmpegLibsInst->av_fifo_init(&mEncAudioFifo, 1024);

   // Allocate a buffer to read OUT of the FIFO into. The FIFO maintains its own buffer internally.
   if ((mEncAudioFifoOutBuf = (uint8_t*)FFmpegLibsInst->av_malloc(2*MAX_AUDIO_PACKET_SIZE)) == NULL)
   {
      wxLogMessage(wxT("FFmpeg : ERROR - Can't allocate buffer to read into from audio FIFO."));
      return false;
   }

   return true;
}

bool ExportFFmpeg::Finalize()
{
   int i, nEncodedBytes;

   // Flush the audio FIFO and encoder.
   for (;;)
   {
      AVPacket	pkt;
      int		nFifoBytes = FFmpegLibsInst->av_fifo_size(&mEncAudioFifo);	// any bytes left in audio FIFO?

      nEncodedBytes = 0;
      int		nAudioFrameSizeOut = mEncAudioCodecCtx->frame_size * mEncAudioCodecCtx->channels * sizeof(int16_t);
      if (mEncAudioCodecCtx->frame_size == 1) nAudioFrameSizeOut = mEncAudioEncodedBufSiz;

      // Flush the audio FIFO first if necessary. It won't contain a _full_ audio frame because
      // if it did we'd have pulled it from the FIFO during the last encodeAudioFrame() call - 
      // the encoder must support short/incomplete frames for this to work.
      if (nFifoBytes > 0)
      {
         // Fill audio buffer with zeroes. If codec tries to read the whole buffer,
         // it will just read silence. If not - who cares?
         memset(mEncAudioFifoOutBuf,0,nAudioFrameSizeOut);
         AVCodec *codec = mEncAudioCodecCtx->codec;

         // If codec supports CODEC_CAP_SMALL_LAST_FRAME, we can feed it with smaller frame
         // If codec is FLAC, feed it anyway (it doesn't have CODEC_CAP_SMALL_LAST_FRAME, but it works)
         // If frame_size is 1, then it's some kind of PCM codec, they don't have frames
         // If user configured the exporter to feed the encoder with silence
         if ((codec->capabilities & CODEC_CAP_SMALL_LAST_FRAME)
            || codec->id == CODEC_ID_FLAC
            || mEncAudioCodecCtx->frame_size == 1
            || gPrefs->Read(wxT("/FileFormats/OverrideSmallLastFrame"),(long)1)
            )
         {
            int nFrameSizeTmp = mEncAudioCodecCtx->frame_size;

            // The last frame is going to contain a smaller than usual number of samples.
            // For codecs without CODEC_CAP_SMALL_LAST_FRAME use normal frame size
            if (mEncAudioCodecCtx->frame_size != 1 && codec->capabilities & CODEC_CAP_SMALL_LAST_FRAME)
               mEncAudioCodecCtx->frame_size = nFifoBytes / (mEncAudioCodecCtx->channels * sizeof(int16_t));

            wxLogMessage(wxT("FFmpeg : Audio FIFO still contains %d bytes, writing %d sample frame ..."), 
               nFifoBytes, mEncAudioCodecCtx->frame_size);

            // Pull the bytes out from the FIFO and feed them to the encoder.
            if (FFmpegLibsInst->av_fifo_read(&mEncAudioFifo, mEncAudioFifoOutBuf, nFifoBytes) == 0)
            {
               if (mEncAudioCodecCtx->frame_size != 1)
                  nEncodedBytes = FFmpegLibsInst->avcodec_encode_audio(mEncAudioCodecCtx, mEncAudioEncodedBuf, mEncAudioEncodedBufSiz, (int16_t*)mEncAudioFifoOutBuf);
               else
                  nEncodedBytes = FFmpegLibsInst->avcodec_encode_audio(mEncAudioCodecCtx, mEncAudioEncodedBuf, nFifoBytes, (int16_t*)mEncAudioFifoOutBuf);
            }

            mEncAudioCodecCtx->frame_size = nFrameSizeTmp;		// restore the native frame size
         }
      }

      // Now flush the encoder.
      if (nEncodedBytes <= 0)
         nEncodedBytes = FFmpegLibsInst->avcodec_encode_audio(mEncAudioCodecCtx, mEncAudioEncodedBuf, mEncAudioEncodedBufSiz, NULL);

      if (nEncodedBytes <= 0)			
         break;

      // Okay, we got a final encoded frame we can write to the output file.
      FFmpegLibsInst->av_init_packet(&pkt);

      pkt.stream_index = mEncAudioStream->index;
      pkt.data = mEncAudioEncodedBuf;
      pkt.size = nEncodedBytes;
      pkt.flags |= PKT_FLAG_KEY;

      // Set presentation time of frame (currently in the codec's timebase) in the stream timebase.
      if(mEncAudioCodecCtx->coded_frame && mEncAudioCodecCtx->coded_frame->pts != AV_NOPTS_VALUE)
         pkt.pts = FFmpegLibsInst->av_rescale_q(mEncAudioCodecCtx->coded_frame->pts, mEncAudioCodecCtx->time_base, mEncAudioStream->time_base);

      if (FFmpegLibsInst->av_interleaved_write_frame(mEncFormatCtx, &pkt) != 0)
      {
         wxLogMessage(wxT("FFmpeg : ERROR - Couldn't write last audio frame to output file."));
         break;
      }
   }

   // Close the codecs.
   if (mEncAudioStream != NULL)
      FFmpegLibsInst->avcodec_close(mEncAudioStream->codec);

   // Write any file trailers.
   FFmpegLibsInst->av_write_trailer(mEncFormatCtx);

   for (i = 0; i < (int)mEncFormatCtx->nb_streams; i++)
   {
      FFmpegLibsInst->av_freep(&mEncFormatCtx->streams[i]->codec);
      FFmpegLibsInst->av_freep(&mEncFormatCtx->streams[i]);
   }

   // Close the output file if we created it.
   if (!(mEncFormatDesc->flags & AVFMT_NOFILE))
      FFmpegLibsInst->url_fclose(mEncFormatCtx->pb);

   // Free any buffers or structures we allocated.
   FFmpegLibsInst->av_free(mEncFormatCtx);

   if (mEncAudioEncodedBuf != NULL)
      FFmpegLibsInst->av_free(mEncAudioEncodedBuf);

   if (mEncAudioFifoOutBuf != NULL)
      FFmpegLibsInst->av_free(mEncAudioFifoOutBuf);

   FFmpegLibsInst->av_fifo_free(&mEncAudioFifo);
   return true;
}

bool ExportFFmpeg::EncodeAudioFrame(int16_t *pFrame, int frameSize)
{
   AVPacket	pkt;
   int		nBytesToWrite = 0;
   uint8_t *	pRawSamples = NULL;
   int		nAudioFrameSizeOut = mEncAudioCodecCtx->frame_size * mEncAudioCodecCtx->channels * sizeof(int16_t);
   if (mEncAudioCodecCtx->frame_size == 1) nAudioFrameSizeOut = mEncAudioEncodedBufSiz;
   int      ret;

   nBytesToWrite = frameSize;
   pRawSamples  = (uint8_t*)pFrame;
   FFmpegLibsInst->av_fifo_realloc(&mEncAudioFifo, FFmpegLibsInst->av_fifo_size(&mEncAudioFifo) + frameSize);
   // Put the raw audio samples into the FIFO.
   ret = FFmpegLibsInst->av_fifo_generic_write(&mEncAudioFifo, pRawSamples, nBytesToWrite,NULL);
   wxASSERT(ret == nBytesToWrite);

   // Read raw audio samples out of the FIFO in nAudioFrameSizeOut byte-sized groups to encode.
   while ((ret = FFmpegLibsInst->av_fifo_size(&mEncAudioFifo)) >= nAudioFrameSizeOut)
   {
      ret = FFmpegLibsInst->av_fifo_read(&mEncAudioFifo, mEncAudioFifoOutBuf, nAudioFrameSizeOut);
      FFmpegLibsInst->av_init_packet(&pkt);

      pkt.size = FFmpegLibsInst->avcodec_encode_audio(mEncAudioCodecCtx, 
         mEncAudioEncodedBuf, mEncAudioEncodedBufSiz,		// out
         (int16_t*)mEncAudioFifoOutBuf);				// in
      if (mEncAudioCodecCtx->frame_size == 1) { wxASSERT(pkt.size == mEncAudioEncodedBufSiz); }
      if (pkt.size < 0)
      {
         wxLogMessage(wxT("FFmpeg : ERROR - Can't encode audio frame."));
         return false;
      }

      // Rescale from the codec time_base to the AVStream time_base.
      if (mEncAudioCodecCtx->coded_frame && mEncAudioCodecCtx->coded_frame->pts != AV_NOPTS_VALUE)
         pkt.pts = FFmpegLibsInst->av_rescale_q(mEncAudioCodecCtx->coded_frame->pts, mEncAudioCodecCtx->time_base, mEncAudioStream->time_base);
      //wxLogMessage(wxT("FFmpeg : (%d) Writing audio frame with PTS: %lld."), mEncAudioCodecCtx->frame_number, pkt.pts);

      pkt.stream_index = mEncAudioStream->index;
      pkt.data = mEncAudioEncodedBuf;
      pkt.flags |= PKT_FLAG_KEY;

      // Write the encoded audio frame to the output file.
      if ((ret = FFmpegLibsInst->av_write_frame(mEncFormatCtx, &pkt)) != 0)
      {
         wxLogMessage(wxT("FFmpeg : ERROR - Failed to write audio frame to file."));
         return false;
      }
   }
   return true;
}


bool ExportFFmpeg::Export(AudacityProject *project,
                       int channels, wxString fName,
                       bool selectionOnly, double t0, double t1, MixerSpec *mixerSpec, Tags *metadata, int subformat)
{
   mChannels = channels;
   if (channels > fmts[subformat].maxchannels)
   {
      wxLogMessage(wxT("Attempted to export %d channels, but max. channels = %d"),channels,fmts[subformat].maxchannels);
      wxMessageBox(wxString::Format(wxT("Attempted to export %d channels, but max. channels for selected output format is %d"),channels,fmts[subformat].maxchannels),wxT("Error"));
      return false;
   }
   mName = fName;
   mSubFormat = subformat;
   TrackList *tracks = project->GetTracks();
   bool ret = true;

   if (mSubFormat >= FMT_LAST) return false;
   
   wxString shortname(fmts[mSubFormat].shortname);
   if (mSubFormat == FMT_OTHER)
      shortname = gPrefs->Read(wxT("/FileFormats/FFmpegFormat"),wxT("matroska"));
   ret = Init(shortname.mb_str(),project);

   if (!ret) return false;

   if (metadata == NULL) metadata = project->GetTags();

   if (fmts[mSubFormat].canmetadata)
   {
      this->mSupportsUTF8 = fmts[mSubFormat].canutf8;
      AddTags(metadata);
   }

   int pcmBufferSize = 1024;
   int numWaveTracks;
   WaveTrack **waveTracks;
   tracks->GetWaveTracks(selectionOnly, &numWaveTracks, &waveTracks);
   Mixer *mixer = new Mixer(numWaveTracks, waveTracks,
      tracks->GetTimeTrack(),
      t0, t1,
      channels, pcmBufferSize, true,
      mSampleRate, int16Sample, true, mixerSpec);

   ProgressDialog *progress = new ProgressDialog(wxFileName(fName).GetName(),
      selectionOnly ?
      wxString::Format(_("Exporting selected audio as %s"), fmts[mSubFormat].description) :
   wxString::Format(_("Exporting entire file as %s"), fmts[mSubFormat].description));

   bool cancelling = false;

   while(!cancelling) {
      sampleCount pcmNumSamples = mixer->Process(pcmBufferSize);

      if (pcmNumSamples == 0)
         break;

      short *pcmBuffer = (short *)mixer->GetBuffer();

      EncodeAudioFrame(pcmBuffer,(pcmNumSamples)*sizeof(int16_t)*mChannels);

      cancelling = !progress->Update(mixer->MixGetCurrentTime()-t0, t1-t0);
   }

   delete progress;

   delete mixer;

   Finalize();

   return !cancelling;
}

void AddStringTagUTF8(char field[], int size, wxString value)
{
      memset(field,0,size);
      memcpy(field,value.ToUTF8(),(int)strlen(value.ToUTF8()) > size -1 ? size -1 : strlen(value.ToUTF8()));
}

void AddStringTagANSI(char field[], int size, wxString value)
{
      memset(field,0,size);
      memcpy(field,value.mb_str(),(int)strlen(value.mb_str()) > size -1 ? size -1 : strlen(value.mb_str()));
}

bool ExportFFmpeg::AddTags(Tags *tags)
{
   if (tags == NULL) return false;
   void (*AddStringTag)(char [], int, wxString);
   if (mSupportsUTF8)
      AddStringTag = AddStringTagUTF8;
   else
      AddStringTag = AddStringTagANSI;
   AddStringTag(mEncFormatCtx->author, sizeof(mEncFormatCtx->author), tags->GetTag(TAG_ARTIST));
   AddStringTag(mEncFormatCtx->album, sizeof(mEncFormatCtx->album), tags->GetTag(TAG_ALBUM));
   AddStringTag(mEncFormatCtx->comment, sizeof(mEncFormatCtx->comment), tags->GetTag(TAG_COMMENTS));
   AddStringTag(mEncFormatCtx->genre, sizeof(mEncFormatCtx->genre), tags->GetTag(TAG_GENRE));
   tags->GetTag(TAG_YEAR).ToLong((long*)&mEncFormatCtx->year);
   tags->GetTag(TAG_TRACK).ToLong((long*)&mEncFormatCtx->track);

   return true;
}

//----------------------------------------------------------------------------
// AskResample dialog
//----------------------------------------------------------------------------

int ExportFFmpeg::AskResample(int bitrate, int rate, int lowrate, int highrate, const int *sampRates)
{
   wxDialog d(NULL, wxID_ANY, wxString(_("Invalid sample rate")));
   wxChoice *choice;
   ShuttleGui S(&d, eIsCreating);
   wxString text;

   S.StartVerticalLay();
   {
      S.SetBorder(10);
      S.StartStatic(_("Resample"));
      {
         S.StartHorizontalLay(wxALIGN_CENTER, false);
         {
            if (bitrate == 0) {
               text.Printf(_("The project sample rate (%d) is not supported by the current output\nfile format.  "), rate);
            }
            else {
               text.Printf(_("The project sample rate (%d) and bit rate (%d kbps) combination is not\nsupported by the current output file format.  "), rate, bitrate/1024);
            }

            text += _("You may resample to one of the rates below.");
            S.AddTitle(text);
         }
         S.EndHorizontalLay();

         wxArrayString choices;
         wxString selected = wxT("");
         for (int i = 0; sampRates[i] > 0; i++)
         {
            int label = sampRates[i];
            if (label >= lowrate && label <= highrate)
            {
               wxString name = wxString::Format(wxT("%d"),label);
               choices.Add(name);
               if (label <= rate)
               {
                  selected = name;
               }
            }
         }

         if (selected.IsEmpty())
         {
            selected = choices[0];
         }

         S.StartHorizontalLay(wxALIGN_CENTER, false);
         {
            choice = S.AddChoice(_("Sample Rates"),
                                 selected,
                                 &choices);
         }
         S.EndHorizontalLay();
      }
      S.EndStatic();

      S.AddStandardButtons();
   }
   S.EndVerticalLay();

   d.Layout();
   d.Fit();
   d.SetMinSize(d.GetSize());
   d.Center();

   if (d.ShowModal() == wxID_CANCEL) {
      return 0;
   }

   return wxAtoi(choice->GetStringSelection());
}


bool ExportFFmpeg::DisplayOptions(AudacityProject *project, int format)
{
   if (format == FMT_M4A)
   {
      ExportFFmpegAACOptions od(project);
      od.ShowModal();
      return true;
   }
   else if (format == FMT_AC3)
   {
      ExportFFmpegAC3Options od(project);
      od.ShowModal();
      return true;
   }
   else if ((format == FMT_GSMAIFF) || (format == FMT_GSMMSWAV))
   {
      wxMessageBox(wxT("No options for this format."));
      return true;
   }
   else if (format == FMT_AMRNB)
   {
      ExportFFmpegAMRNBOptions od(project);
      od.ShowModal();
      return true;
   }
   else if (format == FMT_AMRWB)
   {
      ExportFFmpegAMRWBOptions od(project);
      od.ShowModal();
      return true;
   }
   else if (format == FMT_WMA2)
   {
      ExportFFmpegWMAOptions od(project);
      od.ShowModal();
      return true;
   }
   else if (format == FMT_OTHER)
   {
      ExportFFmpegOptions od(project);
      od.ShowModal();
      return true;
   }

   return false;
}

//----------------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------------
ExportPlugin *New_ExportFFmpeg()
{
   return new ExportFFmpeg();
}

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
// arch-tag: c1f32472-520f-4864-8086-3dba0d593e84
