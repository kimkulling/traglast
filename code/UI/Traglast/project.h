#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QVector>

class QXmlStreamWriter;

struct Coordinate2D {
    double mX, mY;
};

struct Coordinate3D {
    double mX, mY, mZ;
};

template<class T>
struct TNode {
    T mNodeType;
};

enum class ElementType {
    Beam2D
};

using Node2D = TNode<Coordinate2D>;
using Node3D = TNode<Coordinate3D>;

struct Element2D {
    ElementType type;
    int mNode1;
    int mNode2;
};

class Project {
public:
    Project(const QString &name );
    ~Project();
    void setName( const QString &name );
    QString getName() const;
    bool isDirty() const;
    void addNodes( int numNodes, Node2D *nodes );
    void addElements( int numElements, Element2D *elements);
    bool load( const QString &filename );
    bool save( const QString &filename );

protected:
    void writeNode(QXmlStreamWriter &xmlWriter, const Node2D &node);
    void writeElement(QXmlStreamWriter &xmlWriter,const Element2D &element);

private:
    QString mName;
    bool mDirty;
    QVector<Node2D> mNodes;
    QVector<Element2D> mElements;
};

#endif // PROJECT_H
