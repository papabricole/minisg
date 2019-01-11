#pragma once

#include <vector>

namespace msg {

class Node;

class NodeHandler
{
  public:
    virtual void accept(Node* node) = 0;
};

class Action
{
  public:
    Action();

    void apply(Node* node);

    template<typename T>
    void addHandler(NodeHandler* handler)
    {
        m_handler[T::getClassStackIndex()] = handler;
    }

  protected:
    void traverse(Node* node);

    std::vector<msg::NodeHandler*> m_handler;
};
}
