//16 bit scrollable bg!

#include <PA9.h>
#include "BrickGeneration.h"
#include "player.h"
#include <fat.h>
#include "themes.h"
#include "efs_lib.h"
#include "music.h"
#include "menus.h"
#include "item.h"


void GameOver(void);
int main(int argc, char ** argv){
	PA_Init();
	PA_InitVBL();
	//fatInitDefault();
	EFS_Init(EFS_AND_FAT | EFS_DEFAULT_DEVICE, NULL);
	InitAudio();
	
	PreGameMenu();
	CountThemes();
	RunGame();

	while(1){
	

	}
	return 0;

}
void RunGame(void){
	bool game=1;
	Score=0;
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	PA_Init16bitBg (0,3);
	PA_Init16bitBg (1,3);
	LoadRandomTheme();
	PopulateBricksX();
	LoadBrickGraphics();
	Player.Speed=3;
	LoadPlayer();
	CreateItemSprite();
	CheckMusic();
	
	s8 times;
	for(times=0;times<17;++times)FreeBrickRow(times);
	if(DUALSCREEN==0)CreateBrickRow(192,GetFreeRow());
	else {
		PA_SetScreenSpace (0);
		CreateBrickRow(384,GetFreeRow());
	}
	while(game==1){
		
		ScrollPlatforms(BrickSpeed);
		if(Score%300==0){
			if(MinBrick<14)MinBrick++;
			if(BrickDistance>28)BrickDistance-=2;
			//if(BrickDistance==30)BrickSpeed++;
		}
		if(Player.Y<=16){
			game=0;
			GameOver();
		}
		CheckMusic();
		UpdateItems();
		PlayerMovement();
		UpdateScoreBar();
		PA_WaitForVBL();
	}

}	

	
	
