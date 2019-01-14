#include "action.h"
#include <nodes/node.h>
#include <nodes/group.h>

namespace msg {

Action::Action()
{
    m_handler.resize(Node::getNumStackIndices(), nullptr);
}

void
Action::apply(const std::shared_ptr<Node>& node)
{
    traverse(node);
}

void
Action::traverse(const std::shared_ptr<Node>& node)
{
    std::shared_ptr<NodeHandler> hdl = m_handler[node->classStackIndex()];

    if (hdl)
        hdl->accept(node);

    for (std::shared_ptr<Node>& child : node->m_children) {
        traverse(child);
    }
}
}
