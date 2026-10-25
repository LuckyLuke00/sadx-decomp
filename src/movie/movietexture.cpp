#include "decls.h"
extern float DAT_00956608;
extern unsigned int DAT_01c6e428;
extern unsigned int DAT_01c6e42c;
extern int DAT_05edf7e0;
extern int DAT_05edf7e4;

// FUNCTION: SADX 0x0061fb10
int G_GetMovieSystem()
{
	return DAT_05edf7e4;
}

// STUB: SADX 0x0061fb20
int PlayDShowTextureRenderer()
{
	return (int)0;
}

// STUB: SADX 0x0061fba0
int CheckMovieStatus()
{
	return (int)0;
}

// STUB: SADX 0x0061fbf0
int GetNJTexture()
{
	return (int)0;
}

// FUNCTION: SADX 0x0061fc20
void DrawMovieTex(int max_width, int max_height)
{
	if (DAT_05edf7e0 != 0)
	{
		RenderTexture(0, 0, DAT_01c6e428, DAT_01c6e42c, DAT_00956608, (Magic::RenderCore::Texture *)DAT_05edf7e0, 0.0f, 0.0f, 1.0f, 1.0f, -1);
	}
}
