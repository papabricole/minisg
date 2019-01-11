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
    virtual void visit(Node* node) override;
    virtual void visit(Group* node) override;
    virtual void visit(Transform* node) override;
    virtual void visit(Camera* node) override;
    virtual void visit(Mesh* node) override;
};
}
