#include "Label.h"

Label::Label(uint16_t _posX, uint16_t _posY, uint8_t _zDepth, char * _label)
{
    posX = _posX;
    posY = _posY;
    zDepth = _zDepth;

    label = _label;

    textColor = LABEL_TEXT_COLOR;

    hasTouchEventCallback = false;
    invalid = true;
}

void Label::initialize(void)
{
    width = strlen(label)*guiController->screen->fontSizeX();
    height = guiController->screen->fontSizeY();
}

bool Label::checkBounds(uint16_t touchX, uint16_t touchY)
{
    if
    (
        (touchX >= posX) && (touchX <= (posX + width)) &&
        (touchY >= posY) && (touchY <= (posY + height))
    )
    {
        return true;
    }
    return false;
}

void Label::injectTouch(uint16_t touchX, uint16_t touchY, TouchType_e touchType)
{
    GUIElement::injectTouch(touchX, touchY, touchType);

    if(hasTouchEventCallback)
        onTouchCallback();
}

void Label::draw(bool clearBeforeDraw)
{
    if(clearBeforeDraw)
    {
        guiController->screen->setPenSolid();
        guiController->screen->dRectangle(posX, posY, width, height, LABEL_BACKGROUND_COLOR);
        guiController->screen->setPenSolid(false);
    }

    guiController->screen->gText(posX, posY, label, textColor);

    invalid = false;
}

void Label::registerTouchEventCallback(void (*_onTouchCallback)(void))
{
    hasTouchEventCallback = true;
    onTouchCallback = _onTouchCallback;
}

void Label::setText(char * _label)
{
    invalid = true;

    label = _label;

    initialize();
}

uint16_t Label::getWidth(void)
{
    return width;
}

uint16_t Label::getHeight(void)
{
    return height;
}

uint16_t Label::getPosX(void)
{
    return posX;
}

uint16_t Label::getPosY(void)
{
    return posY;
}

void Label::setColor(uint16_t _color)
{
    invalid = true;
    textColor = _color;
}