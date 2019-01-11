#pragma once

namespace msg {

class Node;
class Group;
class Transform;
class Camera;
class Mesh;

class Action
{
  public:
    Action();

    void apply(Node* node);

    virtual void before() {}
    virtual void visit(Node* node) = 0;
    virtual void visit(Group* node) = 0;
    virtual void visit(Transform* node) = 0;
    virtual void visit(Camera* node) = 0;
    virtual void visit(Mesh* node) = 0;
    virtual void after() {}

  protected:
    void traverse(Node* node);
};
}
