//---------------------------------------------------------------------//
// GameManager.cpp                                                     //
// Used to intialize and release all other manager                     //
// Contains the game loop as well as the Update and Render functions   //
// Used to make sure all functions are called in the correct order     //
//                                                                     //
// By: Ather Omar                                                      //
//---------------------------------------------------------------------//
#include "GameManager.h"

//-----------------------------------------------------------
// QuickSDL
//-----------------------------------------------------------
namespace QuickSDL
{
    // Initializing to nullptr
    GameManager *GameManager::sInstance = nullptr;

    GameManager *GameManager::Instance()
    {
        // Create a new instance if no instance was created before
        if (sInstance == nullptr)
            sInstance = new GameManager();
        return sInstance;
    }

    void GameManager::Release()
    {
        delete sInstance;
        sInstance = nullptr;
    }

    GameManager::GameManager()
    {
        mQuit = false;

        // Initialize SDL
        mGraphics = Graphics::Instance();

        // Quits the game if SDL fails to initialize
        if (!Graphics::Initialized())
            mQuit = true;

        // Initialize AssetManager
        mAssetMgr = AssetManager::Instance();

        // Initialize InputManager
        mInputMgr = InputManager::Instance();

        // Initialize AudioManager
        mAudioMgr = AudioManager::Instance();

        // Initialize Timer
        mTimer = Timer::Instance();

        // Initialize Screen Manager
        mScreenManager = ScreenManager::Instance();
    }

    GameManager::~GameManager()
    {

        AudioManager::Release();
        mAudioMgr = nullptr;

        AssetManager::Release();
        mAssetMgr = nullptr;

        Graphics::Release();
        mGraphics = nullptr;

        InputManager::Release();
        mInputMgr = nullptr;

        Timer::Release();
        mTimer = nullptr;

        ScreenManager::Release();
        mScreenManager = nullptr;
    }

    void GameManager::EarlyUpdate()
    {
        // Updating the input state before any other updates are run to make sure the Input check is accurate
        mInputMgr->Update();
    }

    void GameManager::Update()
    {
        // GameEntity Updates should happen here
        mScreenManager->Update();
    }

    void GameManager::LateUpdate()
    {

        // Any collision detection should happen here

        mTimer->Reset();
        mInputMgr->UpdatePrevInput();
    }

    void GameManager::Render()
    {
        // Clears the last frame's render from the back buffer
        mGraphics->ClearBackBuffer();
        // All other rendering is to happen here
        mScreenManager->Render();
        // Renders the current frame
        mGraphics->Render();
    }

    void GameManager::QUIT()
    {
        mQuit = true;
    }

    void GameManager::Run()
    {
        while (!mQuit)
        {
            mTimer->Update();
            while (SDL_PollEvent(&mEvents) != 0)
            {
                if (mEvents.type == SDL_QUIT)
                {
                    mQuit = true;
                }
            }

            // Calculate the time to wait to maintain the desired frame rate
            float timeToWait = FRAME_TARGET_TIME - mTimer->DeltaTime();

            if (timeToWait > 0.0f && timeToWait <= FRAME_TARGET_TIME)
            {
                // Delay the loop to achieve the desired frame rate
                SDL_Delay(static_cast<Uint32>(timeToWait * 1000)); // Convert seconds to milliseconds
            }
            mTimer->Update();

            if (!mQuit)
            {
                EarlyUpdate();
                Update();
                LateUpdate();
                Render();
            }
        }
    }
}
