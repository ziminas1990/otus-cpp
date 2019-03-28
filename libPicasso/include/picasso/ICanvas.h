#pragma once

#include "Types.h"

namespace picasso
{

class Line;
class Ellipse;

/// \class ICanvas
/// \brief Interface, insipred by "visitor" pattern, that allows different elements
///        to be displayed in some way (OpenGL, Qt and that sort of stuff)
class ICanvas
{
public:
  virtual ~ICanvas() {}

  virtual void draw(const Line* pLine) = 0;
  virtual void draw(const Ellipse* pEllipse) = 0;

  virtual void pushTransformation(const Transform& transform) = 0;
  virtual void popTransformation() = 0;

};

} // namespace picasso
