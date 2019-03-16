#pragma once

#include <memory>
#include "Types.h"

namespace picasso
{

class IExporter;
class ICanvas;

class IObject;
using IObjectPtr      = std::shared_ptr<IObject>;
using IObjectConstPtr = std::shared_ptr<const IObject>;

class IObject
{
public:

  virtual ~IObject() {}

  virtual void exportTo(IExporter* pExporter) const = 0;

  virtual void draw(ICanvas* pCanvas) const = 0;

  /// Check, if click on (x, y) hits the object
  /// Usefull for selecting object
  virtual bool hit(Point const& point) const = 0;

  virtual size_t          getChildrenCount()         const { return 0; }
  virtual IObjectPtr      getChild(size_t /*index*/)       { return nullptr; }
  virtual IObjectConstPtr getChild(size_t /*index*/) const { return nullptr; }
};

} // namespace picasso
