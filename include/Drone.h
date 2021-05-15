#ifndef DRONE_H
#define DRONE_H

#include "Rotor.h"
#include "Cuboid.h"
#include "lacze_do_gnuplota.hh"
#include <sys/stat.h>
#include <sys/types.h>

class Drone
{
private:
    Cuboid body;

    Rotor rotors[4];

    std::string directory = "../data/drone";

    static int id;

public:
    Drone();
    ~Drone();

    void Create_directory();
    void Add_files_names(PzG::LaczeDoGNUPlota &Lacze);
    void Remove_files_names(PzG::LaczeDoGNUPlota &Lacze);
};

#endif // DRONE_H