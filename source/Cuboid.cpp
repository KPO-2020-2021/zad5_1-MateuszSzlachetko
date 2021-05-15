#include "Cuboid.h"

Cuboid::Cuboid()
{
    for (Vector3D vertice : vertices)
        vertice = Vector3D({0, 0, 0});

    position = Vector3D();

    orientation = Matrix3x3({1, 0, 0,
                             0, 1, 0,
                             0, 0, 1});
}

Cuboid::Cuboid(double x1, double y1, double z1, double x2, double y2, double z2)
{
    if (x1 == x2 || y1 == y2 || z1 == z2) // ~~> vertices are not oposing
        throw std::invalid_argument("Not oposing vertices passed in a constructor");

    vertices[0] = Vector3D({x1, y1, z1});
    vertices[1] = Vector3D({x2, y1, z1});
    vertices[2] = Vector3D({x1, y2, z1});
    vertices[3] = Vector3D({x2, y2, z1});

    vertices[4] = Vector3D({x1, y2, z2});
    vertices[5] = Vector3D({x2, y2, z2});
    vertices[6] = Vector3D({x1, y1, z2});
    vertices[7] = Vector3D({x2, y1, z2});

    position = Vector3D();

    orientation = Matrix3x3({1, 0, 0,
                             0, 1, 0,
                             0, 0, 1});
}

Cuboid::Cuboid(std::vector<Vector3D> &vectors)
{
    int index = 0;
    for (Vector3D vertice : vectors)
        vertices[index++] = vertice;

    position = Vector3D();

    orientation = Matrix3x3({1, 0, 0,
                             0, 1, 0,
                             0, 0, 1});
}

Cuboid Cuboid::Rotation(Matrix3x3 &rotation_matrix)
{
    for (int i = 0; i < SIZE; ++i)
    {
        vertices[i] = rotation_matrix * vertices[i];
    }
    return *this;
}

Cuboid Cuboid::Translate(Vector3D translation_vector) // not a reference to pass a constructor
{
    for (int i = 0; i < SIZE; ++i)
    {
        vertices[i] = vertices[i] + translation_vector;
    }
    return *this;
}

Cuboid Cuboid::Scale(double scalar)
{
    for (int i = 0; i < SIZE; ++i)
    {
        vertices[i] = vertices[i] * scalar;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Cuboid &c)
{
    os << std::setprecision(10) << std::fixed;
    for (Vector3D vertice : c.vertices)
    {
        os << vertice;
        os << std::endl;
    }

    return os;
}

std::ofstream &operator<<(std::ofstream &ofs, const Cuboid &c)
{
    ofs << std::setprecision(10) << std::fixed;

    // 3 2 | 7 6
    // 0 1 | 4 5

    // 0 2 | 6 4
    // 1 3 | 7 5

    Vector3D up, down;

    up = c.vertices[6];
    up = up - c.vertices[1];
    up = up / 2;
    up = up + c.vertices[1];

    down = c.vertices[4];
    down = down - c.vertices[3];
    down = down / 2;
    down = down + c.vertices[3];

    ofs << up << std::endl;
    ofs << c.vertices[6] << std::endl;
    ofs << c.vertices[4] << std::endl;
    ofs << down << "\n#\n\n";

    ofs << up << std::endl;
    ofs << c.vertices[0] << std::endl;
    ofs << c.vertices[2] << std::endl;
    ofs << down << "\n#\n\n";

    ofs << up << std::endl;
    ofs << c.vertices[1] << std::endl;
    ofs << c.vertices[3] << std::endl;
    ofs << down << "\n#\n\n";

    ofs << up << std::endl;
    ofs << c.vertices[7] << std::endl;
    ofs << c.vertices[5] << std::endl;
    ofs << down << "\n#\n\n";

    ofs << up << std::endl;
    ofs << c.vertices[6] << std::endl;
    ofs << c.vertices[4] << std::endl;
    ofs << down << "\n#\n\n";

    // Vector3D up, down;

    // up = c.vertices[2];
    // up = up - c.vertices[1];
    // up = up / 2;
    // up = up + c.vertices[1];

    // down = c.vertices[4];
    // down = down - c.vertices[7];
    // down = down / 2;
    // down = down + c.vertices[7];

    // ofs << up << std::endl;
    // ofs << c.vertices[2] << std::endl;
    // ofs << c.vertices[4] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << c.vertices[3] << std::endl;
    // ofs << c.vertices[5] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << c.vertices[1] << std::endl;
    // ofs << c.vertices[7] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << c.vertices[0] << std::endl;
    // ofs << c.vertices[6] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << c.vertices[2] << std::endl;
    // ofs << c.vertices[4] << std::endl;
    // ofs << down << "\n#\n\n";
    // min = c[0];
    // max = c[5];
    // mid = (c[0] + c[5]) / 2;

    // Vector3D up({mid[0], min[1], mid[2]}), down({mid[0], max[1], mid[2]});

    // ofs << up << std::endl;
    // ofs << max[0] << " " << min[1] << " " << max[2] << std::endl;
    // ofs << max[0] << " " << max[1] << " " << max[2] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << max[0] << " " << min[1] << " " << min[2] << std::endl;
    // ofs << max[0] << " " << max[1] << " " << min[2] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << min[0] << " " << min[1] << " " << min[2] << std::endl;
    // ofs << min[0] << " " << max[1] << " " << min[2] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << min[0] << " " << min[1] << " " << max[2] << std::endl;
    // ofs << min[0] << " " << max[1] << " " << max[2] << std::endl;
    // ofs << down << "\n#\n\n";

    // ofs << up << std::endl;
    // ofs << max[0] << " " << min[1] << " " << max[2] << std::endl;
    // ofs << max[0] << " " << max[1] << " " << max[2] << std::endl;
    // ofs << down << "\n#\n\n";

    return ofs;
}

bool operator==(const Cuboid &c1, const Cuboid &c2)
{
    for (int i = 0; i < SIZE; ++i)
    {
        if (!(c1.vertices[i] == c2.vertices[i]))
            return false;
    }
    return true;
}

Vector3D Cuboid::operator[](int index) const
{
    if (index < 0 || index > SIZE - 1)
        throw std::invalid_argument("Index out of range");
    else
    {
        return vertices[index]; // return copy,which let's us only to read the value
    }
}

Vector3D &Cuboid::operator[](int index)
{
    if (index < 0 || index > SIZE - 1)
        throw std::invalid_argument("Index out of range");
    else
    {
        return vertices[index]; // return reference,which let's us set the value
    }
}

void Cuboid::Write_to_file(std::string filename, File_mode mode) const
{
    std::ofstream Data_file;

    if (mode == 0)
        Data_file.open(filename, std::ios::trunc); // overwrite mode
    else
        Data_file.open(filename, std::ios::app); // append mode

    if (Data_file.is_open())
    {
        if (mode == 0)
            Data_file << *this;
        else
        {
            Data_file << std::endl; // newline for cleaner output in the file
            Data_file << *this;
        }
    }
    else
    {
        throw std::invalid_argument("[Cuboid]file opening error\n");
    }

    Data_file.close();
}

Cuboid Cuboid::Move(Matrix3x3 &rotation_matrix, Vector3D translation_vector, std::string filename)
{
    // Apply reference model
    Cuboid temp = (*this);

    // update total position
    this->orientation = rotation_matrix * orientation;
    this->position = position + translation_vector;

    temp.Rotation(this->orientation);
    temp.Translate(this->position);

    temp.Write_to_file(filename, Overwrite);

    return *this;
}
