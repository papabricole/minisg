#pragma once

namespace msg {

class Node;

class Action
{
  public:
    Action();

    void apply(Node* node);

  protected:
    virtual void traverse(Node* node) = 0;
};
}
