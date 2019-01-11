#include "mesh.h"

namespace msg {
Mesh::Mesh()
{
    m_data.reserve(2500 * 6);
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

    m_bbox.extendBy(v);
}

void
Mesh::render()
{}
}
