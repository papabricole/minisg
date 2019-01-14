#pragma once

#include <nodes/node.h>

#include <vector>

namespace msg {

class Group : public Node
{
    NODE_HEADER(Group)
  public:
    Group();
    virtual ~Group() override;

    void addChild(const std::shared_ptr<Node>& node);
    void removeChild(const std::shared_ptr<Node>& node);
    void removeAllChildren();
    const NodeList& children() const { return m_children; }
};
}
