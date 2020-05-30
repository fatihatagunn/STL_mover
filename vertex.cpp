//
// Created by fatih on 28/02/2020.
//

#include "vertex.h"

Vertex::Vertex() {
    x = y = z = 0;
}

Vertex::Vertex(const Vertex &other) {

    x = other.x;
    y = other.y;
    z = other.z;
}

Vertex &Vertex::operator=(const Vertex &other) {

    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

/*
 *   Parametre olan Vertex'in değerlerini kendisiyle karşılaştırır,
 *  küçük olan değeri kendisine yazar.
 */
void Vertex::findStartingVertex(const Vertex &other) {

    if (x > other.x) x = other.x;
    if (y > other.y) y = other.y;
    if (z > other.z) z = other.z;
}
