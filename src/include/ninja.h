// The Ninja types that the shared declarations use, as Sega's headers define them. types.h has the other layouts.
#pragma once

#include "shinobi.h"

// ninjadef.h
typedef int Int;
typedef Sint32 Angle;
typedef Float NJS_MATRIX[16];
typedef Float NJS_FOG_TABLE[128];

// ninjastr.h and ninjacnk.h
typedef struct NJS_POINT3 NJS_VECTOR;
typedef struct obj NJS_OBJECT;
typedef struct cnkobj NJS_CNK_OBJECT;
typedef struct NJS_LIGHT *NJS_LIGHT_PTR;

// ninjastr.h
struct NJS_TEXSURFACE {
    Uint32 Type;
    Uint32 BitDepth;
    Uint32 PixelFormat;
    Uint32 nWidth;
    Uint32 nHeight;
    Uint32 TextureSize;
    Uint32 fSurfaceFlags;
    Uint32 *pSurface;
    Uint32 *pVirtual;
    Uint32 *pPhysical;
};

struct NJS_TEXINFO {
    void *texaddr;
    NJS_TEXSURFACE texsurface;
};

// ninjastr.h: no file needs these layouts yet.
struct NJS_MOTION_LINK;
struct NJS_QUAD_TEXTURE;
struct NJS_SCREEN;
struct NJS_SPLINE;
struct NJS_TEXMEMLIST;
struct NJS_TEXPALETTE;
struct NJS_TEXTURE_VTX;
struct NJS_VERTEX_BUF;
