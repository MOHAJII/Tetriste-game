
//---------------------------------------------------------------------//
// LevelProperties.h //
// Manages the initialization of game levels
// assigns bonuses for insertions and shifting deletions //
//---------------------------------------------------------------------//

#pragma once

enum Level
{
    EZ,
    MEDIUM,
    HARD,
    NIGHTMARE
};

class LevelProperties
{
private:
    int mInitialTime,
        mInitialShapesToSkip,
        mInsertRemoveShapesToSkipBonus,
        mInsertRemoveScore,
        mInsertRemoveTimeBonus,
        mShiftRemoveScore,
        mShiftTimeBonus,
        mShiftShapesToSkipBonus,
        mRandomShapeCount,
        mRandomColorCount;

    Level mCurrentLevel;
    static LevelProperties *sInstance;

public:
    static LevelProperties *Instance();
    static void Release();
    void InitializeLevel(Level lvl);

    int getInitialTime() const;
    int getInitialShapesToSkip() const;
    int getInsertRemoveScore() const;
    int getInsertRemoveTimeBonus() const;
    int getInsertRemoveShapesToSkipBonus() const;
    int getShiftRemoveScore() const;
    int getShiftTimeBonus() const;
    int getShiftShapesToSkipBonus() const;
    int getRandomShapeCount() const;
    int getRandomColorCount() const;

private:
    LevelProperties();
    ~LevelProperties();
};
