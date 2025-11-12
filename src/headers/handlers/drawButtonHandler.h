#ifndef DRAW_BUTTON_HANDLER_H
#define DRAW_BUTTON_HANDLER_H

#include <genesis.h>
#include "commonStructHandler.h"

void drawTiles(Vec2 position, u16 tiles[]);
void drawTile(Vec2 position, u16 tile);
void drawVerticalScroll(Vec2 upPosition, Vec2 downPosition, CursorTiles tilesData);
void drawBorder(Vec2 position, SizeBox size, BorderTiles tilesData);
void drawButtonShape(u16 x, u16 y, int buttonType);


#endif
