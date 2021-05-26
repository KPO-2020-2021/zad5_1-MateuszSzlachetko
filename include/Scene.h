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
    bool Round_route(double radius);

    bool Change_colour(int colour);
    bool Add_drone(int drone_id, Drone drone);
    bool Remove_drone(int drone_id);
};

#endif // SCENE_H