#pragma once
#include <vector>

struct Vec3D
{
  public:

    Vec3D(float x, float y, float z) : x(x), y(y), z(z) {}
    
    float getX() const { return x; };
    float getY() const { return y; };
    float getZ() const { return z; };

   private:

    float x;
    float y;
    float z;
};

class ObjMesh
{
	public:

		ObjMesh();

        void addVertex(Vec3D v);
        void addNormal(Vec3D n);
        void addVertexIndex(unsigned int index);
        void addNormalIndex(unsigned int index);

        const std::vector<Vec3D>& getVertices() const { return vertices; }
        const std::vector<Vec3D>& getNormals() const { return normals; }
        const std::vector<unsigned int>& getVertexIndices() const { return vertexIndices; }
        const std::vector<unsigned int>& getNormalIndices() const { return normalIndices; }

        bool reserve(unsigned int vertexCount, unsigned int normalCount, unsigned int faceCount);

	private:
        
        std::vector<Vec3D> vertices;
        std::vector<Vec3D> normals;
        std::vector<unsigned int> vertexIndices;
        std::vector<unsigned int> normalIndices;
};