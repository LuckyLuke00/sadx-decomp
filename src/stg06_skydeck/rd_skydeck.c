#include "decls.h"
extern short DAT_05b9d724;
extern int DAT_060d0a5c;
void FUN_008895d0(struct task *param_1);
extern struct taskwk *DAT_05baf368[8];
extern struct CCL_INFO object_actchg_info[1];
void FUN_008895d0(struct task *param_1);
extern "C" int rand(void);
extern short DAT_05b9d744;
extern int DAT_05cbef64;
void FUN_008895d0(struct task *param_1);
void ___njSetTexture(struct NJS_TEXLIST *texlist);
void FUN_008895d0(struct task *param_1);
void FUN_008895d0(struct task *param_1);
extern struct CCL_INFO colli_info_M[];
extern struct CCL_INFO colli_info_M[1];
extern struct CCL_INFO colli_info_S[1];
extern struct CCL_INFO colli_info_L[1];
long EntryColliList(struct taskwk *twp);
long CCL_Init(struct task *tp, struct CCL_INFO *info, long nbInfo, unsigned char id);
extern int DAT_05b9d838;
extern struct obj *com_objtbl[324];
extern struct NJS_TEXLIST texlist_obj_skydeck;
void ObjectSkydeck_hangpole_s_Display(struct task *tp);
void ObjectSkydeck_c_top_Exec(struct task *tp);
extern struct CCL_INFO wall_info[1];
extern float DAT_060cf4a4;
extern int DAT_060d0a40;
extern int DAT_060d0a44;
extern float DAT_060cf494;
extern int DAT_060cf498;
extern float DAT_060cf490;
extern int DAT_060cf4a0;
extern float DAT_060cf48c;
extern int DAT_060cf26c;
extern float DAT_060cf268;
extern int DAT_060cf49c;
extern float DAT_060d0a4c;
extern int DAT_060d08a8;
extern float DAT_060d0a50;
extern int DAT_060d0a48;
extern int DAT_060d0a58;
extern int DAT_060d0a54;
extern int DAT_060cf474;
void FUN_0083bdd0(struct task *param_1);
extern int DAT_060d0ad0;
extern int DAT_060d0acc;

// FUNCTION: SADX 0x00838810
void InitIntSkyDeck()
{
	DAT_060d0ad0 = 0;
	DAT_060d0acc = 0;
}

// FUNCTION: SADX 0x00838a10
void Skydeck_SetGravity()
{
	*(unsigned short *)((char *)&DAT_060cf49c + 2) = 0;
	*(unsigned short *)((char *)&DAT_060cf26c + 2) = 0;
	if ((unsigned int)(DAT_060cf49c - 0xe39) <= 0x71c6)
	{
		DAT_060cf49c = 0xe38;
	}
	else if ((unsigned int)(DAT_060cf49c - 0x8001) <= 0x71c5)
	{
		DAT_060cf49c = 0xf1c7;
	}
	if ((unsigned int)(DAT_060cf26c - 0x3f4a) <= 0x40b5)
	{
		DAT_060cf26c = 0x3f49;
	}
	else if ((unsigned int)(DAT_060cf26c - 0x8001) <= 0x40b4)
	{
		DAT_060cf26c = 0xc0b6;
	}
	SetUserGravityXZ(DAT_060cf49c, DAT_060cf26c);
}

// FUNCTION: SADX 0x00838aa0
void FUN_00838aa0()
{
	DAT_060cf4a4 = 120.0f;
	DAT_060d0a40 = 0;
	DAT_060d0a44 = 0;
	DAT_060cf494 = 0.0f;
	DAT_060cf498 = 0;
	DAT_060cf490 = 0.0f;
	DAT_060cf4a0 = 0;
	DAT_060cf48c = 0.0f;
	DAT_060cf26c = 0;
	DAT_060cf268 = 0.0f;
	DAT_060cf49c = 0;
	DAT_060d0a4c = 0.0f;
	DAT_060d08a8 = 0;
	DAT_060d0a50 = 0.0f;
	DAT_060d0a48 = 0;
	DAT_060d0a58 = 0;
	DAT_060d0a54 = 0;
	DAT_060cf474 = 0;
}

// FUNCTION: SADX 0x008391c0
void FUN_008391c0()
{
	float var1;
	float var2;

	var1 = DAT_05b42a7c->pos.x;
	var2 = DAT_05b42a7c->pos.z;
	if ((char)DAT_05b9d744 == 0)
	{
		DAT_05cbef64 = 1;
		if (211.0 < var1)
		{
			if (var2 < 3570.0)
			{
				DAT_05cbef64 = 0;
			}
		}
	}
}

// FUNCTION: SADX 0x00839980
void Bg_Skydeck_cloud_Exit(struct task *tp)
{
	DAT_060d08a8--;
}

// STUB: SADX 0x00839d70
int FUN_00839d70(float *param_1, float param_2, float param_3, float param_4, float param_5)
{
	return (int)0;
}

// STUB: SADX 0x00839f10
long SDCheckRangeOut(struct task *pTask)
{
	return (long)0;
}

// STUB: SADX 0x00839f40
void SysSkydeck_GoAct2(struct task *tp)
{
}

// STUB: SADX 0x00839fe0
void SysSkydeck_GoAct3(struct task *tp)
{
}

// STUB: SADX 0x0083a510
void ObjectSkydeck_c_cyl0_Grab_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083a530
void ObjectSkydeck_hangpole_Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0083a560
void ObjectSkydeck_hangpole_s_Display(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct obj *var2 = *(struct obj **)((char *)com_objtbl + (var1->smode << 4));

	if (DAT_05b9d838)
	{
		return;
	}
	___njSetTexture(&texlist_obj_skydeck);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawObjectClip(var2, 1.0f);
	njPopMatrix(1);
}

// STUB: SADX 0x0083a5e0
void ObjectSkydeck_hangpole_t_Display(struct task *tp)
{
}

// STUB: SADX 0x0083a670
void ObjectSkydeck_radder_Display(struct task *tp)
{
}

// STUB: SADX 0x0083a7f0
void ObjectSkydeck_untei_Display(struct task *tp)
{
}

// FUNCTION: SADX 0x0083a880
void ObjectSkydeck_radder_Exit(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	Free(var1->value.ptr);
	var1->value.ptr = NULL;
	Free(var1->timer.ptr);
	var1->timer.ptr = NULL;
	FreeTaskC(tp);
}

// STUB: SADX 0x0083aa40
void ObjectSkydeck_fence_Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0083ac30
void ObjectSkydeck_hang_a_Display(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (DAT_05b9d838 == 0)
	{
		___njSetTexture(&texlist_obj_skydeck);
		njPushMatrix(NULL);
		njTranslateV(NULL, &var1->pos);
		if (var1->ang.y != 0)
		{
			njRotateY(NULL, (unsigned short)var1->ang.y);
		}
		ds_DrawObjectClip(com_objtbl[84], 1.0f);
		njPushMatrix(NULL);
		if (var1->ang.x != 0)
		{
			njRotateX(NULL, (unsigned short)var1->ang.x);
		}
		ds_DrawObjectClip(com_objtbl[76], 1.0f);
		njPopMatrix(1);
		FUN_0067d830(NULL, 0.0f, 0.0f, -108.0f);
		ds_DrawObjectClip(com_objtbl[80], 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0083ad10
void ObjectSkydeck_hang_c_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083ae70
void FUN_0083ae70()
{
}

// STUB: SADX 0x0083b7d0
void ObjectSkydeck_tcolli_Exit(struct task *tp)
{
}

// FUNCTION: SADX 0x0083b910
void ObjectSkydeck_flap_colli(struct task *tp)
{
	struct taskwk *var1;
	struct obj *var2;
	struct obj *var3;

	var1 = tp->twp;
	var3 = *(struct obj **)((char *)com_objtbl + 4 + (var1->smode << 4));
	var2 = GetMobileLandObject();
	var1->counter.l = (long)var2;
	var2->evalflags = 0x10;
	var2->scl[0] = 1.0f;
	var2->scl[1] = 1.0f;
	var2->scl[2] = 1.0f;
	var2->ang[0] = var1->ang.x;
	var2->ang[1] = var1->ang.y;
	var2->ang[2] = var1->ang.z;
	var2->pos[0] = var1->pos.x;
	var2->pos[1] = var1->pos.y;
	var2->pos[2] = var1->pos.z;
	var2->model = var3->model;
	var2->child = var3->child;
	var2->sibling = var3->sibling;
	RegisterCollisionEntry(0x18000001, tp, var2);
}

// FUNCTION: SADX 0x0083b990
void ObjectSkydeck_Wall(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	switch (var1->mode)
	{
		case 0:
			CCL_Init(tp, (struct CCL_INFO *)&wall_info, 1, 4);
			var1->mode = 1;
			break;
		case 1:
			if (var1->cwp->flag & 1)
				DAT_060d0a58 = 1;
			EntryColliList(var1);
			break;
		default:
			var1->mode = 0;
			break;
	}
}

// FUNCTION: SADX 0x0083bc80
void ObjectSkydeck_homing_Exec(struct task *tp)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOut(tp))
	{
		return;
	}
	if (CheckCollisionP(&var1->pos, 50.0f) == 1)
	{
		var1->cwp->flag |= 0x40;
	}
	else
	{
		var1->cwp->flag &= 0xffbf;
	}
	EntryColliList(var1);
}

// STUB: SADX 0x0083bdd0
void FUN_0083bdd0(struct task *param_1)
{
}

// FUNCTION: SADX 0x0083c150
void SysSkydeck_actchanger(struct task *tp)
{
	struct taskwk *var1;
	struct colliwk *var2;
	struct playerwk *var3;

	var1 = tp->twp;
	switch (var1->mode)
	{
	case 0:
		if (FUN_004c39c0(tp) == 0)
		{
			CCL_Init(tp, object_actchg_info, 1, 4);
		}
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
		break;
	case 1:
		if (FUN_004c39c0(tp) == 0)
		{
			var2 = var1->cwp;
			if ((var2->flag & 1) != 0)
			{
				if (var2->hit_cwp->id == 0)
				{
					LandChangeStage(1);
					AddSetStage(1);
					AddCameraStage(1);
					AdvanceAct(1);
					SetPlayerInitialPosition((struct taskwk *)DAT_05baf368[0]);
				}
			}
			var3 = GetPlayerWorkPointer(0);
			if (var3->htp != tp)
			{
				EntryColliList(var1);
				return;
			}
		}
		break;
	}
}

// STUB: SADX 0x0083c200
void ObjectSkydeck_c_cyl0_Grab(struct task *tp)
{
}

// STUB: SADX 0x0083c270
void ObjectSkydeck_hangpole(struct task *tp)
{
}

// STUB: SADX 0x0083c2d0
void ObjectSkydeck_hangpole_s_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083c320
void ObjectSkydeck_hangpole_t_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083c370
void ObjectSkydeck_c_top_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083c3d0
void ObjectSkydeck_radder_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083c410
void ObjectSkydeck_duct0_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083c500
void ObjectSkydeck_untei_Exec(struct task *tp)
{
}

// FUNCTION: SADX 0x0083c540
void ObjectSkydeck_fence_l(struct task *tp)
{
	tp->exec = ObjectSkydeck_fence_Exec;
	tp->disp = ObjectSkydeck_untei_Display;
	tp->dest = ObjectSkydeck_radder_Exit;
	tp->twp->smode = 0x26;
	dsSetUnteiPath(tp, 3.0, 8.0, 0.0, 0x29, 6.0);
	CCL_Init(tp, (struct CCL_INFO *)&colli_info_L, 1, 4);
}

// FUNCTION: SADX 0x0083c5b0
void ObjectSkydeck_fence_m(struct task *tp)
{
	tp->exec = ObjectSkydeck_fence_Exec;
	tp->disp = ObjectSkydeck_untei_Display;
	tp->dest = ObjectSkydeck_radder_Exit;
	tp->twp->smode = 0x27;
	dsSetUnteiPath(tp, 3.0, 8.0, 0.0, 0x1f, 6.0);
	CCL_Init(tp, (struct CCL_INFO *)&colli_info_M, 1, 4);
}

// FUNCTION: SADX 0x0083c620
void ObjectSkydeck_fence_s(struct task *tp)
{
	tp->exec = ObjectSkydeck_fence_Exec;
	tp->disp = ObjectSkydeck_untei_Display;
	tp->dest = ObjectSkydeck_radder_Exit;
	tp->twp->smode = 0x28;
	dsSetUnteiPath(tp, 0.0f, 8.0f, 0.0f, 0x12, 6.0f);
	CCL_Init(tp, (struct CCL_INFO *)&colli_info_S, 1, 4);
}

// FUNCTION: SADX 0x0083c840
void ObjectSkydeck_hang_c(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct task *var2;

	tp->exec = ObjectSkydeck_hang_c_Exec;
	tp->dest = ObjectSkydeck_radder_Exit;
	if (FUN_004c39c0(tp) == 0)
	{
		var2 = CreateChildTask(2, PathworkGoWithHangingDownFromBars, tp);
		*(unsigned short *)((char *)var2->twp + 0xc) = (unsigned short)(DAT_05b9d724 << 8 | DAT_05b9d744);
		var2->twp->ang.x = 0;
		var2->twp->ang.y = var1->ang.y;
		var2->twp->ang.z = 0;
		DAT_060d0a5c = 0;
		var1->timer.ptr = MAlloc(0xa0);
		var1->value.ptr = MAlloc(0x10);
		var2->twp->value.ptr = var1->value.ptr;
		ObjectSkydeck_hang_c_Repos(tp);
	}
}

// FUNCTION: SADX 0x0083c8e0
void ObjectSkydeck_trail(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2 = rand();
	float var3 = var2 * 3.0517578125e-05f;
	var1->timer.l = (long)(30.0f + var3 * 30.0f);
	tp->exec = ObjectSkydeck_trail_Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x0083ca60
void ObjectSkydeck_flap_Exec(struct task *tp)
{
	struct taskwk *var1;
	int var2;

	var1 = tp->twp;
	dsPlay_Dolby_time(0xa6, (int)tp, 1, 0x20, 2, var1);
	if (SkydeckCheck_break(var1->pos.x, var1->pos.y, var1->pos.z) != 0)
	{
		var1->pos.y -= 1.7999999523162842;
		var1->pos.x += 0.800000011920929;
	}
	var2 = (int)(njSin(DAT_060d0a40 + 0x1000) * 2048.0);
	*(int *)((char *)var1 + 0x1c) = var2;
	ObjectSkydeck_com_Display(tp);
	ObjectSkydeck_com_GC(tp);
	*(int *)((char *)*(void **)((char *)var1 + 8) + 0x1c) = *(int *)((char *)var1 + 0x1c);
}

// FUNCTION: SADX 0x0083caf0
void ObjectSkydeck_homing(struct task *tp)
{
	tp->exec = ObjectSkydeck_homing_Exec;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	CCL_Init(tp, object_homing_info, 1, 4);
}

// STUB: SADX 0x0083cb20
void Rd_Skydeck(struct task *tp)
{
}

// STUB: SADX 0x0083d210
void ObjectSkydeck_c_cyl_s(struct task *tp)
{
}

// STUB: SADX 0x0083d2a0
void ObjectSkydeck_tank_h(struct task *tp)
{
}

// STUB: SADX 0x0083d310
void ObjectSkydeck_c_top(struct task *tp)
{
}

// STUB: SADX 0x0083d880
void ObjectSkydeck_hang_a(struct task *tp)
{
}

// FUNCTION: SADX 0x0083d930
void ObjectSkydeck_tcolli(struct task *tp)
{
	tp->exec = ObjectSkydeck_tcolli_Exec;
	tp->disp = ObjectSkydeck_tcolli_Display;
	tp->dest = ObjectSkydeck_tcolli_Exit;
}

// FUNCTION: SADX 0x0083d950
void ObjectSkydeck_flap01(struct task *tp)
{
	tp->exec = ObjectSkydeck_flap_Exec;
	tp->disp = ObjectSkydeck_com_Display;
	tp->dest = FUN_008895d0;
	tp->twp->smode = 0x42;
	ObjectSkydeck_flap_colli(tp);
}

// FUNCTION: SADX 0x0083d980
void ObjectSkydeck_flap02(struct task *tp)
{
	tp->exec = ObjectSkydeck_flap_Exec;
	tp->disp = ObjectSkydeck_com_Display;
	tp->dest = FUN_008895d0;
	tp->twp->smode = 0x43;
	ObjectSkydeck_flap_colli(tp);
}
