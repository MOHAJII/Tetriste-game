//---------------------------------------------------------------------//
// List.h //
// Represents a doubly linked list specifically for shapes
// Responsible for insertion, deletion, and shifting mechanic
//---------------------------------------------------------------------//

#pragma once
#include "ShapeNode.h"
#include "NextPieceGenerator.h"
class List
{
protected:
    int size;
    ShapeNode *origin;

public:
    List();
    ~List();
    void ShiftByShapeType(ShapeType);
    void ShiftByShapeColor(ShapeColor);

    void insertFront(Shape *);
    void insertBack(Shape *);

    ShapeNode *removeFront();
    void removeFrontDel();

    ShapeNode *removeBack();
    ShapeNode *removeShapeNode(ShapeNode *);

    bool isEmpty();

    Shape *getFront(int);
    Shape *getBack(int);
    int getSize() const;

    ShapeNode *getOrigin() const;
    void setOrigin(ShapeNode *);

    ShapeNode *getFrontNode() const;
    ShapeNode *getBackNode() const;

    Shape *getBackShape() const;
    Shape *getFrontShape() const;

    ShapeNode *getLastInsertedNode() const;
    Shape *getLastInsertedShape() const;
    void clear();
    void display();

private:
    void swap(ShapeNode *, ShapeNode *);
};
