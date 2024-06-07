//---------------------------------------------------------------------//
// Menu.h //
// creates menus with a title and options
//---------------------------------------------------------------------//

#pragma once
#include "GameEntity.h"
#include "Texture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include <iostream>
#include <vector>

using namespace QuickSDL;

class Menu : public GameEntity
{
private:
    Texture *mTitle;
    using ColoredTexture = std::pair<Texture *, SDL_Color>;
    std::vector<ColoredTexture> mOptions;

    int mSelectedOption = 0, titleSize, optionsGap;

    // Handling inputs
    InputManager *mInputMgr;

    // Handling audio
    AudioManager *mAudioMgr;

    GameEntity *mMenu;

    SDL_Color mColor;

public:
    Menu(const char *title, int titleSize = 48, int optionsGap = 12, SDL_Color color = {255, 255, 255});
    Menu(int optionsGap = 12, SDL_Color color = {255, 255, 255});

    ~Menu();

    void addOption(const char *title, int titleSize = 38, SDL_Color hoverColor = {157, 153, 255});
    void Update();
    void Render();

    void changeSelecedOption(int);
    int getSelectedOption();

private:
    bool HandleInputs();
};