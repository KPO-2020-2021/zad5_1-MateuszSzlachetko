#ifndef Rotor_H
#define Rotor_H

#include "Figure.h"
#include "Matrix3x3.h"
#include "Vector3D.h"
#include <fstream>
#include <iomanip>

class Rotor : public Figure
{
private:
    Vector3D vertices[12];

    Vector3D center[2];

    Vector3D position;
    Matrix3x3 orientation;

public:
    Rotor();

    Rotor(double x, double y, double z, double a, double b, double c);

    Rotor Rotation(Matrix3x3 &rotation_matrix);

    Rotor Translate(Vector3D translation_vector);

    Rotor Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename);
    Rotor Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector);

    friend std::ofstream &operator<<(std::ofstream &ofs, const Rotor &r);

    friend bool operator==(const Rotor &r1, const Rotor &r2);

    void Write_to_file(std::string filename) const;
};

#endif // Rotor_H