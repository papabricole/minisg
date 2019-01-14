#include <nodes/camera.h>

#include <cmath>

#include <QtMath>

namespace msg {

NODE_SOURCE(Camera)

Camera::Camera()
  : m_nearDistance(0.01f)
  , m_farDistance(100.f)
  , m_fov(45.f)
  , m_aspect(1.f)
  , m_position(0.f, 0.f, 1.f)
{
    m_proj.setToIdentity();
    m_proj.perspective(m_fov, m_aspect, m_nearDistance, m_farDistance);
}

void
Camera::setFieldOfView(float fieldOfView)
{
    m_fov = fieldOfView;

    m_proj.setToIdentity();
    m_proj.perspective(m_fov, m_aspect, m_nearDistance, m_farDistance);
}

void
Camera::setAspectRatio(float aspectRatio)
{
    m_aspect = aspectRatio;

    m_proj.setToIdentity();
    m_proj.perspective(m_fov, m_aspect, m_nearDistance, m_farDistance);
}

void
Camera::setFocalDistance(float distance)
{
    m_focalDistance = distance;
}

void
Camera::setPosition(const QVector3D& position)
{
    m_position = position;
}

void
Camera::lookAt(const QVector3D& center, const QVector3D& up)
{
    m_view.setToIdentity();
    m_view.lookAt(m_position, center, up);
}

void
Camera::viewBoundingBox(const Box3D& bbox)
{
    // bounding sphere radius
    const float radius = (bbox.max() - bbox.center()).length();

    // Find the distance necessary to fit the object completely in the
    // window.  We don't need any slack, because the bounding sphere
    // is already bigger than the bounding box.
    m_focalDistance = radius / std::sin(qDegreesToRadians(m_fov * 0.5f));
    m_nearDistance = m_focalDistance - radius;
    m_farDistance = m_focalDistance + radius;

    m_position = bbox.center() + m_rotation * QVector3D(0, 0, m_focalDistance);

    m_view.setToIdentity();
    m_view.lookAt(m_position, bbox.center(), QVector3D(0, 1, 0));
}
}
