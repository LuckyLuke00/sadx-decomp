#include "decls.h"
struct NJS_TEXMEMLIST;
extern int DAT_0629c4c0;
extern int DAT_0629c4c4;
extern int DAT_0629c4c8;
extern int DAT_0629c4cc;
extern int DAT_0629c4d0;
extern int DAT_0629c4d4;
extern int DAT_0629c4d8;
extern int DAT_0629c4dc;
struct NJS_TEXMEMLIST * _njSearchEmptyTexMemList(unsigned long);
void stLoadTexture(struct NJS_TEXMEMLIST *,void *);
extern struct NJS_TEXMEMLIST * DAT_0629c50c;
extern struct NJS_TEXMEMLIST * DAT_0629c544;
int stSetTexture(struct NJS_TEXMEMLIST *param_1);
extern int DAT_05ad95dc;
extern signed char *DAT_0629c53c;
extern unsigned long DAT_0629c510;
extern int DAT_0629c718;

// FUNCTION: SADX 0x00423140
void njInitTextureBuffer(signed char *param_1, unsigned long param_2)
{
	DAT_0629c53c = param_1;
	DAT_0629c510 = param_2 & 0xfffff800;
}

// FUNCTION: SADX 0x00423160
void njSetPaletteMode(unsigned long param_1)
{
	DAT_0629c718 = param_1;
}

// STUB: SADX 0x00423170
void njSetPaletteData(long param_1, long param_2, void *param_3)
{
}

// STUB: SADX 0x00423200
long njSetTexture(struct NJS_TEXLIST *param_1)
{
	return (long)0;
}

// STUB: SADX 0x00423230
long njSetTextureNum(unsigned long param_1)
{
	return (long)0;
}

// STUB: SADX 0x00423360
struct NJS_TEXMEMLIST * _njSearchEmptyTexMemList(unsigned long param_1)
{
	return (struct NJS_TEXMEMLIST *)0;
}

// STUB: SADX 0x004233c0
void njInitTexture(struct NJS_TEXMEMLIST *param_1, unsigned long param_2)
{
}

// STUB: SADX 0x00423490
void njSetPaletteBankNum(unsigned long param_1, long param_2)
{
}

// STUB: SADX 0x004234c0
long njLoadPaletteFile(char const *param_1, struct NJS_TEXPALETTE *param_2)
{
	return (long)0;
}

// FUNCTION: SADX 0x00423840
long njSetTextureG(unsigned long param_1)
{
	struct NJS_TEXMEMLIST * var1;
	unsigned long var2;
	unsigned long var3;

	var1 = DAT_0629c544;
	var2 = (unsigned long)DAT_0629c50c;
	var3 = 0;
	if (var2 != 0)
	{
		do
		{
			if (*(int *)((char *)var1 + 0x0) == param_1)
			{
				DAT_05ad95dc = (int)var1;
				stSetTexture(var1);
				return 1;
			}
			var3++;
			var1 = (struct NJS_TEXMEMLIST *)((char *)var1 + 0x44);
		}
		while (var3 < var2);
	}
	return -1;
}

// FUNCTION: SADX 0x00423890
long njReLoadTextureNumG(unsigned long param_1, void *param_2, unsigned long param_3, unsigned long param_4)
{
	struct NJS_TEXMEMLIST *var1;
	unsigned long var2;

	var1 = DAT_0629c544;
	var2 = 0;
	if (DAT_0629c50c != 0)
	{
		while (var2 < (unsigned long)DAT_0629c50c)
		{
			if (*(unsigned long *)((char *)var1) == param_1)
			{
				stSetPaletteBank(*(long *)((char *)var1 + 4));
				stLoadTexture(var1, param_2);
				return 1;
			}
			var2++;
			var1 = (struct NJS_TEXMEMLIST *)((char *)var1 + 0x44);
		}
	}
	return -1;
}

// STUB: SADX 0x00423a90
struct NJS_TEXMEMLIST * _njLoadTextureTexMemList(void *param_1, unsigned long param_2)
{
	return (struct NJS_TEXMEMLIST *)0;
}

// FUNCTION: SADX 0x00423b10
void njExitTexture(void)
{
	njReleaseTextureAll();
	DAT_0629c4c0 = 0;
	DAT_0629c4c4 = 0;
	DAT_0629c4c8 = 0;
	DAT_0629c4cc = 0;
	DAT_0629c4d0 = 0;
	DAT_0629c4d4 = 0;
	DAT_0629c4d8 = 0;
	DAT_0629c4dc = 0;
}
