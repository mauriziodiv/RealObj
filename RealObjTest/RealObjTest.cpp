// RealObjTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ObjMesh.h"
#include "RealObj.h"
#include "pch.h"

static int g_passed = 0;
static int g_failed = 0;

#define CHECK(expr, msg)   \
    do \
    {  \
        if (expr) \
        { \
            std::cout << "[PASS] " << (msg) << "\n"; \
            ++g_passed; \
        } \
        else \
        { \
            std::cout << "[FAIL] " << (msg) << "\n"; \
            ++g_failed; \
        } \
    } while (false)

#define CHECK_EQ(a, b, msg) CHECK((a) == (b), msg)
#define CHECK_NEAR(a, b, eps, msg) CHECK(std::abs((a) - (b)) < (eps), msg)

const char* TETRAHEDRON_PATH = "C:\\Users\\MaurizioDiVitto\\source\\assets\\Obj\\Tetrahedron_01.obj";
const char* BAD_PATH = "C:\\nonexistent\\missing_file.obj";

// ---- Group 1: Vector3D -------------------------------------------------------

void testVector3D()
{
    std::cout << "\n--- Group 1: Vector3D ---\n";

    Vector3D v(1.0f, 2.0f, 3.0f);
    CHECK_NEAR(v.getX(), 1.0f, 1e-6f, "getX returns 1.0");
    CHECK_NEAR(v.getY(), 2.0f, 1e-6f, "getY returns 2.0");
    CHECK_NEAR(v.getZ(), 3.0f, 1e-6f, "getZ returns 3.0");

    Vector3D neg(-1.0f, 0.0f, 0.5f);
    CHECK_NEAR(neg.getX(), -1.0f, 1e-6f, "getX negative value");
    CHECK_NEAR(neg.getY(), 0.0f, 1e-6f, "getY zero");
    CHECK_NEAR(neg.getZ(), 0.5f, 1e-6f, "getZ fractional value");
}

// ---- Group 2: ObjMesh direct API --------------------------------------------

void testObjMeshDirect()
{
    std::cout << "\n--- Group 2: ObjMesh direct API ---\n";

    ObjMesh mesh;

    // Vertices
    mesh.addVertex(Vector3D(0.0f, 1.0f, 0.0f));
    mesh.addVertex(Vector3D(1.0f, 0.0f, 0.0f));
    mesh.addVertex(Vector3D(-1.0f, 0.0f, 0.0f));

    CHECK_EQ(mesh.getVertices().size(), 3u, "getVertices size after 3 adds");
    CHECK_NEAR(mesh.getVertices()[0].getY(), 1.0f, 1e-6f, "vertex[0].y == 1.0");
    CHECK_NEAR(mesh.getVertices()[1].getX(), 1.0f, 1e-6f, "vertex[1].x == 1.0");
    CHECK_NEAR(mesh.getVertices()[2].getX(), -1.0f, 1e-6f, "vertex[2].x == -1.0");

    // Normals
    mesh.addNormal(Vector3D(0.0f, 1.0f, 0.0f));
    mesh.addNormal(Vector3D(0.0f, 0.0f, 1.0f));

    CHECK_EQ(mesh.getNormals().size(), 2u, "getNormals size after 2 adds");
    CHECK_NEAR(mesh.getNormals()[0].getY(), 1.0f, 1e-6f, "normal[0].y == 1.0");
    CHECK_NEAR(mesh.getNormals()[1].getZ(), 1.0f, 1e-6f, "normal[1].z == 1.0");

    // Vertex indices
    mesh.addVertexIndex(1u);
    mesh.addVertexIndex(2u);
    mesh.addVertexIndex(3u);

    CHECK_EQ(mesh.getVertexIndices().size(), 3u, "getVertexIndices size after 3 adds");
    CHECK_EQ(mesh.getVertexIndices()[0], 1u, "vertexIndex[0] == 1");
    CHECK_EQ(mesh.getVertexIndices()[2], 3u, "vertexIndex[2] == 3");

    // Normal indices
    mesh.addNormalIndex(1u);
    mesh.addNormalIndex(2u);
    mesh.addNormalIndex(1u);

    CHECK_EQ(mesh.getNormalIndices().size(), 3u, "getNormalIndices size after 3 adds");
    CHECK_EQ(mesh.getNormalIndices()[1], 2u, "normalIndex[1] == 2");

    // reserve() on a fresh mesh
    ObjMesh fresh;
    bool reserved = fresh.reserve(4u, 4u, 4u);
    CHECK(reserved, "reserve(4,4,4) returns true");
    CHECK_EQ(fresh.getVertices().size(), 0u, "reserve does not add elements");
    CHECK_EQ(fresh.getVertexIndices().size(), 0u, "reserve leaves index list empty");
}

// ---- Group 3: loadObj() error handling ----------------------------------------

void testLoadObjErrors()
{
    std::cout << "\n--- Group 3: loadObj error handling ---\n";

    ObjMesh mesh;
    bool result = loadObj(BAD_PATH, mesh);

    CHECK(!result, "loadObj with bad path returns false");
    CHECK_EQ(mesh.getVertices().size(), 0u, "vertices empty after failed load");
    CHECK_EQ(mesh.getNormals().size(), 0u, "normals empty after failed load");
    CHECK_EQ(mesh.getVertexIndices().size(), 0u, "vertex indices empty after failed load");
    CHECK_EQ(mesh.getNormalIndices().size(), 0u, "normal indices empty after failed load");
}

// ---- Group 4: loadObj() with Tetrahedron_01.obj --------------------------------

void testLoadObjTetrahedron()
{
    std::cout << "\n--- Group 4: Tetrahedron_01.obj ---\n";

    ObjMesh mesh;
    bool loaded = loadObj(TETRAHEDRON_PATH, mesh);
    CHECK(loaded, "loadObj returns true for Tetrahedron_01.obj");

    if (!loaded)
    {
        std::cout << "  [SKIP] Remaining Group 4 tests skipped (file did not load)\n";
        return;
    }

    const auto& verts = mesh.getVertices();
    const auto& norms = mesh.getNormals();
    const auto& vIdx = mesh.getVertexIndices();
    const auto& nIdx = mesh.getNormalIndices();

    // Structural checks
    CHECK_EQ(verts.size(), 4u, "vertex count == 4 (tetrahedron has 4 corners)");
    CHECK_EQ(vIdx.size(), 12u, "vertex index count == 12 (4 faces x 3)");
    CHECK(norms.size() > 0u, "at least 1 normal present");
    CHECK_EQ(nIdx.size(), vIdx.size(), "normalIndex count == vertexIndex count");

    // Index range checks (OBJ uses 1-based indexing)
    bool vIdxInRange = true;
    for (unsigned int i : vIdx)
        if (i < 1u || i > static_cast<unsigned int>(verts.size()))
        {
            vIdxInRange = false;
            break;
        }
    CHECK(vIdxInRange, "all vertex indices in range [1, vertexCount]");

    bool nIdxInRange = true;
    for (unsigned int i : nIdx)
        if (i < 1u || i > static_cast<unsigned int>(norms.size()))
        {
            nIdxInRange = false;
            break;
        }
    CHECK(nIdxInRange, "all normal indices in range [1, normalCount]");

    // Print vertices
    std::cout << "\n  Vertices (" << verts.size() << "):\n";
    std::cout << std::fixed << std::setprecision(6);
    for (size_t i = 0; i < verts.size(); ++i)
        std::cout << "    v[" << i << "] = (" << verts[i].getX() << ", " << verts[i].getY() << ", " << verts[i].getZ()
                  << ")\n";

    // Print normals
    std::cout << "\n  Normals (" << norms.size() << "):\n";
    for (size_t i = 0; i < norms.size(); ++i)
        std::cout << "    vn[" << i << "] = (" << norms[i].getX() << ", " << norms[i].getY() << ", " << norms[i].getZ()
                  << ")\n";

    // Print faces (3 indices at a time)
    unsigned int faceCount = static_cast<unsigned int>(vIdx.size()) / 3u;
    std::cout << "\n  Faces (" << faceCount << "):\n";
    for (unsigned int f = 0; f < faceCount; ++f)
    {
        unsigned int base = f * 3u;
        std::cout << "    f[" << f << "] = " << vIdx[base] << "//" << nIdx[base] << "  " << vIdx[base + 1] << "//"
                  << nIdx[base + 1] << "  " << vIdx[base + 2] << "//" << nIdx[base + 2] << "\n";
    }
}

// ---- main --------------------------------------------------------------------

int main()
{
    std::cout << "=== RealObj Test Suite ===\n";

    testVector3D();
    testObjMeshDirect();
    testLoadObjErrors();
    testLoadObjTetrahedron();

    std::cout << "\n=== Summary: " << g_passed << " passed, " << g_failed << " failed ===\n";
    return g_failed == 0 ? 0 : 1;
}