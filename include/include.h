#ifndef INCLUDE_H
#define  INCLUDE_H

#include <3ds.h>
#include <citro2d.h>
#include <stdbool.h>

//Screen dimensions
#define TOP_SCREEN_WIDTH   400
#define TOP_SCREEN_HEIGHT  240

bool checkCollision(float ax, float ay, C2D_Sprite *aSpr, float bx, float by, C2D_Sprite *bSpr);

#endif