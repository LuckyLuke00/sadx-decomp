#include "decls.h"
extern struct NJS_TEXLIST texlist_erobo;
struct GHSPRITE_INIT_INFO {
};
void FUN_006dd200(void *param_1);
extern int DAT_060bbe3c;
void FreeTask(struct task *tp);
void disp_ElectSegment(struct task *pTask);
extern int DAT_05b9d838;
extern struct DAT_060bbe38 *DAT_060bbe38;

// STUB: SADX 0x006dc8e0
int EffDeathExplosion(struct NJS_POINT3 *pPos)
{
	return (int)0;
}

// FUNCTION: SADX 0x006dc950
void EffCrushlight(struct NJS_POINT3 *pPos, float fLength, long angSpd)
{
	if (fLength > 0.0f)
	{
		cl_data.fLength = fLength;
		cl_data.angMaxSpd = angSpd;
		CreateCrushLight(pPos, &cl_data);
	}
}

// FUNCTION: SADX 0x006dcc80
void EffEmission_SetMode(enum EMISSION_MODE nMode)
{
	if (DAT_060bbe38 != NULL)
	{
		*(int *)((char *)*(void **)((char *)DAT_060bbe38 + 0x2c) + 0xc) = nMode;
	}
}

// STUB: SADX 0x006dce00
void exec_Emission(struct task *pTask)
{
}

// STUB: SADX 0x006dce70
void disp_ElectSegment(struct task *pTask)
{
}

// FUNCTION: SADX 0x006dcec0
void exec_ElectSegment(struct task *pTask)
{
	struct anywk *var1 = pTask->awp;

	if (DAT_05b9d838 != 0)
	{
		return;
	}
	var1->work.ul[6]++;
	if (var1->work.ul[6] >= 8)
	{
		FreeTask(pTask);
	}
	else
	{
		disp_ElectSegment(pTask);
	}
}

// FUNCTION: SADX 0x006dd0b0
void FUN_006dd0b0(int param_1)
{
	if (DAT_060bbe3c != 0)
	{
		int *var1 = *(int **)(DAT_060bbe3c + 0x2c);
		*var1 = param_1;
	}
}

// STUB: SADX 0x006dd0d0
void EffHandSpark_SetPos(struct NJS_POINT3 *pPosRL)
{
}

// STUB: SADX 0x006dd0f0
void disp_HandSpark(struct task *pTask)
{
}

// FUNCTION: SADX 0x006dd280
void EffHandSpark_Init()
{
	if (DAT_060bbe3c == 0)
	{
		struct task *var1;
		void *var2;
		ghSpriteAnimTableInit(&texlist_erobo, (struct GHSPRITE_ANIM_TABLE *)&animtable_HandSpark, 0);
		var1 = CreateElementalTask(2, 4, exec_HandSpark);
		if (var1 != 0)
		{
			DAT_060bbe3c = (int)var1;
			var2 = MAlloc(0x50);
			var1->awp = (struct anywk *)var2;
			FUN_006dd200((char *)var2 + 4);
			*(float *)((char *)var2 + 0x4c) = 0.0f;
			*(int *)var2 = 0;
			*(int *)((char *)var2 + 0x48) = 0;
			var1->disp = disp_HandSpark;
		}
	}
}

// STUB: SADX 0x006dd4e0
void EffSpark(struct GHSPRITE *spr, struct NJS_POINT3 *pPos, float fScale, int flag)
{
}

// STUB: SADX 0x006dd500
void EffAll_Init(struct task *pTask)
{
}

// FUNCTION: SADX 0x006dd540
void EffAll_Exit()
{
	if ((*(struct task *(*))&DAT_060bbe38) != 0)
	{
		FreeTask((*(struct task *(*))&DAT_060bbe38));
		(*(struct task *(*))&DAT_060bbe38) = 0;
	}
	if ((*(struct task *(*))&DAT_060bbe3c) != 0)
	{
		FreeTask((*(struct task *(*))&DAT_060bbe3c));
		(*(struct task *(*))&DAT_060bbe3c) = 0;
	}
}
