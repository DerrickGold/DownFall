#ifndef _brickstuff_h_
#define _brickstuff_h_

#define MINBRICK 2
#define MAXBRICK 126

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




s8 BrickSpeed;
s8 MinBrick;
s8 BrickDistance;//distance between each row of bricks
u16 BrickGfx;
//sets an X position for each brick slot, only needs to be called once
s16 BricksX[17];

void ScrollPlatforms(s8 Speed);
void LoadBrickGraphics(void);
void PopulateBricksX(void);
void FreeBrickRow(s16 rownumber);
void CreateBrickRow(s32 Y,s16 rownumber);
s16 GetFreeRow();
#endif 

