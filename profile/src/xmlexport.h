#ifndef XMLEXPORT_H
#define XMLEXPORT_H
#include <QString>
#include <QVariant>

class QObject;

/**
   This version does not perform any file i/o -
   just converts a QObject with properties
   into an XML string representation.

   @Deprecated - known Issues: This class is not meant to be used in conjunction
   with the DataObjects library.
*/
//start
class XMLExport {
 public:
    virtual ~XMLExport() {}
    virtual QString objectToXml(const QObject* ptr,
                                int indentlevel=0);

    static inline QString variantToString( const QVariant &variant )
    {
      if ( variant.type() == QVariant::String )
        return variant.toString();
      else if ( variant.type() == QVariant::ByteArray )
        return QString::fromUtf8( variant.toByteArray() );
      else {
        qWarning( "Unable to convert variant of type %s to QString", variant.typeName() );
        Q_ASSERT( false );
        return QString();
      }
    }

};
//end
#endif

