#include "pch.h"
#include "ObjMesh.h"

ObjMesh::ObjMesh()
{
}

void ObjMesh::addVertex(Vec3D v)
{
    vertices.push_back(v);
}

void ObjMesh::addNormal(Vec3D n)
{
    normals.push_back(n);
}

void ObjMesh::addVertexIndex(unsigned int index)
{
    vertexIndices.push_back(index);
}

void ObjMesh::addNormalIndex(unsigned int index)
{
    normalIndices.push_back(index);
}

bool ObjMesh::reserve(unsigned int vertexCount, unsigned int normalCount, unsigned int faceCount)
{
    try
    {
        vertices.reserve(vertexCount);
        normals.reserve(normalCount);
        vertexIndices.reserve(faceCount * 3);
        normalIndices.reserve(faceCount * 3);
    }
    catch (const std::bad_alloc&)
    {
        return false;
    }
    return true;
}