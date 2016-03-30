#include "ObjMesh.h"

#include "Logger/Logger.h"

CObjMesh::CObjMesh(const std::string& filename)
    : CMesh()
{
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;

    bool ret = tinyobj::LoadObj(shapes, materials, err, filename.c_str());

    if (!err.empty())   // `err` may contain warning message.
    {
        LOG_ERROR(err.c_str());
    }

    if (ret)
    {
        auto index = filename.find_last_of("/");
        process(filename.substr(0, index), shapes, materials);
    }
}

CObjMesh::~CObjMesh()
{
}

void
CObjMesh::process(const std::string& path, const std::vector<tinyobj::shape_t>& shapes, const std::vector<tinyobj::material_t>& materials)
{
    for each (tinyobj::material_t material in materials)
    {
        process_material(path, material);
    }

    for each (tinyobj::shape_t shape in shapes)
    {
        process_shape(shape);
    }
}

void
CObjMesh::process_shape(const tinyobj::shape_t& shape)
{
    // Create Vertex Data from Mesh Node
    std::vector<Vertex> vertices;
    Vertex vertex;

    const auto& lnumVertices = shape.mesh.positions.size() / 3;
    unsigned int uv_i = 0;
    unsigned int pos_i = 0;
    const bool& have_uv = !shape.mesh.texcoords.empty();

    for (unsigned int i = 0; i < lnumVertices; i++)
    {
        if (have_uv)
        {
            vertex.uv = float2(shape.mesh.texcoords[uv_i++], shape.mesh.texcoords[uv_i++]);
        }

        vertex.position = float3(shape.mesh.positions[pos_i], shape.mesh.positions[pos_i + 1], shape.mesh.positions[pos_i + 2]);
        vertex.normal = float3(shape.mesh.normals[pos_i++], shape.mesh.normals[pos_i++], shape.mesh.normals[pos_i++]);
        vertices.push_back(vertex);
    }

    // Create Mesh Indices for Indexed Drawing
    std::vector<unsigned int> indices;

    const auto& lNumFaces = shape.mesh.num_vertices.size();

    unsigned int actual_i = 0;

    for (unsigned int i = 0; i < lNumFaces; i++)
    {
        const auto& lNumIndices = shape.mesh.num_vertices[i];

        for (unsigned int j = 0; j < lNumIndices; j++)
        {
            indices.push_back(shape.mesh.indices[actual_i++]);
        }
    }

    // Load Mesh Textures into VRAM
    //std::map<GLuint, std::string> textures;
    //auto diffuse = process_material( path, scene->mMaterials[mesh->mMaterialIndex], aiTextureType_DIFFUSE);
    //auto specular = process(path, scene->mMaterials[mesh->mMaterialIndex], aiTextureType_SPECULAR);
    //textures.insert(diffuse.begin(), diffuse.end());
    //textures.insert(specular.begin(), specular.end());

    // Create New Mesh Node
    //mSubMeshes.push_back(std::unique_ptr<Mesh>(new Mesh(vertices, indices, textures)));
}

std::map<unsigned int, std::string>
CObjMesh::process_material(const std::string& path, tinyobj::material_t material)
{
    return std::map<unsigned int, std::string>();
}