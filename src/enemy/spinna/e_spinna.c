#include "decls.h"
extern void FUN_0067d830(float *param_1, float param_2, float param_3, float param_4);
extern struct NJS_TEXLIST texlist_supi_supi;
extern struct obj object_supi_supi_supi;
extern void ___njSetTexture(struct NJS_TEXLIST *texlist);
extern void ___dsSetPalette(long no);
extern void njPushMatrix(float *param_1);
extern void njRotateY(float *param_1, unsigned short param_2);
extern void ___dsDrawObject(struct obj *obj);
extern void njPopMatrix(int param_1);

// FUNCTION: SADX 0x00593ee0
void SpinnaDead(struct taskwk *twp)
{
	int local_8;
	EraseDolbyCtrl(twp);
	for (local_8 = 0; local_8 < 1; local_8++)
	{
		CreateFlash2(twp->pos.x, twp->pos.y + 5.0f, twp->pos.z, 1.4f);
	}
	CreateExpSpring(twp, 8);
	twp->mode = 5;
}

// FUNCTION: SADX 0x005943b0
void SpinnaEditDraw(struct taskwk *twp, float xpos, float ypos, float zpos)
{
	___njSetTexture(&texlist_supi_supi);
	___dsSetPalette(6);
	njPushMatrix(0);
	FUN_0067d830(0, xpos, ypos, zpos);
	if (twp->ang.y != 0)
	{
		njRotateY(0, twp->ang.y);
	}
	___dsDrawObject(&object_supi_supi_supi);
	njPopMatrix(1);
	___dsSetPalette(0);
}

// FUNCTION: SADX 0x00594430
void FUN_00594430(int param_1, int param_2, int param_3)
{
	((void (*)(int, int, int))FUN_005b5aa0)(param_1, param_2, param_3);
}

// STUB: SADX 0x00594450
void FUN_00594450(struct task *pTask, int param_2, int param_3)
{
}

// STUB: SADX 0x005944b0
void FUN_005944b0(struct taskwk *param_1, struct enemywk *param_2)
{
}

// STUB: SADX 0x00594570
void FUN_00594570(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x005945c0
void FUN_005945c0(struct taskwk *twp, struct enemywk *ewp)
{
}

// STUB: SADX 0x00594630
void SpinnaNormalA(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005946c0
void FUN_005946c0(struct taskwk *param_1, struct enemywk *param_2)
{
	if (EnemySearchPlayer(param_1, param_2) != 0)
	{
		param_1->flag |= 0x200;
	}
	else
	{
		param_1->flag &= ~0x200;
	}
}

// FUNCTION: SADX 0x00594c00
void FUN_00594c00(struct taskwk *param_1, struct enemywk *param_2)
{
	SpinnaDamage(param_1, param_2);
	SpinnaDraw(param_1, param_2);
}

// STUB: SADX 0x00594c30
void SpinnaDamage(struct taskwk *twp, struct enemywk *ewp)
{
}

// FUNCTION: SADX 0x005951a0
void FUN_005951a0(struct taskwk *param_1, struct enemywk *param_2)
{
	struct colliwk *local_8;
	local_8 = param_1->cwp;
	FUN_005946c0(param_1, param_2);
	FUN_005945c0(param_1, param_2);
	FUN_00594570(param_1, param_2);
	SpinnaNormalB(param_1, param_2);
	SpinnaNormalA(param_1, param_2);
	SpinnaDraw(param_1, param_2);
	if (EnemyDist2FromPlayer(param_1, 0) < 57600.0f)
	{
		dsPlay_Dolby_timer_vq(0x35b, (int)param_1, 1, 0, 1, 200.0f, param_1);
	}
}

// STUB: SADX 0x00595260
void SpinnaNormalB(struct taskwk *twp, struct enemywk *ewp)
{
}
