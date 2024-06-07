#include "Shape.h"

Shape::Shape(ShapeType type, ShapeColor color) : mType(type), mColor(color)
{
    mShape = new Texture(InitType(type), false);
    mShape->Parent(this);
    mShape->Pos(VEC2_ZERO);
    InitColor(color);
    mWidth = mShape->getWidth();
    mHeight = mShape->getHeight();
}

Shape::Shape(int width, int height, ShapeType type, ShapeColor color) : mType(type), mColor(color), mWidth(width), mHeight(height)
{
    mShape = new Texture(InitType(type), 0, 0, width, height);
    mShape->Parent(this);
    mShape->Pos(VEC2_ZERO);
    InitColor(color);
}

Shape::~Shape()
{
    delete mShape;
    mShape = nullptr;
}

void Shape::InitColor(ShapeColor color)
{
    SDL_Color sdl_color;
    switch (color)
    {
    case RED:
        sdl_color = {242, 72, 34}; // Red color
        break;
    case GREEN:
        sdl_color = {20, 174, 92}; // Green color
        break;
    case YELLOW:
        sdl_color = {255, 205, 41}; // Yellow color
        break;
    case PURPLE:
        sdl_color = {151, 71, 255}; // Purple color
        break;
    case BLACK:
        sdl_color = {80, 80, 80}; // Black color
        break;
    case BLUE:
        sdl_color = {41, 128, 185}; // Blue color
        break;
    case ORANGE:
        sdl_color = {255, 153, 51}; // Orange color
        break;
    default:
        sdl_color = {255, 255, 255}; // Default color
        break;
    }

    mShape->setTextureColor(sdl_color);
}
std::string Shape::InitType(ShapeType type) const
{
    switch (type)
    {
    case SQUARE:
        return "square.png";
        break;
    case CERCLE:
        return "cercle.png";
        break;
    case RHOMBUS:
        return "rhombus.png";
        break;
    case TRIANGLE:
        return "triangle.png";
        break;
    case KITE:
        return "kite.png";
        break;
    case RHOMBOID:
        return "rhomboid.png";
        break;
    case HEXAGON:
        return "hexagon.png";
        break;
    case PENTAGON:
        return "PENTAGON.png";
        break;
    case STAR:
        return "star.png";
        break;
    case STARBURST:
        return "starburst.png";
        break;
    default:
        return "null";
        break;
    }
}

ShapeColor Shape::getShapeColor()
{
    return mColor;
}
ShapeType Shape::getShapeType()
{
    return mType;
}
int Shape::getWidth()
{
    return mShape->getWidth();
}

int Shape::getHeight()
{
    return mShape->getHeight();
}
void Shape::Render()
{

    mShape->Render();
}

void Shape::Update()
{
}

bool operator==(const Shape &shape1, const Shape &shape2)
{
    return shape1.mColor == shape2.mColor && shape1.mType == shape2.mType;
}

std::ostream &operator<<(std::ostream &output, const Shape &obj)
{
    std::string color;
    switch (obj.mColor)
    {
    case 0:
        color = "RED";
        break;
    case 1:
        color = "YELLOW";
        break;
    case 2:
        color = "GREEN";
        break;
    case 3:
        color = "PURPLE";
        break;
    default:
        color = "";
        break;
    }
    output << "{" << obj.InitType(obj.mType) << " " << color << "}";
    return output;
}
