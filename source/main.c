#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include "vshader_shbin.h"
#include "include.h"

int main(int argc, char* argv[])
{
	gfxInitDefault();

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE); 
	C2D_Init(4096); 
	C2D_Prepare();
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	//render targets
	PrintConsole bottomScreen;
	consoleInit(GFX_BOTTOM, &bottomScreen);
	
	//deinitialize graphics
	C3D_Fini(); //for graphics
	gfxExit();
	return 0;
}
