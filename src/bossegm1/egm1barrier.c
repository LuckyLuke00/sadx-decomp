#include "decls.h"

// STUB: SADX 0x006c2940
void InitEgm1Barrier(struct Egm1BarriPrmT *prmp)
{
}

// STUB: SADX 0x006c2980
void Egm1BarrierExec(struct Egm1BarriPrmT *prmp)
{
}

// FUNCTION: SADX 0x006c2c20
long ReqEgm1Barrier(struct Egm1BarriPrmT *prmp, unsigned char req_num)
{
	*(char *)((char *)prmp + 0x1d) = req_num;
	return 1;
}
