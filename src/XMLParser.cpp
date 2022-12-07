#include "XMLParser.h"
#include <QtCore/QtCore>

XMLParser::XMLParser(const QString &name) : QObject(),
                                            mName(name + ":"),
                                            schemaFile(nullptr),
                                            xmlFile(nullptr),
                                            parsed(false),
                                            xmlFileContents("") {
}

void XMLParser::parseXML() {
    if(loadXML("CarPanel.xml")) {
        qDebug().noquote() << mName << "Parsed successfully";
        parsed = true;
    } else {
        qDebug().noquote() << mName << "Could not parse successfully\n" << mName << "Setting contents to known prepared xml contents";
        setFileContents();
        qDebug().noquote() << mName << "Attempting to parse xml file again.";
        if(loadXML("CarPanel.xml")) {
            qDebug().noquote() << mName << "Parsed successfully";
            parsed = true;
        }
    }
    if(parsed) {
        int value = 0;
        std::list<xmlpp::Node*> nodeList = parser.get_document()->get_root_node()->get_children();
        for(auto i: nodeList) {
            if(i->get_name() != "text") {
                value++;
                std::list<xmlpp::Node *> nodeList2 = i->get_children();
                for(auto j: nodeList2) {
                    if(j->get_name() != "text") {
                        emit setValue(Global::ControlPage(value), j->eval_to_number(j->get_path()));
                    }
                }
            }
        }
    }
}

bool XMLParser::loadXML(const QString &fileName) {
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
                writable = false;
            }
            xmlFileContents = xmlFile->readAll();
            if(xmlFileContents.isEmpty()) {
                qDebug().noquote() << mName << "Contents empty";
                return false;
            }
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
