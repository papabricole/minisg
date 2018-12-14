#pragma once

#include <QVector3D>
#include <limits>

class Box3D
{
  public:
    Box3D() { makeEmpty(); }

    Box3D(const QVector3D& a_min, const QVector3D& a_max)
      : m_min(a_min)
      , m_max(a_max)
    {}

    void setBounds(const QVector3D& a_min, const QVector3D& a_max)
    {
        m_min = a_min;
        m_max = a_max;
    }

    bool isEmpty() const
    {
        return (m_max[0] < m_min[0] || m_max[1] < m_min[1] || m_max[2] < m_min[2]);
    }

    void makeEmpty()
    {
        m_min = QVector3D(std::numeric_limits<float>::max(),
                          std::numeric_limits<float>::max(),
                          std::numeric_limits<float>::max());
        m_max = QVector3D(-std::numeric_limits<float>::max(),
                          -std::numeric_limits<float>::max(),
                          -std::numeric_limits<float>::max());
    }

    const QVector3D& min() const { return m_min; }

    const QVector3D& max() const { return m_max; }

    QVector3D size() const { return m_max - m_min; }

    QVector3D center() const
    {
        return QVector3D(
          (m_max[0] + m_min[0]) * 0.5f, (m_max[1] + m_min[1]) * 0.5f, (m_max[2] + m_min[2]) * 0.5f);
    }

    void extendBy(const QVector3D& a_point)
    {
        if (isEmpty()) {
            setBounds(a_point, a_point);
        } else {
            if (a_point[0] < m_min[0])
                m_min[0] = a_point[0];
            if (a_point[1] < m_min[1])
                m_min[1] = a_point[1];
            if (a_point[2] < m_min[2])
                m_min[2] = a_point[2];

            if (a_point[0] > m_max[0])
                m_max[0] = a_point[0];
            if (a_point[1] > m_max[1])
                m_max[1] = a_point[1];
            if (a_point[2] > m_max[2])
                m_max[2] = a_point[2];
        }
    }

  private:
    QVector3D m_min, m_max;
};
