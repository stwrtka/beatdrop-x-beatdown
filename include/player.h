#ifndef PLAYER_H
#define  PLAYER_H

#include <stdbool.h>
#include <3ds.h>
#include <citro2d.h>

#define PLAYER_MAX_HELATH 50
#define PLAYER_SPEED 5
#define PLAYER_SCREEN_BOUND -7
#define PLAYER_SAFE 60
#define PLAYER_ATTACK_COOLDOWN 20

typedef struct Player
{
   	float speed;
   	int health;
   	bool hit;
	float x, y;
	float vy;
	bool onGround;
	C2D_Sprite sprite;
} Player;

void updatePlayer (Player p, int key);

void playerMoveX(Player *p, u32 kDown, u32 kheld);
void  playerMoveY(Player *p, u32 kDown, u32 kheld); //needs jump logic
void playerUpdate(Player *p, u32 kDown, u32 kHeld, C2D_Sprite *plat);//updates player's postion
bool playerHits(Player *p, C2D_Sprite *plat);

#endif