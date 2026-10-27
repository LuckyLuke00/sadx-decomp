#include "decls.h"
extern struct _camcontwk *camcont_wp;
extern float DAT_060b9b00;
extern float DAT_060b9b04;
extern float DAT_060b9b08;

// FUNCTION: SADX 0x006c7d40
void FUN_006c7d40(void)
{
	struct _camcontwk *var1;
	struct _camcontwk *var2;
	struct _camcontwk *var3;
	fld:
	var1 = camcont_wp;
	if (*(float *)((char *)var1 + 0x10) < 2.5f)
	{
		*(float *)((char *)var1 + 0x10) = 2.5f;
	}
	var2 = camcont_wp;
	if (*(float *)((char *)var2 + 0xc) < -537.0f)
	{
		*(float *)((char *)var2 + 0xc) = -537.0f;
	}
	if (*(float *)((char *)var2 + 0xc) > -350.0f)
	{
		*(float *)((char *)var2 + 0xc) = -350.0f;
	}
	var3 = camcont_wp;
	if (*(float *)((char *)var3 + 0x14) < 910.0f)
	{
		*(float *)((char *)var3 + 0x14) = 910.0f;
	}
	if (*(float *)((char *)var3 + 0x14) > 1500.0f)
	{
		*(float *)((char *)var3 + 0x14) = 1500.0f;
	}
	DAT_060b9b00 = *(float *)((char *)var2 + 0xc);
	DAT_060b9b04 = *(float *)((char *)var1 + 0x10);
	DAT_060b9b08 = *(float *)((char *)var3 + 0x14);
}
