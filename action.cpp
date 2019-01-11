#include "action.h"
#include "node.h"
#include "group.h"

namespace msg {
Action::Action() {}

void
Action::apply(Node* node)
{
    before();
    traverse(node);
    after();
}

void
Action::traverse(Node* node)
{
    node->accept(this);

    Group* group = dynamic_cast<Group*>(node);
    if (group) {
        for (Node* child : group->children()) {
            traverse(child);
        }
    }
}
}
