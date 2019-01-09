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

    virtual void visit(Node* node);
    virtual void visit(Group* node);
    virtual void visit(Camera* node);
};
}
