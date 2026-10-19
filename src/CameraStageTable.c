#include "decls.h"
extern unsigned long DAT_05b3e308[16];
extern unsigned long DAT_05cda1b0;
extern unsigned long DAT_05cda1b4;
extern unsigned long DAT_05cda1b8;
extern unsigned long DAT_05cda1bc;
extern unsigned long DAT_05cda1c0;
extern unsigned long DAT_05cda1c4;
extern unsigned long DAT_05cda1c8;
extern unsigned long DAT_009921c0[16];
extern unsigned long DAT_009921c1[16];
extern unsigned long DAT_009921c2[16];
extern unsigned long DAT_009921c3[16];

// FUNCTION: SADX 0x005a4b20
void Init_objCameraEntryTable(unsigned long u32StageNo)
{
	DAT_05cda1b0 = DAT_05b3e308[(unsigned long)(unsigned char)(DAT_009921c0[u32StageNo] & 0xf)];
	DAT_05cda1b4 = DAT_05b3e308[(unsigned long)(unsigned char)((DAT_009921c0[u32StageNo] >> 4) & 0xf)];
	DAT_05cda1b8 = DAT_05b3e308[(unsigned long)(unsigned char)(DAT_009921c1[u32StageNo] & 0xf)];
	DAT_05cda1bc = DAT_05b3e308[(unsigned long)(unsigned char)((DAT_009921c1[u32StageNo] >> 4) & 0xf)];
	DAT_05cda1c0 = DAT_05b3e308[(unsigned long)(unsigned char)(DAT_009921c2[u32StageNo] & 0xf)];
	DAT_05cda1c4 = DAT_05b3e308[(unsigned long)(unsigned char)((DAT_009921c2[u32StageNo] >> 4) & 0xf)];
	DAT_05cda1c8 = DAT_05b3e308[(unsigned long)(unsigned char)(DAT_009921c3[u32StageNo] & 0xf)];
}
