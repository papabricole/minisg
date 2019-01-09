#include "action.h"
#include "node.h"
#include "group.h"

namespace msg {
Action::Action() {}

void
Action::apply(Node* node)
{
    traverse(node);

    Group* group = dynamic_cast<Group*>(node);
    if (group) {
        for (Node* child : group->children()) {
            apply(child);
        }
    }
}
}
