#include "action.h"
#include "node.h"
#include "group.h"

namespace msg {
Action::Action() {}
void
apply(Node* root)
{
    Group* group = dynamic_cast<Group*>(root);

    for (Node* node : group->children()) {
        // node->
    }
}
}
