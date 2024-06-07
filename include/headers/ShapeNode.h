
//---------------------------------------------------------------------//
// ShapeNode.h //
// Represents a node containing a shape in a the list
//---------------------------------------------------------------------//

#pragma once

#include <iostream>
#include "Shape.h"
class ShapeNode
{
private:
    Shape *mShape;

    ShapeNode *next;
    ShapeNode *prev;

public:
    ShapeNode();
    ShapeNode(Shape *mShape);
    ~ShapeNode();

    ShapeNode *getNext();
    void setNext(ShapeNode *next);
    ShapeNode *getPrev();
    void setPrev(ShapeNode *prev);

    Shape *getShape();
    void setShape(Shape *mShape);

    bool operator!=(const ShapeNode &shapeNode) const
    {
        return this->mShape == shapeNode.mShape;
    }
};
