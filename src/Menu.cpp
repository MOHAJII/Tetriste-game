#include "Menu.h"

Menu::Menu(int optionsGap, SDL_Color color)
{
    mColor = color;
    this->optionsGap = optionsGap;

    mMenu = new GameEntity(Vector2(VEC2_ZERO));
    mMenu->Parent(this);
    mTitle = nullptr;

    mInputMgr = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();
}

Menu::Menu(const char *title, int titleSize, int optionsGap, SDL_Color color)
{
    mColor = color;
    this->optionsGap = optionsGap;

    mMenu = new GameEntity(Vector2(VEC2_ZERO));
    mMenu->Parent(this);

    mTitle = new Texture(title, "Ka1.ttf", titleSize, mColor);
    mTitle->Parent(mMenu);
    mTitle->Pos(VEC2_ZERO);

    mInputMgr = InputManager::Instance();
    mAudioMgr = AudioManager::Instance();
}

void Menu::addOption(const char *title, int titleSize, SDL_Color hoverColor)
{

    Texture *newOption = new Texture(title, "Ka1.ttf", titleSize, {255, 255, 255, 255}, false);
    int GAP = Graphics::Instance()->GRID_GAP * 2;
    newOption->Parent(mMenu);
    int titleHeight;
    if (mTitle != nullptr)
        titleHeight = mTitle->getHeight() / 2;
    else
        titleHeight = 0;
    newOption->Pos(Vector2(0.0f, titleHeight + newOption->getHeight() / 2 + GAP + (newOption->getHeight() + optionsGap) * mOptions.size()));

    if (mOptions.size() == 0)
    {
        newOption->setTextureColor(hoverColor);
        newOption->Scale(Vector2(1.2f, 1.2f));
    }

    mOptions.push_back(std::make_pair(newOption, hoverColor));
}

Menu::~Menu()
{
    if (mTitle != nullptr)
        delete mTitle;
    mTitle = nullptr;

    mInputMgr = nullptr;

    mOptions.clear();
}

bool Menu::HandleInputs()
{
    if (mInputMgr->KeyPressed(SDL_SCANCODE_W))
    {
        changeSelecedOption(-1);
        return true;
    }
    else if (mInputMgr->KeyPressed(SDL_SCANCODE_S))
    {
        changeSelecedOption(1);
        return true;
    }
    return false;
}
void Menu::Update()
{

    if (HandleInputs())
    {
        mAudioMgr->PlaySFX("menuSelect.wav");
        for (int i = 0; i < mOptions.size(); ++i)
        {

            // clear title colors to white
            mOptions[i].first->setTextureColor({255, 255, 255});

            if (mOptions[i].first->Scale() != VEC2_ONE)
                // if scale has been changed return it to original
                mOptions[i].first->Scale(VEC2_ONE);
        }

        mOptions[mSelectedOption].first->setTextureColor(mOptions[mSelectedOption].second);
        mOptions[mSelectedOption].first->Scale(Vector2(1.2f, 1.2f));
    }
}
void Menu::changeSelecedOption(int change)
{

    mSelectedOption += change;
    int lastIndex = mOptions.size() - 1;
    if (mSelectedOption < 0)
        mSelectedOption = lastIndex;
    else if (mSelectedOption > lastIndex)
        mSelectedOption = 0;
}

int Menu::getSelectedOption()
{
    return mSelectedOption;
}

void Menu::Render()
{

    if (mTitle != nullptr)
        mTitle->Render();

    for (int i = 0; i < mOptions.size(); i++)
        mOptions[i].first->Render();
}
