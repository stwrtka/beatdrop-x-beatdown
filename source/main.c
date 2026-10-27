#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include "vshader_shbin.h"
#include "include.h"
#include "player.h"

//PLAYER//
Player player;

int main(int argc, char* argv[])
{
	gfxInitDefault();

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); 
	C2D_Init(4096); 
	C2D_Prepare();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	//RENDER TARGETS//
	PrintConsole bottomScreen;
	consoleInit(GFX_BOTTOM, &bottomScreen);

	//GAME LOGIC//
	bool startGame = false;

	//Player Inalization
	player.x = TOP_SCREEN_WIDTH/2;
	player.y = 3 * TOP_SCREEN_HEIGHT/4;
	player.health = PLAYER_MAX_HELATH;
	player.speed = PLAYER_SPEED;
	player.hit = false;
	player.onGround = true;
	player.vy = 0;

	C2D_SpriteSheet sheetPlayer = C2D_SpriteSheetLoad("sdmc:/temp_player.t3x"); //player sprite
	if(!sheetPlayer)
	{
		printf("Player sprite sheet couldnt load"); 
		return -1;
	}
	C2D_SpriteFromSheet(&player.sprite, sheetPlayer, 0);
	C2D_SpriteSetPos(&player.sprite, player.x, player.y);

	//TEMP BG
	C2D_Sprite backgroundSprite;
	C2D_SpriteSheet sheetBackground = C2D_SpriteSheetLoad("sdmc:/temp_bg.t3x"); //bg sprite
	if(!sheetBackground)
	{
		printf("BG sheet couldnt load"); 
		return -1;
	}
	C2D_SpriteFromSheet(&backgroundSprite, sheetBackground, 0);
	C2D_SpriteSetPos(&backgroundSprite, 0, 32);

	//temp platform
	C2D_Sprite platformSprite;
	C2D_SpriteSheet sheetPlatform = C2D_SpriteSheetLoad("sdmc:/temp_platform.t3x"); //bg sprite
	if(!sheetPlatform)
	{
		printf("Platform sheet couldnt load"); 
		return -1;
	}
	C2D_SpriteFromSheet(&platformSprite, sheetPlatform, 0);
	C2D_SpriteSetPos(&platformSprite, 0, 210);


	//GAME LOOP//
	consoleSelect(&bottomScreen);
	printf("\x1b[15;10HPress A to start...");
	//gfxFlushBuffers();
	//gfxSwapBuffers();

	while (aptMainLoop())
	{
		hidScanInput();
		u32 kHeld = hidKeysHeld();
		u32 kDown = hidKeysDown();

		if(!startGame)
		{
			if(kDown & KEY_A) {
				startGame = true;
				consoleClear();
			}
		}
		else
		{
			if (kHeld & KEY_START) {
				break;
			}
			playerUpdate(&player, kDown, kHeld, &platformSprite);

			//DRAWING
			//declare the target and then frame draw on 
        	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(top, C2D_Color32(255, 255, 255, 255));
			C2D_SceneBegin(top);
			C2D_DrawSprite(&backgroundSprite);
			C2D_DrawSprite(&platformSprite);
			C2D_DrawSprite(&player.sprite); 

			C3D_FrameEnd(0);
		}

	}

	//DEINITIALIZE GRAPHICS//
	C2D_Fini();
	C3D_Fini(); //for graphics
	gfxExit();
	return 0;
}
