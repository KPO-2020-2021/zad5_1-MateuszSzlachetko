#ifndef FIGURE_H
#define FIGURE_H

#include "Matrix3x3.h"
#include "Vector3D.h"
#include <string>

class Figure
{
private:
    std::string name;

public:
    Figure(std::string n);

    std::string Update_name(std::string &append);
    std::string Get_name();
};

#endif // FIGURE_H