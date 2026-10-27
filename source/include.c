#include "include.h"
#include <stdbool.h>

bool checkCollision(float ax, float ay, C2D_Sprite *aSpr, float bx, float by, C2D_Sprite *bSpr){
	float aw = aSpr->image.subtex->width;
	float ah = aSpr->image.subtex->height;
	float bw = bSpr->image.subtex->width;
	float bh = bSpr->image.subtex->height;

	return (ax < bx + bw) && (ax + aw > bx) && (ay < by + bh) && (ay + ah > by);
}
