#include "decls.h"
void FUN_0044d460(unsigned short *param_1);
void WcConvFromCStr(unsigned short *wstr, const char *cstr, long ja);
long AlMsgFontCreateWStr_Thread(struct SAlMsgFontStr *self, const unsigned short *wstr, int sx);
extern int DAT_05b31000[1];
extern char DAT_05b31050;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern void *DAT_05b2cae4;
extern struct NJS_TEXNAME DAT_05b31040;
extern struct NJS_TEXLIST DAT_05b30ff4;

// STUB: SADX 0x0044caf0
void AlMsgFontInit()
{
}

// FUNCTION: SADX 0x0044cb60
void AlMsgFontExit()
{
	if (DAT_05b31040.texaddr != 0)
	{
		late_ReleaseTexture(&DAT_05b30ff4);
	}
	syFree(DAT_05b2cae4);
}

// FUNCTION: SADX 0x0044cb90
void FUN_0044cb90()
{
	___njSetTexture(&DAT_05b30ff4);
	njSetQuadTexture(0, -1);
}

// FUNCTION: SADX 0x0044ce30
void FUN_0044ce30()
{
	memset(&DAT_05b31050, 0, 0x348);
}

// STUB: SADX 0x0044cf90
int FUN_0044cf90(short ax)
{
	return (int)0;
}

// FUNCTION: SADX 0x0044d070
int FUN_0044d070(int param_1)
{
	return DAT_05b31000[param_1];
}

// FUNCTION: SADX 0x0044d080
void AlMsgFontColorSet(int id, unsigned long color)
{
	DAT_05b31000[id] = (int)color;
}

// FUNCTION: SADX 0x0044d090
void FUN_0044d090(void)
{
	njQuadTextureStart(1);
	FUN_00422560(7);
	njSetZUpdateMode(0);
}

// FUNCTION: SADX 0x0044d0b0
void FUN_0044d0b0()
{
	FUN_00422560(1);
	njSetZUpdateMode(1);
	njQuadTextureEnd();
}

// STUB: SADX 0x0044d160
void FUN_0044d160()
{
}

// FUNCTION: SADX 0x0044d620
long AlMsgFontCreateCStr(struct SAlMsgFontStr *self, const char *cstr, long ja, int sx)
{
	unsigned short wstr[768];

	WcConvFromCStr(wstr, cstr, ja);
	FUN_0044d460(wstr);
	return AlMsgFontCreateWStr_Thread(self, wstr, sx);
}
