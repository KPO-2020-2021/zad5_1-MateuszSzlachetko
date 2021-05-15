#include "Drone.h"

int Drone::id = 0;

void Drone::Create_directory()
{
    // Create specific directory for current drone
    directory.append(std::to_string(id));
    directory.append("/");

    // make directory c_str == const char * from string | Values for permissions
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

Drone::Drone()
{
    Create_directory();

    Matrix3x3 test({1, 0, 0,
                    0, 1, 0,
                    0, 0, 1});

    body = Cuboid(-15, -15, -15, 15, 15, 15);
    body.Move(test, Vector3D({0, 0, 0}), directory + body.Get_name());

    std::string appender;
    for (int i = 0; i < 4; ++i)
    {
        rotors[i] = Rotor({10, 0, 0, 5, 8.66, 10});

        // Update rotor file name
        appender.append(std::to_string(i + 1));
        appender.append(".dat");
        rotors[i].Update_name(appender);

        // reset appender
        appender = std::string();
    }
    rotors[0].Move(test, body[7]);
    rotors[1].Move(test, body[5]);
    rotors[2].Move(test, body[6]);
    rotors[3].Move(test, body[4]);

    rotors[0].Write_to_file(directory + rotors[0].Get_name());
    rotors[1].Write_to_file(directory + rotors[1].Get_name());
    rotors[2].Write_to_file(directory + rotors[2].Get_name());
    rotors[3].Write_to_file(directory + rotors[3].Get_name());

    id++;
}

void Drone::Add_files_names(PzG::LaczeDoGNUPlota &Lacze)
{
    // whole line for drone's body converted to char *
    Lacze.DodajNazwePliku((directory + body.Get_name()).c_str())
        .ZmienSposobRys(PzG::SR_Ciagly)
        .ZmienSzerokosc(2)
        .ZmienKolor(8);
    Lacze.DodajNazwePliku((directory + body.Get_name()).c_str())
        .ZmienSposobRys(PzG::SR_Punktowy)
        .ZmienSzerokosc(1)
        .ZmienKolor(5);

    // whole line for drone's rotor converted to char *
    for (int i = 0; i < 4; ++i)
    {
        Lacze.DodajNazwePliku((directory + rotors[i].Get_name()).c_str())
            .ZmienSposobRys(PzG::SR_Ciagly)
            .ZmienSzerokosc(2)
            .ZmienKolor(8);
    }
}

void Drone::Remove_files_names(PzG::LaczeDoGNUPlota &Lacze)
{
    // whole line for drone's body converted to char *
    Lacze.UsunNazwePliku((directory + body.Get_name()).c_str());
    //Lacze.UsunNazwePliku((directory + body.Get_name()).c_str());

    // whole line for drone's rotor converted to char *
    for (int i = 0; i < 4; ++i)
    {
        Lacze.UsunNazwePliku((directory + rotors[i].Get_name()).c_str());
    }
}

Drone::~Drone()
{
    std::cout << directory << std::endl;
}