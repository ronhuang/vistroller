#ifndef _CUBE_H_
#define _CUBE_H_


#define NUM_CUBE_VERTEX 8
#define NUM_CUBE_INDEX 12 * 3


static const float CubeVertices[NUM_CUBE_VERTEX * 3] =
{
    -1.0, -1.0, -1.0,
    1.0, -1.0, -1.0,
    1.0,  1.0, -1.0,
    -1.0,  1.0, -1.0,
    -1.0, -1.0,  1.0,
    1.0, -1.0,  1.0,
    1.0,  1.0,  1.0,
    -1.0,  1.0,  1.0
};

static const float CubeColors[NUM_CUBE_VERTEX * 4] =
{
    0,    0,    0,  1.0,
    1.0,    0,    0,  1.0,
    1.0,  1.0,    0,  1.0,
    0,  1.0,    0,  1.0,
    0,    0,  1.0,  1.0,
    1.0,    0,  1.0,  1.0,
    1.0,  1.0,  1.0,  1.0,
    0,  1.0,  1.0,  1.0,
};

static const unsigned short CubeIndices[NUM_CUBE_INDEX] =
{
    0, 4, 5,    0, 5, 1,
    1, 5, 6,    1, 6, 2,
    2, 6, 7,    2, 7, 3,
    3, 7, 4,    3, 4, 0,
    4, 7, 6,    4, 6, 5,
    3, 0, 1,    3, 1, 2
};


#endif // _CUBE_H_
