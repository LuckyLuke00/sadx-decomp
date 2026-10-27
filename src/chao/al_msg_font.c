#include "decls.h"
extern struct NJS_TEXNAME DAT_05b2cab8;
void njSetTextureInfo(int param_1, int param_2, int param_3, int param_4, int param_5);
void njSetTextureName(int param_1, int param_2, int param_3, int param_4);
void FUN_0044d460(unsigned short *param_1);
void WcConvFromCStr(unsigned short *wstr, const char *cstr, long ja);
long AlMsgFontCreateWStr_Thread(struct SAlMsgFontStr *self, const unsigned short *wstr, int sx);
extern int DAT_05b31000[1];
extern char DAT_05b31050;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern void *DAT_05b2cae4;
extern struct NJS_TEXNAME DAT_05b31040;
extern struct NJS_TEXLIST DAT_05b30ff4;
extern int DAT_05b31398;
void FPpInit();

// FUNCTION: SADX 0x0044caf0
void AlMsgFontInit()
{
	struct NJS_TEXNAME *var1;

	var1 = (struct NJS_TEXNAME *)syCalloc(0x40000, 1);
	DAT_05b2cae4 = var1;
	njSetTextureInfo((int)&DAT_05b2cab8, (int)var1, 0x902, 0x200, 0x100);
	njSetTextureName((int)&DAT_05b31040, (int)&DAT_05b2cab8, 0x30d36, 0x40800000);
	DAT_05b30ff4.textures = &DAT_05b31040;
	DAT_05b30ff4.nbTexture = 1;
	njLoadTexture(&DAT_05b30ff4);
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

#pragma optimize("", off)
// STUB: SADX 0x0044d160
void FUN_0044d160()
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0044d620
long AlMsgFontCreateCStr(struct SAlMsgFontStr *self, const char *cstr, long ja, int sx)
{
	unsigned short wstr[768];

	WcConvFromCStr(wstr, cstr, ja);
	FUN_0044d460(wstr);
	return AlMsgFontCreateWStr_Thread(self, wstr, sx);
}

// FUNCTION: SADX 0x0044daf0
void FUN_0044daf0()
{
	int var1 = DAT_05b31398;
	DAT_05b31398 = DAT_05b31398 + 1;
	if (var1 == 0)
	{
		FPpInit();
		AlMsgFontInit();
		FUN_0044ce30();
		FUN_0044d160();
	}
}
