#ifndef DRAW_BUTTON_HANDLER_H
#define DRAW_BUTTON_HANDLER_H

#include <genesis.h>
#include "commonStructHandler.h"

void drawFillBox(Vec2 position, SizeBox fillSize, u16 fillTile);
void drawTextTiles(Vec2 position, u16 tiles[], u16 tilesSize);
void drawTile(Vec2 position, u16 tile);
void drawVerticalScroll(Vec2 upPosition, Vec2 downPosition, CursorTiles tilesData);
void drawBorder(Vec2 position, SizeBox size, BorderTiles tilesData);
void drawButtonShape(u16 x, u16 y, int buttonType);


#endif
