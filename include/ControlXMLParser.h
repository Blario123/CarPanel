#ifndef CONTROLXMLPARSER_H
#define CONTROLXMLPARSER_H

#include <QObject>
#include <libxml++/libxml++.h>
#include <QFile>

class XMLParser : public QObject {
    Q_OBJECT
public:
    explicit XMLParser(const QString &);
private:
    bool parseXML(const QString &);
    void setFileContents();
    QFile *schemaFile;
    QFile *xmlFile;
    QString mName;
};

#endif //CONTROLXMLPARSER_H
