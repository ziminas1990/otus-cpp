//#include
#include <picasso/Shapes.h>

namespace picasso {

void Group::draw(ICanvas *pCanvas) const
{
  pCanvas->pushTransformation(m_Transformation);
  for (IObjectPtr const& pChild : m_Children)
    pChild->draw(pCanvas);
  pCanvas->popTransformation();
}

bool Group::hit(const Point& point) const
{
  Point transformedPoint = m_Transformation.transform(point);
  for (IObjectPtr const& pObject : m_Children)
    if (pObject->hit(transformedPoint))
      return true;
  return false;
}

IObjectConstPtr Group::getChild(size_t index) const
{
  return index < m_Children.size() ? m_Children[index] : nullptr;
}

IObjectPtr Group::getChild(size_t index)
{
  return
      std::const_pointer_cast<IObject>(
        const_cast<const Group*>(this)->getChild(index));
}

} // namespace picasso
