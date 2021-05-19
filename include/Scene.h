#ifndef SCENE_H
#define SCENE_H

/** @file
 */

#include "Drone.h"
#include "lacze_do_gnuplota.hh"
#include <chrono>
#include <thread>

/** @class Scene
 * 
 * Class which holds drones objects
 * and let's user operate on it.
 */
class Scene
{
private:
    Drone Drones[2];

    Drone *Active_drone;

    PzG::LaczeDoGNUPlota Link;

    std::string surface;

    void Draw_surface(int x_min, int x_max, int y_min, int y_max);

public:
    Scene();

    bool Choose_drone(int index);
    void List_drones();

    void Draw();
    void Draw_path(std::vector<Vector3D> total_path);
    bool Calculate_path(double angle, double length, std::vector<Vector3D> &total_path);

    bool Animate(double angle, std::vector<Vector3D> &total_path);

    bool Add_drone(int drone_id, Drone drone);
    bool Remove_drone(int drone_id);
    // /** @fn  Scene()
    // *   @brief Default constructor
    // *
    // *   Each element is created with default value,
    // *   specification of cuboid is also made there.
    // */
    // Scene();

    // /** @fn void Get_rotation_sequence()
    // *   A function for reading rotation sequence.
    // *
    // *   Terminates with a '.' ,basic invalid input handling.
    // */
    // void Get_rotation_sequence();

    // /** @fn void Get_translation_vector()
    // *   A function for reading translation vector.
    // */
    // void Get_translation_vector();

    // /** @fn void Animate(PzG::LaczeDoGNUPlota &Lacze, int number_of_operations)
    // *   @brief Animate holded cuboid
    // *
    // *   After reading new rotation or translation,Cuboid can be animated in gnuplot.
    // *   In this version of scene every small change is added or multiplied
    // *   to total result in order to remember current position.
    // *
    // *   After making whole animation some objects are cleared and the others are filled
    // *   with new values.
    // *
    // *   There will be more improvements in future task.
    // */
    // void Animate(PzG::LaczeDoGNUPlota &Lacze, int number_of_operations);
};

#endif // SCENE_H