#pragma once

namespace msg {

class Node;
class Group;
class Camera;

class Action
{
  public:
    Action();

    void apply(Node* root);

    virtual void visit(Node* node) = 0;
    virtual void visit(Group* node) = 0;
    virtual void visit(Camera* node) = 0;
};
}
