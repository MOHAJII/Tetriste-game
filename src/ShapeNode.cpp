

#include "ShapeNode.h"

ShapeNode::ShapeNode() : mShape(nullptr), next(nullptr), prev(nullptr) {}

ShapeNode::ShapeNode(Shape *mShape) : mShape(mShape), next(nullptr), prev(nullptr) {}

void ShapeNode::setNext(ShapeNode *next)
{
    this->next = next;
}

ShapeNode *ShapeNode::getNext()
{
    return next;
}

void ShapeNode::setPrev(ShapeNode *prev)
{
    this->prev = prev;
}

ShapeNode *ShapeNode::getPrev()
{
    return prev;
}

void ShapeNode::setShape(Shape *mShape)
{
    this->mShape = mShape;
}

Shape *ShapeNode::getShape()
{
    return mShape;
}

ShapeNode::~ShapeNode()
{

    delete mShape;
    mShape = nullptr;

    delete next;
    next = nullptr;

    delete prev;
    prev = nullptr;
}
