#include "LevelProperties.h"
LevelProperties *LevelProperties::sInstance = nullptr;

LevelProperties *LevelProperties::Instance()
{
    if (sInstance == nullptr)
        sInstance = new LevelProperties();
    return sInstance;
}

void LevelProperties::Release()
{
    if (sInstance != nullptr)
    {
        delete sInstance;
        sInstance = nullptr;
    }
}

LevelProperties::LevelProperties()
{
}

LevelProperties::~LevelProperties()
{
}

void LevelProperties::InitializeLevel(Level lvl)
{
    switch (lvl)
    {
    case EZ:
        mInitialTime = 180; // 3 mins
        mInitialShapesToSkip = 5;

        mInsertRemoveTimeBonus = 3;
        mInsertRemoveShapesToSkipBonus = 0;
        mInsertRemoveScore = 3;

        mShiftRemoveScore = 10;
        mShiftTimeBonus = 30;
        mShiftShapesToSkipBonus = 5;
        mRandomShapeCount = 4;
        mRandomColorCount = 4;
        break;
    case MEDIUM:

        mInitialTime = 120; // 2 mins
        mInitialShapesToSkip = 3;

        mInsertRemoveTimeBonus = 2;
        mInsertRemoveShapesToSkipBonus = 0;
        mInsertRemoveScore = 2;

        mShiftRemoveScore = 5;
        mShiftTimeBonus = 10;
        mShiftShapesToSkipBonus = 3;

        mRandomShapeCount = 6;
        mRandomColorCount = 5;
        break;
    case HARD:

        mInitialTime = 60;
        mInitialShapesToSkip = 2;

        mInsertRemoveTimeBonus = 1;
        mInsertRemoveShapesToSkipBonus = 0;
        mInsertRemoveScore = 1;

        mShiftRemoveScore = 3;
        mShiftTimeBonus = 5;
        mShiftShapesToSkipBonus = 2;

        mRandomShapeCount = 8;
        mRandomColorCount = 6;
        break;
    case NIGHTMARE:

        mInitialTime = 30;
        mInitialShapesToSkip = 1;

        mInsertRemoveTimeBonus = 1;
        mInsertRemoveShapesToSkipBonus = 0;
        mInsertRemoveScore = 1;

        mShiftRemoveScore = 3;
        mShiftTimeBonus = 3;
        mShiftShapesToSkipBonus = 1;

        mRandomShapeCount = 10;
        mRandomColorCount = 7;
        break;
    default:

        break;
    }
}

int LevelProperties::getInitialTime() const
{
    return mInitialTime;
}

int LevelProperties::getInitialShapesToSkip() const
{
    return mInitialShapesToSkip;
}

int LevelProperties::getInsertRemoveTimeBonus() const
{
    return mInsertRemoveTimeBonus;
}

int LevelProperties::getInsertRemoveShapesToSkipBonus() const
{
    return mInsertRemoveShapesToSkipBonus;
}

int LevelProperties::getInsertRemoveScore() const
{
    return mInsertRemoveScore;
}

int LevelProperties::getShiftRemoveScore() const
{
    return mShiftRemoveScore;
}

int LevelProperties::getShiftTimeBonus() const
{
    return mShiftTimeBonus;
}

int LevelProperties::getShiftShapesToSkipBonus() const
{
    return mShiftShapesToSkipBonus;
}

int LevelProperties::getRandomShapeCount() const
{
    return mRandomShapeCount;
}

int LevelProperties::getRandomColorCount() const
{
    return mRandomColorCount;
}