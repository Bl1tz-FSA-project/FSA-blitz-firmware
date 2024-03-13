#include "init/init.h"

extern double avg_entropy; //debug

#define ENTROPY_TRESH 1.0 //sensitivity of entropy filter

#ifndef BUFFER_MAX
#define BUFFER_MAX 256
#endif

//BUFFER_MAX % BUFFER_LEN must be 0!
#ifndef BUFFER_LEN
#define BUFFER_LEN 32 
#endif

#ifndef TERM
#define TERM 0xff
#endif

int makehist(unsigned char *S,int *hist,int len);

double entropy(int *hist,int histlen,int len);

int process_entropy(const char packets[BUFFER_MAX], bool isdebug, int f);
