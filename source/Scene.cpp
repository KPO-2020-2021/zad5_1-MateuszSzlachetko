#include "Scene.h"

Scene::Scene()
{
    _cuboid = Cuboid(-30, -30, -30, 30, 30, 30);

    rotation_matrix = Matrix3x3({1, 0, 0,
                                 0, 1, 0,
                                 0, 0, 1});

    previous_rotation_matrix = Matrix3x3({1, 0, 0,
                                          0, 1, 0,
                                          0, 0, 1});

    total_rotation_matrix = Matrix3x3({1, 0, 0,
                                       0, 1, 0,
                                       0, 0, 1});

    translation = Vector3D();
    total_translation = Vector3D();
}

void Scene::Animate(PzG::LaczeDoGNUPlota &Lacze, int number_of_operations)
{
    int i = 0;
    Cuboid cuboid_temp;
    Vector3D translation_temp;

    cuboid_temp = _cuboid;
    translation_temp = translation / number_of_operations; // whole translation will be done after whole animation

    std::cout << "Animating..." << std::endl;

    //First move to set previous position
    cuboid_temp.Translate(total_translation);
    cuboid_temp.Rotation(total_rotation_matrix);
    cuboid_temp.Write_to_file("../data/vertices.dat", Overwrite);

    std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000)); // wait 1s to open GNUplot window
    Lacze.Rysuj();                                                     // first drawing

    //cuboid_temp = _cuboid;
    while (i < number_of_operations)
    {
        // increment total postion
        total_translation = total_translation + translation_temp;
        total_rotation_matrix = rotation_matrix * total_rotation_matrix;

        cuboid_temp.Translate(total_translation);
        cuboid_temp.Rotation(total_rotation_matrix);
        cuboid_temp.Write_to_file("../data/vertices.dat", Overwrite);

        cuboid_temp = _cuboid; //reset values
        std::this_thread::sleep_for(std::chrono::nanoseconds(1000000000 / 60));
        Lacze.Rysuj();

        i++;
    }

    // store current rotation matrix;
    previous_rotation_matrix = rotation_matrix;

    // reset rotation matrix
    rotation_matrix = Matrix3x3({1, 0, 0,
                                 0, 1, 0,
                                 0, 0, 1});
    // reset translation vector
    translation = Vector3D();

    std::cout << "End of animation" << std::endl;
}

void Scene::Get_rotation_sequence()
{
    char axis;
    double angle;
    Matrix3x3 temp;

    std::cout << "Choose rotation axis,and enter angle value" << std::endl;

    while (axis != '.')
    {
        std::cin >> axis;

        if (axis == 'x' || axis == 'y' || axis == 'z')
        {
            std::cin >> angle;
            if (std::cin.fail())
            {
                std::cerr << "Wrong angle,repeat whole process" << std::endl;
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else
            {
                if (axis == 'x')
                {
                    set_Rotation_OX(temp, angle);
                }

                if (axis == 'y')
                {
                    set_Rotation_OY(temp, angle);
                }

                if (axis == 'z')
                {
                    set_Rotation_OZ(temp, angle);
                }

                this->rotation_matrix = temp * this->rotation_matrix; // nowa * aktualna od lewej strony
            }
        }
        else if (axis != '.') // ending term
        {
            std::cout << "Choose between 'x' 'y' 'z'" << std::endl;
        }
    }
}

void Scene::Get_translation_vector()
{
    std::cout << "Enter translation vector" << std::endl;

    std::cin >> translation; // get translation vector
}

void Scene::Show_rotation_matrix()
{
    std::cout << std::fixed;

    std::cout << "Rotation matrix: " << std::endl;
    std::cout << previous_rotation_matrix << std::endl;
}
void Scene::Display_vertices()
{
    Cuboid temp = _cuboid; // get default points

    // calculate current position
    temp.Translate(total_translation);
    temp.Rotation(total_rotation_matrix);

    std::cout << temp << std::endl;
}
void Scene::Check_side_length()
{
    std::cout << std::endl;
    _cuboid.Side_length();
    std::cout << std::endl;
}

void Scene::Set_previous_rotation()
{
    rotation_matrix = previous_rotation_matrix;
}