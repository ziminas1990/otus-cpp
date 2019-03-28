#pragma once

#include <string>
#include "Document.h"

namespace picasso {

/// \class ImporterXML
/// \brief Implements reading document from XML-file, that has been generated
///        by ExporterXML object
class ImporterXML
{
public:
  static Document Read(const std::string& sPathToXmlFile);
};

} // namespace picasso
