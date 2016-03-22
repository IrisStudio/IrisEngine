#pragma once
#ifndef _CObjMesh_
#define _CObjMesh_

#include "Types.h"
#include "Mesh.h"

#include "tiny_obj_loader.h"

#include <string>
#include <vector>

// Vertex Format
struct Vertex
{
    float3 position;
    float3 normal;
    float2 uv;
};

class CObjMesh : public CMesh
{
    public:
        CObjMesh(const std::string& filename);
        virtual ~CObjMesh();
    protected:

    private:
        void process(const std::string& path, const std::vector<tinyobj::shape_t>& shapes, const std::vector<tinyobj::material_t>& materials);
        void process_shape(const tinyobj::shape_t& shape);
        std::map<unsigned int, std::string> process_material(const std::string& path, tinyobj::material_t material);

        DISALLOW_COPY_AND_ASSIGN(CObjMesh);
};

typedef std::shared_ptr< CObjMesh > CObjMeshSPtr;

#endif