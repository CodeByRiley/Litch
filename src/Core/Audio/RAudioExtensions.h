#include "raylib.h"
#ifndef RAUDIOEXTENSIONS
#define RAUDIOEXTENSIONS

#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #define RLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define RLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif
#ifndef API
    #define API
#endif

API void PlaySoundOnce(Sound sound);



#endif RAUDIOEXTENSIONS

#if defined(RAUDIOEXTENSIONS_IMPLEMENTATION)
API void PlaySoundOnce(Sound sound) {
    bool played = false;
    if(!played) {

    }
}
#endif


