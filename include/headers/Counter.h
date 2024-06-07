//--------------------------------------------------------------//
// Counter.h //
// Represents a value that can be modified along with a label //
//--------------------------------------------------------------//

#pragma once
#include "Texture.h"
#include <vector>
using namespace QuickSDL;

class Counter : public GameEntity
{
private:
    std::vector<Texture *> mValue;
    int mFontSize, mCurrentValue, mLabelWidth, mLabelHeight;
    Texture *mValueLabel;

public:
    Counter(std::string, int fontSize = 32);
    Counter(std::string, int count, int fontSize);

    ~Counter();

    int getLabelWidth();
    int getLabelHeight();

    void setValue(int);
    int getValue();

    void incrementValue(int);
    void Render();

private:
    void ClearCount();
};