//
// Created by fatih on 28/02/2020.
//

#include "triangle.h"

Triangle::Triangle() {
    Next = NULL;
}

void Triangle::writeFromBufferToTriangle(char *bufPtr) {

    Normal.x = *(float *) (bufPtr);
    Normal.y = *(float *) (bufPtr + 4);
    Normal.z = *(float *) (bufPtr + 8);
    bufPtr += 12;

    V1.x = *(float *) (bufPtr);
    V1.y = *(float *) (bufPtr + 4);
    V1.z = *(float *) (bufPtr + 8);
    bufPtr += 12;

    V2.x = *(float *) (bufPtr);
    V2.y = *(float *) (bufPtr + 4);
    V2.z = *(float *) (bufPtr + 8);
    bufPtr += 12;

    V3.x = *(float *) (bufPtr);
    V3.y = *(float *) (bufPtr + 4);
    V3.z = *(float *) (bufPtr + 8);
    bufPtr += 12;

    attribute_byte = *(unsigned short int *) (bufPtr);
}

void Triangle::move(float x, float y, float z) {

    V1.x += x;
    V1.y += y;
    V1.z += z;
    V2.x += x;
    V2.y += y;
    V2.z += z;
    V3.x += x;
    V3.y += y;
    V3.z += z;
}

Vertex &Triangle::normal() { return Normal; }

Vertex &Triangle::v1() { return V1; }

Vertex &Triangle::v2() { return V2; }

Vertex &Triangle::v3() { return V3; }

void Triangle::next(Triangle *ptr) { Next = ptr; }

Triangle *Triangle::next() { return Next; }
