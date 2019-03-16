#include <picasso/Document.h>
#include <picasso/IExporter.h>

namespace picasso
{

void Document::exportTo(IExporter *pExporter) const
{
  for (IObjectPtr const& pObject : m_Objects) {
    pObject->exportTo(pExporter);
  }
}



} // namespace picasso
