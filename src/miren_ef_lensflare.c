#include "decls.h"
extern int DAT_05b9d838;
void DrawLensFlare(struct NJS_POINT3 *);
struct task;

// FUNCTION: SADX 0x005708d0
void dispLensFlare(struct task *task_p)
{
	if (DAT_05b9d838 == 0)
	{
		DrawLensFlare((struct NJS_POINT3 *)((int)(*(int **)((char *)task_p + 0x20)) + 0x20));
	}
	return;
}
