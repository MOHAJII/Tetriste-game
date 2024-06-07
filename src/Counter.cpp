#include "Counter.h"
#include <iostream>
Counter::Counter(std::string label, int fontSize)
{
    mFontSize = fontSize;

    mValueLabel = new Texture(label + " :", "Venite.ttf", fontSize, {255, 255, 255, 255});
    mValueLabel->Parent(this);
    mValueLabel->Pos(Vector2(mValueLabel->getWidth() / 2, 0.0f));

    setValue(0);
}

Counter::Counter(std::string label, int value, int fontSize)
{
    mFontSize = fontSize;
    mCurrentValue = value;
    mValueLabel = new Texture(label + " :", "Venite.ttf", fontSize, {255, 255, 255, 255});
    mValueLabel->Parent(this);
    mValueLabel->Pos(Vector2(mValueLabel->getWidth() / 2, 0.0f));

    setValue(value);
}

Counter::~Counter()
{
    ClearCount();
    for (int i = 0; i < mValue.size(); ++i)
    {
        delete mValue[i];
    }
    delete mValueLabel;
    mValueLabel = nullptr;
}

void Counter::setValue(int value)
{

    mCurrentValue = value;
    ClearCount();
    if (value == 0)
    {

        for (int i = 0; i < 2; ++i)
        {
            mValue.push_back(new Texture("0", "Venite.ttf", mFontSize, {230, 230, 230}));
            mValue[i]->Parent(this);
            mValue[i]->Pos(Vector2(190 + (-mFontSize + 4) * (i - 1), 0.0f));
        }
    }
    else
    {
        std::string str = std::to_string(value);
        int lastIndex = str.length() - 1;
        for (int i = 0; i <= lastIndex; ++i)
        {
            mValue.push_back(new Texture(str.substr(i, 1), "Venite.ttf", mFontSize, {230, 230, 230}));
            mValue[i]->Parent(this);
            mValue[i]->Pos(Vector2(190 + (-mFontSize + 4) * (lastIndex - i - 1), 0.0f));
        }
    }
}
int Counter::getValue() { return mCurrentValue; }

void Counter::incrementValue(int addedValue)
{
    mCurrentValue += addedValue;
    if (mCurrentValue < 0)
        return;
    setValue(mCurrentValue);
}

void Counter::ClearCount()
{
    for (int i = 0; i < mValue.size(); ++i)
    {
        delete mValue[i];
        mValue[i] = nullptr;
    }
    mValue.clear();
}

int Counter::getLabelWidth()
{
    return mValueLabel->getWidth();
}
int Counter::getLabelHeight()
{
    return mValueLabel->getHeight();
}

void Counter::Render()
{
    mValueLabel->Render();
    for (int i = 0; i < mValue.size(); ++i)
        mValue[i]->Render();
}
