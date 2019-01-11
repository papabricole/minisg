#pragma once

#include <QMatrix4x4>

#include <node.h>

namespace msg {

class Transform : public Node
{
    NODE_HEADER(Transform)
  public:
    Transform();

    QMatrix4x4 matrix;
};
}
