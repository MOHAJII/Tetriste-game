#include "Board.h"

Board::Board()
{
    lvl = LevelProperties::Instance();
    mInputMgr = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();

    mBackground = new Texture("Board.png");
    mBackground->Parent(this);
    mBackground->Pos(VEC2_ZERO);
    mMainList = new List();

    for (int i = -7; i <= 7; ++i)
    {
        mShapePosX[i + 7] = i * Graphics::Instance()->GRID_BOX;
    }
}

Board::~Board()
{
    delete mBackground;
    mBackground = nullptr;

    delete mMainList;
    mMainList = nullptr;
    mInputMgr = nullptr;
    mAudioMgr = nullptr;
    lvl = nullptr;
}

void Board::AddShape(Shape *shape, bool isRight)
{

    mAudioMgr->PlaySFX("shapeInserted.wav", 0, shapeInsertedChannel);

    shape->Parent(mBackground);
    if (isRight)
        shape->Pos(Vector2(mShapePosX[mEndPositionIndex], 0.0f));
    else
        shape->Pos(Vector2(mShapePosX[mStartPositionIndex], 0.0f));

    shape->Scale(Vector2(0.45, 0.45));

    if (isRight)
    {
        mMainList->insertBack(shape);
        // check for the left and right side to see if there are 3 shapes having the same color or form
        checkInsertSimilars(mMainList->getLastInsertedNode(), &List::removeBack, &ShapeNode::getPrev);
    }
    else
    {
        mMainList->insertFront(shape);
        // check for the left and right side to see if there are 3 shapes having the same color or form if so remove the 3
        checkInsertSimilars(mMainList->getLastInsertedNode(), &List::removeFront, &ShapeNode::getNext);
    }

    //  Call the function to center the shapes within th board
    balancePositions();
}

void Board::checkInsertSimilars(ShapeNode *lastInsertedNode, ShapeNode *(List::*remove)(), ShapeNode *(ShapeNode::*nextOrPrev)())
{
    if (mMainList->getSize() > 2)
    {
        int similarShapes = 1, similarColors = 1;

        for (int i = 0; i < 2; ++i)
        {
            if (lastInsertedNode->getShape()->getShapeType() == (lastInsertedNode->*nextOrPrev)()->getShape()->getShapeType())
                similarShapes++;
            if (lastInsertedNode->getShape()->getShapeColor() == (lastInsertedNode->*nextOrPrev)()->getShape()->getShapeColor())
                similarColors++;

            lastInsertedNode = (lastInsertedNode->*nextOrPrev)();
        }

        if (similarColors >= 3 || similarShapes >= 3)
        {
            for (int i = 0; i < 3; i++)
            {
                (mMainList->*remove)();
            }
            mAudioMgr->PlaySFX("shapeRemoved.wav", 0, shapeRemovedChannel);
            PlaySideBar::Instance()->addBonuses(lvl->getInsertRemoveScore() * 3, lvl->getInsertRemoveShapesToSkipBonus(), lvl->getInsertRemoveTimeBonus());
        }
    }
}

void Board::checkShiftSimilars()
{
    int size = mMainList->getSize();
    if (mMainList->getSize() > 2)
    {
        int similarShapes = 1, similarColors = 1;
        ShapeNode *shapeHeader = mMainList->getFrontNode();
        ShapeNode *colorHeader = mMainList->getFrontNode();

        ShapeNode *currentNode = mMainList->getFrontNode();
        for (int i = 0; i < size; i++)
        {
            if (similarShapes == 1)
                shapeHeader = currentNode;
            if (similarColors == 1)
                colorHeader = currentNode;
            if (currentNode->getShape()->getShapeType() == currentNode->getNext()->getShape()->getShapeType() && i < size - 1)
                similarShapes++;
            else
            {
                if (similarShapes >= 3)
                {
                    ShapeNode *tmp;
                    do
                    {
                        tmp = shapeHeader;
                        mMainList->removeShapeNode(tmp);
                        shapeHeader = shapeHeader->getNext();
                    } while (shapeHeader != currentNode->getNext());
                    similarColors = 1;
                    mAudioMgr->PlaySFX("shapeRemoved.wav", 0, shapeRemovedChannel);
                    PlaySideBar::Instance()->addBonuses(lvl->getShiftRemoveScore() * similarShapes, lvl->getShiftShapesToSkipBonus(), lvl->getShiftTimeBonus());
                }
                similarShapes = 1;
            }
            if (currentNode->getShape()->getShapeColor() == currentNode->getNext()->getShape()->getShapeColor() && i < size - 1)
                similarColors++;
            else
            {
                if (similarColors >= 3)
                {
                    ShapeNode *tmp;
                    do
                    {
                        tmp = colorHeader;

                        mMainList->removeShapeNode(tmp);
                        colorHeader = colorHeader->getNext();
                    } while (colorHeader != currentNode->getNext());
                    similarShapes = 1;
                    mAudioMgr->PlaySFX("shapeRemoved.wav", 0, shapeRemovedChannel);
                    PlaySideBar::Instance()->addBonuses(lvl->getShiftRemoveScore() * similarColors, lvl->getShiftShapesToSkipBonus(), lvl->getShiftTimeBonus());
                }
                similarColors = 1;
            }
            currentNode = currentNode->getNext();
        }
    }
}

void Board::balancePositions()
{
    int startIndex, lastIndex, arraySize = mMainList->getSize();

    if (arraySize > 0)
    {
        lastIndex = (int)(arraySize / 2);
        startIndex = lastIndex - arraySize + 1;
        mStartPositionIndex = startIndex - 1;
        mEndPositionIndex = lastIndex + 1;
        for (int i = 0; i < arraySize; i++)
        {
            mMainList->getFront(i)->Pos(Vector2((startIndex + i) * Graphics::Instance()->GRID_BOX, 0.0f));
        }
    }
}

int Board::ShapesInserted()
{
    return mMainList->getSize();
}

void Board::clear()
{
    mMainList->clear();
}

bool hasIntersectionWithMouse(Vector2 mousePos, Shape *object)
{
    int mouseX = mousePos.x;
    int mouseY = mousePos.y;

    int objectCenterX = object->Pos().x;
    int objectCenterY = object->Pos().y;
    int objectLeftX = objectCenterX - 48 / 2;
    int objectRightX = objectCenterX + 48 / 2;
    int objectTopY = objectCenterY - 48 / 2;
    int objectBottomY = objectCenterY + 48 / 2;
    if (mouseX >= objectLeftX && mouseX <= objectRightX && mouseY <= objectBottomY && mouseY >= objectTopY)
        return true;
    else
        return false;
}
void Board::ShiftTypesByMouse()
{
    ShapeNode *currentNode = mMainList->getFrontNode();
    for (int i = 0; i < mMainList->getSize(); i++)
    {
        if (hasIntersectionWithMouse(mInputMgr->MousePos(), currentNode->getShape()))
        {
            mMainList->ShiftByShapeType(currentNode->getShape()->getShapeType());
            break;
        }
        currentNode = currentNode->getNext();
    }
    checkShiftSimilars();
}
void Board::ShiftColorsByMouse()
{
    ShapeNode *currentNode = mMainList->getFrontNode();

    for (int i = 0; i < mMainList->getSize(); i++)
    {
        if (hasIntersectionWithMouse(mInputMgr->MousePos(), currentNode->getShape()))
        {
            mMainList->ShiftByShapeColor(currentNode->getShape()->getShapeColor());
            break;
        }
        currentNode = currentNode->getNext();
    }
    checkShiftSimilars();
}
void Board::Update()
{
    if (mInputMgr->MouseButtonReleased(left) && mInputMgr->KeyDown(SDL_SCANCODE_W))
    {
        ShiftTypesByMouse();
        balancePositions();
    }
    if (mInputMgr->MouseButtonReleased(left) && mInputMgr->KeyDown(SDL_SCANCODE_S))
    {
        ShiftColorsByMouse();
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_1))
    {
        mMainList->ShiftByShapeColor(RED);
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_2))
    {
        mMainList->ShiftByShapeColor(PURPLE);
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_3))
    {
        mMainList->ShiftByShapeType(SQUARE);
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_4))
    {
        mMainList->ShiftByShapeType(CERCLE);
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_5))
    {
        mMainList->display();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_6))
    {
        mAudioMgr->PlaySFX("shapeRemoved.wav", 0, 1);
        mMainList->removeFrontDel();
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_7))
    {
        mAudioMgr->PlaySFX("shapeRemoved.wav", 0, 1);
        mMainList->removeBack();
        balancePositions();
    }
    if (mInputMgr->KeyPressed(SDL_SCANCODE_8))
    {
        checkShiftSimilars();
        balancePositions();
    }
}

void Board::Render()
{
    mBackground->Render();
    for (int i = 0; i < mMainList->getSize(); ++i)
    {
        mMainList->getBack(i)->Render();
    }
}