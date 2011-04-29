/*==============================================================================
            Copyright (c) 2010 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
            
@file 
    CubeShaders.h

@brief
    Defines OpenGL shaders as char* strings.

==============================================================================*/

#ifndef _QCAR_CUBE_SHADERS_H_
#define _QCAR_CUBE_SHADERS_H_

#ifndef USE_OPENGL_ES_1_1

static const char* cubeMeshVertexShader = " \
  \
attribute vec4 vertexPosition; \
attribute vec4 vertexNormal; \
 \
varying vec4 normal; \
 \
uniform mat4 modelViewProjectionMatrix; \
 \
void main() \
{ \
   gl_Position = modelViewProjectionMatrix * vertexPosition; \
   normal = vertexNormal; \
} \
";


static const char* cubeFragmentShader = " \
 \
precision mediump float; \
 \
varying vec4 normal; \
 \
void main() \
{ \
   gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0); \
} \
";

#endif

#endif // _QCAR_CUBE_SHADERS_H_
