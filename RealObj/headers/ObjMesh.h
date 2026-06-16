#pragma once
#include <vector>

struct Vertex
{
  public:

    Vertex(float x, float y, float z) : x(x), y(y), z(z) {}
    
    float getX() { return x; };
    float getY() { return y; };
    float getZ() { return z; };

   private:

    float x;
    float y;
    float z;
};

class ObjMesh
{
	public:

		ObjMesh();

        void addVertex(Vertex v);
        void addIndices(unsigned int a, unsigned int b, unsigned int c);

        bool reserve(unsigned int vertexCount, unsigned int faceCount);

	private:
        
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
};