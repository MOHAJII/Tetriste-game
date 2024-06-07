#include "ScoreBoard.h"

ScoreBoard *ScoreBoard::sInstance = nullptr;

ScoreBoard *ScoreBoard::Instance()
{
    if (sInstance == nullptr)
        sInstance = new ScoreBoard();
    return sInstance;
}

void ScoreBoard::Release()
{
    delete sInstance;
    sInstance = nullptr;
}

ScoreBoard::ScoreBoard() : mScoreData(JsonHandler::ReadFromFile("./saves/scores.json"))
{
    mInputMgr = InputManager::Instance();
    mBackground = new Texture("ScoreBackground.png");
    mBackground->Parent(this);
    mBackground->Pos(Vector2(mBackground->getWidth() / 2, mBackground->getHeight() / 2));

    mlvlMenu = new Menu(24);
    mlvlMenu->addOption("EZ", 38, {255, 246, 0});
    mlvlMenu->addOption("MIDIUM", 38, {255, 181, 0});
    mlvlMenu->addOption("HARD", 38, {255, 138, 0});
    mlvlMenu->addOption("NIGHTMARE", 38, {237, 59, 75, 255});

    mlvlMenu->Parent(this);

    mlvlMenu->Pos(Vector2(184, 48));

    if (mScoreData.empty())
    {
        std::cerr << "Failed to read JSON data from file: "
                  << "./saves/scores.json" << std::endl;
        return;
    }

    LoadDataToScoreBoard();
}

void ScoreBoard::setNewScore(std::string playerName, int newScore, int currentLevel)
{
    json &scores = mScoreData["levels"][currentLevel]["scores"];

    // If the first score is null it means the score board is empty then assign the new score and return
    if (scores[0]["score"].is_null())
    {
        scores[0]["score"] = newScore;
        scores[0]["name"] = playerName;
        JsonHandler::WriteToFile(mScoreData, "./saves/scores.json");
        LoadDataToScoreBoard();
        return;
    }
    // find the position to insert
    int insertPosition = 9;
    while (insertPosition >= 0 && (scores[insertPosition]["score"].is_null() || scores[insertPosition]["score"] < newScore))
    {
        insertPosition--;
    }
    // increment by one because the next position is where we want to insert
    ++insertPosition;

    // shift all the scores that are under the new score is position by one position down
    for (int i = 8; i >= insertPosition; i--)
    {
        scores[i + 1]["score"] = scores[i]["score"];
        scores[i + 1]["name"] = scores[i]["name"];
    }

    // assign the new player name and score to the insert position
    scores[insertPosition]["score"] = newScore;
    scores[insertPosition]["name"] = playerName;

    JsonHandler::WriteToFile(mScoreData, "./saves/scores.json");
    LoadDataToScoreBoard();
}

bool ScoreBoard::isHighScore(int newScore, int currentLevel)
{
    const json &scores = mScoreData["levels"][currentLevel]["scores"];

    // If the last score in the leaderboard is null or the last score is less than the new score return true to indicate that the new score should be added
    if ((scores[9]["score"].is_null() || scores[9]["score"] < newScore) && newScore > 0)
        return true;
    return false;
}

void ScoreBoard::LoadDataToScoreBoard()
{
    mLevelPlayerScoresTex.clear();
    if (mScoreData.contains("levels") && mScoreData["levels"].is_array())
    {
        Texture *playerNameTxt;
        Texture *playerScoreTxt;

        // Iterate over each element of the "levels" array
        for (const auto &level : mScoreData["levels"])
        {

            // Check if the current level object is valid
            if (level.is_object())
            {

                // Access properties of the current level object
                int levelIndex = level["levelIndex"];

                // Assuming "scores" is an array within each level object
                if (level.contains("scores") && level["scores"].is_array())
                {
                    int i = 110;
                    int counter = 1;
                    // Iterate over each score object in the "scores" array
                    for (const auto &score : level["scores"])
                    {

                        std::string scoreStr = (score["score"].is_number() ? std::to_string((int)score["score"]) : "--");
                        std::string nameStr = (!score["name"].is_null() ? score["name"] : "--");

                        playerNameTxt = new Texture(nameStr, "Ka1.ttf", 37, {255, 255, 255, 255});
                        playerNameTxt->Parent(this);
                        playerNameTxt->Pos(Vector2(mBackground->getWidth() / 2 + 135, i));

                        playerScoreTxt = new Texture(scoreStr, "Ka1.ttf", 37, {255, 255, 255, 255});
                        playerScoreTxt->Parent(this);
                        playerScoreTxt->Pos(Vector2(mBackground->getWidth() / 2 + 460, i));

                        mLevelPlayerScoresTex[levelIndex].push_back(std::make_pair(playerNameTxt, playerScoreTxt));
                        i += 48;
                    }
                }
            }
        }
    }
}

ScoreBoard::~ScoreBoard()
{
    delete mBackground;
    mBackground = nullptr;
    mInputMgr = nullptr;

    delete mlvlMenu;
    mlvlMenu = nullptr;
}

void ScoreBoard::Update()
{
    mlvlMenu->Update();
    if (mInputMgr->KeyPressed(SDL_SCANCODE_W) || mInputMgr->KeyPressed(SDL_SCANCODE_S))
    {

        mDisplayedScoreLevel = mlvlMenu->getSelectedOption();
    }
    // if (mInputMgr->KeyPressed(SDL_SCANCODE_SPACE))
    // {
    //     setNewScore("new", 16, 0);
    //     // std::cout << (isHighScore(30, 0) == true ? "yess" : "nope");
    // }
}

void ScoreBoard::Render()
{
    mBackground->Render();
    mlvlMenu->Render();

    for (int i = 0; i < 10; ++i)
    {
        mLevelPlayerScoresTex[mDisplayedScoreLevel][i].first->Render();
        mLevelPlayerScoresTex[mDisplayedScoreLevel][i].second->Render();
    }
}