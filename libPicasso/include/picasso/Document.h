#pragma once

#include <vector>
#include "IExporter.h"
#include "IObject.h"

/// \mainpage
/// Welcome to libPicasso library!
/// ==============================
/// We are exited to provide a powerfull (no) library for you, that allows you simply add
/// flexible vector graphic engine to your C++ project!
///
/// Vector graphic has never been so easy before!

namespace picasso {

/// \class Document
/// \brief Contain all elements of document, allows to add and remove elements,
///        implements logic of selecting elements
class Document
{
public:
  class Iterator
  {
  public:
    IObjectPtr operator*();

    Iterator& operator++();
    Iterator& operator--();
  };

  void exportTo(IExporter* pExporter) const;

  Iterator begin();
  Iterator end();
  
  /// Adds new object \pObject to document
  /// \return iterator to insterted element
  Iterator insert(IObjectPtr pObject);

  /// Removes element from document
  /// \param it Iterator to element
  /// \return Pair of iterator to next element and boolean value, that shows
  /// if element was actualy removed (true) or not (false)
  std::pair<Iterator, bool> remove(Iterator it);

  /// Allows to select element by clicking on it
  /// \param point Click position
  /// \param lAppend If false, than other objects, that has been selected already,
  /// would be deselected
  void selectByClick(const Point& point, bool lAppend = false);

  /// \return All selected objects
  std::vector<Iterator> getSelectedObjects() const;

private:
  std::vector<IObjectPtr> m_Objects;
};

} // namespace picasso
