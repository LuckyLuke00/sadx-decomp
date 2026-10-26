#include "decls.h"
extern void *DAT_060eea80;
extern void FUN_007d21b0(...);

// FUNCTION: SADX 0x006e69d0
void ObjectC0Grass0(struct task *pTask)
{
	pTask->twp->counter.ptr = *(void **)((char *)DAT_060eea80 + 0x108);
	pTask->exec = (void (__cdecl *)(struct task *))FUN_007d21b0;
	pTask->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x006e6a00
void ObjectC0Grass1(struct task *pTask)
{
	pTask->twp->counter.l = *(int *)((char *)DAT_060eea80 + 0x10c);
	pTask->exec = (void (__cdecl *)(struct task *))FUN_007d21b0;
	pTask->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x006e6a30
void ObjectC0Grass2(struct task *pTask)
{
	pTask->twp->counter.ptr = *(void **)((char *)DAT_060eea80 + 0x110);
	pTask->exec = (void (__cdecl *)(struct task *))FUN_007d21b0;
	pTask->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
}

// FUNCTION: SADX 0x006e6a60
void ObjectC0Grass3(struct task *pTask)
{
	pTask->twp->counter.l = *(int *)((char *)DAT_060eea80 + 0x114);
	pTask->exec = (void (__cdecl *)(struct task *))FUN_007d21b0;
	pTask->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
