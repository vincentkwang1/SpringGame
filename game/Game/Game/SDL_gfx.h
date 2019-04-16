00001 /*
00002
00003 SDL2_rotozoom.c: rotozoomer, zoomer and shrinker for 32bit or 8bit surfaces
00004
00005 Copyright (C) 2001-2012  Andreas Schiffler
00006
00007 This software is provided 'as-is', without any express or implied
00008 warranty. In no event will the authors be held liable for any damages
00009 arising from the use of this software.
00010
00011 Permission is granted to anyone to use this software for any purpose,
00012 including commercial applications, and to alter it and redistribute it
00013 freely, subject to the following restrictions:
00014
00015 1. The origin of this software must not be misrepresented; you must not
00016 claim that you wrote the original software. If you use this software
00017 in a product, an acknowledgment in the product documentation would be
00018 appreciated but is not required.
00019
00020 2. Altered source versions must be plainly marked as such, and must not be
00021 misrepresented as being the original software.
00022
00023 3. This notice may not be removed or altered from any source
00024 distribution.
00025
00026 Andreas Schiffler -- aschiffler at ferzkopp dot net
00027
00028 */
00029
00030 #ifndef _SDL2_rotozoom_h
00031 #define _SDL2_rotozoom_h
00032
00033 #include <math.h>
00034
00035 /* Set up for C function definitions, even when using C++ */
00036 #ifdef __cplusplus
00037 extern "C" {
	00038 #endif
		00039
		00040 #ifndef M_PI
		00041 #define M_PI    3.1415926535897932384626433832795
		00042 #endif
		00043
		00044 #include "SDL.h"
		00045
		00046         /* ---- Defines */
		00047
		00051 #define SMOOTHING_OFF           0
		00052
		00056 #define SMOOTHING_ON            1
		00057
		00058         /* ---- Function Prototypes */
		00059
		00060 #ifdef _MSC_VER
		00061 #  if defined(DLL_EXPORT) && !defined(LIBSDL2_GFX_DLL_IMPORT)
		00062 #    define SDL2_ROTOZOOM_SCOPE __declspec(dllexport)
		00063 #  else
		00064 #    ifdef LIBSDL2_GFX_DLL_IMPORT
		00065 #      define SDL2_ROTOZOOM_SCOPE __declspec(dllimport)
		00066 #    endif
		00067 #  endif
		00068 #endif
		00069 #ifndef SDL2_ROTOZOOM_SCOPE
		00070 #  define SDL2_ROTOZOOM_SCOPE extern
		00071 #endif
		00072
		00073         /*
		00074
		00075         Rotozoom functions
		00076
		00077         */
		00078
		00079         SDL2_ROTOZOOM_SCOPE SDL_Surface *rotozoomSurface(SDL_Surface * src, double angle, double zoom, int smooth);
	00080
		00081         SDL2_ROTOZOOM_SCOPE SDL_Surface *rotozoomSurfaceXY
		00082                 (SDL_Surface * src, double angle, double zoomx, double zoomy, int smooth);
	00083
		00084
		00085         SDL2_ROTOZOOM_SCOPE void rotozoomSurfaceSize(int width, int height, double angle, double zoom, int *dstwidth,
			00086                 int *dstheight);
	00087
		00088         SDL2_ROTOZOOM_SCOPE void rotozoomSurfaceSizeXY
		00089                 (int width, int height, double angle, double zoomx, double zoomy,
			00090                 int *dstwidth, int *dstheight);
	00091
		00092         /*
		00093
		00094         Zooming functions
		00095
		00096         */
		00097
		00098         SDL2_ROTOZOOM_SCOPE SDL_Surface *zoomSurface(SDL_Surface * src, double zoomx, double zoomy, int smooth);
	00099
		00100         SDL2_ROTOZOOM_SCOPE void zoomSurfaceSize(int width, int height, double zoomx, double zoomy, int *dstwidth, int *dstheight);
	00101
		00102         /*
		00103
		00104         Shrinking functions
		00105
		00106         */
		00107
		00108         SDL2_ROTOZOOM_SCOPE SDL_Surface *shrinkSurface(SDL_Surface * src, int factorx, int factory);
	00109
		00110         /*
		00111
		00112         Specialized rotation functions
		00113
		00114         */
		00115
		00116         SDL2_ROTOZOOM_SCOPE SDL_Surface* rotateSurface90Degrees(SDL_Surface* src, int numClockwiseTurns);
	00117
		00118         /* Ends C function definitions when using C++ */
		00119 #ifdef __cplusplus
		00120 }
00121 #endif
00122
00123 #endif                          /* _SDL2_rotozoom_h */