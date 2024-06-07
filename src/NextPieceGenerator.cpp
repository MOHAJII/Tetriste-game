#include "NextPieceGenerator.h"
#include <time.h>
int NextPieceGenerator::RANDOM_SHAPES_COUNT = 4;
int NextPieceGenerator::RANDOM_COLORS_COUNT = 4;

NextPieceGenerator::NextPieceGenerator(Texture *TargetPositions[])
{
    mList = new DoublyLinkedList<Shape>();

    for (int i = 0; i < SHAPES_TO_RENDER; ++i)
    {
        if (TargetPositions[i] != nullptr)
        {
            mTargetPositions[i] = TargetPositions[i];
            tmp = getRandomShape();
            tmp->Parent(TargetPositions[i]);
            tmp->Pos(VEC2_ZERO);
            if (i != 0)
                tmp->Scale(Vector2(0.48, 0.48));
            mList->insertBack(tmp);
        }
    }
}
NextPieceGenerator ::~NextPieceGenerator()
{
    delete tmp;
    tmp = nullptr;
    delete mList;
    mList = nullptr;
}

Shape *NextPieceGenerator::getNextShape()
{

    if (!mList->isEmpty())
    {
        return mList->removeFront()->getData();
    }

    return nullptr;
}

void NextPieceGenerator::Update()
{
    if (mList->getSize() < SHAPES_TO_RENDER)
    {
        for (int i = 0; i < SHAPES_TO_RENDER - 1; ++i)
        {
            tmp = mList->getFront(i);
            tmp->Parent(mTargetPositions[i]);
            tmp->Pos(VEC2_ZERO);
            if (i == 0)
                tmp->Scale(VEC2_ONE);
        }

        tmp = getRandomShape();
        tmp->Parent(mTargetPositions[4]);
        tmp->Pos(VEC2_ZERO);
        tmp->Scale(Vector2(0.48, 0.48));
        mList->insertBack(tmp);
    }
}
void NextPieceGenerator::Render()
{
    for (int i = 0; i < SHAPES_TO_RENDER; ++i)
    {
        if (mList->getFront(i) != nullptr)
            mList->getFront(i)->Render();
    }
}

Shape *NextPieceGenerator::getRandomShape()
{
    ShapeType randomShapeType = static_cast<ShapeType>(rand() % RANDOM_SHAPES_COUNT);
    ShapeColor randomShapeColor = static_cast<ShapeColor>(rand() % RANDOM_COLORS_COUNT);

    return new Shape(randomShapeType, randomShapeColor);
}