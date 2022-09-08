//16 bit scrollable bg!

#include <PA9.h>
#include <fat.h>
#include "gfx/all_gfx.h"
#include "gfx/all_gfx.c"

#define MINBRICK 1
#define MAXBRICK 127

typedef struct{
	s32 X,Y;
	bool Used;
}bricksinfo;
bricksinfo Brick[128];

typedef struct{
	s16 numbers[512][17];//stores sprite numbers in the platform
	bool Used[512];
	s32 Y[512];//y position of rows
	s32 Count;
}rowinfos;
rowinfos PlatForms;
s8 BrickSpeed=1;
s8 BrickDistance=36;//distance between each row of bricks
u16 BrickGfx;
//sets an X position for each brick slot, only needs to be called once
s16 BricksX[17];


inline void PopulateBricksX(void){
	s16 number;
	for(number=0;number<16;number++){
		BricksX[number]=number*16;
	}
}
inline s8 GetBrickNumber(){
   s8 i;
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
//creates a row of bricks
inline void FreeBrickRow(s16 rownumber){
	s8 sprite;
	for(sprite=0;sprite<17;++sprite){
		Brick[PlatForms.numbers[rownumber][sprite]].Used=0;
		PA_SetSpriteXY (0,PlatForms.numbers[rownumber][sprite],-32,-32);
		PlatForms.numbers[rownumber][sprite]=-1;
	}
	PlatForms.Used[rownumber]=0;
}
		
void CreateBrickRow(s32 Y,s16 rownumber){
	s8 NumOfBricks=PA_RandMinMax (1,15);
	bool BrickSlots[17];
	s8 Bricks;
	for(Bricks=0;Bricks<NumOfBricks;++Bricks){
		s8 Slot=PA_RandMax (15);
		if(BrickSlots[Slot]==0){
			s8 number=GetBrickNumber();
			Brick[number].Y=Y;
			PA_CreateSpriteFromGfx(0,number,BrickGfx,OBJ_SIZE_16X8, 1, 0,BricksX[Slot],Y);
			PlatForms.numbers[rownumber][Slot]=number;
			BrickSlots[Slot]=1;
			PA_OutputText(1,0,0,"Spritenum = %d ",number);
			PA_OutputText(1,0,1,"RowNumber = %d ",rownumber);
		}
	}
	PlatForms.Y[rownumber]=Y;
	PlatForms.Count++;

}	
inline void ScrollRow(s16 rownumber,s8 Speed){	
	s8 sprite=0;
	for (sprite=0;sprite<17;++sprite){
		if(Brick[PlatForms.numbers[rownumber][sprite]].Used==1){
			Brick[PlatForms.numbers[rownumber][sprite]].Y-=Speed;
			PA_SetSpriteY(0,PlatForms.numbers[rownumber][sprite],Brick[PlatForms.numbers[rownumber][sprite]].Y);
		}
	}
	PlatForms.Y[rownumber]-=Speed;
}

bool CheckRowSpawn(s16 Rownumber){
	if((PlatForms.Y[Rownumber]>=(192-BrickDistance))&&(PlatForms.Y[Rownumber]<=(192-BrickDistance)))return 1;
	return 0;
}
void ScrollPlatforms(s8 Speed){
	s32 PlatForm;
	for(PlatForm=0;PlatForm<=511;PlatForm++){
		if(PlatForms.Used[PlatForm]==1){
			ScrollRow(PlatForm,Speed);
			if(PlatForms.Y[PlatForm]<=-8)FreeBrickRow(PlatForm);
			if(CheckRowSpawn(PlatForm))CreateBrickRow(192,GetFreeRow());
		}
	}
}
		
int main(int argc, char ** argv){
	PA_Init();
	PA_InitVBL();
	PA_InitText(1,0);
	//fatInitDefault();
	
	PA_LoadSpritePal(0,0,(void*)brick_Pal);
	BrickGfx=PA_CreateGfx(0,(void*)brick_Sprite,OBJ_SIZE_16X8,1);
	
	PopulateBricksX();
	
	CreateBrickRow(192,GetFreeRow());
	while(1){
		
		ScrollPlatforms(BrickSpeed);
		if(Pad.Newpress.Up)BrickSpeed++;
		if(Pad.Newpress.Down)BrickSpeed--;
		PA_OutputText(1,0,5,"Brick Speed = %d ",BrickSpeed);
		PA_WaitForVBL();
	
	}

	return 0;

}
