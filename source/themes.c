#include <PA9.h>
#include "themes.h"
#include "INIParsing.h"
#include "player.h"
#include "item.h"
#include <fat.h>
#include <sys/dir.h>
//Scans for all folders within a directory
s16 CollectFolders(DIR_ITER* dir ){
	s16 foldernum =0; 
	struct stat st;
	if (dir == NULL) 
	{
		PA_OutputText(1,2,2,"Unable to open the directory.");
	} 
	else 
	while (dirnext(dir, filename, &st) == 0) 
	{
		char *temp;
		temp = strchr(filename,'.');
		if(temp==NULL){
			if(st.st_mode & S_IFDIR){//is folder
				strncpy (BAG_Folders[foldernum].foldername,filename,sizeof(filename));
				foldernum++;
			}
		}
	}
	return foldernum;
}

void FatLoadBmp(bool Screen, char* file){
	FILE* bmpFile = fopen (file, "rb"); //rb = read
	if(bmpFile){
		u32 bmpSize;
		fseek (bmpFile, 0 , SEEK_END);
		bmpSize = ftell (bmpFile);
		rewind (bmpFile);
		char * buffer;
		buffer = (char*) malloc (sizeof(char)*bmpSize);
		fread (buffer, 1, bmpSize, bmpFile);
		fclose (bmpFile);
		PA_LoadBmpEx (Screen,0,0, (void *)buffer);
		free(buffer);
	}	
}
void FatLoadScoreBar(bool Screen, char* file){
	FILE* bmpFile = fopen (file, "rb"); //rb = read
	if(bmpFile){
		u32 bmpSize;
		fseek (bmpFile, 0 , SEEK_END);
		bmpSize = ftell (bmpFile);
		rewind (bmpFile);
		ScoreBarBuf = (char*) malloc (sizeof(char)*bmpSize);
		fread (ScoreBarBuf, 1, bmpSize, bmpFile);
		fclose (bmpFile);
		PA_LoadBmpEx (Screen,0,0, (void *)ScoreBarBuf);
	}	
}
void FatLoadSprite(char *file, s8 sprite){
	FILE* gifFile = fopen (file, "rb"); //rb = read
	if(gifFile){
		u32 gifSize;
		fseek (gifFile, 0 , SEEK_END);
		gifSize = ftell (gifFile);
		rewind (gifFile);
		char * buffer;
		buffer = (char*) malloc (sizeof(char)*gifSize);
		fread (buffer, 1, gifSize, gifFile);
		fclose (gifFile);
		if(sprite==0){
			PA_GifToTexTransp(PA_RGB(31, 0, 31)); 
			spritegfx = PA_GifToTiles((void*)buffer,spritepal); // our palette
		}
		else if(sprite==1) {
			PA_GifToTexTransp(PA_RGB(31, 0, 31)); 
			brickgfx = PA_GifToTiles((void*)buffer,brickpal); // our palette
		}
		else if(sprite==2){
			PA_GifToTexTransp(PA_RGB(31, 0, 31)); 
			itemgfx = PA_GifToTiles((void*)buffer,itempal); // our palette			
		}
	}
}	
s8 ReturnSize(s8 size){
	if(size==8)return 0;
	if(size==16)return 1;
	return 0;
}
void CountThemes(void){
	DIR_ITER* dir = diropen("/DownFall/Themes/");
	NumOfThemes=CollectFolders(dir);
}
void LoadTheme(s32 themeNum){
	char temp[512];
	sprintf(temp,"/DownFall/Themes/%s/pictop.bmp",BAG_Folders[themeNum].foldername);
	FatLoadBmp(1,temp);
	sprintf(temp,"/DownFall/Themes/%s/picbottom.bmp",BAG_Folders[themeNum].foldername);
	FatLoadBmp(0,temp);
	sprintf(temp,"/DownFall/Themes/%s/scorebar.bmp",BAG_Folders[themeNum].foldername);
	FatLoadScoreBar(1,temp);
	sprintf(temp,"/DownFall/Themes/%s/character.gif",BAG_Folders[themeNum].foldername);
	FatLoadSprite(temp,0);
	sprintf(temp,"/DownFall/Themes/%s/brick.gif",BAG_Folders[themeNum].foldername);
	FatLoadSprite(temp,1);
	sprintf(temp,"/DownFall/Themes/%s/item.gif",BAG_Folders[themeNum].foldername);
	FatLoadSprite(temp,2);
	sprintf(temp,"/DownFall/Themes/%s/theme.ini",BAG_Folders[themeNum].foldername);
	Red=readIniFileInt(temp,"Red");
	Green=readIniFileInt(temp,"Green");
	Blue=readIniFileInt(temp,"Blue");
	FontSize=readIniFileInt(temp,"Size");
	TextX=readIniFileInt(temp,"TextX");
	TextY=readIniFileInt(temp,"TextY");	
	//grabs sprite sizes
	//Bricks
	s8 tempX=readIniFileInt(temp,"BrickWidth");
	s8 tempY=readIniFileInt(temp,"BrickHeight");
	if(tempX==16 && tempY==16){//16X16
		BrickSizeX=0;
		BrickSizeY=1;
	}
	else{//8X8
		BrickSizeX=1;
		BrickSizeY=0;	
	}
	//Player
	tempX=readIniFileInt(temp,"PlayerWidth");
	tempY=readIniFileInt(temp,"PlayerHeight");	
	if(tempX==16 && tempY==16){	
		PlayerSizeX=0;
		PlayerSizeY=1;
	}
	else {
		PlayerSizeX=0;
		PlayerSizeY=0;	
	}

}
void LoadRandomTheme(void){
	s16 random=PA_RandMax(NumOfThemes-1);
	LoadTheme(random);
}
void UpdateScoreBar(void){
	Score++;
	char Scorebuf[256];
	PA_LoadBmpEx (1,0,0, (void *)ScoreBarBuf);
	sprintf(Scorebuf, "%d       ",Score);
	PA_16bitText(1,TextX,TextY,256,16,Scorebuf,PA_RGB(Red,Green,Blue),FontSize,1,100);
}

	
