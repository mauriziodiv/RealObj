// RealObj.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "ObjMesh.h"

bool openFile(const char* filename, std::ifstream& objFile)
{
	// TODO: Implement file opening logic
    
    objFile.open(filename);

	if (!objFile.is_open()) { return false; }

	return true;
}

// TODO: This is an example of a library function
bool loadObj(const char* filename, ObjMesh& objMesh)
{
    std::ifstream objFile;

	// Call bool openFile(const char* filename) to open the Obj file. If the function return true go to the next step.
    if (!openFile(filename, objFile))
    {
        objFile.close();
        return false;
    }

	// Loop through the file and read the vertices, for each vertex call void ObjMesh::addVertex(Vertex v) to add the
    // vertex to the mesh.

	//llok for the v prefix
    std::string line;

    unsigned int vertexCount = 0;
    unsigned int faceCount = 0;

    // Loop through the file and count the number of vertices and faces, for each vertex call void
    // ObjMesh::addVertex(Vertex v) to add the vertex to the mesh.
    while (std::getline(objFile, line))
    {
        if (line.starts_with("v ")) {vertexCount++;}
        if (line.starts_with("f ")) {faceCount++;}
    }

    if (vertexCount == 0 || faceCount == 0)
    {
        objFile.close();
        return false;
    }

    objFile.seekg(0);

    // Call bool ObjMesh::reserve(unsigned int vertexCount, unsigned int faceCount) to reserve the memory for the
    if (!objMesh.reserve(vertexCount, faceCount))
    {
        objFile.close();
        return false;
    }

    // Loop through the file and read the vertices, for each vertex call void ObjMesh::addVertex(Vertex v) to add the
    while (std::getline(objFile, line))
    {
        std::istringstream vtx(line);
        std::string prefix;

        if (line.starts_with("v "))
        {
            float x, y, z;

            vtx >> prefix >> x >> y >> z;
            objMesh.addVertex(Vertex(x, y, z));
        }

        if (line.starts_with("f "))
        {
            unsigned int x, y, z;

            vtx >> prefix >> x >> y >> z;
            objMesh.addIndices(x, y, z);
        }
    }

    objFile.close();

	return true;
}