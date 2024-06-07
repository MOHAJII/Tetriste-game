#include "List.h"

void List::ShiftByShapeType(ShapeType type)
{
    if (!isEmpty())
    {
        ShapeNode *currentShapeNode = origin->getNext();
        ShapeNode *prevShapeNode = nullptr;

        do
        {
            currentShapeNode = currentShapeNode->getNext();
            if (currentShapeNode->getShape()->getShapeType() == type)
            {
                if (prevShapeNode != currentShapeNode && prevShapeNode != nullptr)
                    swap(prevShapeNode, currentShapeNode);
                prevShapeNode = currentShapeNode;
            }
        } while (currentShapeNode != origin->getNext());
    }
}

void List::ShiftByShapeColor(ShapeColor Color)
{
    if (!isEmpty())
    {
        ShapeNode *currentShapeNode = origin->getNext();
        ShapeNode *prevShapeNode = nullptr;

        do
        {
            currentShapeNode = currentShapeNode->getNext();
            if (currentShapeNode->getShape()->getShapeColor() == Color)
            {
                if (prevShapeNode != currentShapeNode && prevShapeNode != nullptr)
                    swap(prevShapeNode, currentShapeNode);

                prevShapeNode = currentShapeNode;
            }
        } while (currentShapeNode != origin->getNext());
    }
}

void List::swap(ShapeNode *shape, ShapeNode *nextshape)
{
    Shape *tmp = shape->getShape();
    shape->setShape(nextshape->getShape());
    nextshape->setShape(tmp);
}

List::List()
{
    origin = new ShapeNode();
    origin->setNext(origin);
    size = 0;
}

void List::insertFront(Shape *data)
{
    ShapeNode *newShapeNode = new ShapeNode(data);

    if (size == 0)
    {
        newShapeNode->setNext(newShapeNode);
        newShapeNode->setPrev(newShapeNode);
        origin->setNext(newShapeNode);
    }
    else
    {

        newShapeNode->setNext(origin->getNext());
        newShapeNode->setPrev(origin->getNext()->getPrev());
        origin->getNext()->getPrev()->setNext(newShapeNode);
        origin->getNext()->setPrev(newShapeNode);
        origin->setNext(newShapeNode);
    }
    origin->setPrev(newShapeNode);
    size++;
}

void List::insertBack(Shape *data)
{
    ShapeNode *newShapeNode = new ShapeNode(data);

    if (size == 0)
    {
        newShapeNode->setNext(newShapeNode);
        newShapeNode->setPrev(newShapeNode);
        origin->setNext(newShapeNode);
    }
    else
    {

        newShapeNode->setNext(origin->getNext());
        newShapeNode->setPrev(origin->getNext()->getPrev());
        origin->getNext()->getPrev()->setNext(newShapeNode);
        origin->getNext()->setPrev(newShapeNode);
    }
    origin->setPrev(newShapeNode);
    size++;
}

ShapeNode *List::removeFront()
{
    if (!isEmpty())
    {
        ShapeNode *tmp = origin->getNext();
        tmp->getNext()->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(tmp->getNext());
        origin->setNext(tmp->getNext());
        size--;
        return tmp;
    }
    return nullptr;
}

void List::removeFrontDel()
{
    if (!isEmpty())
    {
        ShapeNode *tmp = origin->getNext();
        tmp->getNext()->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(tmp->getNext());
        origin->setNext(tmp->getNext());
        size--;
        std::cout << "deleted is " << *tmp->getShape() << "next of deleted is " << *tmp->getNext()->getShape() << "prev of deleted is " << *tmp->getPrev()->getShape();
        delete tmp;
    }
}

ShapeNode *List::removeBack()
{
    if (!isEmpty())
    {
        ShapeNode *tmp = origin->getNext()->getPrev();
        tmp->getNext()->setPrev(tmp->getPrev());
        tmp->getPrev()->setNext(origin->getNext());
        size--;
        return tmp;
    }
    return nullptr;
}

ShapeNode *List::removeShapeNode(ShapeNode *currentShapeNode)
{

    currentShapeNode->getPrev()->setNext(currentShapeNode->getNext());
    currentShapeNode->getNext()->setPrev(currentShapeNode->getPrev());
    if (currentShapeNode == origin->getNext())
        origin->setNext(currentShapeNode->getNext());
    size--;
    return currentShapeNode;
}

bool List::isEmpty()
{
    return size == 0;
}

Shape *List::getFront(int i)
{
    int counter = 0;
    ShapeNode *currentShapeNode = origin->getNext();

    if (currentShapeNode->getNext() != nullptr)
    {
        while (currentShapeNode->getNext() != currentShapeNode && counter++ < i)
        {

            currentShapeNode = currentShapeNode->getNext();
        }
    }

    return currentShapeNode->getShape();
}

Shape *List::getBack(int i)
{
    int counter = 0;
    ShapeNode *currentShapeNode = origin->getNext();
    if (currentShapeNode->getPrev() != nullptr)
    {
        while (currentShapeNode->getPrev() != currentShapeNode && counter++ < i)
        {
            currentShapeNode = currentShapeNode->getPrev();
        }
    }
    return currentShapeNode->getShape();
}

ShapeNode *List::getOrigin() const { return origin; }
void List::setOrigin(ShapeNode *neworigin) { this->origin = neworigin; }

ShapeNode *List::getBackNode() const { return origin->getNext()->getPrev(); }
ShapeNode *List::getFrontNode() const { return origin->getNext(); }
ShapeNode *List::getLastInsertedNode() const { return origin->getPrev(); }

Shape *List::getBackShape() const { return origin->getNext()->getPrev()->getShape(); }
Shape *List::getFrontShape() const { return origin->getNext()->getShape(); }
Shape *List::getLastInsertedShape() const { return origin->getPrev()->getShape(); }

int List::getSize() const { return size; }

void List::display()
{
    if (!isEmpty())
    {
        std::cout << "size :" << this->getSize() << "\nMain Infos : {\n";

        ShapeNode *currentShapeNode = origin->getNext();
        int counter = 0;

        while (currentShapeNode->getNext() != currentShapeNode && counter++ < size)
        {
            std::cout << *currentShapeNode->getPrev()->getShape() << "<==" << *currentShapeNode->getShape() << "==>" << *currentShapeNode->getNext()->getShape()
                      << " }\n";
            currentShapeNode = currentShapeNode->getNext();
        }
    }
    else
    {
        std::cout << "Main List is empty" << std::endl;
    }
}

void List::clear()
{

    while (!isEmpty())
    {
        removeFront();
    }
}

List::~List()
{

    while (!isEmpty())
    {
        delete removeFront();
    }
    origin = nullptr;
}