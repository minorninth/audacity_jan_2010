#include <Sound.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  SndChannelPtr            chan;
  SndDoubleBufferHeader    dbheader;
  SndDoubleBuffer          *buffer[2];
  char                     *nextBuffer;
  int                      frameSize;
  int                      curBuffer;
  int                      curSize;
  int                      bufferSize;
  int                      firstTime;
  int                      finished;
  int                      busy;
} buffer_state;
	
#ifdef __cplusplus
}
#endif
