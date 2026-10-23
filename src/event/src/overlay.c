#include "decls.h"
void FUN_007d21b0(void *param_1);

// FUNCTION: SADX 0x007d4be0
void COverlayExec(struct task *_this)
{
	struct taskwk *local_8 = _this->twp;
	float local_c = local_8->scl.y + local_8->scl.x;
	if (local_c > 1.0f)
	{
		local_c = 1.0f;
	}
	else if (local_c < 0.0f)
	{
		local_c = 0.0f;
	}
	local_8->scl.x = local_c;
	COverlayDisp(_this);
}

// FUNCTION: SADX 0x007d4c50
void COverlayCons(struct task *_this)
{
	_this->exec = COverlayExec;
	_this->disp = COverlayDisp;
	_this->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
	COverlayExec(_this);
}

// STUB: SADX 0x007d4c80
struct task *FUN_007d4c80(float param_1, float param_2, float param_3, float param_4, float param_5)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x007d4ce0
void COverlaySetAlpha(struct task *_this, float a)
{
	((struct taskwk *)_this->twp)->scl.x = a;
}
