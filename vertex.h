//
// Created by fatih on 28/02/2020.
//

#ifndef STL_MOVER_VERTEX_H
#define STL_MOVER_VERTEX_H

#include <iostream>

struct Vertex {

    explicit Vertex();

    explicit Vertex(const Vertex &);

    virtual Vertex &operator=(const Vertex &);

    //  Orjin'e en yakın olan noktayı bulur.
    virtual void findStartingVertex(const Vertex &);

    float x;
    float y;
    float z;
};

#endif //STL_MOVER_VERTEX_H
