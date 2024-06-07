#include "TimerCountDown.h"

TimerCountDown *TimerCountDown::sInstance = nullptr;

TimerCountDown *TimerCountDown::Instance()
{
    if (sInstance == nullptr)
        sInstance = new TimerCountDown();

    return sInstance;
}

TimerCountDown::TimerCountDown(int time)
{
    mColor = {255, 255, 255, 255};
    setTimerCountDown(time);
    mTimer = Timer::Instance();
    mAudioMgr = AudioManager::Instance();
}

void TimerCountDown::Release()
{
    if (sInstance != nullptr)
    {
        delete sInstance;
        sInstance = nullptr;
    }
}

TimerCountDown::~TimerCountDown()
{
    for (int i = 0; i < mTimerCountDown.size(); ++i)
    {
        delete mTimerCountDown[i];
        mTimerCountDown[i] = nullptr;
    }
    mTimer = nullptr;
    mAudioMgr = nullptr;
}

void TimerCountDown::ResumeTimer()
{
    mIsPaused = false;
}

void TimerCountDown::StopTimer()
{
    mIsPaused = true;
}

int TimerCountDown::getRemainingTime() const
{
    return mCurrentTime;
}

void TimerCountDown::setTimerCountDown(int time)
{
    mCurrentTime = time;
    clearTimer();
    if (time == 0)
    {
        for (int i = 0; i < 5; ++i)
        {
            if (i != 2)
            {
                mTimerCountDown.push_back(new Texture("0", "Venite.ttf", 32, mColor));
            }
            else
            {
                mTimerCountDown.push_back(new Texture(":", "Venite.ttf", 32, mColor));
            }
            mTimerCountDown[i]->Parent(this);
            mTimerCountDown[i]->Pos(Vector2(24.0f * i, 0.0f));
        }
    }
    else
    {
        mMinutes = time / 60;
        mSeconds = time % 60;

        std::string secondsStr = std::to_string(mSeconds);
        if (secondsStr.length() == 1)
            secondsStr.insert(0, "0");
        std::string minutesStr = std::to_string(mMinutes);
        if (minutesStr.length() == 1)
            minutesStr.insert(0, "0");
        int TimerComponenetsLength = 4;

        for (int i = 0; i < 2; ++i)
        {
            mTimerCountDown.push_back(new Texture(minutesStr.substr(i, 1), "Venite.ttf", 32, mColor));
            mTimerCountDown[i]->Parent(this);
            mTimerCountDown[i]->Pos(Vector2(24.0f * i, 0.0f));
        }
        mTimerCountDown.push_back(new Texture(":", "Venite.ttf", 32, mColor));
        mTimerCountDown[2]->Parent(this);
        mTimerCountDown[2]->Pos(Vector2(24.0f * 2, 0.0f));
        for (int i = 0; i < 2; ++i)
        {
            mTimerCountDown.push_back(new Texture(secondsStr.substr(i, 1), "Venite.ttf", 32, mColor));
            mTimerCountDown[i + 3]->Parent(this);
            mTimerCountDown[i + 3]->Pos(Vector2(24.0f * (i + 3), 0.0f));
        }
    }
}

void TimerCountDown::IncrementTimer(int addedTime)
{
    mCurrentTime += addedTime;
    setTimerCountDown(mCurrentTime);
}

void TimerCountDown::clearTimer()
{
    for (int i = 0; i < mTimerCountDown.size(); ++i)
    {
        delete mTimerCountDown[i];
        mTimerCountDown[i] = nullptr;
    }
    mTimerCountDown.clear();
}
void TimerCountDown::Update()
{

    if (mCurrentTime > 0 && !mIsPaused)
    {
        mDecrementUnit -= mTimer->DeltaTime();
        if (mDecrementUnit <= 0)
        {
            mCurrentTime--;
            setTimerCountDown(mCurrentTime);
            mDecrementUnit = 1;
            if (mCurrentTime <= 5)
            {
                mAudioMgr->PlaySFX("FastClockTicks.wav", 0, ticksChannel);
                mColor = {255, 0, 0, 255};
            }
            // else
            // {
            //     // mAudioMgr->PlaySFX("ClockTicks.wav", 0, ticksChannel);
            // }
        }
    }
}

void TimerCountDown::Render()
{
    for (int i = 0; i < mTimerCountDown.size(); ++i)
    {
        mTimerCountDown[i]->Render();
    }
}