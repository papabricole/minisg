#pragma once

namespace msg {

class Node;

class Action
{
  public:
    Action();

    void apply(Node* node);

  protected:
    void traversal(Node* node);

    virtual void before() {}
    virtual void traverse(Node* node) = 0;
    virtual void after() {}
};
}
