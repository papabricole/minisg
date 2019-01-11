#pragma once

#include <memory>
#include <vector>
#include <iostream>

namespace msg {

class Node;

class NodeHandler
{
  public:
    virtual void accept(const std::shared_ptr<Node>& node) = 0;
};

class Action
{
  public:
    Action();

    void apply(const std::shared_ptr<Node>& node);

    template<typename T>
    void setHandler(const std::shared_ptr<NodeHandler>& handler)
    {
        std::cout << "addHandler for " << T::getClassName() << " " << T::getClassStackIndex()
                  << std::endl;
        m_handler[T::getClassStackIndex()] = handler;
    }

  protected:
    void traverse(const std::shared_ptr<Node>& node);

    std::vector<std::shared_ptr<NodeHandler>> m_handler;
};
}
