#include "decls.h"
extern enum AvaTexLdEnum *DAT_025add78[27];
int FUN_004b0a10(int param_1);
void FUN_004b0a50(int param_1);
void FUN_004b6520(int param_1);
void FUN_004b08f0(void);
extern enum AvaTexLdEnum DAT_00985418;
extern int DAT_05b40a48;

extern int DAT_05b3ebbc;
extern unsigned int DAT_05b40a40[2];
extern void *(*DAT_025add48[5])[2];

void FUN_004b0870(int param_1);
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2);

// FUNCTION: SADX 0x004b0790
void AvaLoadTex(enum AvaTexLdEnum *enumlist_ptr)
{
	int local_8;

	if (enumlist_ptr == 0)
	{
		return;
	}
	while ((local_8 = *enumlist_ptr++) != 0x24)
	{
		FUN_004b0870(local_8);
		if (local_8 == 0x1f)
		{
			void *(*local_c)[2];

			local_c = DAT_025add48[DAT_05b3ebbc];
			texLoadTexturePvmFile((char *)local_c[local_8][0], (struct NJS_TEXLIST *)local_c[local_8][1]);
			FUN_004b6460((struct NJS_TEXLIST *)local_c[local_8][1], (char *)local_c[local_8][0]);
		}
		else
		{
			void *(*local_10)[2];

			local_10 = DAT_025add48[DAT_05b3ebbc];
			texLoadTexturePvmFile((char *)local_10[local_8][0], (struct NJS_TEXLIST *)local_10[local_8][1]);
			FUN_004b6460((struct NJS_TEXLIST *)local_10[local_8][1], (char *)local_10[local_8][0]);
		}
	}
}

// FUNCTION: SADX 0x004b0870
void FUN_004b0870(int param_1)
{
	int local_8g;
	int local_cg;

	local_8g = param_1 / 32;
	local_cg = param_1 % 32;
	DAT_05b40a40[local_8g] |= 1 << local_cg;
}

// FUNCTION: SADX 0x004b08c0
void AvaLoadTexForCommon()
{
	FUN_004b08f0();
	AvaLoadTex(&DAT_00985418);
	DAT_05b40a48 = 1;
}

// FUNCTION: SADX 0x004b08f0
void FUN_004b08f0(void)
{
	unsigned int local_8;

	for (local_8 = 0; local_8 < 2; local_8++)
	{
		DAT_05b40a40[local_8] = 0;
	}
}

// FUNCTION: SADX 0x004b0920
void AvaReleaseTexForAll()
{
	enum AvaTexLdEnum LdListBuf[37];
	int local_8g;

	for (local_8g = 0; local_8g < 0x24; local_8g++)
	{
		LdListBuf[local_8g] = (enum AvaTexLdEnum)local_8g;
	}
	LdListBuf[local_8g] = (enum AvaTexLdEnum)0x24;
	AvaReleaseTex(LdListBuf);
}

// FUNCTION: SADX 0x004b0990
void AvaReleaseTex(enum AvaTexLdEnum *enumlist_ptr)
{
	int local_8;

	if (enumlist_ptr == 0)
	{
		return;
	}
	while ((local_8 = *enumlist_ptr++) != 0x24)
	{
		if (FUN_004b0a10(local_8))
		{
			void *(*local_c)[2];

			FUN_004b0a50(local_8);
			local_c = DAT_025add48[DAT_05b3ebbc];
			FUN_004b6520((int)local_c[local_8][1]);
			late_ReleaseTexture((struct NJS_TEXLIST *)local_c[local_8][1]);
		}
	}
}

// FUNCTION: SADX 0x004b0a10
int FUN_004b0a10(int param_1)
{
	int local_8g;
	int local_cg;

	local_8g = param_1 / 32;
	local_cg = param_1 % 32;
	return (1 << local_cg) & DAT_05b40a40[local_8g];
}

// FUNCTION: SADX 0x004b0a50
void FUN_004b0a50(int param_1)
{
	int local_8g;
	int local_cg;

	local_8g = param_1 / 32;
	local_cg = param_1 % 32;
	DAT_05b40a40[local_8g] &= ~(1 << local_cg);
}

// FUNCTION: SADX 0x004b1920
void AvaLoadTexForEachMode(enum AdvaModeEnum mode)
{
	AvaLoadTex(DAT_025add78[mode]);
	LoadGameDDS();
}
