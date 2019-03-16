#pragma once

#include "ICanvas.h"

namespace picasso
{

/// \class CanvasOpenGL
/// \brief Implements displaying document via OpenGL
class CanvasOpenGL : public ICanvas
{
public:

  // overrides from ICanvas interface
  void draw(const Line *pLine) override;
  void draw(const Ellipse *pEllipse) override;
  void pushTransformation(const Transform &transform) override;
  void popTransformation() override;
};

} // namespace picasso
