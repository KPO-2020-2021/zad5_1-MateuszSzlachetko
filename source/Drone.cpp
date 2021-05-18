#include "Drone.h"

int Drone::id = 0;

void Drone::Create_directory()
{
    // Create specific directory for current drone
    directory.append(std::to_string(id + 1));
    directory.append("/");

    // make directory c_str == const char * from string | Values for permissions
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    id++;
}

Drone::Drone()
{
    Create_directory();

    Matrix3x3 test({1, 0, 0,
                    0, 1, 0,
                    0, 0, 1});

    body = Cuboid(0, 0, 0, 30, 30, 30);

    Vector3D init_body_height({0, 0, 0});

    // if (body[0][2] < 0) // w default constructorze nie potrzebne,przenieść potem do nie defaultowego
    //     init_body_height[2] = -body[0][2];

    body.Move(test, init_body_height, directory + body.Get_name());

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
    // Move rotors to body corners

    rotors[0].Translate(body[7]);
    rotors[1].Translate(body[5]);
    rotors[2].Translate(body[6]);
    rotors[3].Translate(body[4]);

    // Save rotors positions
    rotors[0].Write_to_file(directory + rotors[0].Get_name());
    rotors[1].Write_to_file(directory + rotors[1].Get_name());
    rotors[2].Write_to_file(directory + rotors[2].Get_name());
    rotors[3].Write_to_file(directory + rotors[3].Get_name());
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

    // whole line for drone's rotor converted to char *
    for (int i = 0; i < 4; ++i)
    {
        Lacze.UsunNazwePliku((directory + rotors[i].Get_name()).c_str());
    }
}

Drone Drone::Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector)
{
    Propeller_rotation();

    // Move drone in space

    body.Move(rotation_matrix, translation_vector, directory + body.Get_name());

    rotors[0].Move(rotation_matrix, translation_vector, directory + rotors[0].Get_name());
    rotors[1].Move(rotation_matrix, translation_vector, directory + rotors[1].Get_name());
    rotors[2].Move(rotation_matrix, translation_vector, directory + rotors[2].Get_name());
    rotors[3].Move(rotation_matrix, translation_vector, directory + rotors[3].Get_name());

    return *this;
}

void Drone::Propeller_rotation()
{
    // This method does not destroy object even though it is modified
    // it is possible to do it without changing it at all but it is worthless

    Matrix3x3 rotors_right, rotors_left;

    set_Rotation_OZ(rotors_left, 4);
    set_Rotation_OZ(rotors_right, -4);

    // Move to default
    rotors[0].Translate((body[7]) * (-1));
    rotors[1].Translate((body[5]) * (-1));
    rotors[2].Translate((body[6]) * (-1));
    rotors[3].Translate((body[4]) * (-1));

    //  2   3   |   direction
    //  0   1   v
    // Rotate in default
    rotors[0].Rotation(rotors_left);
    rotors[1].Rotation(rotors_right);
    rotors[2].Rotation(rotors_right);
    rotors[3].Rotation(rotors_left);

    // Move back
    rotors[0].Translate(body[7]);
    rotors[1].Translate(body[5]);
    rotors[2].Translate(body[6]);
    rotors[3].Translate(body[4]);
}