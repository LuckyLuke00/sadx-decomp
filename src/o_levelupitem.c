#include "decls.h"
extern const long seq_item_flag[18];
extern short DAT_05b9d724;
extern short DAT_05b9d744;
void FUN_004f5550(int param_1);
extern struct obj DAT_05a91394;
extern struct obj DAT_05a914a0;
extern int DAT_05b9d838;
void FUN_005e7120(void);
void putTubu(long no);
extern short DAT_00997d78[4];

// STUB: SADX 0x005e5f80
void levelupitemDisplay(struct task *tp)
{
}

// STUB: SADX 0x005e6010
void *FUN_005e6010(void)
{
	return (void *)0;
}

// FUNCTION: SADX 0x005e6370
bool FUN_005e6370(short param_1, short param_2)
{
	return *(short *)((char *)DAT_00997d78 + param_1 * 8) == param_2;
}

// FUNCTION: SADX 0x005e6390
int FUN_005e6390(short param_1, int param_2)
{
	if (param_1 < 0xd)
	{
		return (*(int *)((char *)DAT_00997d78 + param_1 * 8 + 4) == param_2);
	}
	else
	{
		return 1;
	}
}

// STUB: SADX 0x005e63c0
void FUN_005e63c0(short param_1, int param_2, int *param_3)
{
}

// FUNCTION: SADX 0x005e6410
void displayEffectGet(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	njPushMatrix(NULL);
	njTranslateV(NULL, &local_8->pos);
	if (local_8->ang.z != 0)
	{
		njRotateZ(NULL, (unsigned short)local_8->ang.z);
	}
	if (local_8->ang.x != 0)
	{
		njRotateX(NULL, (unsigned short)local_8->ang.x);
	}
	if (local_8->ang.y != 0)
	{
		njRotateY(NULL, (unsigned short)local_8->ang.y);
	}
	SetRegularTexture();
	late_DrawObjectClip(&DAT_05a914a0, 0, 1.0f);
	late_DrawObjectClip(&DAT_05a91394, 0, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x005e64e0
void FUN_005e64e0(struct task *param_1)
{
}

// STUB: SADX 0x005e6990
void displayEffectNormal(struct task *tp)
{
}

// STUB: SADX 0x005e6ad0
void FUN_005e6ad0(struct task *param_1)
{
}

// STUB: SADX 0x005e6b30
void levelupitemItemSpot(struct task *tp)
{
}

// STUB: SADX 0x005e6e80
void levelupitemPlayerEyeCheck(struct task *tp)
{
}

// FUNCTION: SADX 0x005e6fb0
void FUN_005e6fb0(int param_1)
{
	if (param_1 <= 0xc)
	{
		FUN_004f5550(seq_item_flag[param_1]);
	}
	else
	{
		if (((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x2000)
		{
			FUN_004f5550(0x1de);
		}
		else
		{
			if (((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x800)
			{
				FUN_004f5550(0x1df);
			}
			else
			{
				if ((((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x1a00) ||
					(((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x1b00) ||
					(((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x1c00))
				{
					FUN_004f5550(0x1e0);
				}
				else
				{
					if (((DAT_05b9d724 << 8 | DAT_05b9d744) & 0xff00) == 0x2100)
					{
						FUN_004f5550(0x1e1);
					}
				}
			}
		}
	}
}

// FUNCTION: SADX 0x005e70e0
void FUN_005e70e0(void)
{
	int local_8;

	FUN_005e7120();
	for (local_8 = 0; local_8 < 4; local_8++)
	{
		putTubu(local_8);
	}
}

// STUB: SADX 0x005e71b0
void putTubu(long no)
{
}

// STUB: SADX 0x005e7310
void init_tubu()
{
}

// STUB: SADX 0x005e7430
void tikalManager(struct task *tp)
{
}

// STUB: SADX 0x005e74e0
void messagechecker(struct task *tp)
{
}
