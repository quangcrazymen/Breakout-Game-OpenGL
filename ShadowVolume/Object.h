#pragma once
# define INFINITY 1000
// Structure Describing A Vertex In An Object
struct Point3f
{
    float x, y, z;
};

// Structure Describing A Plane, In The Format: ax + by + cz + d = 0
struct Plane
{
    float a, b, c, d;
};

// Structure Describing An Object's Face
struct Face
{
    int vertexIndices[3];           // Index Of Each Vertex Within An Object That Makes Up The Triangle Of This Face
    Point3f normals[3];         // Normals To Each Vertex
    Plane planeEquation;            // Equation Of A Plane That Contains This Triangle
    int neighbourIndices[3];        // Index Of Each Face That Neighbours This One Within The Object
    bool visible;               // Is The Face Visible By The Light?
};

struct ShadowedObject
{
    int nVertices;
    Point3f* pVertices;         // Will Be Dynamically Allocated

    int nFaces;
    Face* pFaces;               // Will Be Dynamically Allocated
};

class Object
{
};

