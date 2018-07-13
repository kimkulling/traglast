#include "project.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

Project::Project(const QString &name )
: mName(name)
, mDirty( true )
, mNodes()
, mElements() {
    // empty
}

Project::~Project() {
    // empty
}

void Project::setName( const QString &name ) {
    if ( mName != name ) {
        mName = name;
        mDirty = true;
    }
}

QString Project::getName() const {
    return mName;
}

bool Project::isDirty() const {
    return mDirty;
}

void Project::addNodes( int numNodes, Node2D *nodes ) {
    if ( 0 == numNodes || nullptr == nodes ) {
        return;
    }

    mNodes.reserve( numNodes + mNodes.size() );
    for ( size_t i=0; i<numNodes; ++i ) {
        mNodes.push_back( nodes[ i ] );
    }
    mDirty = true;
}

void Project::addElements( int numElements, Element2D *elements) {
    if ( 0 == numElements  || nullptr == elements ) {
        return;
    }

    mElements.reserve( numElements + mElements.size() );
    for ( int i=0; i<static_cast<int>(numElements); ++i ) {
        mElements.push_back(elements[ i ] );
    }
}

static const QString ProjectElement_Token = "Project";
static const QString NodesElement_Token = "Nodes";
static const QString NodeElement_Token = "Node";
static const QString ElementsElement_Token = "Elements";
static const QString ElementElement_Token = "Element";
static const QString ElementNode1Attribute_Token = "Node1";
static const QString ElementNode2Attribute_Token = "Node2";
static const QString ElementTypeAttribute_Token = "TYpe";

bool Project::load( const QString &filename ) {
    if ( filename.isEmpty() ) {
        return false;
    }

    QFile file( filename );
    if ( !file.open(QIODevice::ReadOnly) ) {
        return false;
    }

    QXmlStreamReader xmlReader( &file );
    while ( !xmlReader.atEnd() ) {
        if ( xmlReader.isStartElement()) {
            QString value = xmlReader.readElementText();
            if ( value == "") {

            }
        }
    }

    return true;
}

bool Project::save( const QString &filename ) {
    if ( filename.isEmpty() ) {
        return false;
    }

    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(ProjectElement_Token);
    xmlWriter.writeStartElement(NodesElement_Token);
    for ( int i=0; i<mNodes.size(); ++i ) {
        writeNode( xmlWriter, mNodes[ i ] );
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement(ElementsElement_Token);
    for ( int i=0; i<mElements.size(); ++i ) {
        writeElement(xmlWriter, mElements[ i ] );
    }
    xmlWriter.writeEndElement();

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();

    return true;
}

void Project::writeNode(QXmlStreamWriter &xmlWriter, const Node2D &node) {
    xmlWriter.writeStartElement(NodeElement_Token);
    QString coordStr;
    coordStr += node.mNodeType.mX;
    coordStr += ", ";
    coordStr += node.mNodeType.mY;
    xmlWriter.writeCDATA(coordStr);
    xmlWriter.writeEndElement();
}

void Project::writeElement(QXmlStreamWriter &xmlWriter, const Element2D &element) {
    xmlWriter.writeStartElement(ElementElement_Token);
    QString type( static_cast<int>(element.type )), node1( element.mNode1), node2( element.mNode2 );
    xmlWriter.writeAttribute(ElementNode1Attribute_Token, type);
    xmlWriter.writeAttribute(ElementNode1Attribute_Token, node1);
    xmlWriter.writeAttribute(ElementNode2Attribute_Token, node2);
    xmlWriter.writeEndElement();
}
