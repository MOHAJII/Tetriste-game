#include "ScreenManager.h"
#include <iostream>
#include "GameManager.h"
#include "JsonHandler.h"

ScreenManager *ScreenManager::sInstance = nullptr;

ScreenManager *ScreenManager::Instance()
{
    if (sInstance == nullptr)
        sInstance = new ScreenManager();
    return sInstance;
}

ScreenManager::ScreenManager()
{
    mMainMenu = new MainMenu();
    mPlayScreen = new PlayScreen();

    mScoreBoard = ScoreBoard::Instance();

    mInputMgr = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();
}

void ScreenManager::Update()
{
    switch (mCurrentScreen)
    {
    case Menu:
        mMainMenu->Update();
        if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN))
        {
            mAudioMgr->PlaySFX("selectedMode.wav");

            mCurrentScreen = static_cast<Screens>(mMainMenu->getSelectedMode() + 1);
        }
        break;
    case Play:
        mPlayScreen->Update();
        if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            mAudioMgr->PlaySFX("selectedMode.wav");

            mCurrentScreen = Menu;
        }
        break;
    case Score:
        mScoreBoard->Update();

        if (mInputMgr->KeyPressed(SDL_SCANCODE_ESCAPE))
        {
            mAudioMgr->PlaySFX("selectedMode.wav");

            mCurrentScreen = Menu;
        }
        break;
    case Rules:
        break;
    case Control:
        break;

    default:
        GameManager::Instance()->QUIT();
        break;
    }
}

void ScreenManager::Render()
{
    switch (mCurrentScreen)
    {
    case Menu:
        mMainMenu->Render();
        break;
    case Play:
        mPlayScreen->Render();
        break;
    case Score:
        mScoreBoard->Render();
        break;
    default:
        break;
    }
}
void ScreenManager::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

ScreenManager::~ScreenManager()
{
    delete mMainMenu;
    mMainMenu = nullptr;

    delete mPlayScreen;
    mPlayScreen = nullptr;

    ScoreBoard::Release();
    mScoreBoard = nullptr;

    mInputMgr = nullptr;
    mAudioMgr = nullptr;
}