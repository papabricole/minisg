/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QResource>
#include <cmath>

bool GLWidget::m_transparent = false;

QVector3D
sphereSheetProjector(const QVector2D& pos)
{
    QVector3D rayOrigin(pos.x() - 0.5f, 0.5f - pos.y(), -0.5f);
    const QVector3D rayDirection(0, 0, 1);
    const QVector3D sphereOrigin(0, 0, 0);
    const float sphereRadius = 0.35f;

    // ray / sphere intersection
    const QVector3D r_to_s = rayOrigin - sphereOrigin;

    // Compute A, B and C coefficients
    const float A = rayDirection.lengthSquared();
    const float B = 2.0f * QVector3D::dotProduct(r_to_s, rayDirection);
    const float C = r_to_s.lengthSquared() - sphereRadius * sphereRadius;

    // Find discriminant
    const float disc = B * B - 4.0 * A * C;

    // if discriminant is negative there are no real roots
    if (disc >= 0.0) {
        const float t0 = (-B + std::sqrt(disc)) / (2.0 * A);
        if (t0 > 0) {
            rayOrigin = rayOrigin + t0 * rayDirection;
        }
    }

    // intersection with the sheet
    const QVector3D planeHit =
      rayOrigin + rayDirection * rayOrigin.distanceToPlane(sphereOrigin, -rayDirection);

    // distance from plane hit point to plane center in the projector
    const float planarDist = (planeHit - sphereOrigin).length();

    // let sphere and hyperbolic sheet meet at 45°
    const float meetDist = sphereRadius * (float)std::cos(M_PI / 4.0);

    if (planarDist < meetDist)
        return rayOrigin;

    // By Pythagoras' we know that the value of the sphere at 45°
    // angle from the groundplane will be (radius^2 * 0.5).
    const float v = (sphereRadius * sphereRadius) * 0.5f;

    // A hyperbolic function is given by y = 1 / x, where x in our
    // case is the "radial" distance from the plane centerpoint to the
    // plane intersection point.
    const float hyperbval = (1.0f / planarDist) * v;

    return planeHit + QVector3D(0.0f, 0.0f, hyperbval);
}

GLWidget::GLWidget(QWidget* parent)
  : QOpenGLWidget(parent)
  , m_xRot(0)
  , m_yRot(0)
  , m_zRot(0)
  , m_program(0)
{
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }
    m_mesh.loadObj("female-usertest.obj");
}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize
GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize
GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void
qNormalizeAngle(int& angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void
GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_xRot) {
        m_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void
GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_yRot) {
        m_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void
GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_zRot) {
        m_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void
GLWidget::cleanup()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_meshVbo.destroy();
    delete m_program;
    m_program = 0;
    doneCurrent();
}

void
GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       (const char*)QResource(":/shaders/vert.glsl").data());
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       (const char*)QResource(":/shaders/frag.glsl").data());
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    m_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);

    // Setup our vertex buffer object.
    m_meshVbo.create();
    m_meshVbo.bind();
    m_meshVbo.allocate(m_mesh.constData(), m_mesh.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Light position is fixed.
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();

    viewAll();
}

void
GLWidget::setupVertexAttribs()
{
    m_meshVbo.bind();
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(
      1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    m_meshVbo.release();
}

void
GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // m_world.setToIdentity();
    // m_world.rotate(180.0f - (m_xRot / 16.0f), 1, 0, 0);
    // m_world.rotate(m_xRot / 16.0f, 1, 0, 0);
    // m_world.rotate(m_yRot / 16.0f, 0, 1, 0);
    // m_world.rotate(m_zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_camera.projectionMatrix());
    m_program->setUniformValue(m_mvMatrixLoc, m_camera.viewMatrix() * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    glDrawArrays(GL_TRIANGLES, 0, m_mesh.vertexCount());

    m_program->release();
}

void
GLWidget::resizeGL(int w, int h)
{
    m_camera.setAspectRatio(GLfloat(w) / h);
}

void
GLWidget::mousePressEvent(QMouseEvent* event)
{
    m_lastPos = event->pos();
    m_lastWorld = m_world;
}

void
GLWidget::mouseMoveEvent(QMouseEvent* event)
{
#if 0
    int dx = event->x() - m_lastPos.x();
    int dy = event->y() - m_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(m_xRot + 8 * dy);
        setYRotation(m_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(m_xRot + 8 * dy);
        setZRotation(m_zRot + 8 * dx);
    }
    m_lastPos = event->pos();
#else
    if (event->buttons() & Qt::LeftButton) {
        const QVector3D lstart = sphereSheetProjector(getNormalizedPosition(m_lastPos));
        const QVector3D lend = sphereSheetProjector(getNormalizedPosition(event->pos()));
        const QQuaternion rotation = QQuaternion::rotationTo(lstart, lend);

        m_world.setToIdentity();
        m_world.rotate(rotation);
        m_world *= m_lastWorld;
        update();
    }
#endif
}

void
GLWidget::viewAll()
{
    m_camera.viewBoundingBox(m_mesh.box());
}
