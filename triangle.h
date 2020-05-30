//
// Created by fatih on 28/02/2020.
//

#ifndef STL_MOVER_TRIANGLE_H
#define STL_MOVER_TRIANGLE_H

#include "vertex.cpp"

class Triangle {

public:
    explicit Triangle();

    //  Karakter dizininden gelen bir üçgenlik bilgiyi üçgenin içine yazar.
    void writeFromBufferToTriangle(char *);

    //  Üçgeni gelen parametrelere göre taşır.
    void move(float = 0, float = 0, float = 0);

    //  Normal vector'ü geri döndürür.
    Vertex &normal();

    //  Vertex 1'i geri döndürür.
    Vertex &v1();

    //  Vertex 2'yi geri döndürür.
    Vertex &v2();

    //  Vertex 3'ü geri döndürür.
    Vertex &v3();

    //  Üçgenin sonraki üçgeninin adresini atar.
    void next(Triangle *);

    // Üçgenin sonraki üçgeninin adresini geri döndürür.
    Triangle *next();

private:
    Vertex Normal;  //  Normal vector
    Vertex V1;      //  Vertex 1
    Vertex V2;      //  Vertex 2
    Vertex V3;      //  Vertex 3
    unsigned short int attribute_byte;  //  Attribute byte count (Sadece binary okuma için).

    Triangle *Next; //  Sonraki üçgenin adresi (Singly Linked List'e göre).
};

#endif //STL_MOVER_TRIANGLE_H
