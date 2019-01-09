#include "renderaction.h"
#include "node.h"
#include "group.h"
#include "camera.h"

#include <iostream>

namespace msg {

RenderAction::RenderAction() {}

void
RenderAction::traverse(Node* node)
{
    node->render();
}
}
