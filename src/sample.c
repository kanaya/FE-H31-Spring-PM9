#include <stdio.h>

#define InName "sample.c"

#define Swap(x, y) (x ^= y, y ^= x, x ^= y)

int main() {
  FILE *infile;
  int chr, i;
  /* 1 */
  int ih, ix, code[256];
  long cnt;
  long freq[256];

  for (chr = 0; chr <= 255; chr++)
    freq[chr] = 0;

  infile = fopen(InName, "rb");
  cnt = 0;
  while ((chr = fgetc(infile)) != EOF) {
    cnt++;
    freq[chr]++;
  }
  fclose(infile);

  printf(" %10ld bytes processed\n\n", /* a */ cnt);
  for (i = 0; i < 64; i++) {
    for (chr = i; chr <= /* b */ i + 192; chr += /* c */ 64) {
      if ((0x20 <= chr) && (chr <= 0x7E))
	printf(" %10ld %02X '%c'", freq[chr], chr, chr);
      else
	printf(" %10ld %02X    ", freq[chr], chr);
    }
    printf("\n");
  }

  /* (2) */
  for (i = 0; i <= 255; i++)
    code[i] = i;
  ih = 255;
  while (ih > 0) {
    /* (4) */
    ix = 0;
    for (i = 0; i < ih; i++) {
      if (freq[i] < freq[i+1]) {
	Swap(code[i], code[i+1]);
	Swap(freq[i], freq[i+1]);
	/* (7) */
	ix = i;
      }
    }
    /* (8) */
    /* ih--; */
    ih = ix;    
  }
  printf("\n");

  for (i = 0; i < 64; i++) {
    for (chr = i; chr <= /* b */ i + 192; chr += /* c */ 64) {
      if ((0x20 <= code[chr]) && (code[chr] <= 0x7E))
	printf(" %10ld %02X '%c'", freq[chr], code[chr], code[chr]);
      else
	printf(" %10ld %02X    ", freq[chr], code[chr]);
    }
    printf("\n");
  }
  return 0;
}
