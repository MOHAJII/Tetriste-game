#pragma once
#include "GameEntity.h"
#include "Texture.h"
#include <iostream>
#include <vector>
#include "JsonHandler.h"
#include "InputManager.h"
#include "Menu.h"
using namespace QuickSDL;

class ScoreBoard : public GameEntity
{
private:
    using PlayerScorePair = std::pair<Texture *, Texture *>;
    using ScoreLevelPair = std::vector<PlayerScorePair>;

    ScoreLevelPair scorelevelVector;
    std::map<int, ScoreLevelPair> mLevelPlayerScoresTex;

    Texture *mBackground;

    json mScoreData;
    int mDisplayedScoreLevel = 0;

    InputManager *mInputMgr;

    Menu *mlvlMenu;

    static ScoreBoard *sInstance;

public:
    static ScoreBoard *Instance();
    static void Release();

    void Update();
    void Render();

    void setNewScore(std::string playerName, int newScore, int currentLevel);
    bool isHighScore(int newScore, int currentLevel);

private:
    ScoreBoard();
    ~ScoreBoard();

    void LoadDataToScoreBoard();
};
