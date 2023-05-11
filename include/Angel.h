//////////////////////////////////////////////////////////////////////////////
//
//  --- Angel.h ---
//
//   The main header file for all examples from Angel 6th Edition
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ANGEL_H__
#define __ANGEL_H__

//----------------------------------------------------------------------------
//
// --- Include system headers ---
//

#include <cmath>
#include <iostream>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

//----------------------------------------------------------------------------
//
// --- Include OpenGL header files and helpers ---
//
//   The location of these files vary by operating system.  We've included
//     copies of open-soruce project headers in the "GL" directory local
//     this this "include" directory.
//

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

namespace Angel {

    //  Helper function to load vertex and fragment shader files
    GLuint InitShader(const char* vertexShaderFile,
        const char* fragmentShaderFile);

    //  Defined constant for when numbers are too small to be used in the
    //    denominator of a division operation.  This is only used if the
    //    DEBUG macro is defined.
    const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

    //  Degrees-to-radians constant
    const GLfloat  DegreesToRadians = GLfloat(M_PI) / GLfloat(180.0);

}  // namespace Angel

#include "vec.h"
#include "mat.h"

using namespace Angel;

#endif // __ANGEL_H__
