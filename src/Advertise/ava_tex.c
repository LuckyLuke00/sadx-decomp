#include "decls.h"

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
