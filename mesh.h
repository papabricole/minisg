#pragma once

#include <string>

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

#include <box3d.h>

class Mesh
{
  public:
    Mesh();
    const GLfloat* constData() const { return m_data.constData(); }
    int count() const { return m_data.size(); }
    int vertexCount() const { return m_data.size() / 6; }
    const Box3D& box() const { return m_bbox; }

    void add(const QVector3D& v, const QVector3D& n);

  private:
    QVector<GLfloat> m_data;
    Box3D m_bbox;
};
