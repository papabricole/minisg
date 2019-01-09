#pragma once

#include <refptr.h>
#include <action.h>
#include <string>

namespace msg {

class Base : public utils::refcounted
{
  public:
    Base();

    virtual std::string className() const = 0;
    virtual void accept(Action* action) = 0;
};
}
