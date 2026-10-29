#include "decls.h"
extern struct NJS_TEXMEMLIST *DAT_0629c50c;
extern struct NJS_TEXMEMLIST *DAT_0629c544;
extern int DAT_0629c724;
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
void njInitTextureBuffer(signed char *addr, unsigned long size)
{
	DAT_0629c53c = addr;
	DAT_0629c510 = size & 0xfffff800;
}

// FUNCTION: SADX 0x00423160
void njSetPaletteMode(unsigned long mode)
{
	DAT_0629c718 = mode;
}

// STUB: SADX 0x00423170
void njSetPaletteData(long offset, long count, void *data)
{
}

// FUNCTION: SADX 0x00423200
long njSetTexture(struct NJS_TEXLIST *texlist)
{
	DAT_0629c724 = (int)texlist;
	if (texlist != (struct NJS_TEXLIST *)0)
	{
		DAT_05ad95dc = (int)texlist->textures->texaddr;
		stSetTexture((struct NJS_TEXMEMLIST *)DAT_05ad95dc);
	}
	return 1;
}

// FUNCTION: SADX 0x00423230
long njSetTextureNum(unsigned long n)
{
	if (DAT_0629c724 != 0)
	{
		int var1 = *(int *)(*(int *)DAT_0629c724 + n * 12 + 8);
		DAT_05ad95dc = var1;
		stSetTexture((struct NJS_TEXMEMLIST *)var1);
		return 1;
	}
	return -1;
}

// STUB: SADX 0x00423270
long _njCheckFileName(char *param_1, char const *param_2, char const *param_3)
{
	return (long)0;
}

// STUB: SADX 0x00423360
struct NJS_TEXMEMLIST * _njSearchEmptyTexMemList(unsigned long param_1)
{
	return (struct NJS_TEXMEMLIST *)0;
}

// STUB: SADX 0x004233c0
void njInitTexture(struct NJS_TEXMEMLIST *addr, unsigned long n)
{
}

// FUNCTION: SADX 0x00423490
void njSetPaletteBankNum(unsigned long n, long bank)
{
	if (DAT_0629c724 != 0)
	{
		int *var1 = (int *)DAT_0629c724;
		int *var2 = (int *)*var1;
		int *var3 = (int *)(var2 + n * 3 + 2);
		int *var4 = (int *)*var3;
		*(long *)(var4 + 1) = bank;
	}
}

// STUB: SADX 0x004234c0
long njLoadPaletteFile(char const *filename, struct NJS_TEXPALETTE *pl)
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
long njReLoadTextureNumG(unsigned long globalIndex, void *texaddr, unsigned long attr, unsigned long lod)
{
	struct NJS_TEXMEMLIST *var1;
	unsigned long var2;

	var1 = DAT_0629c544;
	var2 = 0;
	if (DAT_0629c50c != 0)
	{
		while (var2 < (unsigned long)DAT_0629c50c)
		{
			if (*(unsigned long *)((char *)var1) == globalIndex)
			{
				stSetPaletteBank(*(long *)((char *)var1 + 4));
				stLoadTexture(var1, texaddr);
				return 1;
			}
			var2++;
			var1 = (struct NJS_TEXMEMLIST *)((char *)var1 + 0x44);
		}
	}
	return -1;
}

// STUB: SADX 0x00423920
long njReleaseTexture(struct NJS_TEXLIST *texlist)
{
	return (long)0;
}

#pragma optimize("", off)
// STUB: SADX 0x004239f0
void njReleaseTextureAll(void)
{
}
#pragma optimize("", on)

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
