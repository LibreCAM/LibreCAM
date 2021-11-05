#ifndef CAMPROFILEDATAPARSER_H
#define CAMPROFILEDATAPARSER_H

#include <QList>
#include <QXmlDefaultHandler>

class CAMProfileData;
class CAMProfileDataModel;

class CAMProfileDataParser : public QXmlDefaultHandler
{
public:
    CAMProfileDataParser(CAMProfileDataModel *camProfileDataModel);
private:
    bool startDocument();
    bool endElement( const QString&, const QString&, const QString &name );
    bool startElement( const QString&, const QString&, const QString &name, const QXmlAttributes &attrs );

    bool inProfileData;
    CAMProfileDataModel *camProfileDataModel;
    CAMProfileData *newSet;
    bool characters(const QString &str);
    QString currentText;
};

#endif // CAMPROFILEDATAPARSER_H
