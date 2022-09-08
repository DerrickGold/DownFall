#ifndef _themestuff_h_
#define _themestuff_h_

//holds folder names
typedef struct{
	char foldername[256];
}folderinfos;
folderinfos BAG_Folders[256];//store max 256 folders
char filename[256]; // temp storage of file name
char *ScoreBarBuf;
u8 *brickgfx;
u16 brickpal[256]; 

s16 NumOfThemes;

s8 BrickSizeX;
s8 BrickSizeY;

s16 TextX,TextY;

s8 Red,Green,Blue;
s8 FontSize;

void LoadRandomTheme(void);
void CountThemes(void);
void FatLoadBmp(bool Screen, char* file);
void LoadTheme(s32 themeNum);
void UpdateScoreBar(void);
#endif
