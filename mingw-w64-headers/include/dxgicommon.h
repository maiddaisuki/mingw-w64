/*** Autogenerated by WIDL 10.12 from include/dxgicommon.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __dxgicommon_h__
#define __dxgicommon_h__

/* Forward declarations */

/* Headers for imported files */


#ifdef __cplusplus
extern "C" {
#endif

#if 0
typedef unsigned int UINT;
#endif
#define DXGI_STANDARD_MULTISAMPLE_QUALITY_PATTERN (0xffffffff)

#define DXGI_CENTER_MULTISAMPLE_QUALITY_PATTERN (0xfffffffe)

typedef enum DXGI_COLOR_SPACE_TYPE {
    DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709 = 0x0,
    DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 = 0x1,
    DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P709 = 0x2,
    DXGI_COLOR_SPACE_RGB_STUDIO_G22_NONE_P2020 = 0x3,
    DXGI_COLOR_SPACE_RESERVED = 0x4,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_NONE_P709_X601 = 0x5,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P601 = 0x6,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P601 = 0x7,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P709 = 0x8,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P709 = 0x9,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_LEFT_P2020 = 0xa,
    DXGI_COLOR_SPACE_YCBCR_FULL_G22_LEFT_P2020 = 0xb,
    DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 = 0xc,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_LEFT_P2020 = 0xd,
    DXGI_COLOR_SPACE_RGB_STUDIO_G2084_NONE_P2020 = 0xe,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G22_TOPLEFT_P2020 = 0xf,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G2084_TOPLEFT_P2020 = 0x10,
    DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P2020 = 0x11,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_GHLG_TOPLEFT_P2020 = 0x12,
    DXGI_COLOR_SPACE_YCBCR_FULL_GHLG_TOPLEFT_P2020 = 0x13,
    DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P709 = 0x14,
    DXGI_COLOR_SPACE_RGB_STUDIO_G24_NONE_P2020 = 0x15,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P709 = 0x16,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_LEFT_P2020 = 0x17,
    DXGI_COLOR_SPACE_YCBCR_STUDIO_G24_TOPLEFT_P2020 = 0x18,
    DXGI_COLOR_SPACE_CUSTOM = 0xffffffff
} DXGI_COLOR_SPACE_TYPE;
typedef struct DXGI_SAMPLE_DESC {
    UINT Count;
    UINT Quality;
} DXGI_SAMPLE_DESC;
typedef struct DXGI_RATIONAL {
    UINT Numerator;
    UINT Denominator;
} DXGI_RATIONAL;
/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __dxgicommon_h__ */
