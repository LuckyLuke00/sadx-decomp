#include "decls.h"
void FUN_005d51b0(void *param_1);
extern struct WIREMODEL wire_cube1;
extern struct WIREMODEL wire_cube2;

// FUNCTION: SADX 0x005d51b0
void FUN_005d51b0(void *param_1)
{
	Free(*(void **)((char *)param_1 + 0x10));
	Free(*(void **)((char *)param_1 + 0x14));
}

// FUNCTION: SADX 0x005d51e0
void DrawWireModel(struct WIREMODEL *wmdl, unsigned long attr)
{
	int local_8;
	local_8 = wmdl->nbLine;
	late_DrawLine3D(&wmdl->p3col, local_8, attr, 4);
}

// FUNCTION: SADX 0x005d5210
void InitLockOnCursor(struct WIREMODEL *cursor1, struct WIREMODEL *cursor2)
{
	*cursor1 = wire_cube1;
	SetWireModel(cursor1);
	*cursor2 = wire_cube2;
	SetWireModel(cursor2);
}

// FUNCTION: SADX 0x005d5250
void DeleteLockOnCursor(struct WIREMODEL *cursor1, struct WIREMODEL *cursor2)
{
	FUN_005d51b0(cursor1);
	FUN_005d51b0(cursor2);
}
