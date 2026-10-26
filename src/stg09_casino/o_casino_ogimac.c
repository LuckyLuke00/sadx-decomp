#include "decls.h"
void FUN_00422560(int param_1);
void FUN_0087ea70(struct task *, float);
void njPrintC(int, char const *);
long CheckRangeOutWithR(struct task *tp, float fRange);
void late_ObjCasino_InitUV(struct task *tp, struct obj *pobject, struct TEXUVINFO *tui, signed char num, signed char patnum);
extern void DispUV2ObjSE(struct task *tp);
extern void ExecUV2SE(struct task *tp);
static void DispH(struct task *tp);
void FUN_0087ea70(struct task *param_1, float param_2);
void DispObjV(struct task *tp);
extern long CheckRangeOutWithR(struct task *tp, float fRange);
struct TEXUVINFO;
struct taskwk;
void DispUV2ObjSE(struct task *tp);
void ObjCasino_SetTexUvInfo2(struct TEXUVINFO2 *puvinfo, int cnt, union NJS_COLOR *vertuv, short btimer);
void SetObjectTexture2(long No);
extern int DAT_05b9d838;
extern struct taskwk *DAT_05b42a7c;

// FUNCTION: SADX 0x008894a0
long ObjCasino_CheckUpperY(float ypos)
{
	if (DAT_05baf368[0] != 0)
	{
		if (DAT_05baf368[0]->pos.y >= ypos)
		{
			return 1;
		}
	}
	if (DAT_05baf368[1] != 0)
	{
		if (DAT_05baf368[1]->pos.y >= ypos)
		{
			return 1;
		}
	}
	if (DAT_05b42a7c->pos.y >= ypos)
	{
		return 1;
	}
	return 0;
}

// STUB: SADX 0x008894f0
void ObjCasino_InitGColl(struct task *tp, struct obj *pobj, float rad, long attr)
{
}

// FUNCTION: SADX 0x00889860
void ObjCasino_DrawSphere(struct NJS_POINT3 *center, float scl)
{
	if (DAT_05b9d838)
	{
		return;
	}
	scl *= 0.10000000149011612;
	njPushMatrix(0);
	njTranslateV(0, center);
	FUN_0067d2d0(0, scl, scl, scl);
	ds_DrawObjectClip(&object_sphere01, scl);
	njPopMatrix(1);
}

// STUB: SADX 0x008898c0
void ObjCasino_DrawCylinder(struct NJS_POINT3 *center, float a, float b)
{
}

// STUB: SADX 0x00889970
void ObjCasino_InitTexUvInfo(struct TEXUVINFO *puvinfo, int cnt)
{
}

// FUNCTION: SADX 0x00889a20
void ObjCasino_SetTexUvInfo(struct TEXUVINFO *puvinfo, int cnt)
{
	if (cnt != 0)
	{
		while (1)
		{
			puvinfo->pmeshset->vertuv = puvinfo->vertuv;
			puvinfo++;
			cnt--;
			if (cnt == 0)
			{
				break;
			}
		}
	}
}

// FUNCTION: SADX 0x00889a40
void ObjCasino_ResetTexUvInfo(struct TEXUVINFO *puvinfo, int cnt)
{
	if (cnt != 0)
	{
		while (1)
		{
			puvinfo->pmeshset->vertuv = puvinfo->oldvertuv;
			cnt--;
			puvinfo++;
			if (cnt == 0)
				break;
		}
	}
}

// FUNCTION: SADX 0x00889a60
void ObjCasino_EndTexUvInfo(struct TEXUVINFO *puvinfo, int cnt)
{
	if (cnt > 0)
	{
		do
		{
			puvinfo->nRef--;
			if (puvinfo->nRef == 0)
			{
				Free(puvinfo->vertuv);
				puvinfo->vertuv = 0;
			}
			puvinfo = (struct TEXUVINFO *)((char *)puvinfo + 0x14);
			cnt--;
		} while (cnt != 0);
	}
}

// FUNCTION: SADX 0x00889aa0
void ObjCasino_InitTexUvInfo2(struct TEXUVINFO2 *puvinfo, int cnt)
{
	int var1;

	if (cnt > 0)
	{
		for (var1 = 0; var1 < cnt; var1++)
		{
			puvinfo[var1].oldvertuv = puvinfo[var1].pmeshset->vertuv;
		}
	}
}

// STUB: SADX 0x00889ac0
void ObjCasino_SetTexUvInfo2(struct TEXUVINFO2 *puvinfo, int cnt, union NJS_COLOR *vertuv, short btimer)
{
}

// FUNCTION: SADX 0x00889b90
void ObjCasino_ResetTexUvInfo2(struct TEXUVINFO2 *puvinfo, int cnt)
{
	if (cnt != 0)
	{
		do
		{
			puvinfo->pmeshset->vertuv = puvinfo->oldvertuv;
			puvinfo++;
			cnt--;
		} while (cnt != 0);
	}
}

// FUNCTION: SADX 0x00889bb0
void ObjCasino_InitTexAnimInfo(struct TEXANIMINFO *paniminfo, int cnt)
{
	if (cnt > 0)
	{
		do
		{
			paniminfo->orgtexid = paniminfo->pmat->attr_texId;
			paniminfo = (struct TEXANIMINFO *)((char *)paniminfo + 0xc);
			cnt--;
		} while (cnt != 0);
	}
}

// FUNCTION: SADX 0x00889bf0
void ObjCasino_ResetTexAnimInfo(struct TEXANIMINFO *paniminfo, int cnt)
{
	while (cnt != 0)
	{
		paniminfo->pmat->attr_texId = paniminfo->orgtexid;
		paniminfo++;
		cnt--;
	}
}

// STUB: SADX 0x00889c10
void ObjCasino_CreateSmokeR(struct NJS_POINT3 *pos, struct NJS_POINT3 *vec, float scl, float rad)
{
}

// FUNCTION: SADX 0x00889d30
void DispSVObj(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, var1->value.f))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	FUN_0067d2d0(0, var1->scl.x + 1.0f, var1->scl.y + 1.0f, var1->scl.z + 1.0f);
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, FUN_00500c70(var1->scl.x + 1.0f, var1->scl.y + 1.0f, var1->scl.z + 1.0f));
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00889f60
void ObjCasino_InitS3(struct task *tp, struct obj *pobject)
{
	struct taskwk *var1;

	var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) != 0)
	{
		return;
	}
	tp->disp = DispS3Obj;
	tp->exec = DispS3Obj;
	var1->timer.l = (long)pobject;
}

// FUNCTION: SADX 0x00889fa0
void ExecSCV(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, var1->value.f))
	{
		return;
	}
	DispSVObj(tp);
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
}

// STUB: SADX 0x00889fe0
void CalcCollisionScale(struct taskwk *twp)
{
}

// STUB: SADX 0x0088a090
void ObjCasino_InitSCV(struct task *tp, float range, struct obj *pobject, struct CCL_INFO *pinfo, int cnum)
{
}

// STUB: SADX 0x0088a100
void DispObjVL(struct task *tp)
{
}

// STUB: SADX 0x0088a1f0
void ExecCVL(struct task *tp)
{
}

// STUB: SADX 0x0088a250
void ObjCasino_InitCVL(struct task *tp, float range, struct obj *pobject, struct CCL_INFO *pinfo, int cnum)
{
}

// FUNCTION: SADX 0x0088a2d0
void DispObjV(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, var1->value.f))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0088a350
void ExecCV(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, var1->value.f))
	{
		return;
	}
	DispObjV(tp);
	if (!FUN_004c39c0(tp))
	{
		EntryColliList(var1);
	}
}

// STUB: SADX 0x0088a390
void ObjCasino_InitCV(struct task *tp, float range, struct obj *pobject, struct CCL_INFO *pinfo, int cnum)
{
}

// FUNCTION: SADX 0x0088a410
void DispObj(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 360010.0f) != 0)
		return;
	if (DAT_05b9d838 != 0)
		return;
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0088a490
void ExecG(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 360010.0f))
	{
		return;
	}
	DispObj(tp);
	if (!FUN_004c39c0(tp))
	{
		FUN_0087ea70(tp, (float)var1->wtimer);
	}
}

// STUB: SADX 0x0088a4e0
void ObjCasino_InitG(struct task *tp, struct obj *pobject)
{
}

// FUNCTION: SADX 0x0088a590
void DispRObj(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	int var2;

	if (CheckRangeOutWithR(tp, 360010.0f))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	var2 = var1->counter.w[0] + var1->ang.y;
	if (var2)
	{
		njRotateY(0, (unsigned short)(var1->ang.y + var1->counter.w[0]));
	}
	ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x0088a620
void ExecR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		DispRObj(tp);
		var1->counter.w[0] += (short)(var1->scl.x * 65536.0 / 360.0) + var1->counter.w[1];
		if (FUN_004c39c0(tp) != 0)
		{
			njPrintC(0x120013, "RotSpd");
		}
	}
}

// STUB: SADX 0x0088a6b0
void ObjCasino_InitR(struct task *tp, struct obj *pobject, long rotY)
{
}

// FUNCTION: SADX 0x0088a700
static void DispH(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 360010.0f))
	{
		return;
	}
	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0xc);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, var1->ang.y);
	}
	if (var1->value.f != 0.0f)
	{
		___dsAction((struct NJS_ACTION *)var1->counter.ptr, var1->value.f, 1.0f);
		njPopMatrix(1);
	}
	else
	{
		ds_DrawObjectClip((struct obj *)var1->timer.ptr, 1.0f);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x0088aa20
void ObjCasino_InitH(struct task *tp, struct obj *pobject, struct CCL_INFO *pinfo, struct NJS_ACTION *paction)
{
	struct taskwk *var1 = tp->twp;

	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		if (FUN_004c39c0(tp) == 0)
		{
			var1->ang.x = 0;
			var1->ang.z = 0;
			CCL_Init(tp, pinfo, 1, 4);
		}
		tp->disp = DispH;
		tp->exec = (void (__cdecl *)(struct task *))0x88a7c0;
		var1->value.f = 0.0f;
		var1->timer.l = (long)pobject;
		var1->counter.l = (long)paction;
	}
}

// STUB: SADX 0x0088aa90
void DispUV2ObjSE_sub(struct task *tp)
{
}

// FUNCTION: SADX 0x0088ac20
void ExecUV2SE(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (CheckRangeOutWithR(tp, 360010.0f) == 0)
	{
		DispUV2ObjSE(tp);
		if (FUN_004c39c0(tp) != 0)
		{
			njPrintC(0x120015, "Speed");
		}
		var1->wtimer += (short)(int)var1->scl.z;
		if (DAT_05b9d838 == 0)
		{
			dsPlay_timer_v(var1->counter.l, (int)var1, 1, -40, 10, var1->pos.x, var1->pos.y, var1->pos.z);
		}
	}
}

// STUB: SADX 0x0088acd0
void ObjCasino_InitUV2SE(struct task *tp, struct obj *pobject, struct TEXUVINFO2 *tui, signed char cnt, int se)
{
}

// STUB: SADX 0x0088ae80
void ExecUV(struct task *tp)
{
}

// STUB: SADX 0x0088af00
void ObjCasino_InitUV(struct task *tp, struct obj *pobject, struct TEXUVINFO *tui, signed char num, signed char patnum)
{
}

// STUB: SADX 0x0088af80
void ExecUVG(struct task *tp)
{
}

// STUB: SADX 0x0088b010
void EndUVG(struct task *tp)
{
}

// STUB: SADX 0x0088b080
void ObjCasino_InitUVG(struct task *tp, struct obj *pobject, struct TEXUVINFO *tui, signed char num, signed char patnum)
{
}

// STUB: SADX 0x0088b290
void ExecTGR(struct task *tp)
{
}

// STUB: SADX 0x0088b370
void ObjCasino_InitTGR(struct task *tp, struct obj *pobject, struct TEXANIMINFO *tui, signed char num, signed char patnum)
{
}

// STUB: SADX 0x0088b430
void ExecUVC(struct task *tp)
{
}

// STUB: SADX 0x0088b4b0
void EndUV(struct task *tp)
{
}

// STUB: SADX 0x0088b4f0
void ObjCasino_InitUVC(struct task *tp, struct obj *pobject, struct CCL_INFO *pinfo, int cnum, struct TEXUVINFO *tui, signed char num, signed char patnum)
{
}

// FUNCTION: SADX 0x0088b580
void late_DispUVObj_sub(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	signed char var2;
	signed char var3;
	struct TEXUVINFO *var4;

	if (var1 != 0)
	{
		if (DAT_05b9d838 == 0)
		{
			var2 = var1->btimer;
			var3 = var1->mode;
			var4 = (struct TEXUVINFO *)var1->value.l;
			if (var3 != 0)
			{
				ObjCasino_SetTexUvInfo(var4 + (var3 - 1) * var2, var2);
			}
			FUN_00422560(3);
			SetObjectTexture2(0xc);
			late_DrawObjectClip((struct obj *)var1->timer.l, 1, 1.0f);
			npSetZCompare();
			if (var3 != 0)
			{
				ObjCasino_ResetTexUvInfo(var4 + (var3 - 1) * var2, var2);
			}
		}
	}
}

// STUB: SADX 0x0088b710
void late_ExecUV(struct task *tp)
{
}

// STUB: SADX 0x0088b790
void late_ObjCasino_InitUV(struct task *tp, struct obj *pobject, struct TEXUVINFO *tui, signed char num, signed char patnum)
{
}
