#include "decls.h"
extern long TexBankList[6][3];

// FUNCTION: SADX 0x00437b50
void AL_PaletteInit(struct task *tp)
{
	*(void **)((char *)tp->twp + 0x684) = syMalloc(0x60);
}

// FUNCTION: SADX 0x00437b70
void AL_PaletteFree(struct task *tp)
{
	syFree(*(void **)((char *)tp->twp + 0x684));
}

// FUNCTION: SADX 0x00437b90
void alpalSetBank(struct task *tp, int cno)
{
	int var1;
	int var2;

	switch (*(unsigned char *)((char *)(*(void **)((char *)tp->twp + 0x6c)) + 0x80))
	{
		case 2:
			var2 = 0;
			break;
		case 6:
			var2 = 1;
			break;
		case 9:
			var2 = 2;
			break;
		case 12:
			var2 = 3;
			break;
		case 15:
			var2 = 4;
			break;
		case 18:
			var2 = 5;
			break;
		default:
			return;
	}
	for (var1 = 0; var1 < 3; var1++)
	{
		njSetPaletteBankNum(TexBankList[var2][var1], cno * 3 + var1);
	}
}
