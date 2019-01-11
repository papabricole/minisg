#include "group.h"

namespace msg {
NODE_SOURCE(Group)

Group::Group() {}
Group::~Group() {}
void
Group::addChild(Node* node)
{
    m_children.push_back(node);
}

void
Group::removeChild(Node* node)
{}

void
Group::removeAllChildren()
{
    m_children.clear();
}
}
