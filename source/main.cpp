#include <iostream>
#include "Scene.h"

void Display_menu();

int main()
{
    std::cout << "TEST" << std::endl;

    PzG::LaczeDoGNUPlota Lacze;
    Lacze.DodajNazwePliku("../data/vertices.dat")
        .ZmienSposobRys(PzG::SR_Ciagly)
        .ZmienSzerokosc(2)
        .ZmienKolor(8);
    Lacze.DodajNazwePliku("../data/vertices.dat")
        .ZmienSposobRys(PzG::SR_Punktowy)
        .ZmienSzerokosc(1)
        .ZmienKolor(5);
    Lacze.Inicjalizuj();
    Lacze.ZmienTrybRys(PzG::TR_3D);
    Lacze.UstawZakresX(-200, 200);
    Lacze.UstawZakresY(-200, 200);
    Lacze.UstawZakresZ(-100, 120);
    Lacze.UstawRotacjeXZ(64, 65);

    Scene scene_3D;
    char option = ' ';
    int i = 0, o = 0;

    Display_menu();

    do
    {
        std::cout << "Choice (m-menu):\t";
        std::cin >> option;

        if (option != 'r' && option != 'o' && option != 's' && option != 't' && option != 'd' && option != 'm' && option != 'q' && option != 'c')
        {
            std::cerr << "[ERROR] Invalid menu argument" << std::endl;
            option = ' ';
        }

        switch (option)
        {
        case 'm':
            Display_menu();
            break;
        case 'c':
            scene_3D.Check_side_length();
            break;
        case 'd':
            scene_3D.Display_vertices();
            break;
        case 's':
            scene_3D.Show_rotation_matrix();
            break;
        case 'r':
            scene_3D.Get_rotation_sequence();
            std::cout << "How many times do you want to rotate it?" << std::endl;
            std::cout << "Insert amount of rotations ";
            std::cin >> i;
            o = i;
            std::cout << "Estimated time of animation " << double(i / 60) << "[s]" << std::endl;
            scene_3D.Animate(Lacze, i);
            i = 0;
            break;
        case 'o':
            scene_3D.Set_previous_rotation();
            scene_3D.Animate(Lacze, o);
            break;
        case 't':
            scene_3D.Get_translation_vector();
            std::cout << "In how many frames do you want to animate it?" << std::endl;
            std::cout << "Insert amount of frames ";
            std::cin >> i;
            std::cout << "Estimated time of animation " << double(i / 60) << "[s]" << std::endl;
            scene_3D.Animate(Lacze, i);
            i = 0;
            break;
        default:
            break;
        }
    } while (option != 'q');

    Matrix4x4 m;
    RotXYZ_translate(m, 30, 30, 30, Vector3D({1, 1, 1}));
}

void Display_menu()
{
    std::cout << "\n r-rotate cuboid" << std::endl;
    std::cout << " o-repeat previous rotation" << std::endl;
    std::cout << " s-show rotation matrix" << std::endl;
    std::cout << " t-translate cuboid" << std::endl;
    std::cout << " d-display cuboid's vertices" << std::endl;
    std::cout << " c-check length of cuboid's sides" << std::endl;
    std::cout << " m-show menu" << std::endl;
    std::cout << " q-quit" << std::endl;
}
