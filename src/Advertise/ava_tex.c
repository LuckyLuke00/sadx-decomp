#include "decls.h"

extern int DAT_05b3ebbc;
extern unsigned int DAT_05b40a40[2];
extern void *(*DAT_025add48[5])[2];

void FUN_004b0870(int param_1);
void FUN_004b6460(struct NJS_TEXLIST *param_1, char *param_2);

// FUNCTION: SADX 0x004b0790
void AvaLoadTex(enum AvaTexLdEnum *list)
{
	int tex;

	if (list == 0)
	{
		return;
	}
	while ((tex = *list++) != 0x24)
	{
		FUN_004b0870(tex);
		if (tex == 0x1f)
		{
			void *(*a)[2];

			a = DAT_025add48[DAT_05b3ebbc];
			texLoadTexturePvmFile((char *)a[tex][0], (struct NJS_TEXLIST *)a[tex][1]);
			FUN_004b6460((struct NJS_TEXLIST *)a[tex][1], (char *)a[tex][0]);
		}
		else
		{
			void *(*b)[2];

			b = DAT_025add48[DAT_05b3ebbc];
			texLoadTexturePvmFile((char *)b[tex][0], (struct NJS_TEXLIST *)b[tex][1]);
			FUN_004b6460((struct NJS_TEXLIST *)b[tex][1], (char *)b[tex][0]);
		}
	}
}

// FUNCTION: SADX 0x004b0870
void FUN_004b0870(int param_1)
{
	int word;
	int bit;

	word = param_1 / 32;
	bit = param_1 % 32;
	DAT_05b40a40[word] |= 1 << bit;
}
