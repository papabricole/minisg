#pragma once

#include <node.h>

#include <vector>

namespace msg {

using NodeList = std::vector<utils::refptr<Node>>;

class Group : public Node
{
    NODE_HEADER(Group)
  public:
    Group();

    void addChild(Node* node);
    void removeChild(Node* node);
    void removeAllChildren();
    const NodeList& children() const { return m_children; }

  protected:
    virtual ~Group() override;

    NodeList m_children;
};
}
