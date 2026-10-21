#include "decls.h"
extern int DAT_05b9d838;
void DrawLensFlare(struct NJS_POINT3 *);
struct task;
struct LensFlareParam;

// FUNCTION: SADX 0x00570850
struct task *MirenCreateLensFlare(const struct NJS_POINT3 *pos_p)
{
	struct NJS_POINT3 local_18m;
	struct task *local_8g;

	local_18m = *pos_p;
	local_8g = MirenSetTask((enum tasklevel)4, &MirenEfLensFlareTaskInfo, &local_18m);
	return local_8g;
}

// FUNCTION: SADX 0x005708a0
void initLensFlare(struct task *task_p, const struct LensFlareParam *param_p)
{
	if (param_p != NULL)
	{
		task_p->twp->pos = *(const struct NJS_POINT3 *)param_p;
	}
	return;
}

// FUNCTION: SADX 0x005708d0
void dispLensFlare(struct task *task_p)
{
	if (DAT_05b9d838 == 0)
	{
		DrawLensFlare((struct NJS_POINT3 *)((int)(*(int **)((char *)task_p + 0x20)) + 0x20));
	}
	return;
}
