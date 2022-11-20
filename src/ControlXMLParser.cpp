#include "ControlXMLParser.h"
#include <QtCore/QtCore>

XMLParser::XMLParser(const QString &name) : QObject(), mName(name + ":"), schemaFile(nullptr), xmlFile(nullptr) {
    if(parseXML("CarPanel.xml")) {
        qDebug().noquote() << mName << "Parsed successfully";
    } else {
        qDebug().noquote() << mName << "Could not parse successfully\nSetting contents to known prepared xml contents";
        setFileContents();
        qDebug().noquote() << mName << "Attempting to parse xml file again.";
        if(parseXML("CarPanel.xml")) {
            qDebug().noquote() << mName << "Parsed successfully on attempt 2.";
        }
    }
}

bool XMLParser::parseXML(const QString &fileName) {
    try {
        schemaFile = new QFile(":/resources/parser.xsd");
        schemaFile->open(QFile::ReadOnly);
        xmlpp::XsdSchema schema;
        schema.parse_memory(schemaFile->readAll().toStdString());
        xmlpp::XsdValidator validator(&schema, false);
        try {
            xmlFile = new QFile(fileName);
            xmlFile->open(QFile::ReadWrite);
            if(!xmlFile->isOpen()) {
                qDebug().noquote() << mName << "Could not open read-write.\nAttempting to open read-only.";
                xmlFile->open(QFile::ReadOnly);
            }
            QByteArray xmlFileContents = xmlFile->readAll();
            if(xmlFileContents.isEmpty()) {
                qDebug().noquote() << mName << "Contents empty";
                return false;
            }
            xmlpp::DomParser parser;
            parser.parse_memory(xmlFileContents.toStdString());
            parser.set_throw_messages();
            validator.validate(parser.get_document());
        } catch(const std::exception &e) {
            qDebug() << mName << "Exception:" << e.what();
            return false;
        }
    } catch (const std::exception &e) {
        qDebug() << mName << "Exception:" << e.what();
        return false;
    }
    return true;
}

void XMLParser::setFileContents() {
    QFile emptyXmlFile(":/resources/emptyCarPanel.xml");
    emptyXmlFile.open(QFile::ReadOnly);
    xmlFile->resize(0);
    xmlFile->write(emptyXmlFile.readAll());
    xmlFile->flush();
}
