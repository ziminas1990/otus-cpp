#pragma once

#include <vector>
#include "IObject.h"
#include "Types.h"

#include "IExporter.h"
#include "ICanvas.h"

namespace picasso
{

/// \class Line
/// \brief Describes a line on surface
class Line : public IObject
{
public:
  Line();
  Line(Point begin, Point end);

  // overrides from IObject
  void exportTo(IExporter* pExporter) const override { pExporter->exportOne(this); }
  void draw(ICanvas* pCanvas)         const override { pCanvas->draw(this); }
  bool hit(const Point& point)        const override;

private:
  Point m_Begin;
  Point m_End;
  Color m_Color;
};


/// \class Ellipse
/// \brief Describes an ellipse on surface
class Ellipse : public IObject
{
public:
  Ellipse();
  Ellipse(Point center, double rx, double ry);

  // overrides from IObject
  void exportTo(IExporter* pExporter) const override { pExporter->exportOne(this); }
  void draw(ICanvas* pCanvas)         const override { pCanvas->draw(this); }
  bool hit(const Point& point)        const override;

private:
  Point  m_Center;
  double m_Rx;
  double m_Ry;
  Color m_FillColor;
  Color m_BorderColor;
};


/// \class Group
/// \brief This class allows to group several elements (lines, ellipses or other Groups)
///        in order to select them with "one click" and apply transformations on them
class Group : public IObject
{
public:
  Group();
  Group(std::vector<IObjectPtr>&& children);

  void appendChild(IObjectPtr child);
  void appendChildren(std::vector<IObjectPtr>&& children);

  void      setTransformation(Transform const& transform);
  Transform getTransformation() const;

  // overrides from IObject interface
  void exportTo(IExporter* pExporter) const override { pExporter->exportOne(this); }
  void draw(ICanvas* pCanvas)         const override;
  bool hit(const Point& point)        const override;

  // overrides from IObject
  size_t          getChildrenCount()     const override { return m_Children.size(); }
  IObjectConstPtr getChild(size_t index) const override;
  IObjectPtr      getChild(size_t index) override;

private:
  std::vector<IObjectPtr> m_Children;
  Transform               m_Transformation;
};

} // namespace picasso
