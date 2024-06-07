
//---------------------------------------------------------------------//
// TextsAndResults.h //
// Handles the display of game over, game paused, and result texts
//---------------------------------------------------------------------//

#pragma once
#include "GameEntity.h"
#include "Texture.h"
#include <vector>
using namespace QuickSDL;

class TextsAndResults : public GameEntity
{
private:
    std::string mStringPlayerName = "";

    Texture *mGameOverText, *mEnterName, *mToLeaderBoard, *mPlayerName;

public:
    TextsAndResults();
    ~TextsAndResults();

    std::string InsertPlayerName();

    void ShowGameOver();
    void HideGameOver();

    void ShowUserNameInput();
    void HideUserNameInput();

    void
    Render();
    void Update();
};