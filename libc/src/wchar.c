#include "../include/wchar.h"

static const unsigned char table[]{
  16,16,16,18,19,20,21,22,23,24,25,26,27,28,29,30,31,16,16,32,16,16,16,33,34,35,
36,37,38,39,16,16,40,16,16,16,16,16,16,16,16,16,16,16,41,42,16,16,43,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,44,16,45,46,47,48,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,49,16,16,50,
51,16,52,53,54,16,16,16,16,16,16,55,16,16,16,16,16,56,57,58,59,60,61,62,63,16,
16,64,16,65,66,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,67,68,16,16,16,69,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,16,16,16,16,16,70,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,16,71,72,16,16,16,16,16,16,16,73,16,16,16,16,16,74,16,16,16,16,16,16,16,75,
76,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,248,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,254,255,255,255,255,191,182,0,0,0,0,0,0,0,63,0,255,23,0,0,0,0,0,248,255,
255,0,0,1,0,0,0,0,0,0,0,0,0,0,0,192,191,159,61,0,0,0,128,2,0,0,0,255,255,255,
7,0,0,0,0,0,0,0,0,0,0,192,255,1,0,0,0,0,0,0,248,15,0,0,0,192,251,239,62,0,0,0,
0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,240,255,255,255,255,
255,7,0,0,0,0,0,0,20,254,33,254,0,12,0,0,0,2,0,0,0,0,0,0,16,30,32,0,0,12,0,0,
0,6,0,0,0,0,0,0,16,134,57,2,0,0,0,35,0,6,0,0,0,0,0,0,16,190,33,0,0,12,0,0,252,
2,0,0,0,0,0,0,144,30,32,64,0,12,0,0,0,4,0,0,0,0,0,0,0,1,32,0,0,0,0,0,0,1,0,0,
0,0,0,0,192,193,61,96,0,12,0,0,0,2,0,0,0,0,0,0,144,64,48,0,0,12,0,0,0,3,0,0,0,
0,0,0,24,30,32,0,0,12,0,0,0,0,0,0,0,0,0,0,0,0,4,92,0,0,0,0,0,0,0,0,0,0,0,242,
7,128,127,0,0,0,0,0,0,0,0,0,0,0,0,242,27,0,63,0,0,0,0,0,0,0,0,0,3,0,0,160,2,0,
0,0,0,0,0,254,127,223,224,255,254,255,255,255,31,64,0,0,0,0,0,0,0,0,0,0,0,0,
224,253,102,0,0,0,195,1,0,30,0,100,32,0,32,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,224,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,0,
0,0,28,0,0,0,12,0,0,0,12,0,0,0,0,0,0,0,176,63,64,254,15,32,0,0,0,0,0,120,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,135,1,4,14,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,9,0,0,0,0,0,0,64,127,
229,31,248,159,0,0,0,0,0,0,255,127,0,0,0,0,0,0,0,0,15,0,0,0,0,0,208,23,4,0,0,
0,0,248,15,0,3,0,0,0,60,59,0,0,0,0,0,0,64,163,3,0,0,0,0,0,0,240,207,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,247,255,253,33,16,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,
251,0,248,0,0,0,124,0,0,0,0,0,0,223,255,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,
255,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,3,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,128,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,0,0,0,0,
0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,128,247,63,0,0,0,192,0,0,0,0,0,0,0,0,0,0,3,0,68,8,0,0,96,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,48,0,0,0,255,255,3,0,0,0,0,0,192,63,0,0,128,255,3,0,0,
0,0,0,7,0,0,0,0,0,200,19,0,0,0,0,32,0,0,0,0,0,0,0,0,126,102,0,8,16,0,0,0,0,0,
16,0,0,0,0,0,0,157,193,2,0,0,0,0,48,64,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,33,0,0,0,0,0,64,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,0,0,255,255,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,110,240,0,0,0,0,0,135,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,
0,2,0,0,0,0,0,0,255,127,0,0,0,0,0,0,128,3,0,0,0,0,0,120,38,0,0,0,0,0,0,0,0,7,
0,0,0,128,239,31,0,0,0,0,0,0,0,8,0,3,0,0,0,0,0,192,127,0,28,0,0,0,0,0,0,0,0,0,
0,0,128,211,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,248,7,0,0,3,0,0,0,0,
0,0,16,1,0,0,0,192,31,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,
92,0,0,0,0,0,0,0,0,0,0,0,0,0,248,133,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,60,176,1,0,0,48,0,0,0,0,0,0,0,0,0,0,248,167,1,0,0,0,0,0,0,
0,0,0,0,0,0,40,191,0,0,0,0,0,0,0,0,0,0,0,0,224,188,15,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,
0,126,6,0,0,0,0,248,121,128,0,126,14,0,0,0,0,0,252,127,3,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,127,191,0,0,0,0,0,0,0,0,0,0,252,255,255,252,109,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,126,180,191,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,0,0,0,0,0,0,0,127,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,128,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
96,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,3,248,255,231,15,0,0,
0,60,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,28,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,
255,255,255,255,127,248,255,255,255,255,255,31,32,0,16,0,0,248,254,255,0,0,0,
0,0,0,0,0,0,0,127,255,255,249,219,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,0,0,0,0,0,0,
0,0,0,0,0,0,0,240,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

static const unsigned char wtable[]{
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,18,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,19,16,20,21,22,16,16,16,23,16,16,24,25,26,27,28,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,29,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,30,16,16,16,16,31,16,16,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,32,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,17,16,16,16,33,
  34,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,35,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,36,17,17,37,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,38,39,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,40,41,42,43,44,45,46,16,16,47,16,16,16,16,16,
  16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,0,6,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,30,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,96,0,0,48,0,0,0,0,0,0,255,15,0,0,0,0,128,0,0,8,
  0,2,12,0,96,48,64,16,0,0,4,44,36,32,12,0,0,0,1,0,0,0,80,184,0,0,0,0,0,0,0,224,
  0,0,0,1,128,0,0,0,0,0,0,0,0,0,0,0,24,0,0,0,0,0,0,33,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,251,255,255,255,255,255,255,255,
  255,255,255,15,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,63,0,0,0,255,15,255,255,255,255,
  255,255,255,127,254,255,255,255,255,255,255,255,255,255,127,254,255,255,255,
  255,255,255,255,255,255,255,255,255,224,255,255,255,255,127,254,255,255,255,
  255,255,255,255,255,255,255,127,255,255,255,255,255,7,255,255,255,255,15,0,
  255,255,255,255,255,127,255,255,255,255,255,0,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,127,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,
  0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,31,255,255,255,255,255,255,127,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,
  255,255,31,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,15,0,0,0,0,0,0,0,0,0,0,0,0,0,255,3,0,0,255,255,255,255,247,255,127,15,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,254,255,255,255,255,255,255,255,255,255,255,
  255,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,127,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,31,0,
  0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,7,0,255,255,255,127,0,0,0,0,0,0,0,
  0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,
  15,16,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,64,254,7,0,0,0,0,0,0,0,0,0,0,0,0,7,0,255,255,255,
  255,255,15,255,1,3,0,63,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,255,
  1,224,191,255,255,255,255,255,255,255,255,223,255,255,15,0,255,255,255,255,
  255,135,15,0,255,255,17,255,255,255,255,255,255,255,255,127,253,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
  159,255,255,255,255,255,255,255,63,0,120,255,255,255,0,0,4,0,0,96,0,16,0,0,0,
  0,0,0,0,0,0,0,248,255,255,255,255,255,255,255,255,255,255,0,0,0,0,0,0,255,255,
  255,255,255,255,255,255,63,16,7,0,0,24,240,1,0,0,255,255,255,255,255,127,255,
  31,255,255,255,15,0,0,255,255,255,0,0,0,0,0,1,0,255,255,127,0,0,
  0,

};

wint_t        btowc(int) { }
wint_t        fgetwc(FILE*) { }
wchar_t      *fgetws(wchar_t * restrict, int, FILE *restrict) { }
wint_t        fputwc(wchar_t,FILE *) { }
int           fputws(const wchar_t *restrict, FILE *restrict) { }
int           fwide(FILE*, int) { }
int           fwprintf(FILE*restrict, const wchar_t *restrict, ...) { }
int           fwscanf(FILE*restrict, const wchar_t *restrict, ...) { }
wint_t        getwc(FILE*) { }
wint_t        getwchar(void) { }
int           iswalnum(wint_t) { }
int           iswalpha(wint_t) { }
int           iswcntrl(wint_t) { }
int           iswctype(wint_t,wctype_t) { }
int           iswdigit(wint_t) { }
int           iswgraph(wint_t) { }
int           iswlower(wint_t) { }
int           iswprint(wint_t) { }
int           iswpunct(wint_t) { }
int           iswspace(wint_t) { }
int           iswupper(wint_t) { }
int           iswxdigit(wint_t) { }
size_t        mbrlen(const char *restrict, size_t, mbstate_t *restrict) { }
size_t        mbrtowc(wchar_t * restrict, const char *restrict, size_t,mbstate_t *restrict) { }
int           mbsinit(const mbstate_t *) { }
size_t        mbsnrtowcs(wchar_t * restrict, const char **restrict, size_t, size_t, mbstate_t *restrict) { }
size_t        mbsrtowcs(wchar_t * restrict, const char **restrict, size_t,mbstate_t *restrict) { }
FILE         *open_wmemstream(wchar_t**, size_t *) { }
wint_t        putwc(wchar_t,FILE *) { }
wint_t        putwchar(wchar_t) { }
int           swprintf(wchar_t * restrict, size_t,const wchar_t *restrict, ...) { }
int           swscanf(const wchar_t *restrict,const wchar_t *restrict, ...) { }
wint_t        towlower(wint_t) { }
wint_t        towupper(wint_t) { }
wint_t        ungetwc(wint_t,FILE *) { }
int           vfwprintf(FILE*restrict, const wchar_t *restrict, va_list) { }
int           vfwscanf(FILE*restrict, const wchar_t *restrict, va_list) { }
int           vwprintf(const wchar_t *restrict, va_list) { }
int           vswprintf(wchar_t * restrict, size_t,const wchar_t *restrict, va_list) { }
int           vswscanf(const wchar_t *restrict, const wchar_t *restrict,va_list) { }
int           vwscanf(const wchar_t *restrict, va_list) { }
wchar_t      *wcpcpy(wchar_t restrict*, const wchar_t *restrict) { }
wchar_t      *wcpncpy(wchar_t restrict *, const wchar_t *restrict, size_t) { }
size_t        wcrtomb(char * restrict, wchar_t, mbstate_t *restrict) { }
int           wcscasecmp(const wchar_t *, const wchar_t *) { }
int           wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t) { }
wchar_t      *wcscat(wchar_t * restrict, const wchar_t *restrict) { }
wchar_t      *wcschr(const wchar_t *, wchar_t) { }
int           wcscmp(const wchar_t *, const wchar_t *) { }
int           wcscoll(const wchar_t *, const wchar_t *) { }
int           wcscoll_l(const wchar_t *, const wchar_t *, locale_t) { }
wchar_t      *wcscpy(wchar_t* restrict, const wchar_t *restrict) { }
size_t        wcscspn(const wchar_t *, const wchar_t *) { }
wchar_t      *wcsdup(const wchar_t *) { }
size_t        wcsftime(wchar_t * restrict, size_t,const wchar_t *restrict, const struct tm *restrict) { }
size_t        wcslen(const wchar_t *) { }
int           wcsncasecmp(const wchar_t *, const wchar_t *, size_t) { }
int           wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t,locale_t) { }
wchar_t      *wcsncat(wchar_t * restrict, const wchar_t *restrict, size_t) { }
int           wcsncmp(const wchar_t *, const wchar_t *, size_t) { }
wchar_t      *wcsncpy(wchar_t * restrict, const wchar_t *restrict, size_t) { }
size_t        wcsnlen(const wchar_t *, size_t) { }
size_t        wcsnrtombs(char*, const wchar_t **, size_t, size_t,mbstate_t *) { }
wchar_t      *wcspbrk(const wchar_t *, const wchar_t *) { }
wchar_t      *wcsrchr(const wchar_t *, wchar_t) { }
size_t        wcsrtombs(char * restrict, const wchar_t **restrict,size_t, mbstate_t *restrict) { }
size_t        wcsspn(const wchar_t *, const wchar_t *) { }
wchar_t      *wcsstr(const wchar_t *restrict, const wchar_t *restrict) { }
double        wcstod(const wchar_t *restrict, wchar_t **restrict) { }
float         wcstof(const wchar_t *restrict, wchar_t **restrict) { }
wchar_t      *wcstok(wchar_t * restrict, const wchar_t *restrict,wchar_t **restrict) { }
long          wcstol(const wchar_t *restrict, wchar_t **restrict, int) { }
long double   wcstold(const wchar_t *restrict, wchar_t **restrict) { }
long long     wcstoll(const wchar_t *restrict, wchar_t **restrict, int) { }
unsigned long wcstoul(const wchar_t *restrict, wchar_t **restrict, int) { }
unsigned long longwcstoull(const wchar_t *restrict, wchar_t **restrict, int) { }
int           wcswidth(const wchar_t *, size_t) { }
size_t        wcsxfrm(wchar_t * restrict, const wchar_t *restrict, size_t) { }
size_t        wcsxfrm_l(wchar_t * restrict, const wchar_t *restrict,size_t, locale_t) { }
int           wctob(wint_t) { }
wctype_t      wctype(const char *) { }

int wcwidth(wchar_t wc) {
	if (wc < 0xffU)
		return (wc+1 & 0x7f) >= 0x21 ? 1 : wc ? -1 : 0;
	if ((wc & 0xfffeffffU) < 0xfffe) {
		if ((table[table[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1)
			return 0;
		if ((wtable[wtable[wc>>8]*32+((wc&255)>>3)]>>(wc&7))&1)
			return 2;
		return 1;
	}
	if ((wc & 0xfffe) == 0xfffe)
		return -1;
	if (wc-0x20000U < 0x20000)
		return 2;
	if (wc == 0xe0001 || wc-0xe0020U < 0x5f || wc-0xe0100 < 0xef)
		return 0;
	return 1;
}

wchar_t *wmemchr(const wchar_t * s, wchar_t c , size_t n) {
  wchar_t * p = s;
  while(n--){
    if(*p != c)
      p++;
    else
      return p;
  }
  return 0;
}


int wmemcmp(const wchar_t * aptr, const wchar_t *bptr, size_t size) {
  const wchar_t* a = aptr;
	const wchar_t* b = bptr;
	for (size_t i = 0; i < size; i++) {
		if (a[i] < b[i])
			return -1;
		else if (b[i] < a[i])
			return 1;
	}
	return 0;
}


wchar_t *wmemcpy(wchar_t * restrict destPtr,
                const wchar_t *restrict srcPtr , size_t size ){
                  wchar_t * dest = destPtr;
                  wchar_t * src = srcPtr;
                  for(size_t i = 0; i < size; i++){
                    dest[i] = src[i];
                  }
                  return destPtr;
        }

wchar_t *wmemmove(wchar_t* destPtr , const wchar_t * srcPtr, size_t size){
  wchar_t * dest = destPtr;
  const wchar_t * src = srcPtr;
  if(destPtr < srcPtr){
    for (size_t i = 0; i < size ; i++){
      dest[i] = src[i];
    }
  }else{
    for(size_t i = size; i != 0 ; i--){
      dest[i-1] = src[i-1];
    }
  }

  return destPtr;
 }

wchar_t *wmemset(wchar_t* bufptr, wchar_t value, size_t size) {
  wchar_t* buf = bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = value;
	return bufptr;
}

//TODO: Create a design in which wprintf can output to the screen
int           wprintf(const wchar_t *restrict, ...) { }
int           wscanf(const wchar_t *restrict, ...) { }
