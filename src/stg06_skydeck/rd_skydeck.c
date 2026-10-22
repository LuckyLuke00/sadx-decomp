#include "decls.h"
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

// STUB: SADX 0x00838a10
void Skydeck_SetGravity()
{
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

// STUB: SADX 0x008391c0
void FUN_008391c0()
{
}

// FUNCTION: SADX 0x00839980
void Bg_Skydeck_cloud_Exit(struct task *tp)
{
	DAT_060d08a8--;
}

// STUB: SADX 0x00839f10
long SDCheckRangeOut(struct task *pTask)
{
	return (long)0;
}

// STUB: SADX 0x0083a510
void ObjectSkydeck_c_cyl0_Grab_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083a530
void ObjectSkydeck_hangpole_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083a560
void ObjectSkydeck_hangpole_s_Display(struct task *tp)
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

// STUB: SADX 0x0083b910
void ObjectSkydeck_flap_colli(struct task *tp)
{
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

// STUB: SADX 0x0083bc80
void ObjectSkydeck_homing_Exec(struct task *tp)
{
}

// STUB: SADX 0x0083bdd0
void FUN_0083bdd0(struct task *tp)
{
}

// STUB: SADX 0x0083c150
void SysSkydeck_actchanger(struct task *tp)
{
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

// STUB: SADX 0x0083c540
void ObjectSkydeck_fence_l(struct task *tp)
{
}

// STUB: SADX 0x0083c5b0
void ObjectSkydeck_fence_m(struct task *tp)
{
}

// STUB: SADX 0x0083c620
void ObjectSkydeck_fence_s(struct task *tp)
{
}

// STUB: SADX 0x0083c840
void ObjectSkydeck_hang_c(struct task *tp)
{
}

// STUB: SADX 0x0083c8e0
void ObjectSkydeck_trail(struct task *tp)
{
}

// STUB: SADX 0x0083ca60
void ObjectSkydeck_flap_Exec(struct task *tp)
{
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

// STUB: SADX 0x0083d950
void ObjectSkydeck_flap01(struct task *tp)
{
}

// STUB: SADX 0x0083d980
void ObjectSkydeck_flap02(struct task *tp)
{
}
