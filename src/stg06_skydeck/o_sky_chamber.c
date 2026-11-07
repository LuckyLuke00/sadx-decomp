#include "decls.h"

// FUNCTION: SADX 0x00843640
void dispSkyFalling(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 20.0f))
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(0, (unsigned short)var1->ang.z);
		}
		if (var1->ang.x)
		{
			njRotateX(0, (Uint16)var1->ang.x);
		}
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		SetObjectTexture();
		___dsDrawObject((struct obj *)((int)var1->counter.l));
		njPopMatrix(1);
	}
}

// FUNCTION: SADX 0x008436e0
void dispSkyFallingWMotion(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 20.0f))
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.z != 0)
		{
			njRotateZ(0, (unsigned short)var1->ang.z);
		}
		if (var1->ang.x)
		{
			njRotateX(0, (Uint16)var1->ang.x);
		}
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		SetObjectTexture();
		FUN_004a88c0((NJS_ACTION *)((int)var1->counter.l), var1->timer.f);
		njPopMatrix(1);
		if (FUN_004c39c0(tp) == 0)
		{
			float var2 = var1->timer.f + 1.0;
			var1->timer.f = var2;
			struct NJS_MOTION *var3 = *(struct NJS_MOTION **)((char *)(var1->counter.ptr) + 4);
			if ((float)(unsigned int)var3->nbFrame <= var2)
			{
				var1->timer.f = 0.0f;
			}
		}
	}
}

// STUB: SADX 0x00843d40
void ObjectSkyFalling(struct task *tp)
{
}

// FUNCTION: SADX 0x00843d70
void dispSkyChamber(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 100.0f))
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (var1->ang.y)
		{
			njRotateY(0, (Uint16)var1->ang.y);
		}
		SetObjectTexture();
		njEasyDrawObject((struct obj *)var1->timer.ptr);
		njPopMatrix(1);
	}
}

// STUB: SADX 0x00843eb0
void execSkyDoor(struct task *tp)
{
}
