#include "Cuboid.h"

Cuboid::Cuboid()
{
    for (Vector3D vertice : vertices)
        vertice = Vector3D({0, 0, 0});
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
}

Cuboid::Cuboid(std::vector<Vector3D> &vectors)
{
    int index = 0;
    for (Vector3D vertice : vectors)
        vertices[index++] = vertice;
}

Cuboid Cuboid::Rotation(Matrix3x3 &rotation_matrix)
{
    for (int i = 0; i < SIZE; ++i)
    {
        vertices[i] = rotation_matrix * vertices[i];
    }
    return *this;
}

Cuboid Cuboid::Translate(Vector3D translation_vector) // not a reference to pass a consturctor
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

void Cuboid::Side_length() const
{
    std::cout << std::setprecision(10) << std::fixed;
    double sideW1_W2, sideW3_W4, sideW5_W6, sideW7_W8; // set 1
    double sideW2_W4, sideW1_W3, sideW8_W6, sideW7_W5; // set 2

    double sideW1_W7, sideW2_W8, sideW4_W6, sideW3_W5; // along Z axis

    sideW1_W2 = (vertices[0] - vertices[1]).Length();
    sideW3_W4 = (vertices[2] - vertices[3]).Length();
    sideW5_W6 = (vertices[4] - vertices[5]).Length();
    sideW7_W8 = (vertices[6] - vertices[7]).Length();

    sideW2_W4 = (vertices[1] - vertices[3]).Length();
    sideW1_W3 = (vertices[0] - vertices[2]).Length();
    sideW8_W6 = (vertices[7] - vertices[5]).Length();
    sideW7_W5 = (vertices[6] - vertices[4]).Length();

    sideW1_W7 = (vertices[0] - vertices[6]).Length();
    sideW2_W8 = (vertices[1] - vertices[7]).Length();
    sideW4_W6 = (vertices[3] - vertices[5]).Length();
    sideW3_W5 = (vertices[2] - vertices[4]).Length();

    if (sideW1_W2 > sideW2_W4) // first set of sides is longer
    {
        if ((std::abs(sideW1_W2 - sideW3_W4) < MIN_DIFF) && (std::abs(sideW1_W2 - sideW5_W6) < MIN_DIFF) && (std::abs(sideW1_W2 - sideW7_W8) < MIN_DIFF))
        {
            std::cout << "Longer sides are equal" << std::endl;
            std::cout << "First: " << sideW1_W2 << std::endl;
            std::cout << "Second: " << sideW3_W4 << std::endl;
            std::cout << "Third: " << sideW5_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W8 << std::endl;
        }
        else
        {
            std::cout << "Longer sides are not equal" << std::endl;
            std::cout << "First: " << sideW1_W2 << std::endl;
            std::cout << "Second: " << sideW3_W4 << std::endl;
            std::cout << "Third: " << sideW5_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W8 << std::endl;
        }

        if ((std::abs(sideW2_W4 - sideW1_W3) < MIN_DIFF) && (std::abs(sideW2_W4 - sideW8_W6) < MIN_DIFF) && (std::abs(sideW2_W4 - sideW7_W5) < MIN_DIFF))
        {
            std::cout << "Shorter sides are equal" << std::endl;
            std::cout << "First: " << sideW2_W4 << std::endl;
            std::cout << "Second: " << sideW1_W3 << std::endl;
            std::cout << "Third: " << sideW8_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W5 << std::endl;
        }
        else
        {
            std::cout << "Shorter sides are not equal" << std::endl;
            std::cout << "First: " << sideW2_W4 << std::endl;
            std::cout << "Second: " << sideW1_W3 << std::endl;
            std::cout << "Third: " << sideW8_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W5 << std::endl;
        }
    }
    else // second set of sides is longer
    {
        if ((std::abs(sideW2_W4 - sideW1_W3) < MIN_DIFF) && (std::abs(sideW2_W4 - sideW8_W6) < MIN_DIFF) && (std::abs(sideW2_W4 - sideW7_W5) < MIN_DIFF))
        {
            std::cout << "Longer sides are equal" << std::endl;
            std::cout << "First: " << sideW2_W4 << std::endl;
            std::cout << "Second: " << sideW1_W3 << std::endl;
            std::cout << "Third: " << sideW8_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W5 << std::endl;
        }
        else
        {
            std::cout << "Longer sides are not equal" << std::endl;
            std::cout << "First: " << sideW2_W4 << std::endl;
            std::cout << "Second: " << sideW1_W3 << std::endl;
            std::cout << "Third: " << sideW8_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W5 << std::endl;
        }

        if ((std::abs(sideW1_W2 - sideW3_W4) < MIN_DIFF) && (std::abs(sideW1_W2 - sideW5_W6) < MIN_DIFF) && (std::abs(sideW1_W2 - sideW7_W8) < MIN_DIFF))
        {
            std::cout << "Shorter sides are equal" << std::endl;
            std::cout << "First: " << sideW1_W2 << std::endl;
            std::cout << "Second: " << sideW3_W4 << std::endl;
            std::cout << "Third: " << sideW5_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W8 << std::endl;
        }
        else
        {
            std::cout << "Shorter sides are not equal" << std::endl;
            std::cout << "First: " << sideW1_W2 << std::endl;
            std::cout << "Second: " << sideW3_W4 << std::endl;
            std::cout << "Third: " << sideW5_W6 << std::endl;
            std::cout << "Fourth: " << sideW7_W8 << std::endl;
        }
    }

    if ((std::abs(sideW1_W7 - sideW2_W8) < MIN_DIFF) && (std::abs(sideW1_W7 - sideW4_W6) < MIN_DIFF) && (std::abs(sideW1_W7 - sideW3_W5) < MIN_DIFF))
    {
        std::cout << "Vertical sides are equal" << std::endl;
        std::cout << "First: " << sideW1_W7 << std::endl;
        std::cout << "Second: " << sideW2_W8 << std::endl;
        std::cout << "Third: " << sideW4_W6 << std::endl;
        std::cout << "Fourth: " << sideW3_W5 << std::endl;
    }
    else
    {
        std::cout << "Vertical sides are not equal" << std::endl;
        std::cout << "First: " << sideW1_W7 << std::endl;
        std::cout << "Second: " << sideW2_W8 << std::endl;
        std::cout << "Third: " << sideW4_W6 << std::endl;
        std::cout << "Fourth: " << sideW3_W5 << std::endl;
    }
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
    int i = 0;
    for (Vector3D vertice : c.vertices)
    {
        ofs << vertice;
        ofs << std::endl;
        if (i % 2)
            ofs << std::endl;
        i++;
    }

    ofs << c.vertices[0] << std::endl;
    ofs << c.vertices[1] << std::endl;
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
