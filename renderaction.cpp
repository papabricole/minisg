#include "renderaction.h"
#include <nodes/node.h>
#include <nodes/group.h>
#include <nodes/transform.h>
#include <nodes/camera.h>
#include <nodes/mesh.h>

#include <elements/element.h>
#include <elements/cameraelement.h>
#include <elements/meshelement.h>

#include <iostream>

namespace msg {

class TransformHandler : public NodeHandler
{
  public:
    virtual void accept(const std::shared_ptr<Node>& node) override
    {
        std::cout << "transform handler " << this << " for " << node->className() << std::endl;
    }
};

RenderAction::RenderAction()
{
    std::cout << "num stack indices: " << Node::getNumStackIndices() << std::endl;

    setHandler<Transform>(std::make_shared<TransformHandler>());
}
}
