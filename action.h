#pragma once

#include <refptr.h>

#include <vector>
#include <iostream>

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
    void setHandler(NodeHandler* handler)
    {
        std::cout << "addHandler for " << T::getClassName() << " " << T::getClassStackIndex()
                  << std::endl;
        m_handler[T::getClassStackIndex()] = handler;
    }

  protected:
    void traverse(Node* node);

    std::vector<utils::refptr<NodeHandler>> m_handler;
};
}
