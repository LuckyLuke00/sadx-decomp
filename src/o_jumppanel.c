#include "decls.h"
void RefreshJumpPanel();
extern struct obj DAT_05a8c05c;
extern struct obj DAT_05a8c248;
void FUN_005b3ee0(struct task *param_1);
extern int DAT_05edbe48[10];

// FUNCTION: SADX 0x005b35b0
void InitJumpPanel(void)
{
	int local_8;

	for (local_8 = 0; local_8 < 10; local_8++)
	{
		DAT_05edbe48[local_8] = 0;
	}
}

// FUNCTION: SADX 0x005b35e0
long CheckCollisionedForJumpPanel(struct taskwk *ptwp)
{
	struct colliwk *local_8g;
	struct taskwk *local_cg;

	local_8g = ptwp->cwp->hit_cwp;
	if (local_8g == 0)
		return 0;
	if (ptwp->counter.b[0] != 0)
		return 0;
	local_cg = local_8g->mytask->twp;
	if (local_cg->id != 8)
		return 0;
	return 1;
}

// FUNCTION: SADX 0x005b3640
long CanIMakePanelJump(struct taskwk *ptwp)
{
	struct colliwk *local_8g;
	struct taskwk *local_cg;

	if (CheckCollisionedForJumpPanel(ptwp) == 0)
	{
		if (ptwp->counter.b[0] == 0)
		{
			RefreshJumpPanel();
		}
		return 0;
	}
	local_8g = ptwp->cwp->hit_cwp;
	local_cg = local_8g->mytask->twp;
	if (local_cg->wtimer == 0)
	{
		RefreshJumpPanel();
		return -1;
	}
	if (ptwp->cwp->hit_num != 1)
	{
		RefreshJumpPanel();
		return 0;
	}
	if (local_cg->timer.l >= 30.0f)
	{
		RefreshJumpPanel();
		return 0;
	}
	return 1;
}

// FUNCTION: SADX 0x005b36e0
void RefreshJumpPanel(void)
{
	int local_8;

	for (local_8 = 0; local_8 < 10; local_8++)
	{
		if (DAT_05edbe48[local_8] == 0)
		{
			continue;
		}
		*((char *)*(int *)(DAT_05edbe48[local_8] + 0x20)) = 0;
	}
}

// STUB: SADX 0x005b3730
void StartPlayerPanelJump(struct taskwk *ptwp)
{
}

// FUNCTION: SADX 0x005b3c80
int FUN_005b3c80(void)
{
	int local_cg;
	int local_8g;

	local_cg = 0;
	for (local_8g = 0; local_8g < 10; local_8g++)
	{
		if (DAT_05edbe48[local_8g] == 0)
		{
			continue;
		}
		if (*((char *)*(int *)(DAT_05edbe48[local_8g] + 0x20)) == 1)
		{
			local_cg = local_8g;
		}
	}
	return local_cg;
}

// STUB: SADX 0x005b3ce0
void ObjectJumpPanel(struct task *tp)
{
}

// STUB: SADX 0x005b3db0
void ObjectJumpPanelSetNumber(struct task *tp)
{
}

// FUNCTION: SADX 0x005b3e10
void ObjectJumpPanelRegular(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (CheckRangeOut(tp) != 0)
	{
		return;
	}
	if (FUN_004c39c0(tp) == 0)
	{
		FUN_005b3ee0(tp);
		if (local_8->mode != 1)
		{
			EntryColliList(local_8);
		}
		ObjectSetupInput(local_8, 0);
	}
	else
	{
		ObjectJumpPanelSetNumber(tp);
		njPrintC(0x110010, "-> ROTATION X");
		njPrintC(0x110011, "-> ROTATION Y");
		njPrintC(0x110012, "-> ROTATION Z");
		njPrintC(0x110013, "-> PANEL NUMBER");
	}
	ObjectJumpPanelDisplay(tp);
}

// STUB: SADX 0x005b3ee0
void FUN_005b3ee0(struct task *param_1)
{
}

// FUNCTION: SADX 0x005b3f80
void ObjectJumpPanelDisplay(struct task *tp)
{
	struct taskwk *local_8;

	local_8 = tp->twp;
	if (DAT_05b9d838 != 0)
	{
		return;
	}
	if (DAT_05baf368[0] == 0 || DAT_05b42a7c == 0)
	{
		return;
	}
	if (njSqrt((DAT_05b42a7c->pos.x - local_8->pos.x) * (DAT_05b42a7c->pos.x - local_8->pos.x) + (DAT_05b42a7c->pos.y - local_8->pos.y) * (DAT_05b42a7c->pos.y - local_8->pos.y) + (DAT_05b42a7c->pos.z - local_8->pos.z) * (DAT_05b42a7c->pos.z - local_8->pos.z)) >= 500.0f)
	{
		return;
	}
	if (local_8->wtimer == 0 && CheckEditMode() == 0)
	{
		return;
	}
	SaveControl3D();
	njControl3D(0x10);
	SetMaterial(1.0f, 1.0f, 1.0f, 1.0f);
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
	if (local_8->wtimer == 0)
	{
		SetRegularTexture();
		late_DrawObjectClipMesh(&DAT_05a8c05c, 0, 1.0f);
	}
	else
	{
		___njSetTexture(&texlist_yellow_numbers[local_8->wtimer]);
		ds_DrawObjectClip(&DAT_05a8c248, 1.0f);
		SetRegularTexture();
		late_DrawObjectClipMesh(&DAT_05a8c05c, 0, 1.0f);
	}
	njPopMatrix(1);
	ResetMaterial();
	LoadControl3D();
}

// FUNCTION: SADX 0x005b4170
void ObjectJumpPanelExit(struct task *tp)
{
	short local_8;

	local_8 = tp->twp->wtimer;
	if (DAT_05edbe48[local_8] == (int)tp)
	{
		DAT_05edbe48[local_8] = 0;
	}
}

// FUNCTION: SADX 0x005b41b0
void EffectJumpPannel(struct task *tp)
{
	tp->exec = EffJPExec;
	tp->disp = EffJPDisp;
	EffJPDisp(tp);
}

// STUB: SADX 0x005b41e0
void EffJPDisp(struct task *tp)
{
}

// STUB: SADX 0x005b42f0
void EffJPExec(struct task *tp)
{
}
