#include "group.h"

namespace msg {
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
}
