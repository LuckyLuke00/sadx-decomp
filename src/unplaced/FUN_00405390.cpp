#include "decls.h"
#include "../advertise.h"

extern void* DAT_0629c340;
extern signed char DAT_060f4ae0[0x40000];
extern float DAT_060eead0;
extern NJS_MATRIX DAT_06274b18[0x80];
extern NJS_TEXMEMLIST DAT_06276c48[0x800];

void FUN_004b6140();

// STUB: SADX 0x00405390
void FUN_00405390()
{
}

// STUB: SADX 0x004054a0
void FUN_004054a0()
{
}

// STUB: SADX 0x00405830
void FUN_00405830()
{
}

// FUNCTION: SADX 0x004059d0
void FUN_004059d0()
{
	njInitTextureBuffer(DAT_060f4ae0, 0x40000);
	njInitVertexBuffer(-0x20, 0, 0x160000, 0, 0x38000);
	njInitPrint(0, 0, 0);
	njPrintSize(0xc);
	njInit3D((NJS_VERTEX_BUF *)DAT_060f4ae0, 0x6000);
	njInitShape(&DAT_060eead0);
	njInitMatrix(DAT_06274b18, 0x80, 0);
	njInitTexture(DAT_06276c48, 0x800);
	syTmrGenStart();
	njControl3D(8);
	___njSetBackColor(0, 0, 0);
	FUN_007d21b0(1);
	((Magic::Base::Singleton<DAT_0629c340_0>*)&DAT_0629c340)->GetSubject()->FUN_00425db0();
	FUN_00405f00()->FUN_00424a90(Magic::Base::App::Get("hInstance"), Magic::Base::App::Get("hWnd"));
}

// FUNCTION: SADX 0x00405b40
void FUN_00405b40()
{
	FUN_004b6140();
	___njReleaseTextureAll();
	FUN_00405f00()->FUN_00424ac0();
	((Magic::Base::Singleton<DAT_0629c340_0>*)&DAT_0629c340)->GetSubject()->FUN_00425e30();
	syTmrGenStop();
	njExitTexture();
	njExitPrint();
}

// STUB: SADX 0x00405c20
void FUN_00405c20()
{
}

// STUB: SADX 0x00405cc0
void FUN_00405cc0()
{
}

// STUB: SADX 0x00405ed0
void FUN_00405ed0()
{
}
