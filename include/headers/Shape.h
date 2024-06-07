
//---------------------------------------------------------------------//
// Shape.h //
// Represents the shapes used in the game
//---------------------------------------------------------------------//

#pragma once

#include <time.h>
#include <cstdlib>
#include <iostream>
#include "Texture.h"

using namespace QuickSDL;

enum ShapeColor
{
    RED,
    YELLOW,
    GREEN,
    PURPLE,
    BLACK,
    BLUE,
    ORANGE
};
enum ShapeType
{
    SQUARE,
    CERCLE,
    TRIANGLE,
    RHOMBUS,
    KITE,
    RHOMBOID,
    HEXAGON,
    PENTAGON,
    STAR,
    STARBURST
};
class Shape : public GameEntity
{

private:
    int mWidth, mHeight;
    Texture *mShape;
    ShapeType mType;
    ShapeColor mColor;

public:
    ShapeColor getShapeColor();
    ShapeType getShapeType();

private:
    std::string InitType(ShapeType) const;
    void InitColor(ShapeColor);

public:
    Shape(ShapeType, ShapeColor);
    Shape(int, int, ShapeType, ShapeColor);
    ~Shape();
    void Render();
    void Update();
    int getHeight();
    int getWidth();
    friend bool operator==(const Shape &, const Shape &);
    friend std::ostream &operator<<(std::ostream &, const Shape &);
};