#include "decls.h"
struct task *CTikalLight_Create(float x, float y, float z);

// FUNCTION: SADX 0x007d21c0
void CTikalLight_Exec(struct task *_this)
{
	struct taskwk *var1 = _this->twp;
	if (var1->ewp->path.list != 0)
	{
		ExecEventPath(var1);
	}
	float local_c = var1->scl.y + var1->scl.x;
	float local_8 = var1->scl.z;
	if (local_c < 0.0f)
	{
		local_c = 0.0f;
	}
	else if (local_c > 1.0f)
	{
		local_c = 1.0f;
	}
	if (local_8 < 0.0f)
	{
		local_8 = 0.0f;
	}
	TikalSetParameter((struct task *)var1->value.ptr, local_8, local_c);
	var1->ang.y--;
	if (var1->ang.y == 0)
	{
		TikalSetIllusion((struct task *)var1->value.ptr);
		var1->ang.y = var1->ang.x;
	}
	LoopTaskC(_this);
}

// STUB: SADX 0x007d2270
struct task *CTikalLight_Create(float x, float y, float z)
{
	return (struct task *)0;
}
