//---------------------------------------------------------------------//
// PlaySideBar.h //
// Represents the sidebar that displays the next 5 shapes, timer, and bonus information//
//---------------------------------------------------------------------//

#pragma once
#include "Texture.h"
#include "Timer.h"

#include "Counter.h"
#include "TimerCountDown.h"

#include "InputManager.h"
#include "AudioManager.h"

#include "Shape.h"
#include "NextPieceGenerator.h"
#include "LevelProperties.h"

using namespace QuickSDL;

class PlaySideBar : public GameEntity
{
private:
    Shape *tmpShapes[5];
    Texture *mBackground;
    Texture *NextPieceHolders[5];

    InputManager *mInputMgr;
    AudioManager *mAudioMgr;

    static Counter *mScore;
    static Counter *mShapeToSkip;

    Timer *mTimer;
    Texture *mTimerLogo;
    static TimerCountDown *mTimerCountDown;

    Texture *mNextPieceLabel;

    NextPieceGenerator *mNextShape;

    LevelProperties *lvl;

public:
    static PlaySideBar *Instance();
    static void Release();

    Shape *getNextShape();

    int getRemainingTime() const;
    int getRemainingShapesToskip() const;

    void Update();
    void Render();

    void addBonuses(int score, int shapesToSkip, int addedTime);
    void InitializeVars(int time, int shapesToSkip, int rndShape, int rndColor);
    int getScore();

private:
    static PlaySideBar *sInstance;
    PlaySideBar();
    ~PlaySideBar();
};