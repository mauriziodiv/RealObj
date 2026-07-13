// RealObj.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "ObjMesh.h"

struct FaceCorner
{
    unsigned int vertexIndex;
    unsigned int textureIndex;
    unsigned int normalIndex;
};

bool openFile(const char* filename, std::ifstream& objFile)
{
	// TODO: Implement file opening logic
    
    objFile.open(filename);

	if (!objFile.is_open()) { return false; }

	return true;
}

void tokenIndex(std::string& tkn, unsigned int& index, unsigned int& textureIndex, unsigned int& normalIndex)
{
    size_t firstSlash = tkn.find('/');

     if (firstSlash == std::string::npos)
     {
         throw std::invalid_argument("Invalid token format");
     }

     index = std::stoul(tkn.substr(0, firstSlash));

     size_t secondSlash = tkn.find('/', firstSlash + 1);

     if (secondSlash == std::string::npos)
     {
         throw std::invalid_argument("Invalid token format");
     }

     auto ti = tkn.substr(firstSlash + 1, secondSlash - firstSlash - 1);

     if (ti.empty())
     {
         textureIndex = 0; // No texture index
     }
     else
     {
         textureIndex = std::stoul(ti);
     }

     normalIndex = std::stoul(tkn.substr(secondSlash + 1));
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
    unsigned int normalCount = 0;
    unsigned int indexCount = 0;

    // Loop through the file and count the number of vertices and faces, for each vertex call void
    // ObjMesh::addVertex(Vertex v) to add the vertex to the mesh.
    while (std::getline(objFile, line))
    {
        if (line.starts_with("v ")) { vertexCount++; }
        if (line.starts_with("vn ")) { normalCount++; }
        if (line.starts_with("f ")) { indexCount++; }
    }

    if (vertexCount == 0 || indexCount == 0 || normalCount == 0)
    {
        objFile.close();
        return false;
    }

    objFile.clear();
    objFile.seekg(0);

    // Call bool ObjMesh::reserve(unsigned int vertexCount, unsigned int faceCount, unsigned int normalCount) to reserve the memory for the
    if (!objMesh.reserve(vertexCount, normalCount, indexCount))
    {
        objFile.close();
        return false;
    }

    // Loop through the file and read the vertices, for each vertex call void ObjMesh::addVertex(Vector3D v) to add the
    while (std::getline(objFile, line))
    {
        std::istringstream vtx(line);
        std::string prefix;

        if (line.starts_with("v "))
        {
            float x, y, z;

            vtx >> prefix >> x >> y >> z;
            objMesh.addVertex(Vec3D(x, y, z));
        }

        if (line.starts_with("vt "))
        {
            float u, v;

            vtx >> prefix >> u >> v;
            objMesh.addTexture(Vec2D(u, v));
        }

        if (line.starts_with("vn "))
        {
            float x, y, z;

            vtx >> prefix >> x >> y >> z;
            objMesh.addNormal(Vec3D(x, y, z));
        }

        if (line.starts_with("f "))
        {
            std::string token;

            vtx >> prefix;

            std::vector<FaceCorner> corners;

            while (vtx >> token)
            {
                FaceCorner corner;
                tokenIndex(token, corner.vertexIndex, corner.textureIndex, corner.normalIndex);
                corners.push_back(corner);
            }

            for (size_t i = 1; i + 1 < corners.size(); ++i)
            {
                const FaceCorner* triangle[3] = {&corners[0], &corners[i], &corners[i + 1]};

                for (const FaceCorner* faceCorner : triangle)
                {
                    objMesh.addVertexIndex(faceCorner->vertexIndex);
                    objMesh.addTextureIndex(faceCorner->textureIndex);
                    objMesh.addNormalIndex(faceCorner->normalIndex);
                }
            }
        }
    }

    objFile.close();

	return true;
}