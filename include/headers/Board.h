
//--------------------------------------------------------------//
// Board.h //
// Represents the board where shapes are inserted //
// Balances the positions of the shapes //
// Responsible for removing similar shapes or colors //
//--------------------------------------------------------------//
#pragma once
#include "Texture.h"
#include "List.h"

#include "InputManager.h"
#include "AudioManager.h"

#include "LevelProperties.h"
#include "PlaySideBar.h"
using namespace QuickSDL;

class Board : public GameEntity
{

private:
    int NUMBER_OF_SUB_LISTS = 9;

    List *mMainList;

    InputManager *mInputMgr;
    AudioManager *mAudioMgr;
    Texture *mBackground;

    int mShapePosX[15], mStartPositionIndex = 7, mEndPositionIndex = 7;

    LevelProperties *lvl;

public:
public:
    Board();
    ~Board();

    void AddShape(Shape *, bool);

    void Update();
    void Render();
    int ShapesInserted();
    void clear();

private:
    void balancePositions();
    void checkInsertSimilars(ShapeNode *, ShapeNode *(List::*)(), ShapeNode *(ShapeNode::*)());
    void checkShiftSimilars();
    void ShiftColorsByMouse();
    void ShiftTypesByMouse();
};