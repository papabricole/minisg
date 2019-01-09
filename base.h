#pragma once

#include <refptr.h>

namespace msg {

class Base : public utils::refcounted
{
  public:
    Base();
};
}
