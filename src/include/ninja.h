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

struct NJS_TEXMEMLIST {
    Uint32 globalIndex;
    Uint32 bank;
    Uint32 tspparambuffer;
    Uint32 texparambuffer;
    Uint32 texaddr;
    NJS_TEXINFO texinfo;
    Uint16 count;
    Uint16 dummy;
};

struct NJS_TEXPALETTE {
    void *palette;
    Uint16 mode;
    Sint16 bank;
    Sint16 offset;
    Sint16 count;
};

struct NJS_LINE {
    Float px;
    Float py;
    Float pz;
    Float vx;
    Float vy;
    Float vz;
};
typedef struct NJS_LINE NJS_PLANE;
typedef struct NJS_LINE NJS_PVECTOR;

struct NJS_MOTION_LINK {
    struct NJS_MOTION *motion[2];
    Float frame[2];
};

struct NJS_ACTION_LINK {
    NJS_OBJECT *object;
    NJS_MOTION_LINK *motionlink;
};

struct NJS_CMOTION_DATA {
    Float *pos;
    Float *vect;
    Angle *roll;
    Angle *ang;
};

struct NJS_POLYGON_VTX {
    Float x;
    Float y;
    Float z;
    Uint32 col;
};

struct NJS_TEXTURE_VTX {
    Float x;
    Float y;
    Float z;
    Float u;
    Float v;
    Uint32 col;
};

struct NJS_QUAD_TEXTURE {
    Float x1;
    Float y1;
    Float x2;
    Float y2;
    Float u1;
    Float v1;
    Float u2;
    Float v2;
};

struct NJS_QUAD_TEXTURE_EX {
    Float x;
    Float y;
    Float z;
    Float vx1;
    Float vy1;
    Float vx2;
    Float vy2;
    Uint32 dmy;
    Float u;
    Float v;
    Float vu1;
    Float vv1;
    Float vu2;
    Float vv2;
    Uint32 dmy2[2];
};

struct NJS_QUATERNION {
    float re;
    float im[3];
};

// ninjastr.h: no file needs these layouts yet. NJS_SPHERE holds an NJS_POINT3, which types.h lays out after this file.
struct NJS_SCREEN;
struct NJS_SPHERE;
struct NJS_SPLINE;
struct NJS_VERTEX_BUF;
