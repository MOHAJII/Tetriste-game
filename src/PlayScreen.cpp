#include "PlayScreen.h"
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 1);

PlayScreen::PlayScreen()
{
    int GAP = Graphics::Instance()->GRID_GAP;
    int SCREEN_HEIGHT = Graphics::Instance()->SCREEN_HEIGHT;
    int SCREEN_WIDTH = Graphics::Instance()->SCREEN_WIDTH;

    mTimer = Timer::Instance();
    mInputMgr = InputManager::Instance();

    mAudioMgr = AudioManager::Instance();

    mSideBar = PlaySideBar::Instance();
    mSideBar->Parent(this);
    mSideBar->Pos(Vector2(SCREEN_WIDTH - 124 - GAP, SCREEN_HEIGHT / 2));

    mBoard = new Board();
    mBoard->Parent(this);
    mBoard->Pos(Vector2(SCREEN_WIDTH / 2 - 148 + GAP, SCREEN_HEIGHT / 2));

    mControls = new Texture("controls.png");
    mControls->Parent(this);
    mControls->Pos(Vector2(mControls->getWidth() / 2 + GAP, SCREEN_HEIGHT - mControls->getHeight() / 2 - GAP));

    mGameResultsText = new TextsAndResults();
    mGameResultsText->Parent(mBoard);
    mGameResultsText->Pos(Vector2(0.0f, -148.0f));

    mGameOver = false;

    mLvlMenu = new Menu("Choose a level", 48, 0);
    mLvlMenu->addOption("EZ");
    mLvlMenu->addOption("MIDIUM");
    mLvlMenu->addOption("HARD");
    mLvlMenu->addOption("NIGHTMARE");

    mLvlMenu->Parent(this);

    mLvlMenu->Pos(Vector2(SCREEN_WIDTH / 2 - 148 + GAP, GAP + 24));

    lvl = LevelProperties::Instance();
    lvl->InitializeLevel(static_cast<Level>(EZ));

    mGamePausedMenu = new Menu("GAME PAUSED", 48, 12);
    mGamePausedMenu->addOption("RESTART");
    mGamePausedMenu->addOption("SAVE");
    mGamePausedMenu->addOption("QUIT");
    mGamePausedMenu->Active(false);
    mGamePausedMenu->Parent(this);
    mGamePausedMenu->Pos(Vector2(SCREEN_WIDTH / 2 - 148 + GAP, GAP + 24));

    mSideBar->InitializeVars(lvl->getInitialTime(), lvl->getInitialShapesToSkip(), lvl->getRandomShapeCount(), lvl->getRandomColorCount());
}

PlayScreen::~PlayScreen()
{
    mInputMgr = nullptr;
    mTimer = nullptr;
    mAudioMgr = nullptr;
    delete mBoard;
    mBoard = nullptr;

    delete mControls;
    mControls = nullptr;

    PlaySideBar::Release;
    mSideBar = nullptr;

    LevelProperties::Release();

    delete mLvlMenu;
    mLvlMenu = nullptr;

    delete mGamePausedMenu;
    mGamePausedMenu = nullptr;
}

void PlayScreen::Update()
{
    if (!mLvlMenu->Active())
    {
        if (mInputMgr->KeyPressed(SDL_SCANCODE_TAB) && !mGameOver)
        {
            mAudioMgr->PlaySFX("GamePaused.wav", 0, GamePausedOverChannel);
            mGamePausedMenu->Active(!mGamePausedMenu->Active());
            mControls->Active(!mControls->Active());
        }
        if ((mBoard->ShapesInserted() >= 15 || mSideBar->getRemainingTime() <= 0) && !mGameOver)
        {
            mGameOver = true;
            mGameResultsText->ShowGameOver();
            mAudioMgr->PlaySFX("GameOver.wav", 0, GamePausedOverChannel);
        }
        if (!mGamePausedMenu->Active() && !mGameOver)
        {
            // int randomNumber = dis(gen);
            // timeToGenerate += mTimer->DeltaTime();
            // std::cout << "\n"
            //           << mTimer->DeltaTime();
            // if (timeToGenerate >= 2)
            // {
            // mBoard->AddShape(mSideBar->getNextShape(), randomNumber);
            // timeToGenerate = 0;
            // }
            if (mInputMgr->KeyPressed(SDL_SCANCODE_D))
            {
                mBoard->AddShape(mSideBar->getNextShape(), true);
            }
            else if (mInputMgr->KeyPressed(SDL_SCANCODE_A))
            {
                mBoard->AddShape(mSideBar->getNextShape(), false);
            }

            mSideBar->Update();
            mBoard->Update();
        }
        else
        {
            if (mGameOver)
            {
                if (ScoreBoard::Instance()->isHighScore(mSideBar->getScore(), mLvlMenu->getSelectedOption()))
                {
                    mGameResultsText->ShowUserNameInput();
                    std::string playerName = mGameResultsText->InsertPlayerName();
                    if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN) && playerName.length() > 0)
                    {
                        ScoreBoard::Instance()->setNewScore(playerName, mSideBar->getScore(), mLvlMenu->getSelectedOption());
                        RestartGame();
                    }
                }
                else
                {
                    if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN))
                        RestartGame();
                }
            }
            if (mGamePausedMenu->Active())
            {
                mGamePausedMenu->Update();
                if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN))
                {
                    if (mGamePausedMenu->getSelectedOption() == 0)
                    {
                        mGamePausedMenu->Active(false);
                        RestartGame();
                    }
                }
            }
        }
    }
    else
    {
        mLvlMenu->Update();

        if (mInputMgr->KeyPressed(SDL_SCANCODE_S) || mInputMgr->KeyPressed(SDL_SCANCODE_W))
        {

            lvl->InitializeLevel(static_cast<Level>(mLvlMenu->getSelectedOption()));
            mSideBar->InitializeVars(lvl->getInitialTime(), lvl->getInitialShapesToSkip(), lvl->getRandomShapeCount(), lvl->getRandomColorCount());
        }
        else if (mInputMgr->KeyPressed(SDL_SCANCODE_RETURN))
        {
            for (int i = 0; i < 5; i++)
            {
                mSideBar->getNextShape();
                mSideBar->Update();
            }
            mControls->Active(false);
            mLvlMenu->Active(false);
            mAudioMgr->PlaySFX("GameStart.wav", 0, GameStartedChannel);
        }
    }
}

void PlayScreen::RestartGame()
{
    mAudioMgr->PlaySFX("StartAgain.wav", 0, GameStartedChannel);

    TimerCountDown::Instance()->mColor = {255, 255, 255, 255};
    mGameResultsText->HideGameOver();
    mGameResultsText->HideUserNameInput();
    mSideBar->InitializeVars(lvl->getInitialTime(), lvl->getInitialShapesToSkip(), lvl->getRandomShapeCount(), lvl->getRandomColorCount());
    mLvlMenu->Active(true);
    mControls->Active(true);
    mBoard->clear();
    mGameOver = false;
}

void PlayScreen::Render()
{
    mSideBar->Render();
    mBoard->Render();
    mGameResultsText->Render();

    if (mControls->Active())
        mControls->Render();

    if (mLvlMenu->Active())
        mLvlMenu->Render();

    if (mGamePausedMenu->Active())
        mGamePausedMenu->Render();
}
