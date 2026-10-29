#include "decls.h"
void stInitVertex(unsigned long param_1, unsigned long param_2, void *param_3);

// FUNCTION: SADX 0x00426470
void njInit3D(struct NJS_VERTEX_BUF *vbuf, int vn)
{
	stInitVertex(0x20, vn, vbuf);
}
