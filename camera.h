#pragma once

#include <QMatrix4x4>

#include <node.h>
#include <box3d.h>

namespace msg {

class Camera : public Node
{
  public:
    Camera();

    float nearDistance() const { return m_nearDistance; }
    float farDistance() const { return m_farDistance; }
    float fieldOfView() const { return m_fov; }
    float aspectRatio() const { return m_aspect; }
    float focalDistance() const { return m_focalDistance; }
    QVector3D position() const { return m_position; }
    QMatrix4x4 projectionMatrix() const { return m_proj; }
    QMatrix4x4 viewMatrix() const { return m_view; }

    void setFieldOfView(float fieldOfView);
    void setAspectRatio(float aspectRatio);
    void setPosition(const QVector3D& position);
    void setFocalDistance(float distance);

    void lookAt(const QVector3D& center, const QVector3D& up);
    void viewBoundingBox(const Box3D& bbox);

  private:
    float m_nearDistance, m_farDistance, m_fov, m_aspect, m_focalDistance;
    QVector3D m_position;
    QQuaternion m_rotation;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_view;
};
}
