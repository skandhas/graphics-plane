#ifndef GFX_GL_H
#define GFX_GL_H

#ifdef WIN32
#include "gl/glew.h"
#include "gl/wglew.h"
#elif __APPLE__
    #include "TargetConditionals.h"
    #ifdef TARGET_OS_MAC
        #include <OpenGL/gl.h>
    #endif
#endif

#endif
