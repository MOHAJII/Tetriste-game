//---------------------------------------------------------------------//
// ScreenManager.h //
// Manages the screens and transitions between them
//---------------------------------------------------------------------//

#pragma once
#include "mainMenu.h"
#include "PlayScreen.h"
#include "ScoreBoard.h"

#include "AudioManager.h"

class ScreenManager
{
private:
    enum Screens
    {
        Menu,
        Play,
        Score,
        Rules,
        Control,

    };
    static ScreenManager *sInstance;
    InputManager *mInputMgr;
    MainMenu *mMainMenu;
    PlayScreen *mPlayScreen;
    ScoreBoard *mScoreBoard;
    Screens mCurrentScreen = Menu;
    AudioManager *mAudioMgr;

public:
    static ScreenManager *Instance();
    static void Release();

    void Update();
    void Render();

private:
    ScreenManager();
    ~ScreenManager();
};