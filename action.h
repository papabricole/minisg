#pragma once

#include <refptr.h>

#include <vector>

namespace msg {

class Node;

class NodeHandler : public utils::refcounted
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

    std::vector<utils::refptr<NodeHandler>> m_handler;
};
}
