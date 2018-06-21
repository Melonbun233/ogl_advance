#ifndef DATA_H
#define DATA_H
//this file contains all data you may use in this project
#include "glm/glm.hpp"

//this array contains 4 vertices that construct a squre
//for each vertex, 
//	the first 3 floats are the position of the vertex
//  the next 3 floats are the RGB color value of the vertex
//  the last 2 floats are the texture coordinates of this vertex
const int square_vertices_num = 4;
const float square_vertices[] = {
	//positions		      //texture coords //normal
	0.5f, 0.0f, 0.5f,     1.0f, 1.0f,      0.0f, 1.0f, 0.0f,// top right
	0.5f, 0.0f, -0.5f,    1.0f, 0.0f,      0.0f, 1.0f, 0.0f,// bottom right
	-0.5f, 0.0f, -0.5f,   0.0f, 0.0f,      0.0f, 1.0f, 0.0f,// bottom left
	-0.5f, 0.0f, 0.5f,    0.0f, 1.0f,      0.0f, 1.0f, 0.0f// top right
};

//this array is used to describe the order that OpenGL should draw a squre
const int square_indices_num = 6;
const unsigned int square_indices[] = {
	0, 1, 3,
	1, 2, 3
};

//this array contains all 36 vertices that required to draw a cube
//for each vertex,
// the first 3 floats are the position of the vertex
// the next 2 floats are the texture coordinates of this vertex
const int cube_vertices_num = 36;
const float cube_vertices[] = {
	//positions			  //texture coords	//normal
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       0.0f, 0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,       0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       0.0f, 0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       0.0f, 0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f, 0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,       0.0f, 0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,       0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,       0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       1.0f, 0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       0.0f, -1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,       0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,       0.0f, -1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,       0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,       0.0f, -1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,       0.0f, -1.0f, 0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,       0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,       0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,       0.0f, 1.0f, 0.0f
};

const int cube_indices_num = 36;
const unsigned int cube_indices[] = {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35,
};

#endif