#include <PA9.h>
#include "menus.h"
#include "title1.h"
#include "player.h"
#include "item.h"
FILE *savefile;
void DisplayHighScores(bool screen,s8 yoffset){
	s8 i;
	PA_OutputText(screen,8,yoffset,"High Scores");
	for(i=0;i<10;i++){
		PA_OutputText(screen,8,i+yoffset+2,"%02d.%s-%d",i+1,High[i].Name,High[i].Score);
	}
}
void PreGameMenu(void){
	bool runmenu=1;
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	PA_Init8bitBg(1, 3); 	// Init a 8 bit Bg on screen 1	
	PA_InitText(0,0);
	
	PA_LoadGif(	1,(void*)title1);
	PA_OutputText(0,0,0,"Coded by BassAceGold");
	PA_OutputText(0,0,1,"Title GFX by Eponasoft");
	PA_OutputText(0,5,6,"Press anykey to play");
	
	savefile = fopen("/DownFall/downfall.bin", "rb");	
	if(savefile){
		fread((void*)&High, sizeof(High), 1, savefile);	
		PA_WaitForVBL();
		fclose(savefile);
	}
	else{
		savefile=fopen("/DownFall/downfall.bin", "wb");	
		fwrite(&High, sizeof(High), 1, savefile);
		PA_WaitForVBL();
		fclose(savefile);
	}

	DisplayHighScores(0,10);

	
	while(runmenu==1){
		if(Pad.Newpress.Anykey || Stylus.Newpress)runmenu=0;
		PA_WaitForVBL();
	}
}
s8 CheckScorePosition(void){
	s8 position,place=0;
	for(position=0;position<10;position++){
		if(Score<High[position].Score)place++;
	}
	return place;
}
void ShiftScoresDown(s8 Place){
	s8 position;
	int tempscore[10];
	char tempname[10][32];
	for(position=Place;position<10;position++){
		tempscore[position]=High[position].Score;
		PA_CopyText(tempname[position],High[position].Name);
	}
	for(position=Place;position<10;position++){
		High[position].Score=tempscore[position-1];
		PA_CopyText(High[position].Name,tempname[position-1]);
	}
}


void SaveHighScore(void){
	bool saving=1;
	PA_ResetBgSys();
	PA_WaitForVBL();
	PA_InitText(1,0);
	PA_InitKeyboard(3);
	PA_KeyboardIn(20, 95);
	savefile = fopen("/DownFall/downfall.bin", "rb");	
	if(savefile){
		fread((void*)&High, sizeof(High), 1, savefile);	
		PA_WaitForVBL();
		fclose(savefile);
	}	
	
	s8 Position=CheckScorePosition();
	ShiftScoresDown(Position);
	DisplayHighScores(1,1);
	
	
	PA_OutputText(1, 2, Position+3,"You->"); // Write the text
	
	PA_OutputText(1, 11, Position+3,"                      ");//clears line
	s32 nletter = 0; // Next letter to right. 0 since no letters are there yet
	char letter = 0; // New letter to write.
	char text[25];
	s8 num=0;
	for(num=0;num<8;num++)text[num]=' ';
	while(saving==1){
		letter = PA_CheckKeyboard();
		if(nletter<8){
			if (letter > 31) { // there is a new letter
				text[nletter] = letter;
				nletter++;
			}
		}
		if ((letter == PA_BACKSPACE)&&nletter) { // Backspace pressed
			nletter--;
			text[nletter] = ' '; // Erase the last letter
		}
		else if (letter == '\n'){ // Enter pressed
			PA_CopyText(High[Position].Name,text);
			High[Position].Score=Score;
			savefile=fopen("/DownFall/downfall.bin", "wb");	
			fwrite(&High, sizeof(High), 1, savefile);
			PA_WaitForVBL();
			fclose(savefile);
			saving=0;
			RunGame();
		}	
		PA_OutputText(1, 11, Position+3,"%s-%d ",text,Score); // Write the text
		PA_WaitForVBL();
	}
}
		
void GameOver(void){
	bool GameOver=1;
	PA_ResetBgSys();
	PA_ResetSpriteSys();
	DestroyItem();
	PA_InitText(1,0);
	PA_InitText(0,0);
	s8 NewScore=CheckScorePosition();
	if(NewScore!= -2 && NewScore!=-1){
		PA_OutputText(1,9,8,"New High Score!");
		PA_OutputText(0,4,6,"Press Start to save Score");
		PA_OutputText(0,15,8,"Or");
	}	
	PA_OutputText(1,3,10,"Game Over- Your Score:%d ", Score);
	
	PA_OutputText(0,4,10,"Press A To play again");
	while(GameOver==1){
		if(Pad.Newpress.A){
			GameOver=0;
			RunGame();
		}
		if(Pad.Newpress.Start){
			GameOver=0;
			SaveHighScore();
		}
		PA_WaitForVBL();
	}
}
