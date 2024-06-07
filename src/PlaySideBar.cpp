#include "PlaySideBar.h"

#include <time.h>

PlaySideBar *PlaySideBar::sInstance = nullptr;

Counter *PlaySideBar::mScore = nullptr;
Counter *PlaySideBar::mShapeToSkip = nullptr;
TimerCountDown *PlaySideBar::mTimerCountDown = nullptr;

PlaySideBar *PlaySideBar::Instance()
{
    if (sInstance == nullptr)
        sInstance = new PlaySideBar();
    return sInstance;
}

void PlaySideBar::Release()
{
    if (sInstance != nullptr)
    {
        delete sInstance;
        sInstance = nullptr;
    }
}

void PlaySideBar::InitializeVars(int time, int shapesToSkip, int rndShape, int rndColor)
{
    mScore->setValue(0);
    mTimerCountDown->setTimerCountDown(time);
    mShapeToSkip->setValue(shapesToSkip);

    mNextShape->RANDOM_COLORS_COUNT = rndColor;
    mNextShape->RANDOM_SHAPES_COUNT = rndShape;
}

PlaySideBar::PlaySideBar()
{
    lvl = LevelProperties::Instance();

    mAudioMgr = AudioManager::Instance();
    mInputMgr = InputManager::Instance();

    srand((unsigned)time(NULL));
    int GRID_GAP = Graphics::Instance()->GRID_GAP;
    mTimer = Timer::Instance();
    mBackground = new Texture("SideBarBackground.png");
    mBackground->Parent(this);
    mBackground->Pos(VEC2_ZERO);

    NextPieceHolders[0] = new Texture("NextPieceHolder.png");
    NextPieceHolders[0]->Parent(mBackground);
    int HolderHeight = NextPieceHolders[0]->getHeight();
    int HolderWidth = NextPieceHolders[0]->getWidth();

    NextPieceHolders[0]->Pos(Vector2(0.0f, (mBackground->getHeight() / 2) - HolderHeight / 2 - GRID_GAP));

    for (int i = 1; i < 5; i++)
    {
        NextPieceHolders[i] = new Texture("NextPieceHolderSmall.png");
        NextPieceHolders[i]->Parent(NextPieceHolders[0]);
    }

    int smallHolderWidth = NextPieceHolders[1]->getWidth();
    int smallHolderHeight = NextPieceHolders[1]->getHeight();

    NextPieceHolders[4]->Pos(Vector2(HolderWidth / 2 - smallHolderWidth / 2, -HolderHeight / 2 - 3 * smallHolderHeight / 2 - GRID_GAP * 2));
    NextPieceHolders[3]->Pos(Vector2(-HolderWidth / 2 + smallHolderWidth / 2, -HolderHeight / 2 - 3 * smallHolderHeight / 2 - GRID_GAP * 2));
    NextPieceHolders[2]->Pos(Vector2(+HolderWidth / 2 - smallHolderWidth / 2, -HolderHeight / 2 - smallHolderHeight / 2 - GRID_GAP));
    NextPieceHolders[1]->Pos(Vector2(-HolderWidth / 2 + smallHolderWidth / 2, -HolderHeight / 2 - smallHolderHeight / 2 - GRID_GAP));

    mTimerLogo = new Texture("Timer.png");

    mTimerLogo->Parent(mBackground);
    mTimerLogo->Pos(Vector2(-mBackground->getWidth() / 2 + mTimerLogo->getWidth() / 2 + 40.0f, -mBackground->getHeight() / 2 + mTimerLogo->getWidth() / 2 + GRID_GAP));
    mTimerCountDown = TimerCountDown::Instance();
    mTimerCountDown->Parent(mTimerLogo);
    mTimerCountDown->Pos(Vector2(mTimerLogo->getWidth() / 2 + GRID_GAP, 2.0f));

    int infosHeight = -mBackground->getHeight() / 2 + GRID_GAP * 4 + mTimerLogo->getHeight();

    mScore = new Counter("Score", 24);
    mScore->Parent(mBackground);
    mScore->Pos(Vector2(-mBackground->getWidth() / 2 + GRID_GAP, infosHeight));

    mShapeToSkip = new Counter("Skips", lvl->getInitialShapesToSkip(), 24);
    mShapeToSkip->Parent(mBackground);
    mShapeToSkip->Pos(Vector2(-mBackground->getWidth() / 2 + GRID_GAP, infosHeight + mScore->getLabelHeight() + GRID_GAP));

    mNextPieceLabel = new Texture("Next Pieces :", "Venite.ttf", 24, {255, 255, 255, 255});
    mNextPieceLabel->Parent(NextPieceHolders[3]);
    mNextPieceLabel->Pos(Vector2(-NextPieceHolders[3]->getWidth() / 2 + mNextPieceLabel->getWidth() / 2, -NextPieceHolders[3]->getHeight() / 2 - mNextPieceLabel->getHeight() / 2 - GRID_GAP));

    mNextShape = new NextPieceGenerator(NextPieceHolders);
}

void PlaySideBar::addBonuses(int score, int shapesToSkip, int addedTime)
{
    mScore->incrementValue(score);
    mShapeToSkip->incrementValue(shapesToSkip);
    mTimerCountDown->IncrementTimer(addedTime);
}

PlaySideBar::~PlaySideBar()
{
    delete mBackground;
    mBackground = nullptr;

    mInputMgr = nullptr;
    mAudioMgr = nullptr;
    mTimer = nullptr;

    delete mTimerLogo;
    mTimerLogo = nullptr;

    TimerCountDown::Release();
    mTimerCountDown = nullptr;

    delete mScore;
    mScore = nullptr;

    delete mShapeToSkip;
    mShapeToSkip = nullptr;

    delete mNextPieceLabel;
    mNextPieceLabel = nullptr;

    for (int i = 0; i < 5; ++i)
    {
        delete NextPieceHolders[i];
        NextPieceHolders[i] = nullptr;
    }
    delete mNextShape;
    mNextShape = nullptr;
    lvl = nullptr;
}

Shape *PlaySideBar::getNextShape()
{
    return mNextShape->getNextShape();
}

void PlaySideBar::Update()
{

    if (mInputMgr->KeyPressed(SDL_SCANCODE_SPACE))
    {
        if (getRemainingShapesToskip() > 0)
        {
            mShapeToSkip->incrementValue(-1);
            getNextShape();

            mAudioMgr->PlaySFX("shapeSkipped.wav", 0, shapeSkippedChannel);
        }
        else
        {
            mAudioMgr->PlaySFX("insufficient.wav", 0, shapeSkippedChannel);
        }
    }

    mScore->Update();
    mTimerCountDown->Update();
    mScore->Update();
    mNextShape->Update();
}

int PlaySideBar::getScore()
{
    return mScore->getValue();
}

int PlaySideBar::getRemainingTime() const
{
    return mTimerCountDown->getRemainingTime();
}

int PlaySideBar::getRemainingShapesToskip() const
{
    return mShapeToSkip->getValue();
}

void PlaySideBar::Render()
{
    mBackground->Render();
    mTimerLogo->Render();
    mTimerCountDown->Render();
    mScore->Render();
    mShapeToSkip->Render();

    mNextPieceLabel->Render();
    for (int i = 0; i < 5; ++i)
    {
        NextPieceHolders[i]->Render();
    }
    mNextShape->Render();
}