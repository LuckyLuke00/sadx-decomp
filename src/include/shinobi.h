// The Shinobi types that the shared declarations use, as Sega's headers define them.
#pragma once

// sg_xpt.h
typedef unsigned char Uint8;
typedef signed char Sint8;
typedef unsigned short Uint16;
typedef signed short Sint16;
typedef unsigned long Uint32;
typedef signed long Sint32;
typedef float Float;
typedef void Void;
typedef Sint32 Bool;

// sg_gd.h
typedef struct GDS_FS_HANDLE GDFS_HANDLE;
typedef GDFS_HANDLE *GDFS;
typedef struct GDS_FS_DIRREC_TBL GDFS_DIRREC_TBL;
typedef GDFS_DIRREC_TBL *GDFS_DIRREC;

// sg_pdkbd.h, sg_pdms.h, sg_pdvib.h and sg_syrtc.h: no file needs these layouts yet.
struct PDS_KEYBOARD;
struct PDS_MOUSE_BUTTON;
struct PDS_MOUSE_AXIS;
struct PDS_VIBPARAM;
typedef struct _SYS_RTC_DATE SYS_RTC_DATE;
