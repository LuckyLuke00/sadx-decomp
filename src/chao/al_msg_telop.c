#include "decls.h"

// STUB: SADX 0x00713750
void AlMsgTelopCreate(struct SAlMsgTelop *self)
{
}

// FUNCTION: SADX 0x007137a0
void AlMsgTelopSetPos(struct SAlMsgTelop *self, float px, float py, float pz)
{
	*(float *)((char *)self + 0) = px;
	*(float *)((char *)self + 4) = py;
	*(float *)((char *)self + 8) = pz;
}

// FUNCTION: SADX 0x007137c0
void AlMsgTelopSetSize(struct SAlMsgTelop *self, float sx, float sy)
{
	*(float *)((char *)self + 0xc) = sx;
	*(float *)((char *)self + 0x10) = sy;
}

// STUB: SADX 0x007137f0
void AlMsgTelopAddLineC(struct SAlMsgTelop *self, const char *cstr, long ja)
{
}

// STUB: SADX 0x00713830
void AlMsgTelopExec(struct SAlMsgTelop *self)
{
}

// STUB: SADX 0x00713890
void AlMsgTelopDisp(struct SAlMsgTelop *self)
{
}
