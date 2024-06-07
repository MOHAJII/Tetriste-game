#include "TextsAndResults.h"
#include <iostream>
TextsAndResults::TextsAndResults()
{
    mGameOverText = new Texture("Game Over", "ka1.ttf", 48, {255, 255, 255});
    mGameOverText->Parent(this);
    mGameOverText->Pos(VEC2_ZERO);
    mGameOverText->Active(false);

    mToLeaderBoard = new Texture("TO THE LEADER BOARD", "ka1.ttf", 48, {247, 208, 0});
    mToLeaderBoard->Parent(mGameOverText);
    mToLeaderBoard->Pos(Vector2(0, mToLeaderBoard->getHeight() / 2 + 250));
    mToLeaderBoard->Active(false);

    mEnterName = new Texture("Enter your name  :", "ka1.ttf", 48, {255, 255, 255});
    mEnterName->Parent(mToLeaderBoard);
    mEnterName->Pos(Vector2(-148.0f, mEnterName->getHeight() / 2 + 88));
    mEnterName->Active(false);
}

TextsAndResults::~TextsAndResults()
{
    delete mGameOverText;
    mGameOverText = nullptr;
    delete mEnterName;
    mEnterName = nullptr;
    delete mToLeaderBoard;
    mToLeaderBoard = nullptr;
    delete mPlayerName;
    mPlayerName = nullptr;
}

void TextsAndResults::ShowGameOver()
{
    mGameOverText->Active(true);
}

void TextsAndResults::HideGameOver()
{
    mGameOverText->Active(false);
}

void TextsAndResults::ShowUserNameInput()
{
    mEnterName->Active(true);
    mToLeaderBoard->Active(true);
}

void TextsAndResults::HideUserNameInput()
{
    mEnterName->Active(false);
    mToLeaderBoard->Active(false);
}

std::string TextsAndResults::InsertPlayerName()
{
    const int maxCharacters = 7;

    // Event handler
    SDL_Event event;

    // Track the current player name and its length
    // Main loop for handling events
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            break;
        }
        // If a key is pressed
        if (event.type == SDL_KEYDOWN)
        {
            // If the key is a printable character and the player name length is less than the maximum allowed characters
            if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z && mStringPlayerName.size() < maxCharacters)
            {
                // Add the character to the player name
                mStringPlayerName += event.key.keysym.sym;
                // Create a texture for the character
                mPlayerName = new Texture(mStringPlayerName, "ka1.ttf", 48, {255, 255, 255});
                mPlayerName->Parent(mEnterName);
                mPlayerName->Pos(Vector2(mEnterName->getWidth() / 2 + mPlayerName->getWidth() / 2 + 24, 0));
            }
            // If backspace is pressed and there are characters in the player name
            else if (event.key.keysym.sym == SDLK_BACKSPACE && mStringPlayerName.size() > 0)
            {
                mStringPlayerName.pop_back();
                mPlayerName = new Texture(mStringPlayerName, "ka1.ttf", 48, {255, 255, 255});
                mPlayerName->Parent(mEnterName);
                mPlayerName->Pos(Vector2(mEnterName->getWidth() / 2 + mPlayerName->getWidth() / 2 + 24, 0));
            }
        }
    }

    return mStringPlayerName;
}

void TextsAndResults::Render()
{
    if (mGameOverText->Active())
        mGameOverText->Render();
    if (mToLeaderBoard->Active() && mEnterName->Active())
    {
        mToLeaderBoard->Render();
        mEnterName->Render();
        if (mPlayerName)
        {
            mPlayerName->Render();
        }
    }
}

void TextsAndResults::Update()
{
}