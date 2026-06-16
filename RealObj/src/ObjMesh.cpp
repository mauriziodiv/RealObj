#include "pch.h"
#include "ObjMesh.h"

ObjMesh::ObjMesh()
{
}

void ObjMesh::addVertex(Vertex v)
{
    vertices.push_back(v);
}

void ObjMesh::addIndices(unsigned int a, unsigned int b, unsigned int c)
{
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

bool ObjMesh::reserve(unsigned int vertexCount, unsigned int faceCount)
{
    try
    {
        vertices.reserve(vertexCount);
        indices.reserve(faceCount * 3);
    }
    catch (const std::bad_alloc&)
    {
        return false;
    }
    return true;
}