#include "entropy.h"

double avg_entropy; //debug

int makehist(unsigned char *S, int *hist, int len)
{
	int wherechar[256];
	int i, histlen;
	histlen = 0;
	for (i = 0; i < 256; i++)
		wherechar[i] = -1;
	for (i = 0; i < len; i++)
	{
		if (wherechar[(int)S[i]] == -1)
		{
			wherechar[(int)S[i]] = histlen;
			histlen++;
		}
		hist[wherechar[(int)S[i]]]++;
	}
	return histlen;
}

double entropy(int *hist, int histlen, int len)
{
	int i;
	double H;
	H = 0;
	for (i = 0; i < histlen; i++)
	{
		H -= (double)hist[i] / len * log2((double)hist[i] / len);
	}
	return H;
}

int process_entropy(const char buffer[BUFFER_MAX], bool isdebug, int f)
{

	int len, *hist, histlen;
	double H;
	avg_entropy = 0;

	int trigger = 0;
	len = BUFFER_LEN; 
	char t_buffer[BUFFER_LEN];
	memset(t_buffer, 0, BUFFER_LEN);

	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (i < len) // index under len
		{
			t_buffer[i] = buffer[i];
		}
		else // index greater than len EXAMPLE: len = 20 20-th element must be on 0;
		{
			t_buffer[i % len] = buffer[i];
		}
		if (i % len == 0) // may be bug?? Tryin` to check if len cycles passed
		{
			hist = (int *)calloc(len, sizeof(int)); // carefully with this!

			histlen = makehist((unsigned char *)t_buffer, hist, len);

			// hist now has no order (known to the program) but that doesn't matter
			H = entropy(hist, histlen, len);
			if (H > ENTROPY_TRESH)
			{
				trigger++;
				if (isdebug) printf(" Entropy: %lf  FREQ: %f", H, f*STEP+FREQ), printf("\n");
			}
			avg_entropy += H;
			
				
			free(hist);
		}
	}
	avg_entropy /= fRange;
	//if (isdebug) printf(" AVG: %lf  CNT: %d", avg_entropy, trigger), printf("\n");

	return trigger;
}
