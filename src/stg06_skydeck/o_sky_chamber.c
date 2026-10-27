#include "decls.h"
struct taskwk *var1;

// FUNCTION: SADX 0x00843640
void dispSkyFalling(struct task *tp)
{
	struct taskwk *var1 = tp->twp;

	if (dsCheckViewV(&var1->pos, 20.0f))
	{
		njPushMatrix(0);
		njTranslateV(0, &var1->pos);
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (var1->ang.x)
		{
			njRotateX(0, var1->ang.x);
		}
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		SetObjectTexture();
		___dsDrawObject((struct obj *)(*(int *)((char *)var1 + 8)));
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
		if (*(int *)((char *)var1 + 0x1c) != 0)
		{
			njRotateZ(0, *(unsigned short *)((char *)var1 + 0x1c));
		}
		if (var1->ang.x)
		{
			njRotateX(0, var1->ang.x);
		}
		if (var1->ang.y)
		{
			njRotateY(0, var1->ang.y);
		}
		SetObjectTexture();
		FUN_004a88c0((NJS_ACTION *)(*(int *)((char *)var1 + 8)), *(float *)((char *)var1 + 0xc));
		njPopMatrix(1);
		if (FUN_004c39c0(tp) == 0)
		{
			float var2 = *(float *)((char *)var1 + 0xc) + 1.0;
			*(float *)((char *)var1 + 0xc) = var2;
			struct NJS_MOTION *var3 = *(struct NJS_MOTION **)((char *)(*(void **)((char *)var1 + 8)) + 4);
			if ((float)(unsigned int)var3->nbFrame <= var2)
			{
				*(float *)((char *)var1 + 0xc) = 0.0f;
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
			njRotateY(0, var1->ang.y);
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
