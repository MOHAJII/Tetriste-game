
//---------------------------------------------------------------------//
// MainMenu.h //
// Represents the screen of the main menu where players can start, view scores, or quit//
//---------------------------------------------------------------------//
#pragma once

#include "Texture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Menu.h"

using namespace QuickSDL;

enum TitleIndexes
{
    StartIndex,
    ScoresIndex,
    QuitIndex
};
class MainMenu : public GameEntity
{
private:


    // Handling inputs
    InputManager *mInputMgr;

    // Handling audio
    AudioManager *mAudioMgr;

    // Specifies the selected modes
    // int mSelectedmode = 0;

    Menu *mMainMenu;

public:
    MainMenu();
    ~MainMenu();
    void Update();
    void Render();
    // void changeSelecedMode(int);
    int getSelectedMode();

private:
    bool HandleInputs();
};
