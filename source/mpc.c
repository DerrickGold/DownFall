#include <PA9.h>
#include "mpc.h"

u16 NumToNote(u8 number){
	switch(number){	
		case 1:return 35002;break;
		case 2:return 37083;break;
		case 3:return 39288;break;
		case 4:return 41624;break;
		case 5:return 44100;break;
		case 6:return 49500;break;
		case 7:return 52444;break;
		case 8:return 55562;break;
		case 9:return 58866;break;
		case 10:return 46722;break;
		case 11:return 49500;break;
		case 12:return 52444;break;
		case 13:return 55562;break;
		case 14:return 58866;break;
		case 15:return 62366;break;
		case 16:return 33037;break;
		case 17:return 35002;break;
		case 18:return 37083;break;
		case 19:return 39288;break;
		case 20:return 41624;break;
		case 21:return 44100;break;
		case 22:return 46722;break;
		case 23:return 29433;break;
		case 24:return 46722;break;
		case 25:return 49500;break;
		case 26:return 52444;break;
		case 27:return 55562;break;
		case 28:return 58866;break;
		case 29:return 27781;break;
	}
	return 0;	
}
void PickSoundFile(int note, int page){
	switch(Sprite[page][note].SoundFile){
		
		case 0:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(mario1);break;
				case 1: MPCchan = AS_SoundQuickPlay(mario2);break;
				case 2: MPCchan = AS_SoundQuickPlay(mario3);break;
			}
		break;
		case 1:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(mushroom1);break;
				case 1: MPCchan = AS_SoundQuickPlay(mushroom2);break;
				case 2: MPCchan = AS_SoundQuickPlay(mushroom3);break;
			}
		break;
		case 2:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(yoshi1);break;
				case 1: MPCchan = AS_SoundQuickPlay(yoshi2);break;
				case 2: MPCchan = AS_SoundQuickPlay(yoshi3);break;
			}
		break;
		case 3:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(star1);break;
				case 1: MPCchan = AS_SoundQuickPlay(star2);break;
				case 2: MPCchan = AS_SoundQuickPlay(star3);break;
			}
		break;
		case 4:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(flower1);break;
				case 1: MPCchan = AS_SoundQuickPlay(flower2);break;
				case 2: MPCchan = AS_SoundQuickPlay(flower3);break;
			}
		break;
		case 5:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(gameboy1);break;
				case 1: MPCchan = AS_SoundQuickPlay(gameboy2);break;
				case 2: MPCchan = AS_SoundQuickPlay(gameboy3);break;
			}
		break;
		case 6:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(dog1);break;
				case 1: MPCchan = AS_SoundQuickPlay(dog2);break;
				case 2: MPCchan = AS_SoundQuickPlay(dog3);break;
			}
		break;
		case 7:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(cat1);break;
				case 1: MPCchan = AS_SoundQuickPlay(cat2);break;
				case 2: MPCchan = AS_SoundQuickPlay(cat3);break;
			}
		break;
		case 8:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(pig1);break;
				case 1: MPCchan = AS_SoundQuickPlay(pig2);break;
				case 2: MPCchan = AS_SoundQuickPlay(pig3);break;
			}
		break;
		case 9:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(swan1);break;
				case 1: MPCchan = AS_SoundQuickPlay(swan2);break;
				case 2: MPCchan = AS_SoundQuickPlay(swan3);break;
			}
		break;
		case 10:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(face1);break;
				case 1: MPCchan = AS_SoundQuickPlay(face2);break;
				case 2: MPCchan = AS_SoundQuickPlay(face3);break;
			}
		break;
		case 11:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(plane1);break;
				case 1: MPCchan = AS_SoundQuickPlay(plane2);break;
				case 2: MPCchan = AS_SoundQuickPlay(plane3);break;
			}
		break;
		case 12:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(boat1);break;
				case 1: MPCchan = AS_SoundQuickPlay(boat2);break;
				case 2: MPCchan = AS_SoundQuickPlay(boat3);break;
			}
		break;
		case 13:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(car1);break;
				case 1: MPCchan = AS_SoundQuickPlay(car2);break;
				case 2: MPCchan = AS_SoundQuickPlay(car3);break;
			}
		break;
		case 14:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(heart1);break;
				case 1: MPCchan = AS_SoundQuickPlay(heart2);break;
				case 2: MPCchan = AS_SoundQuickPlay(heart3);break;
			}
		break;
		case 15:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(bowser1);break;
				case 1: MPCchan = AS_SoundQuickPlay(bowser2);break;
				case 12: MPCchan = AS_SoundQuickPlay(bowser3);break;
			}
		break;
		case 16:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(umbrella1);break;
				case 1: MPCchan = AS_SoundQuickPlay(umbrella2);break;
				case 2: MPCchan = AS_SoundQuickPlay(umbrella3);break;
			}
		break;
		case 17:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(orchestral1);break;
				case 1: MPCchan = AS_SoundQuickPlay(orchestral2);break;
				case 2: MPCchan = AS_SoundQuickPlay(orchestral3);break;
			}
		break;
		case 18:
			switch(Sprite[page][note].Pitch){
				case 0:MPCchan = AS_SoundQuickPlay(harp1);break;
				case 1: MPCchan = AS_SoundQuickPlay(harp2);break;
				case 2: MPCchan = AS_SoundQuickPlay(harp3);break;
			}
		break;
	}
}

u16 FindLastPage(void){
	u16 temppage;
	u8 sprite=0;
	u8 count=0;
	u8 pagecount=0;
	for(temppage=0;temppage<256;++temppage){
		count=0;
		for(sprite=0;sprite<29;++sprite){
			if(Sprite[temppage][sprite].used==0)count++;
			if(count==29){
				pagecount++;
			}
		}
		if(count<29)pagecount=0;
		if(temppage>=256&&pagecount<5)return 256;
		if(pagecount==5)return temppage-5;
	}
	return 0;
}


inline bool LoadMPCFile(char *file){
	FILE* MPCfile = fopen(file, "rb");
	if(MPCfile){
		fread((void*)&Sprite,1,sizeof(Sprite),MPCfile);	//Copy the notes
		fread((void*)&Tempo,1, sizeof(Tempo), MPCfile);	// Copy temp
		//fread((void*)&Original,1, sizeof(Original), MPCfile);	// checks if file is already authorized
		//fread((void*)&Author,1, sizeof(Author), MPCfile);	// checks if file is already authorized
		
		fclose(MPCfile);
		return true;
	} else {
		return false;
	}
}

void PlayMPC(void){
	Page=0;
	EndPage=FindLastPage();
	Play=1;
	NoteBar=0.0;
	
}
void StopMPC(void){
	Play=0;
	s8 chan;
	for(chan=0;chan<16;chan++)PA_StopSound(chan);
}
bool MPCPlaying(void){
	return Play;
}

void UpdateMPC(void){
	if(Play==1){
		for(Note=0;Note<29;++Note){
			if(Sprite[Page][Note].used!=0 && NoteBar+8>=Sprite[Page][Note].x-(Tempo/2) && NoteBar+8<=Sprite[Page][Note].x+(Tempo/2)){
				PickSoundFile(Note,Page);
				AS_SetSoundRate(MPCchan,NumToNote(Sprite[Page][Note].Note));
			}
		}
		NoteBar+=Tempo;
		if(NoteBar+8>=225){
			if(Page!=EndPage){
				Page++;
				NoteBar=-8;
			}
			else StopMPC();
		}
	}
}
void InitMPCLib(void){
	PA_VBLFunctionInit(UpdateMPC);
}


