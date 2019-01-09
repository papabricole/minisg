#pragma once

#include <action.h>

class Node;
class Group;
class Camera;

namespace msg {

class RenderAction : public Action
{
  public:
    RenderAction();

  protected:
    virtual void traverse(Node* node) override;
};
}
