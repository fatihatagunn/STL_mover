#include <iostream>

#include "STL_file.cpp"

int main() {

    //  STL giriş dosyalarının adresi.
    std::string STL_IN = "STL_IN/";

    //  STL çıkış dosyalarının adresi.
    std::string STL_OUT = "STL_OUT/";

    //  Oluşturulan STL nesneleri (ikinci parametre "ASCII" ya da "binary" olacak).
    STL tux(STL_IN + "Tux.stl", "ASCII"),
            ironmanBinary(STL_IN + "IronmanBinary.stl", "binary"),
            rocket(STL_IN + "Rocket.stl", "ASCII"),
            teapot(STL_IN + "Teapot.stl", "ASCII"),
            eiffel(STL_IN + "Eiffel.stl", "ASCII"),
            android(STL_IN + "Android.stl", "ASCII");

    std::cout << std::endl;

    //  Tüm STL nesneleri orjine taşınacak.
    tux.moveToOrigin();
    ironmanBinary.moveToOrigin();
    rocket.moveToOrigin();
    teapot.moveToOrigin();
    eiffel.moveToOrigin();
    android.moveToOrigin();

    //  Orjine taşınan nesneler istenilen şekilde taşınarak dizilecek.
    tux.move(55);
    ironmanBinary.move(-25);
    rocket.move(-25, 25);
    teapot.move(-25, 10);
    eiffel.move();
    android.move(-130, -20);

    std::cout << std::endl;

    //  İstenirse her STL nesnesi çıkış adresine yazdırılacak.
//    tux.writeToFile(STL_OUT + "outTux.stl");
//    ironmanBinary.writeToFile(STL_OUT + "outIronman.stl");
//    rocket.writeToFile(STL_OUT + "outAndroid.stl");
//    teapot.writeToFile(STL_OUT + "outTeapot.stl");
//    eiffel.writeToFile(STL_OUT + "outEiffel.stl");
//    android.writeToFile(STL_OUT + "outAndroid.stl");

    STL solid;  //  Okunan tüm STL dosyaları buna yazılacak.

    solid += tux;
    solid += ironmanBinary;
    solid += rocket;
    solid += teapot;
    solid += eiffel;
    solid += android;

    solid.writeToFile(STL_OUT + "outSolid.stl");

    std::cout << "End of the Program!!!" << std::endl;
}
