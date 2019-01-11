#include "renderaction.h"
#include "node.h"
#include "group.h"
#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "element.h"

#include "cameraelement.h"
#include "meshelement.h"

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
