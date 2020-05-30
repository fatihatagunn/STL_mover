//
// Created by fatih on 28/02/2020.
//

#ifndef STL_MOVER_STL_FILE_H
#define STL_MOVER_STL_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdarg>

#include "triangle.cpp"

class STL {

public:
    explicit STL();

    explicit STL(const STL &);

    explicit STL(const std::string &, const std::string &);

    ~STL();

    //  STL nesnesini parametre olarak verilen dosyaya yazar.
    void writeToFile(const std::string &) const;

    //  STL nesnesini parametrelere göre taşır.
    void move(float = 0, float = 0, float = 0);

    //  STL nesnesini orjin'e taşır.
    void moveToOrigin();

    //  STL nesnesindeki üçgen sayısını geri döndürür.
    unsigned int size() const;

    //  İki STL nesnesini birleştirir.
    void operator+=(const STL &);

    //  STL nesnesini yazdırır.
    friend std::ostream &operator<<(std::ostream &, const STL &);

protected:
    //  STL nesnesinin ilk üçgeninin adresini geri döndürür.
    Triangle *get_head() const;

    //  Bellekte yeni üçgen oluşturur.
    static Triangle *createTriangle();

private:
    unsigned int sumTri;    //  Toplam üçgen sayısı.
    Triangle *head;         //  STL nesnesinin ilk üçgeni
    char *buffer;           //  Binary dosyanın ilk 80 karakterini tutar.
};

#endif //STL_MOVER_STL_FILE_H
