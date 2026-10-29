#include "decls.h"
extern struct NJS_MODEL model_casi_tuule01a_tuule01a[1];
extern struct NJS_MODEL model_casi_tuule02a_tuule02a[1];
void SetObjectTexture2(long No);
extern int DAT_05b9d838;
extern struct NJS_MODEL model_casi_tuure01a_tuure01a[1];
extern struct NJS_MODEL model_casi_tuure01b_tuure01b[1];
extern struct NJS_MODEL model_casi_tuure02a_tuure02a[1];
extern struct NJS_MODEL model_casi_tuure02b_tuure02b[1];
extern struct NJS_MODEL model_casi_tuure03a_tuure03a[1];
extern struct NJS_MODEL model_casi_tuure03b_tuure03b[1];

// FUNCTION: SADX 0x008841e0
void DispUR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure01a_tuure01a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure02a_tuure02a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure03a_tuure03a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure01b_tuure01b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure02b_tuure02b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuure03b_tuure03b, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008842b0
void DispUL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule01a_tuule01a, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule02a_tuule02a, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x00884330
void DispDL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (DAT_05b9d838)
	{
		return;
	}
	SetObjectTexture2(0x22);
	njPushMatrix(0);
	njTranslateV(0, &var1->pos);
	if (var1->ang.y)
	{
		njRotateY(0, (Uint16)var1->ang.y);
	}
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule01b_tuule01b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule02b_tuule02b, 1.0f);
	ds_DrawModelClip((struct NJS_MODEL *)&model_casi_tuule03b_tuule03b, 1.0f);
	njPopMatrix(1);
}

// FUNCTION: SADX 0x008843c0
void NormalUR(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct OBJ_CONDITION *var2 = (struct OBJ_CONDITION *)var1->counter.ptr;
	float var3 = *(float *)((char *)var2->pTask + 0x24) + 20.0f;
	if (CheckCollisionP(&var1->pos, var3))
	{
		var1->flag |= 0x100;
	}
	else
	{
		var1->flag &= 0xfeff;
	}
	*(int *)((char *)var2 + 0x18) = *(int *)((char *)var1 + 0x18) + 0x80;
	*(int *)((char *)var1 + 0x18) = *(int *)((char *)var2 + 0x18);
	DispUR(tp);
}

// FUNCTION: SADX 0x00884430
void NormalUL(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	struct OBJ_CONDITION *var2 = (struct OBJ_CONDITION *)var1->counter.ptr;
	float var3 = *(float *)((char *)var2->pTask + 0x24) + 20.0f;
	if (CheckCollisionP(&var1->pos, var3))
	{
		var1->flag |= 0x100;
	}
	else
	{
		var1->flag &= 0xfeff;
	}
	if (var1->value.l)
	{
		var1->value.l--;
		DispUL(tp);
		return;
	}
	*(int *)((char *)var2 + 0x18) = *(int *)((char *)var1 + 0x18) - 0x200;
	*(int *)((char *)var1 + 0x18) = *(int *)((char *)var2 + 0x18);
	if (((*(int *)((char *)var1 + 0x18) & 0xff00) == 0) ||
		((*(int *)((char *)var1 + 0x18) & 0xff00) == 0x4000) ||
		((*(int *)((char *)var1 + 0x18) & 0xff00) == 0x8000) ||
		((*(int *)((char *)var1 + 0x18) & 0xff00) == 0xc000))
	{
		var1->value.l = 0x3c;
	}
	DispUL(tp);
}

// STUB: SADX 0x008844d0
void NormalDL(struct task *tp)
{
}

// STUB: SADX 0x00884590
void ObjectRollUpR(struct task *tp)
{
}

// STUB: SADX 0x008845e0
void ObjectRollUpL(struct task *tp)
{
}

// STUB: SADX 0x00884630
void ObjectRollDownL(struct task *tp)
{
}
