#include <PA9.h>
#include "BrickGeneration.h"
#include "player.h"
#include "themes.h"
#include "item.h"



//Loads all the possible sprite positions
inline void PopulateBricksX(void){
	BrickSpeed=2;
	BrickDistance=36;
	MinBrick=1;
	s16 number;
	for(number=0;number<16;number++){
		BricksX[number]=number*16;
	}
}
//Finds free sprites and rows to use
inline s16 GetBrickNumber(){
   s16 i;
   for(i=MINBRICK;i<MAXBRICK;++i){
      if(Brick[i].Used==0){
         Brick[i].Used=1;
			return i;
		}			
   }
	return MINBRICK;
}
inline s16 GetFreeRow(){
   s16 i;
   for(i=0;i<512;++i){
      if(PlatForms.Used[i]==0){
         PlatForms.Used[i]=1;
			return i;
		}			
   }
	return 0;
}

//Frees a row of bricks
inline void FreeBrickRow(s16 rownumber){
	s8 sprite;
	for(sprite=0;sprite<17;++sprite){
		Brick[PlatForms.numbers[rownumber][sprite]].Used=0;
		PA_DualSetSpriteXY (PlatForms.numbers[rownumber][sprite],-32,-32);
		PlatForms.numbers[rownumber][sprite]=127;
	}
	PlatForms.Used[rownumber]=0;
}
//Creates a new row of bricks
bool BrickSlots[17];
void CreateBrickRow(s32 Y,s16 rownumber){
	s8 NumOfBricks=PA_RandMinMax (MinBrick,15);
	s8 Bricks;
	for(Bricks=0;Bricks<17;++Bricks)BrickSlots[Bricks]=0;
	for(Bricks=0;Bricks<NumOfBricks;++Bricks){
		s8 Slot=PA_RandMax (15);
		if(BrickSlots[Slot]==0){
			s8 number=GetBrickNumber();
			Brick[number].Y=Y;
			PA_DualCloneSprite (number,127);
			PA_DualSetSpriteXY (number,BricksX[Slot],Y);
			PA_DualSetSpritePrio (number,2);
			PlatForms.numbers[rownumber][Slot]=number;
			BrickSlots[Slot]=1;
		}
	}
	PlatForms.Y[rownumber]=Y;
	PlatForms.Count++;

}
//Scrolls a row of bricks
inline void ScrollRow(s16 rownumber,s8 Speed){	
	s8 sprite=0;
	for (sprite=0;sprite<17;++sprite){
		if(Brick[PlatForms.numbers[rownumber][sprite]].Used==1){
			Brick[PlatForms.numbers[rownumber][sprite]].Y-=Speed;
			PA_DualSetSpriteY(PlatForms.numbers[rownumber][sprite],Brick[PlatForms.numbers[rownumber][sprite]].Y);
		}
	}
	PlatForms.Y[rownumber]-=Speed;
}
//checks the point of a row to see if another row of bricks is needed to spawn
inline bool CheckRowSpawn(s16 Rownumber){
	if((PlatForms.Y[Rownumber]>=(384-BrickDistance-BrickSpeed))&&(PlatForms.Y[Rownumber]<=(384-BrickDistance-BrickSpeed)))return 1;
	return 0;
}
inline void DualCheckRowCollision(s16 rownumber){
	s16 sprite=0;
	if(PlatForms.Used[rownumber]==1){
		for (sprite=0;sprite<17;++sprite){
			if(Player.Y<192-8&&spritecollide(1,0,PlatForms.numbers[rownumber][sprite]))Player.Y=PlatForms.Y[rownumber]-12;
			else if(Player.Y>192-8&&spritecollide(0,0,PlatForms.numbers[rownumber][sprite]))Player.Y=PlatForms.Y[rownumber]-12;
		}
	}
}	
//Mass Scrolls PlatForms
void ScrollPlatforms(s8 Speed){
	s32 PlatForm;
	for(PlatForm=0;PlatForm<=511;PlatForm++){
		if(PlatForms.Used[PlatForm]==1){
			ScrollRow(PlatForm,Speed);
			if(PlatForms.Y[PlatForm]<=16)FreeBrickRow(PlatForm);
			DualCheckRowCollision(PlatForm);
			ItemCheckRowCollision(PlatForm);
			if(CheckRowSpawn(PlatForm))CreateBrickRow(384,GetFreeRow());
		}
	}
}
//loads Brick Graphics
inline void LoadBrickGraphics(void){
	PA_DualLoadSpritePal(0,(void*)brickpal);
	PA_DualCreateSprite(127,(void*)brickgfx,BrickSizeX,BrickSizeY,1, 0,-32, -32); 
	free(brickgfx);
}
