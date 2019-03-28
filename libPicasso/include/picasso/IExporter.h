#pragma once

namespace picasso
{

class Line;
class Ellipse;
class Group;

/// \class IExporter
/// \brief Interface, inspiried by "visitor" pattern, that allows to store elements
///        of document in different ways
class IExporter
{
public:
  virtual ~IExporter() {}

  virtual void exportOne(const Line* pLine) = 0;
  virtual void exportOne(const Ellipse* pEllipse) = 0;
  virtual void exportOne(const Group* pGroup) = 0;

};

} // namespace picasso
