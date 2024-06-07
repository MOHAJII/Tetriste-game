
//---------------------------------------------------------------------//
// TimerCountDown.h //
// Manages a countdown timer for the game
//---------------------------------------------------------------------//

#pragma once
#include <vector>
#include "Texture.h"
#include "Timer.h"
#include "AudioManager.h"

using namespace QuickSDL;

class TimerCountDown : public GameEntity
{
public:
     SDL_Color mColor;

private:
    static TimerCountDown *sInstance; // Static member to hold the singleton instance
    std::vector<Texture *> mTimerCountDown;

    Timer *mTimer;
    AudioManager *mAudioMgr;

    int mSeconds, mMinutes, mR, mG, mB;
    float mCurrentTime;

    float mDecrementUnit = 1.0f;

    bool mIsPaused = false;

public:
    // Method to get the singleton instance
    static TimerCountDown *Instance();

    static void Release();

    void setTimerCountDown(int time);
    void IncrementTimer(int addedTime);
    void Update();
    void Render();
    void ResumeTimer();
    void StopTimer();
    int getRemainingTime() const;

private:
    // Private constructor & Destructor to prevent direct instantiation
    TimerCountDown(int time = 0);
    ~TimerCountDown();

    void clearTimer();
};