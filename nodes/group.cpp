#include "group.h"

namespace msg {
NODE_SOURCE(Group)

Group::Group() {}
Group::~Group() {}
void
Group::addChild(const std::shared_ptr<Node>& node)
{
    m_children.push_back(node);
}

void
Group::removeChild(const std::shared_ptr<Node>& node)
{}

void
Group::removeAllChildren()
{
    m_children.clear();
}
}
