#include "mesh.h"
#include "tiny_obj_loader.h"
#include <qmath.h>
#include <iostream>
#include <cassert>

Mesh::Mesh()
{
    m_data.reserve(2500 * 6);
}

bool
Mesh::loadObj(const std::string& filename)
{
    const bool triangulate = true;
    const char* basepath = nullptr;

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(
      &attrib, &shapes, &materials, &warn, &err, filename.c_str(), basepath, triangulate);

    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "ERR: " << err << std::endl;
    }

    if (!ret) {
        printf("Failed to load/parse .obj.\n");
        return false;
    }

    std::cout << "# of vertices  : " << (attrib.vertices.size() / 3) << std::endl;
    std::cout << "# of normals   : " << (attrib.normals.size() / 3) << std::endl;
    std::cout << "# of texcoords : " << (attrib.texcoords.size() / 2) << std::endl;
    std::cout << "# of shapes    : " << shapes.size() << std::endl;
    std::cout << "# of materials : " << materials.size() << std::endl;

    m_data.clear();

    // For each shape
    for (size_t i = 0; i < shapes.size(); i++) {

        size_t index_offset = 0;

        // For each face
        for (size_t f = 0; f < shapes[i].mesh.num_face_vertices.size(); f++) {
            const size_t fnum = shapes[i].mesh.num_face_vertices[f];

            assert(fnum == 3);

            // For each vertex in the face
            for (size_t v = 0; v < fnum; v++) {
                tinyobj::index_t idx = shapes[i].mesh.indices[index_offset + v];

                const QVector3D vp(attrib.vertices[3 * idx.vertex_index + 0],
                                   attrib.vertices[3 * idx.vertex_index + 1],
                                   attrib.vertices[3 * idx.vertex_index + 2]);
                const QVector3D vn(attrib.normals[3 * idx.vertex_index + 0],
                                   attrib.normals[3 * idx.vertex_index + 1],
                                   attrib.normals[3 * idx.vertex_index + 2]);
                add(vp, vn);
            }
            index_offset += fnum;
        }
    }
    return ret;
}

void
Mesh::add(const QVector3D& v, const QVector3D& n)
{
    m_data.append(v.x());
    m_data.append(v.y());
    m_data.append(v.z());
    m_data.append(n.x());
    m_data.append(n.y());
    m_data.append(n.z());
}
