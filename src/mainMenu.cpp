#include "mainMenu.h"
#include <iostream>
MainMenu::MainMenu()
{
    mMainMenu = new Menu(24);
    mMainMenu->addOption("Start", 48);
    mMainMenu->addOption("Score", 48);
    // mMainMenu->addOption("Rules", 48);
    // mMainMenu->addOption("inputs", 48);
    mMainMenu->addOption("Quit", 48);

    mMainMenu->Parent(this);
    mMainMenu->Pos(Vector2(184, 124));

    mInputMgr = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();

    //mAudioMgr->PlayMusic("menu.wav");
}

MainMenu::~MainMenu()
{
    mInputMgr = nullptr;
    mAudioMgr = nullptr;

    delete mMainMenu;
    mMainMenu = nullptr;
}

void MainMenu::Update()
{
    mMainMenu->Update();
}

int MainMenu::getSelectedMode()
{
    return mMainMenu->getSelectedOption();
}

void MainMenu::Render()
{
    mMainMenu->Render();
}