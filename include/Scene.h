#ifndef SCENE_H
#define SCENE_H

/** @file
 */

#include "Cuboid.h"
#include "lacze_do_gnuplota.hh"
#include <chrono>
#include <thread>

/** @class Scene
 * 
 * Class which holds a specific cuboid object
 * and let's user operate on it.
 */
class Scene
{
public:
    Cuboid _cuboid;

    Matrix3x3 rotation_matrix;
    Matrix3x3 previous_rotation_matrix;
    Matrix3x3 total_rotation_matrix;

    Vector3D translation;
    Vector3D total_translation;

public:
    /** @fn  Scene()
    *   @brief Default constructor
    *   
    *   Each element is created with default value,
    *   specification of cuboid is also made there.
    */
    Scene();

    /** @fn void Get_rotation_sequence()
    *   A function for reading rotation sequence.
    *   
    *   Terminates with a '.' ,basic invalid input handling.    
    */
    void Get_rotation_sequence();

    /** @fn void Get_translation_vector()
    *   A function for reading translation vector.
    */
    void Get_translation_vector();

    /** @fn void Animate(PzG::LaczeDoGNUPlota &Lacze, int number_of_operations)
    *   @brief Animate holded cuboid
    * 
    *   After reading new rotation or translation,Cuboid can be animated in gnuplot.
    *   In this version of scene every small change is added or multiplied
    *   to total result in order to remember current position.
    * 
    *   After making whole animation some objects are cleared and the others are filled
    *   with new values.
    * 
    *   There will be more improvements in future task.
    */
    void Animate(PzG::LaczeDoGNUPlota &Lacze, int number_of_operations);

    /** @fn  void Show_rotation_matrix()
    *   A basic menu function.
    */
    void Show_rotation_matrix();

    /** @fn  void Display_vertices()
    *   A basic menu function.
    */
    void Display_vertices();

    /** @fn  void Check_side_length()
    *   A basic menu function.
    */
    void Check_side_length();

    /** @fn  void Set_previous_rotation()
    *   After calling current rotation matrix is filled with 
    *   the previous one
    */
    void Set_previous_rotation();
};

#endif // SCENE_H