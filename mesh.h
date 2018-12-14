#pragma once

#include <string>

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class Mesh
{
  public:
    Mesh();
    const GLfloat* constData() const { return m_data.constData(); }
    int count() const { return m_data.size(); }
    int vertexCount() const { return m_data.size() / 6; }

    bool loadObj(const std::string& filename);

  private:
    void add(const QVector3D& v, const QVector3D& n);

    QVector<GLfloat> m_data;
};
