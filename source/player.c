#include "player.h"
#include "include.h"
#include <3ds.h>
#include <citro2d.h>

#define GRAVITY    0.4f
#define JUMP_SPEED -7.0f
#define MAX_FALL   8.0f

bool playerHits(Player *p, C2D_Sprite *plat)
{
    return checkCollision(p->x, p->y, &p->sprite, plat->params.pos.x, plat->params.pos.y, plat);
}

void playerUpdate(Player *p, u32 kDown, u32 kHeld, C2D_Sprite *plat)
{
    float pw = p->sprite.image.subtex->width;
    float ph = p->sprite.image.subtex->height;
    float bx = plat->params.pos.x;
    float by = plat->params.pos.y;
    float bw = plat->image.subtex->width;
    float bh = plat->image.subtex->height;

    float dx = 0;
    if (kHeld & KEY_LEFT)       
        dx = -p->speed;
    else if (kHeld & KEY_RIGHT) 
        dx =  p->speed;

    p->x += dx;
    if(p->x <0)
        p->x = 0;

    if(p->x + pw > TOP_SCREEN_WIDTH )
        p->x = TOP_SCREEN_WIDTH - pw;

    if (playerHits(p, plat))
    {
        if (dx > 0)     
            p->x = bx - pw;   //right
        else if (dx < 0) 
            p->x = bx + bw;   //left
    }

    if ((kDown & KEY_B) && p->onGround)    // jump
        p->vy = JUMP_SPEED;

    p->vy += GRAVITY;
    if (p->vy > MAX_FALL) p->vy = MAX_FALL;

    p->y += p->vy;
    p->onGround = false;

    if (playerHits(p, plat))
    {
        if (p->vy > 0)          
        {
            p->y = by - ph;     
            p->vy = 0;
            p->onGround = true;
        }
        else if (p->vy < 0) 
        {
            p->y = by + bh;
            p->vy = 0;
        }
    }
    if (p->y + ph > TOP_SCREEN_HEIGHT)
    {
        p->y = TOP_SCREEN_HEIGHT - ph;
        p->vy = 0;
        p->onGround = true;
    }

    C2D_SpriteSetPos(&p->sprite, p->x, p->y);
}