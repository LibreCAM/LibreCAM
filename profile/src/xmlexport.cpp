#include "xmlexport.h"
#include <QMetaProperty>
#include <QObject>
#include <QStringList>

//start id=exportinstance
QString XMLExport::objectToXml(const QObject* doptr,
                               int indentlevel) {

    QStringList result;
    QString indentspace;

    indentspace.fill(' ', indentlevel*3);
    const QMetaObject* meta = doptr->metaObject();
    result += QString("\n%1<object class=\"%2\" name=\"%3\" >").
              arg(indentspace).
              arg(meta->className()).
              arg(doptr->objectName());

    for (int i= 0; i < meta->propertyCount(); ++i) { /* Iterate
             through each property. */
        QMetaProperty qmp = meta->property(i);
        const char* propname = qmp.name();
        if (strcmp(propname, "objectName")==0)
            continue;
        QVariant qv;
        if (qmp.isEnumType()) {
            QMetaEnum qme = qmp.enumerator();
            qv = qme.valueToKey(qv.toInt());
        } else {
            qv = doptr->property(propname);
        }

        result += QString (
                      "%1  <property name=\"%2\" type=\"%3\" value=\"%4\" />"
                  ).arg(indentspace).arg(propname).arg(qv.typeName())
                  .arg(variantToString(qv));
    }

    QObjectList childlist = doptr->findChildren<QObject*>(QString());
    foreach (QObject* objptr, childlist) { /* Iterate through
        the child list. */
        if (objptr->parent()==doptr) { /* findChildren also includes
grandchildren and great-great grandchildren, so we skip over those. */
            result += objectToXml(objptr, indentlevel+1); /* recursive
            call */
        }
    }
    result += QString("%1</object>\n").arg(indentspace);
    return result.join("\n");
}
//end
