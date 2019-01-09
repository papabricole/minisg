#pragma once

#include <node.h>

#include <vector>

namespace msg {

class Group : public Node
{
  public:
    Group();

    void addChild(Node* node);
    void removeChild(Node* node);

    const std::vector<Node*>& children() const { return m_children; }

  protected:
    virtual ~Group();

    std::vector<Node*> m_children;
};
}
