#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <libxml++/libxml++.h>
#include <libxml++/attribute.h>
#include <QFile>

#include "Global.h"

class XMLParser : public QObject {
Q_OBJECT
public:
    explicit XMLParser(const QString &);
    void parseXML();
public slots:
    void writeValue(int, double);
private:
    bool loadXML(const QString &fileName);
    bool parsed;
    bool writable = true;
    void setFileContents();
    QFile *schemaFile;
    QFile *xmlFile;
    QString mName;
    QByteArray xmlFileContents;
    xmlpp::DomParser parser;
    std::vector<std::string> pathList;
signals:
    void setValue(int, double);
    void setValueFromPage(Global::ControlPage, double);
};

#endif //XMLPARSER_H
