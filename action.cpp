#include "action.h"
#include "node.h"
#include "group.h"

namespace msg {

Action::Action()
{
    m_handler.resize(Node::getNumStackIndices(), nullptr);
}

void
Action::apply(Node* node)
{
    traverse(node);
}

void
Action::traverse(Node* node)
{
    NodeHandler* hdl = m_handler[node->classStackIndex()];

    if (hdl)
        hdl->accept(node);

    Group* group = dynamic_cast<Group*>(node);
    if (group) {
        for (Node* child : group->children()) {
            traverse(child);
        }
    }
}
}
