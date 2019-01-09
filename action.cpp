#include "action.h"
#include "node.h"
#include "group.h"

namespace msg {
Action::Action() {}

void
Action::apply(Node* root)
{
    root->accept(this);

    Group* group = dynamic_cast<Group*>(root);
    if (group) {
        for (Node* node : group->children()) {
            apply(node);
        }
    }
}
}
