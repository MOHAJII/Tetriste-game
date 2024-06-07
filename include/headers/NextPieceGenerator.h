
//---------------------------------------------------------------------//
// NextPieceGenerator.h //
// Generates the next 5 shapes //
//---------------------------------------------------------------------//

#pragma once
#include "DoublyLinkedList.h"
#include "Shape.h"
#include "Texture.h"

using namespace QuickSDL;
class NextPieceGenerator : public GameEntity
{
public:
    static int RANDOM_SHAPES_COUNT, RANDOM_COLORS_COUNT;

private:
    DoublyLinkedList<Shape> *mList;
    const int SHAPES_TO_RENDER = 5;

    Shape *tmp;
    int mSize = 10;
    Texture *mTargetPositions[5];

public:
    NextPieceGenerator(Texture *[]);
    ~NextPieceGenerator();
    Shape *getNextShape();
    void Update();
    void Render();

private:
    Shape *getRandomShape();
};