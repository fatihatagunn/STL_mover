//
// Created by fatih on 28/02/2020.
//

#include "STL_file.h"

STL::STL() {
    head = NULL;
    sumTri = 0;
    buffer = NULL;
}

STL::STL(const STL &other) {

    head = NULL;
    sumTri = 0;
    buffer = NULL;
    *this += other;
}

STL::STL(const std::string &fileName, const std::string &openMode) {

    head = NULL;
    sumTri = 0;
    buffer = NULL;

    if (openMode == "ASCII") {

        //  Dosyayı aç.
        std::ifstream filePtr(fileName, std::ifstream::in);

        std::string face, nor, nor1, nor2, nor3;

        filePtr >> face >> nor;

        //  Dosyanın ASCII formatında olduğunu kontrol et.
        if (face != "solid") {
            filePtr.close();
            std::cout << "The file could not be read!!!" << std::endl;
            return;
        }

        filePtr >> face >> nor >> nor1 >> nor2 >> nor3;

        if (face == "endsolid") {
            filePtr.close();
            std::cout << "The file could not be read!!!" << std::endl;
            return;
        }

        head = createTriangle();
        Triangle *temp = head;

        //  Dosyadaki üçgenleri STL nesnesine yaz.
        while (true) {

            temp->normal().x = std::stof(nor1);
            temp->normal().y = std::stof(nor2);
            temp->normal().z = std::stof(nor3);

            filePtr >> face >> nor
                    >> face >> temp->v1().x >> temp->v1().y >> temp->v1().z
                    >> face >> temp->v2().x >> temp->v2().y >> temp->v2().z
                    >> face >> temp->v3().x >> temp->v3().y >> temp->v3().z
                    >> face
                    >> face;

            ++sumTri;

            filePtr >> face >> nor >> nor1 >> nor2 >> nor3;

            if (face == "endsolid") break;

            temp->next(createTriangle());
            temp = temp->next();
        }

        filePtr.close();

    } else if (openMode == "binary") {

        buffer = new char[80];

        //  Dosyayı aç.
        std::ifstream filePtr(fileName, std::ifstream::binary);

        //  buffer'a ilk 80 karakteri yaz.
        filePtr.read(buffer, 80);

        char bfrTri[4];

        filePtr.read(bfrTri, 4);

        // Üçgen sayısını kaydet.
        sumTri = *(unsigned int *) (bfrTri);

        char bfr[50];

        //  İlk üçgeni oluştur.
        head = createTriangle();
        Triangle *temp = head;

        //  Dosyadaki üçgenleri STL nesnesine yaz.
        for (int i = 1;; ++i) {

            filePtr.read(bfr, 50);

            temp->writeFromBufferToTriangle(bfr);

            if (i == sumTri) break;

            temp->next(createTriangle());
            temp = temp->next();
        }

        filePtr.close();
    } else {

        std::cout << "The file could not be read!!!" << std::endl;
        return;
    }

    std::cout << "Number of Triangles in " << fileName << ": " << sumTri << std::endl;
}

STL::~STL() {

    Triangle *temp = NULL;

    while (head != NULL) {

        temp = head;
        head = head->next();
        delete temp;
    }
}

void STL::writeToFile(const std::string &fileName) const {

    std::ofstream filePtr(fileName, std::ofstream::out);

    filePtr << *this;

    filePtr.close();
}

void STL::move(float x, float y, float z) {

    Triangle *temp = head;

    while (temp != NULL) {

        temp->move(x, y, z);    //  Triangle nesnesinin move fonksiyonunu kullanır.
        temp = temp->next();
    }
}

void STL::moveToOrigin() {

    //  Kontrol için ilk üçgenin adresini tutar.
    Triangle *tempTri = head;

    //  Geçici bir vektör oluşturur.
    Vertex tempVer(tempTri->v1());

    //  Nesnenin her üçgenin her vektörünü kontrol ederek orrin'e en yakın vektörü bulur.
    while (tempTri != NULL) {

        tempVer.findStartingVertex(tempTri->v1());
        tempVer.findStartingVertex(tempTri->v2());
        tempVer.findStartingVertex(tempTri->v3());

        //  Bir sonraki üçgene geçer.
        tempTri = tempTri->next();
    }

    std::cout << "MOVED! " << "x: " << tempVer.x << " y: " << tempVer.y << " z: " << tempVer.z << std::endl;

    move(-tempVer.x, -tempVer.y, -tempVer.z);
}

unsigned int STL::size() const { return sumTri; }

void STL::operator+=(const STL &other) {

    Triangle *temp = head,
            *tempOther = other.head;

    //  Parametre olarak gelen STL nesnesinin içini kontrol eder.
    if (tempOther == NULL) return;

    //  STL nesnesinin içini kontrol eder.
    if (temp == NULL) temp = head = createTriangle();
    else {

        //  STL nesnesinin son üçgenine gider.
        while (temp->next() != NULL) temp = temp->next();

        //  STL nesnesinin son üçgenine yeni üçgen bağlar.
        temp->next(createTriangle());

        //  Yeni bağlanan üçgene geçer.
        temp = temp->next();
    }

    //  Parametre olarak gelen STL nesnesini, asıl STL nesnesine ekler.
    while (true) {

        temp->normal() = tempOther->normal();
        temp->v1() = tempOther->v1();
        temp->v2() = tempOther->v2();
        temp->v3() = tempOther->v3();

        ++sumTri;
        tempOther = tempOther->next();

        if (tempOther == NULL) break;

        //  Her üçgen eklemeden sonra yeni bir üçgen ekleyerek, eklenen üçgene geçer.
        temp->next(createTriangle());
        temp = temp->next();
    }
}

std::ostream &operator<<(std::ostream &filePtr, const STL &file) {

    Triangle *temp = file.get_head();

    filePtr << "solid AssimpScene" << std::endl;

    while (temp != NULL) {

        filePtr << "  facet normal " << temp->normal().x << " " << temp->normal().y << " " << temp->normal().z
                << std::endl
                << "    outer loop" << std::endl
                << "      vertex " << temp->v1().x << " " << temp->v1().y << " " << temp->v1().z << std::endl
                << "      vertex " << temp->v2().x << " " << temp->v2().y << " " << temp->v2().z << std::endl
                << "      vertex " << temp->v3().x << " " << temp->v3().y << " " << temp->v3().z << std::endl
                << "    endloop" << std::endl
                << "  endfacet" << std::endl;

        temp = temp->next();
    }

    filePtr << "endsolid AssimpScene" << std::endl;

    return filePtr;
}

Triangle *STL::get_head() const { return head; }

Triangle *STL::createTriangle() {

    Triangle *temp = new Triangle;
    return temp;
}