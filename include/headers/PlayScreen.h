#pragma once
#include "Texture.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"

#include "Board.h"
#include "Menu.h"
#include "TextsAndResults.h"

#include "ScoreBoard.h"

using namespace QuickSDL;

class PlayScreen : public GameEntity
{
private:
    PlaySideBar *mSideBar;
    Timer *mTimer;

    InputManager *mInputMgr;
    AudioManager *mAudioMgr;

    Board *mBoard;
    Texture *mControls;

    bool mGameOver, mIsLevelMenu;
    TextsAndResults *mGameResultsText;

    LevelProperties *lvl;
    Menu *mLvlMenu, *mGamePausedMenu;
    float timeToGenerate = 0;

public:
    PlayScreen();
    ~PlayScreen();

    void Update();
    void Render();

private:
    void RestartGame();
};