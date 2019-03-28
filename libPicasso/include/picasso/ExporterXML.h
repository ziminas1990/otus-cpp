#pragma once

#include <string>

#include "IExporter.h"

namespace picasso {

/// \class ExporterXML
/// \brief Implements document export as XML-document
class ExporterXML : public IExporter
{
public:

  /// Flush all prefiously exported objects to XML-file **sPathToFIle**
  void storeExportedObjectsToFile(const std::string sPathToFIle) const;

  // overrides from IExporter interface
  void exportOne(const Line *pLine) override;
  void exportOne(const Ellipse *pEllipse) override;
  void exportOne(const Group *pGroup) override;
};

} // namespace picasso
